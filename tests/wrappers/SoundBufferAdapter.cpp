#include "aquila/source/generator/SineGenerator.h"
#include "aquila/wrappers/SoundBufferAdapter.h"
#include "UnitTest++/UnitTest++.h"


SUITE(SoundBufferAdapter)
{
    TEST(NumSamples)
    {
        Aquila::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        Aquila::SoundBufferAdapter buffer(generator);
        CHECK_EQUAL(generator.length(), buffer.getSampleCount());
    }

    TEST(SampleFrequency)
    {
        Aquila::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        Aquila::SoundBufferAdapter buffer(generator);
        CHECK_EQUAL(static_cast<unsigned int>(generator.getSampleFrequency()), buffer.getSampleRate());
    }
}
