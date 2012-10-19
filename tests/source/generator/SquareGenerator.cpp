#include "aquila/global.h"
#include "aquila/source/generator/SquareGenerator.h"
#include <boost/cstdint.hpp>
#include <boost/lambda/lambda.hpp>
#include <unittestpp.h>
#include <algorithm>
#include <cstddef>

using namespace boost::lambda;

SUITE(SquareGenerator)
{
    // sample frequency is fixed at 1 kHz, signal frequency at 10 Hz
    Aquila::SquareGenerator gen(1000);

    // prints number of positive samples in generated signal
    TEST(DutyCycle05)
    {
        double duty = 0.5;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), _1 > 0);
        CHECK_EQUAL(500, samplesCount);
    }

    TEST(DutyCycle025)
    {
        double duty = 0.25;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), _1 > 0);
        CHECK_EQUAL(250, samplesCount);
    }

    TEST(DutyCycle075)
    {
        double duty = 0.75;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), _1 > 0);
        CHECK_EQUAL(750, samplesCount);
    }

    TEST(DutyCycle0)
    {
        double duty = 0.0;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), _1 > 0);
        CHECK_EQUAL(0, samplesCount);
    }

    TEST(DutyCycle1)
    {
        double duty = 1.0;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), _1 > 0);
        CHECK_EQUAL(1000, samplesCount);
    }

    TEST(DutyCycle001)
    {
        double duty = 0.01;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = std::count_if(gen.begin(), gen.end(), _1 > 0);
        CHECK_EQUAL(10, samplesCount);
    }
}
