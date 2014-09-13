#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/Mfcc.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>


SUITE(Mfcc)
{
    TEST(Sine9Coeffs)
    {
        Aquila::SineGenerator generator(2048);
        generator.setAmplitude(1).setFrequency(128).generate(2048);

        Aquila::Mfcc mfcc(generator.getSamplesCount());
        auto mfccValues = mfcc.calculate(generator, 9);
        Aquila::SampleType expected[9] = {
            418.046, 200.327, 35.796, 485.892, 311.312, -111.424, 214.684, 311.887, -194.111
        };
        CHECK_ARRAY_CLOSE(expected, mfccValues, 9, 0.001);
    }
}
