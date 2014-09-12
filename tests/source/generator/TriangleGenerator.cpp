#include "aquila/global.h"
#include "aquila/source/generator/TriangleGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <algorithm>
#include <cstddef>

SUITE(TriangleGenerator)
{
    // sample frequency is fixed at 1 kHz
    Aquila::TriangleGenerator gen(1000);

    TEST(Amplitude)
    {
        gen.setAmplitude(250).setFrequency(10).generate(100);
        auto min = *std::min_element(gen.begin(), gen.end());
        CHECK_EQUAL(-250, min);
    }

    TEST(SymmetricTriangle)
    {
        gen.setWidth(0.5).setAmplitude(250).setFrequency(10).generate(100);
        auto min = *std::min_element(gen.begin(), gen.end());
        CHECK_EQUAL(-250, min);
    }

    TEST(UnevenPeriod)
    {
        gen.setWidth(0.5).setAmplitude(250).setFrequency(13).generate(100);
        auto min = *std::min_element(gen.begin(), gen.end());
        CHECK_EQUAL(-250, min);
    }
}
