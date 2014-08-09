#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <algorithm>
#include <cstddef>
#include <numeric>

SUITE(SineGenerator)
{
    // sample frequency is fixed at 1 kHz
    Aquila::SineGenerator gen(1000);

    TEST(ExactlyOnePeriod)
    {
        gen.setAmplitude(1).setFrequency(10).generate(100);
        CHECK_CLOSE(0.0, Aquila::mean(gen), 0.000001);
    }

    TEST(ExactlyTenPeriods)
    {
        gen.setAmplitude(1).setFrequency(100).generate(100);
        CHECK_CLOSE(0.0, Aquila::mean(gen), 0.000001);
    }
}
