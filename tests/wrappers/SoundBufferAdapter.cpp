#include "aquila/source/generator/SineGenerator.h"
#include "aquila/wrappers/SoundBufferAdapter.h"
#include "UnitTest++/UnitTest++.h"


SUITE(SoundBufferAdapter)
{
    TEST(Empty)
    {
        Aquila::SoundBufferAdapter buffer;
        CHECK_EQUAL(0u, buffer.getSampleCount());
    }

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

    TEST(Copy)
    {
        Aquila::SineGenerator generator(128);
        generator.setAmplitude(1).setFrequency(8).generate(64);
        Aquila::SoundBufferAdapter buffer(generator);
        Aquila::SoundBufferAdapter buffer2(buffer);
        CHECK_EQUAL(generator.length(), buffer2.getSampleCount());
    }
}
