#include "aquila/global.h"
#include "aquila/source/WaveFile.h"
#include "aquila/source/FramesCollection.h"
#include "constants.h"
#include <unittestpp.h>
#include <algorithm>
#include <string>
#include <vector>


SUITE(WaveFile)
{
    TEST(Filename)
    {
        std::string filename(Aquila_TEST_WAVEFILE_8B_MONO);
        Aquila::WaveFile wav(filename);
        CHECK(filename == wav.getFilename());
    }

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

    TEST(BytesPerSample8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(1, wav.getBytesPerSample());
    }

    TEST(BytesPerSample8Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(2, wav.getBytesPerSample());
    }

    TEST(BytesPerSample16Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(2, wav.getBytesPerSample());
    }

    TEST(BytesPerSample16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(4, wav.getBytesPerSample());
    }

    TEST(BytesPerSecond)
    {
        std::vector<std::string> filenames;
        filenames.push_back(Aquila_TEST_WAVEFILE_8B_MONO);
        filenames.push_back(Aquila_TEST_WAVEFILE_8B_STEREO);
        filenames.push_back(Aquila_TEST_WAVEFILE_16B_MONO);
        filenames.push_back(Aquila_TEST_WAVEFILE_16B_STEREO);
        std::for_each(
            std::begin(filenames),
            std::end(filenames),
            [] (std::string filename) {
                Aquila::WaveFile wav(filename);
                unsigned int expected = static_cast<unsigned int>(
                    wav.getSampleFrequency() * wav.getBytesPerSample()
                );
                CHECK_EQUAL(expected, wav.getBytesPerSec());
            }
        );
    }

    TEST(Channels8Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
        CHECK(wav.isMono());
        CHECK(!wav.isStereo());
    }

    TEST(Channels8Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
        CHECK(!wav.isMono());
        CHECK(wav.isStereo());
    }

    TEST(Channels16Mono)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_MONO);
        CHECK_EQUAL(1, wav.getChannelsNum());
        CHECK(wav.isMono());
        CHECK(!wav.isStereo());
    }

    TEST(Channels16Stereo)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_16B_STEREO);
        CHECK_EQUAL(2, wav.getChannelsNum());
        CHECK(!wav.isMono());
        CHECK(wav.isStereo());
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
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 0, 0);
        CHECK_EQUAL(0, frames.count());
    }

    TEST(FramesCount2)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 10, 0);
        CHECK_EQUAL(10, frames.count());
    }

    TEST(FramesCount3)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 20, 0);
        CHECK_EQUAL(5, frames.count());
    }

    TEST(FramesCount4)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 0, 0.5);
        CHECK_EQUAL(0, frames.count());
    }

    TEST(FramesCount5)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 10, 0.5);
        CHECK_EQUAL(19, frames.count());
    }

    TEST(FramesCount6)
    {
        Aquila::WaveFile wav(Aquila_TEST_WAVEFILE_8B_MONO);
        auto frames = Aquila::FramesCollection::createFromDuration(wav, 20, 0.66);
        CHECK_EQUAL(13, frames.count());
    }
}
