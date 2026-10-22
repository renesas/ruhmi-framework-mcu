/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * PlatformMathPq.cc
 * Zero-Float `p/q` ("Counting Divided") MCU Math, Laser Phoenix Phase-Lattice
 * Twiddle Oscillator, Omni BFP-64 & Quantum 64-Trit (`POPCNT`) Kernel for
 * Renesas RUHMI MCU Framework (RA8P1 / Cortex-M85 / Ethos-U55).
 *
 * Authored by 8b-is (https://8b.is) — Visiting Tokyo R&D teams
 * (through October 24th; WhatsApp: +1 757-614-7542 — Chris).
 */

#include "PlatformMathPq.hpp"
#include <algorithm>
#include <cstdlib>

namespace arm {
namespace app {
namespace math {

    static inline int32_t ClampI32(int32_t v, int32_t lo, int32_t hi)
    {
        return (v < lo) ? lo : ((v > hi) ? hi : v);
    }

    void Bfp64Block::QuantizeFromQ16(const int32_t* srcQ16, size_t len)
    {
        this->count = static_cast<uint8_t>(std::min<size_t>(64U, len));
        if (this->count == 0U) {
            this->exponent = -16;
            return;
        }
        int32_t maxAbs = 0;
        for (uint8_t i = 0; i < this->count; ++i) {
            int32_t a = std::abs(srcQ16[i]);
            if (a > maxAbs) {
                maxAbs = a;
            }
        }
        if (maxAbs == 0) {
            this->exponent = -16;
            for (uint8_t i = 0; i < 64U; ++i) {
                this->mantissas[i] = 0;
            }
            return;
        }
        int shift = 0;
        while ((maxAbs >> shift) > 127) {
            ++shift;
        }
        int32_t half = (shift > 0) ? (1 << (shift - 1)) : 0;
        for (uint8_t i = 0; i < this->count; ++i) {
            int32_t v = srcQ16[i];
            int32_t q = (v >= 0) ? ((v + half) >> shift) : -((-v + half) >> shift);
            this->mantissas[i] = static_cast<int8_t>(ClampI32(q, -127, 127));
        }
        for (uint8_t i = this->count; i < 64U; ++i) {
            this->mantissas[i] = 0;
        }
        this->exponent = static_cast<int8_t>(shift - 16);
    }

    void Bfp64Block::DequantizeToQ16(int32_t* dstQ16) const
    {
        int shift = static_cast<int>(this->exponent) + 16;
        for (uint8_t i = 0; i < this->count; ++i) {
            int32_t m = static_cast<int32_t>(this->mantissas[i]);
            dstQ16[i] = (shift >= 0) ? (m << shift) : (m >> (-shift));
        }
    }

    uint32_t MathUtilsPq::IsqrtU64(uint64_t x)
    {
        if (x == 0ULL) {
            return 0U;
        }
        uint64_t op  = x;
        uint64_t res = 0ULL;
        uint64_t one = 1ULL << 62;
        while (one > op) {
            one >>= 2;
        }
        while (one != 0ULL) {
            if (op >= res + one) {
                op  -= res + one;
                res  = (res >> 1) + one;
            } else {
                res >>= 1;
            }
            one >>= 2;
        }
        return static_cast<uint32_t>(res);
    }

    int32_t MathUtilsPq::ExpNegPqQ16(int32_t xQ16)
    {
        if (xQ16 <= 0) {
            return kPqQ16One;
        }
        int32_t g = ClampI32(xQ16, 0, 15 * kPqQ16One);
        int32_t k = g / kPqLn2Q16;
        if (k >= 16) {
            return 0;
        }
        int64_t u   = static_cast<int64_t>(g - k * kPqLn2Q16);
        int64_t q16 = static_cast<int64_t>(kPqQ16One);

        /* Pade-[2,2]: (12 - 6*u + u^2) / (12 + 6*u + u^2) */
        int64_t c0  = 12LL * q16 * q16;
        int64_t c1  = 6LL * u * q16;
        int64_t c2  = u * u;
        int64_t num = c0 - c1 + c2;
        int64_t den = c0 + c1 + c2;

        int32_t rU  = static_cast<int32_t>((num * q16 + (den >> 1)) / den);
        return rU >> k;
    }

    int32_t MathUtilsPq::SigmoidPqQ16(int32_t xQ16)
    {
        if (xQ16 >= 0) {
            int32_t eNeg = ExpNegPqQ16(xQ16);
            int64_t num  = static_cast<int64_t>(kPqQ16One) * static_cast<int64_t>(kPqQ16One);
            int64_t den  = static_cast<int64_t>(kPqQ16One) + static_cast<int64_t>(eNeg);
            return static_cast<int32_t>((num + (den >> 1)) / den);
        } else {
            int32_t ePos = ExpNegPqQ16(-xQ16);
            int64_t num  = static_cast<int64_t>(ePos) * static_cast<int64_t>(kPqQ16One);
            int64_t den  = static_cast<int64_t>(kPqQ16One) + static_cast<int64_t>(ePos);
            return static_cast<int32_t>((num + (den >> 1)) / den);
        }
    }

    int32_t MathUtilsPq::ComputeYoloInt8ObjectnessCutoff(int32_t zeroPoint,
                                                         int32_t scaleQ16,
                                                         int32_t thresholdQ16)
    {
        if (scaleQ16 <= 0) {
            return -128;
        }
        int32_t cutoff = -128;
        while (cutoff <= 127) {
            int32_t xQ16 = (cutoff - zeroPoint) * scaleQ16;
            if (SigmoidPqQ16(xQ16) > thresholdQ16) {
                break;
            }
            ++cutoff;
        }
        return cutoff;
    }

    void MathUtilsPq::SoftmaxPqQ16(std::vector<int32_t>& logitsInProbsOutQ16)
    {
        if (logitsInProbsOutQ16.empty()) {
            return;
        }
        int32_t maxVal = *std::max_element(logitsInProbsOutQ16.begin(), logitsInProbsOutQ16.end());
        int64_t sumExp = 0LL;
        for (size_t i = 0; i < logitsInProbsOutQ16.size(); ++i) {
            int32_t e = ExpNegPqQ16(maxVal - logitsInProbsOutQ16[i]);
            logitsInProbsOutQ16[i] = e;
            sumExp += static_cast<int64_t>(e);
        }
        if (sumExp <= 0LL) {
            return;
        }
        for (size_t i = 0; i < logitsInProbsOutQ16.size(); ++i) {
            int64_t num = static_cast<int64_t>(logitsInProbsOutQ16[i]) * static_cast<int64_t>(kPqQ16One);
            logitsInProbsOutQ16[i] = static_cast<int32_t>((num + (sumExp >> 1)) / sumExp);
        }
    }

    int32_t MathUtilsPq::SinePhaseU32Q16(uint32_t phaseU32)
    {
        /*
         * Bhaskara I's rational `p/q` approximation on half-turn u in [0, 2^31):
         *   sin(pi * u / H) ~= 16 * u * (H - u) / (5 * H^2 - 4 * u * (H - u))
         * Scale u to H = 32768 so u * (H - u) fits cleanly in 64-bit integer arithmetic.
         */
        const bool neg = (phaseU32 >= 0x80000000U);
        const uint32_t halfTurn = phaseU32 & 0x7FFFFFFFU;
        const int64_t H = 32768LL;
        const int64_t u = static_cast<int64_t>((halfTurn + 32768U) >> 16);
        const int64_t p = u * (H - u);
        const int64_t num = 16LL * p * static_cast<int64_t>(kPqQ16One);
        const int64_t den = 5LL * H * H - 4LL * p;
        const int32_t mag = static_cast<int32_t>((num + (den >> 1)) / den);
        return neg ? -mag : mag;
    }

    int32_t MathUtilsPq::CosinePhaseU32Q16(uint32_t phaseU32)
    {
        /* cos(theta) == sin(theta + pi/2), where pi/2 == 0x40000000 in Z_{2^32} */
        return SinePhaseU32Q16(phaseU32 + 0x40000000U);
    }

    void MathUtilsPq::FftRealPqQ16(const std::vector<int32_t>& inputQ16,
                                   std::vector<int32_t>& fftOutputQ16)
    {
        const size_t N = inputQ16.size();
        if (N == 0U || fftOutputQ16.size() < N) {
            return;
        }
        const size_t halfLen = N / 2U;

        int64_t dcSum  = 0LL;
        int64_t nyqSum = 0LL;
        for (size_t t = 0U; t < N; ++t) {
            dcSum  += static_cast<int64_t>(inputQ16[t]);
            nyqSum += ((t & 1U) != 0U) ? -static_cast<int64_t>(inputQ16[t])
                                       :  static_cast<int64_t>(inputQ16[t]);
        }
        fftOutputQ16[0] = static_cast<int32_t>(dcSum);
        fftOutputQ16[1] = static_cast<int32_t>(nyqSum);

        /* Z_{2^32} phase-locked twiddle oscillator: stepU32 = round(2^32 * k / N) */
        for (size_t k = 1U, j = 2U; k < halfLen; ++k, j += 2U) {
            const uint32_t stepU32 = static_cast<uint32_t>(((1ULL << 32) * k) / N);
            uint32_t angleU32 = 0U;
            int64_t sumReal = 0LL;
            int64_t sumImag = 0LL;

            for (size_t t = 0U; t < N; ++t) {
                const int64_t x   = static_cast<int64_t>(inputQ16[t]);
                const int64_t c   = static_cast<int64_t>(CosinePhaseU32Q16(angleU32));
                const int64_t s   = static_cast<int64_t>(SinePhaseU32Q16(angleU32));
                sumReal  += (x * c) / kPqQ16One;
                sumImag  -= (x * s) / kPqQ16One;
                angleU32 += stepU32;
            }
            fftOutputQ16[j]     = static_cast<int32_t>(sumReal);
            fftOutputQ16[j + 1] = static_cast<int32_t>(sumImag);
        }
    }

    static PhoenixLatticeRelation ClassifyRelationU32(uint32_t phaseU32)
    {
        int32_t signedP = static_cast<int32_t>(phaseU32);
        uint32_t absP   = (signedP < 0) ? static_cast<uint32_t>(-signedP) : static_cast<uint32_t>(signedP);
        if (absP < 0x10000000U) {
            return PhoenixLatticeRelation::Bound0Deg;
        } else if (absP < 0x30000000U) {
            return PhoenixLatticeRelation::Related45Deg;
        } else if (absP < 0x50000000U) {
            return PhoenixLatticeRelation::Independent90;
        } else if (absP < 0x70000000U) {
            return PhoenixLatticeRelation::Contrasting135;
        }
        return PhoenixLatticeRelation::Conflicting180;
    }

    void MathUtilsPq::LockPhaseSequencePhoenix(const std::vector<uint32_t>& measuredPhasesU32,
                                               std::vector<PhoenixPhaseLockState>& outStates)
    {
        const size_t n = measuredPhasesU32.size();
        outStates.resize(n);
        if (n == 0U) {
            return;
        }

        /* Marine Salience Second-Difference Phase-Velocity Jitter Gate */
        uint32_t coherenceQ16 = static_cast<uint32_t>(kPqQ16One);
        if (n > 2U) {
            uint64_t totalJitter = 0ULL;
            int32_t prevStep = static_cast<int32_t>(measuredPhasesU32[1] - measuredPhasesU32[0]);
            for (size_t i = 2U; i < n; ++i) {
                int32_t curStep = static_cast<int32_t>(measuredPhasesU32[i] - measuredPhasesU32[i - 1U]);
                int64_t diff = static_cast<int64_t>(curStep) - static_cast<int64_t>(prevStep);
                totalJitter += static_cast<uint64_t>((diff < 0) ? -diff : diff);
                prevStep = curStep;
            }
            uint64_t meanJitter = totalJitter / static_cast<uint64_t>(n - 2U);
            uint64_t refScale   = 0x10000000ULL;
            coherenceQ16 = static_cast<uint32_t>((refScale * static_cast<uint64_t>(kPqQ16One)) / (refScale + meanJitter));
        }

        uint32_t lockedU32 = measuredPhasesU32[0];
        int32_t velI32     = 0;
        const int atten    = (coherenceQ16 < 22938U) ? 1 : 0;

        for (size_t i = 0U; i < n; ++i) {
            if (i > 0U) {
                int32_t err = static_cast<int32_t>(measuredPhasesU32[i] - lockedU32);
                int32_t prop = static_cast<int32_t>((static_cast<int64_t>(err) * kPhoenixPhiDen) / kPhoenixPhiNum) >> atten;
                int32_t integ = (err / 16) >> atten;
                velI32    += integ;
                lockedU32 += static_cast<uint32_t>(prop + velI32);
            }
            outStates[i].lockedPhaseU32     = lockedU32;
            outStates[i].phaseVelocityI32   = velI32;
            outStates[i].marineCoherenceQ16 = coherenceQ16;
            outStates[i].relation           = ClassifyRelationU32(lockedU32);
        }
    }

    static int32_t CatmullRomPqScalar(int32_t p0, int32_t p1, int32_t p2, int32_t p3,
                                      int32_t tNum, int32_t tDen)
    {
        if (tDen <= 0 || tNum <= 0) {
            return p1;
        }
        if (tNum >= tDen) {
            return p2;
        }
        int64_t d = tDen, d2 = d * d, d3 = d2 * d;
        int64_t n = tNum, n2 = n * n, n3 = n2 * n;
        int64_t q0 = p0, q1 = p1, q2 = p2, q3 = p3;

        int64_t c0 = 2LL * q1 * d3;
        int64_t c1 = (-q0 + q2) * n * d2;
        int64_t c2 = (2LL * q0 - 5LL * q1 + 4LL * q2 - q3) * n2 * d;
        int64_t c3 = (-q0 + 3LL * q1 - 3LL * q2 + q3) * n3;
        int64_t num = c0 + c1 + c2 + c3;
        int64_t den = 2LL * d3;
        return static_cast<int32_t>((num >= 0LL) ? ((num + (den >> 1)) / den)
                                                 : -((-num + (den >> 1)) / den));
    }

    void MathUtilsPq::RestoreDropoutsCatmullRomPq(const std::vector<int32_t>& samplesQ16,
                                                  const std::vector<uint8_t>& droppedMask,
                                                  std::vector<int32_t>& restoredOutQ16)
    {
        const size_t n = samplesQ16.size();
        restoredOutQ16 = samplesQ16;
        if (n == 0U || droppedMask.size() < n) {
            return;
        }
        std::vector<size_t> validIdx;
        validIdx.reserve(n);
        for (size_t i = 0U; i < n; ++i) {
            if (droppedMask[i] == 0U) {
                validIdx.push_back(i);
            }
        }
        if (validIdx.empty()) {
            std::fill(restoredOutQ16.begin(), restoredOutQ16.end(), 0);
            return;
        }
        const size_t firstV = validIdx.front();
        const size_t lastV  = validIdx.back();
        for (size_t i = 0U; i < firstV; ++i) {
            restoredOutQ16[i] = restoredOutQ16[firstV];
        }
        for (size_t i = lastV + 1U; i < n; ++i) {
            restoredOutQ16[i] = restoredOutQ16[lastV];
        }
        for (size_t k = 0U; k + 1U < validIdx.size(); ++k) {
            const size_t i1 = validIdx[k];
            const size_t i2 = validIdx[k + 1U];
            const size_t span = i2 - i1;
            if (span <= 1U) {
                continue;
            }
            const size_t i0 = (k > 0U) ? validIdx[k - 1U] : i1;
            const size_t i3 = (k + 2U < validIdx.size()) ? validIdx[k + 2U] : i2;
            const int64_t p1 = restoredOutQ16[i1];
            const int64_t p2 = restoredOutQ16[i2];
            const int64_t m1 = ((p2 - restoredOutQ16[i0]) * static_cast<int64_t>(span))
                             / static_cast<int64_t>((i2 > i0) ? (i2 - i0) : 1U);
            const int64_t m2 = ((restoredOutQ16[i3] - p1) * static_cast<int64_t>(span))
                             / static_cast<int64_t>((i3 > i1) ? (i3 - i1) : 1U);
            const int32_t p0 = static_cast<int32_t>(p2 - 2LL * m1);
            const int32_t p3 = static_cast<int32_t>(p1 + 2LL * m2);
            for (size_t off = 1U; off < span; ++off) {
                restoredOutQ16[i1 + off] = CatmullRomPqScalar(
                    p0, static_cast<int32_t>(p1), static_cast<int32_t>(p2), p3,
                    static_cast<int32_t>(off), static_cast<int32_t>(span));
            }
        }
    }

    int32_t MathUtilsPq::DotProductTrit64Popcnt(uint64_t posMaskA,
                                                uint64_t negMaskA,
                                                uint64_t posMaskB,
                                                uint64_t negMaskB)
    {
        int32_t same = __builtin_popcountll(posMaskA & posMaskB)
                     + __builtin_popcountll(negMaskA & negMaskB);
        int32_t opp  = __builtin_popcountll(posMaskA & negMaskB)
                     + __builtin_popcountll(negMaskA & posMaskB);
        return same - opp;
    }

} /* namespace math */
} /* namespace app */
} /* namespace arm */
