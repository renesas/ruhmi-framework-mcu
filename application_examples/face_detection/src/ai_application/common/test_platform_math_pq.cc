/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * test_platform_math_pq.cc
 * Verification suite for Zero-Float `p/q` ("Counting Divided") MCU Math,
 * Int8 YOLO Objectness Pre-Thresholding, Z_{2^32} Laser Phoenix Phase-Lattice
 * Twiddle FFT, Omni BFP-64 & Quantum 64-Trit (`POPCNT`) Kernel.
 */

#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "PlatformMath.hpp"
#include "PlatformMathPq.hpp"

extern "C" int e_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = std::vfprintf(stderr, format, args);
    va_end(args);
    return ret;
}

using namespace arm::app::math;

static void TestSigmoidAndExpNegPq(void)
{
    const float testVals[9] = { -6.0f, -3.0f, -1.5f, -0.5f, 0.0f, 0.5f, 1.5f, 3.0f, 6.0f };
    for (int i = 0; i < 9; ++i) {
        int32_t xQ16 = static_cast<int32_t>(std::round(testVals[i] * kPqQ16One));
        float sigPq  = static_cast<float>(MathUtilsPq::SigmoidPqQ16(xQ16)) / static_cast<float>(kPqQ16One);
        float sigRef = MathUtils::SigmoidF32(testVals[i]);
        assert(std::fabs(sigPq - sigRef) < 5e-4f);
    }
}

static void TestYoloInt8ObjectnessPreThreshold(void)
{
    const int32_t zeroPoint = -12;
    const float scaleF = 0.085f;
    const int32_t scaleQ16 = static_cast<int32_t>(std::round(scaleF * kPqQ16One));
    const float thresholdF = 0.60f;
    const int32_t thresholdQ16 = static_cast<int32_t>(std::round(thresholdF * kPqQ16One));

    int32_t cutoff = MathUtilsPq::ComputeYoloInt8ObjectnessCutoff(zeroPoint, scaleQ16, thresholdQ16);
    for (int q = -128; q <= 127; ++q) {
        int32_t xQ16 = (q - zeroPoint) * scaleQ16;
        bool passSigmoid = (MathUtilsPq::SigmoidPqQ16(xQ16) > thresholdQ16);
        bool passInt8Gate = (q >= cutoff);
        assert(passSigmoid == passInt8Gate);
    }
}

static void TestLaserPhoenixTwiddleAndRealFft(void)
{
    const size_t N = 16U;
    std::vector<float> inF(N);
    std::vector<float> outRefF(N, 0.0f);
    std::vector<int32_t> inQ16(N);
    std::vector<int32_t> outPqQ16(N, 0);

    for (size_t t = 0U; t < N; ++t) {
        inF[t] = 0.6f * std::cos(2.0f * static_cast<float>(M_PI) * 2.0f * static_cast<float>(t) / static_cast<float>(N))
               - 0.3f * std::sin(2.0f * static_cast<float>(M_PI) * 5.0f * static_cast<float>(t) / static_cast<float>(N));
        inQ16[t] = static_cast<int32_t>(std::round(inF[t] * kPqQ16One));
    }

    FftInstance fftInst;
    MathUtils::FftInitF32(static_cast<uint16_t>(N), fftInst, FftType::real);
    MathUtils::FftF32(inF, outRefF, fftInst);
    MathUtilsPq::FftRealPqQ16(inQ16, outPqQ16);

    for (size_t k = 0U; k < N; ++k) {
        float pqVal = static_cast<float>(outPqQ16[k]) / static_cast<float>(kPqQ16One);
        assert(std::fabs(pqVal - outRefF[k]) < 0.04f);
    }
}

static void TestLaserPhoenixPhaseLockAndCatmullRom(void)
{
    std::vector<uint32_t> phases(16U);
    for (size_t i = 0U; i < 16U; ++i) {
        phases[i] = static_cast<uint32_t>(0xFC000000ULL + i * 0x01000000ULL);
    }
    std::vector<PhoenixPhaseLockState> states;
    MathUtilsPq::LockPhaseSequencePhoenix(phases, states);
    assert(states.size() == 16U);
    assert(states.back().marineCoherenceQ16 > 60000U);

    /* Catmull-Rom dropout restoration */
    std::vector<int32_t> gt(32U), degraded(32U), restored;
    std::vector<uint8_t> mask(32U, 0U);
    for (size_t i = 0U; i < 32U; ++i) {
        gt[i] = static_cast<int32_t>(std::round(0.75 * kPqQ16One * std::sin(2.0 * M_PI * static_cast<double>(i) / 32.0)));
        if (i == 9U || i == 10U || i == 11U || i == 22U || i == 23U) {
            mask[i] = 1U;
            degraded[i] = 0;
        } else {
            degraded[i] = gt[i];
        }
    }
    MathUtilsPq::RestoreDropoutsCatmullRomPq(degraded, mask, restored);
    double mseDeg = 0.0, mseRes = 0.0;
    for (size_t i = 0U; i < 32U; ++i) {
        double d1 = static_cast<double>(gt[i] - degraded[i]);
        double d2 = static_cast<double>(gt[i] - restored[i]);
        mseDeg += d1 * d1;
        mseRes += d2 * d2;
    }
    assert(mseRes < mseDeg * 0.01);
}

static void TestBfp64AndTrit64Popcnt(void)
{
    int32_t src[64], dst[64];
    for (int i = 0; i < 64; ++i) {
        src[i] = (i - 32) * 1024;
    }
    Bfp64Block blk;
    blk.QuantizeFromQ16(src, 64U);
    blk.DequantizeToQ16(dst);
    for (int i = 0; i < 64; ++i) {
        assert(std::abs(src[i] - dst[i]) <= 512);
    }

    int32_t dot = MathUtilsPq::DotProductTrit64Popcnt(0xFF00ULL, 0x00FFULL, 0xF0F0ULL, 0x0F0FULL);
    /* Same: popcnt(0xF000)=4 + popcnt(0x000F)=4 = 8; Opp: popcnt(0x0F00)=4 + popcnt(0x00F0)=4 = 8 -> 0 */
    assert(dot == 0);
}

int main(void)
{
    TestSigmoidAndExpNegPq();
    TestYoloInt8ObjectnessPreThreshold();
    TestLaserPhoenixTwiddleAndRealFft();
    TestLaserPhoenixPhaseLockAndCatmullRom();
    TestBfp64AndTrit64Popcnt();
    std::printf("ALL RENESAS RUHMI MCU PLATFORM_MATH_PQ TESTS PASSED!\n");
    return 0;
}
