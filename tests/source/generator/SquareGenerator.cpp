#include "aquila/global.h"
#include "aquila/source/generator/SquareGenerator.h"
#include <boost/cstdint.hpp>
#include <unittestpp.h>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>

using std::count_if;
using std::bind2nd;
using std::greater;

SUITE(SquareGenerator)
{
    // sample frequency is fixed at 1 kHz, signal frequency at 10 Hz
    Aquila::SquareGenerator gen(1000);

    // prints number of positive samples in generated signal
    TEST(DutyCycle05)
    {
        double duty = 0.5;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = count_if(gen.begin(), gen.end(), bind2nd(greater<Aquila::SampleType>(), 0));
        CHECK_EQUAL(samplesCount, 500);
    }

    TEST(DutyCycle025)
    {
        double duty = 0.25;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = count_if(gen.begin(), gen.end(), bind2nd(greater<Aquila::SampleType>(), 0));
        CHECK_EQUAL(samplesCount, 250);
    }

    TEST(DutyCycle075)
    {
        double duty = 0.75;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = count_if(gen.begin(), gen.end(), bind2nd(greater<Aquila::SampleType>(), 0));
        CHECK_EQUAL(samplesCount, 750);
    }

    TEST(DutyCycle0)
    {
        double duty = 0.0;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = count_if(gen.begin(), gen.end(), bind2nd(greater<Aquila::SampleType>(), 0));
        CHECK_EQUAL(samplesCount, 0);
    }

    TEST(DutyCycle1)
    {
        double duty = 1.0;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = count_if(gen.begin(), gen.end(), bind2nd(greater<Aquila::SampleType>(), 0));
        CHECK_EQUAL(samplesCount, 1000);
    }

    TEST(DutyCycle001)
    {
        double duty = 0.01;
        gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);
        int samplesCount = count_if(gen.begin(), gen.end(), bind2nd(greater<Aquila::SampleType>(), 0));
        CHECK_EQUAL(samplesCount, 10);
    }
}
