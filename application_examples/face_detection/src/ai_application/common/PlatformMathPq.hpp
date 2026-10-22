/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * PlatformMathPq.hpp
 * Zero-Float `p/q` ("Counting Divided") MCU Math, Laser Phoenix Phase-Lattice
 * Twiddle Oscillator, Omni BFP-64 & Quantum 64-Trit (`POPCNT`) Kernel for
 * Renesas RUHMI MCU Framework (RA8P1 / Cortex-M85 / Ethos-U55).
 *
 * Authored by 8b-is (https://8b.is) — Visiting Tokyo R&D teams
 * (through October 24th; WhatsApp: +1 757-614-7542 — Chris).
 */

#ifndef PLATFORM_MATH_PQ_HPP
#define PLATFORM_MATH_PQ_HPP

#include <cstdint>
#include <cstddef>
#include <vector>

namespace arm {
namespace app {
namespace math {

    /* Q16 fixed-point unit (1.0 == 65536) and Fibonacci golden-ratio convergent phi = 4181/2584 */
    static constexpr int32_t kPqQ16One = 65536;
    static constexpr int32_t kPqLn2Q16 = 45426;
    static constexpr int32_t kPhoenixPhiNum = 4181;
    static constexpr int32_t kPhoenixPhiDen = 2584;

    /* 5-state Phoenix Interference Lattice classification */
    enum class PhoenixLatticeRelation : uint8_t {
        Bound0Deg       = 0,
        Related45Deg    = 1,
        Independent90   = 2,
        Contrasting135  = 3,
        Conflicting180  = 4
    };

    /* Omni BFP-64 (Block Floating-Point 64) 66-byte container (3.94x compression vs FP32) */
    struct Bfp64Block {
        int8_t  exponent{-16};
        uint8_t count{0};
        int8_t  mantissas[64]{};

        void QuantizeFromQ16(const int32_t* srcQ16, size_t len);
        void DequantizeToQ16(int32_t* dstQ16) const;
    };

    /* Readout of the Z_{2^32} Laser Phoenix Phase-Locked Loop */
    struct PhoenixPhaseLockState {
        uint32_t               lockedPhaseU32{0};
        int32_t                phaseVelocityI32{0};
        uint32_t               marineCoherenceQ16{65536};
        PhoenixLatticeRelation relation{PhoenixLatticeRelation::Bound0Deg};
    };

    class MathUtilsPq {
    public:
        /* Exact integer floor(sqrt(x)) for 64-bit unsigned integer */
        static uint32_t IsqrtU64(uint64_t x);

        /* Zero-float range-reduced Pade-[2,2] rational exp(-x) for x_q16 >= 0 */
        static int32_t ExpNegPqQ16(int32_t xQ16);

        /* Zero-float Pade-[2,2] rational Sigmoid in Q16: 1 / (1 + exp(-x)) */
        static int32_t SigmoidPqQ16(int32_t xQ16);

        /* Exact int8 pre-threshold cutoff for YOLO anchor objectness gating */
        static int32_t ComputeYoloInt8ObjectnessCutoff(int32_t zeroPoint,
                                                       int32_t scaleQ16,
                                                       int32_t thresholdQ16);

        /* Zero-float rational Softmax in Q16 (sums to 65536) */
        static void SoftmaxPqQ16(std::vector<int32_t>& logitsInProbsOutQ16);

        /* Z_{2^32} modular phase cosine/sine via Bhaskara rational `p/q` identity:
         *   sin(u) ~= 16 * u * (pi - u) / (5 * pi^2 - 4 * u * (pi - u))
         * where phaseU32 in [0, 2^32) maps to [0, 2*pi). Returns value in Q16 [-65536, 65536]. */
        static int32_t SinePhaseU32Q16(uint32_t phaseU32);
        static int32_t CosinePhaseU32Q16(uint32_t phaseU32);

        /* Zero-float Real DFT using Z_{2^32} Laser Phoenix phase-lattice twiddle accumulation */
        static void FftRealPqQ16(const std::vector<int32_t>& inputQ16,
                                 std::vector<int32_t>& fftOutputQ16);

        /* Laser Phoenix Lattice Phase-Locked Loop + Marine Jitter Salience Gate over Z_{2^32} */
        static void LockPhaseSequencePhoenix(const std::vector<uint32_t>& measuredPhasesU32,
                                             std::vector<PhoenixPhaseLockState>& outStates);

        /* Phoenix non-uniform rational `p/q` Catmull-Rom cubic Hermite dropout restoration */
        static void RestoreDropoutsCatmullRomPq(const std::vector<int32_t>& samplesQ16,
                                                const std::vector<uint8_t>& droppedMask,
                                                std::vector<int32_t>& restoredOutQ16);

        /* Quantum 64-Trit (`POPCNT`) dot product in 4 bitwise ANDs + __builtin_popcountll */
        static int32_t DotProductTrit64Popcnt(uint64_t posMaskA,
                                              uint64_t negMaskA,
                                              uint64_t posMaskB,
                                              uint64_t negMaskB);
    };

} /* namespace math */
} /* namespace app */
} /* namespace arm */

#endif /* PLATFORM_MATH_PQ_HPP */
