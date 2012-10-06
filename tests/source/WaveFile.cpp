#include "aquila/global.h"
#include "aquila/source/WaveFile.h"
#include "constants.h"
#include <boost/cstdint.hpp>
#include <boost/lambda/lambda.hpp>
#include <unittestpp.h>


SUITE(WaveFile)
{
    TEST(AudioLength)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(wav.getAudioLength(), 103);
    }

    TEST(BitsPerSample8)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(wav.getBitsPerSample(), 8);
    }

    TEST(BitsPerSample16)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(wav.getBitsPerSample(), 16);
    }

    TEST(Channels8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(wav.getChannelsNum(), 1);
    }

    TEST(Channels8Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(wav.getChannelsNum(), 2);
    }

    TEST(Channels16Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(wav.getChannelsNum(), 1);
    }

    TEST(Channels16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(wav.getChannelsNum(), 2);
    }

    TEST(SampleFrequency)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(wav.getSampleFrequency(), 44100);
    }

    TEST(WaveSize8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(wav.getWaveSize(), 4552);
    }

    TEST(WaveSize16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(wav.getWaveSize(), 18208);
    }

    TEST(SamplesCount8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(wav.getSamplesCount(), 4552);
    }

    TEST(SamplesCount16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(wav.getSamplesCount(), 4552);
    }

    TEST(FramesCount1)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(0);
        wav.setFrameOverlap(0);
        CHECK_EQUAL(wav.getFramesCount(), 0);
    }

    TEST(FramesCount2)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(10);
        wav.setFrameOverlap(0);
        CHECK_EQUAL(wav.getFramesCount(), 10);
    }

    TEST(FramesCount3)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(20);
        wav.setFrameOverlap(0);
        CHECK_EQUAL(wav.getFramesCount(), 5);
    }

    TEST(FramesCount4)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(0);
        wav.setFrameOverlap(0.5);
        CHECK_EQUAL(wav.getFramesCount(), 0);
    }

    TEST(FramesCount5)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(10);
        wav.setFrameOverlap(0.5);
        CHECK_EQUAL(wav.getFramesCount(), 19);
    }

    TEST(FramesCount6)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        wav.setFrameLength(20);
        wav.setFrameOverlap(0.66);
        CHECK_EQUAL(wav.getFramesCount(), 13);
    }
}
