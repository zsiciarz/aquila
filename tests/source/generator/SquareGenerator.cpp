#include "aquila/global.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <algorithm>
#include <cstddef>

SUITE(SquareGenerator)
{
    // sample frequency is fixed at 1 kHz
    Aquila::SquareGenerator gen(1000);
    auto isPositive = [](double x) { return x > 0; };

    TEST(Amplitude)
    {
        gen.setAmplitude(250).setFrequency(10).generate(1000);
        auto max = *std::max_element(gen.begin(), gen.end());
        CHECK_EQUAL(250, max);
        auto min = *std::min_element(gen.begin(), gen.end());
        CHECK_EQUAL(-250, min);
    }

    TEST(UnipolarAmplitude)
    {
        gen.setAmplitude(250).setFrequency(10).generate(1000);
        auto getUnipolar = gen + 250;
        auto max = *std::max_element(getUnipolar.begin(), getUnipolar.end());
        CHECK_EQUAL(500, max);
        auto min = *std::min_element(getUnipolar.begin(), getUnipolar.end());
        CHECK_EQUAL(0, min);
    }

    // counts number of positive samples in generated signal
    TEST(DutyCycle05)
    {
        double duty = 0.5;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), isPositive);
        CHECK_EQUAL(500, samplesCount);
    }

    TEST(DutyCycle025)
    {
        double duty = 0.25;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), isPositive);
        CHECK_EQUAL(250, samplesCount);
    }

    TEST(DutyCycle075)
    {
        double duty = 0.75;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), isPositive);
        CHECK_EQUAL(750, samplesCount);
    }

    TEST(DutyCycle0)
    {
        double duty = 0.0;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), isPositive);
        CHECK_EQUAL(0, samplesCount);
    }

    TEST(DutyCycle1)
    {
        double duty = 1.0;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), isPositive);
        CHECK_EQUAL(1000, samplesCount);
    }

    TEST(DutyCycle001)
    {
        double duty = 0.01;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), isPositive);
        CHECK_EQUAL(10, samplesCount);
    }
}
