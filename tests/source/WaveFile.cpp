#include "aquila/global.h"
#include "aquila/source/WaveFile.h"
#include "constants.h"
#include <unittestpp.h>


SUITE(WaveFile)
{
    TEST(AudioLength)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(103, wav.getAudioLength());
    }

    TEST(BitsPerSample8)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(8, wav.getBitsPerSample());
    }

    TEST(BitsPerSample16)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(16, wav.getBitsPerSample());
    }

    TEST(Channels8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
    }

    TEST(Channels8Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
    }

    TEST(Channels16Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
    }

    TEST(Channels16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
    }

    TEST(SampleFrequency)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(44100, wav.getSampleFrequency());
    }

    TEST(WaveSize8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(4552, wav.getWaveSize());
    }

    TEST(WaveSize16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(18208, wav.getWaveSize());
    }

    TEST(SamplesCount8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(4552, wav.getSamplesCount());
    }

    TEST(SamplesCount16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(4552, wav.getSamplesCount());
    }

    TEST(FramesCount1)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(0);
        wav.setFrameOverlap(0);
        CHECK_EQUAL(0, wav.getFramesCount());
    }

    TEST(FramesCount2)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(10);
        wav.setFrameOverlap(0);
        CHECK_EQUAL(10, wav.getFramesCount());
    }

    TEST(FramesCount3)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(20);
        wav.setFrameOverlap(0);
        CHECK_EQUAL(5, wav.getFramesCount());
    }

    TEST(FramesCount4)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(0);
        wav.setFrameOverlap(0.5);
        CHECK_EQUAL(0, wav.getFramesCount());
    }

    TEST(FramesCount5)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(10);
        wav.setFrameOverlap(0.5);
        CHECK_EQUAL(19, wav.getFramesCount());
    }

    TEST(FramesCount6)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(20);
        wav.setFrameOverlap(0.66);
        CHECK_EQUAL(13, wav.getFramesCount());
    }
}
