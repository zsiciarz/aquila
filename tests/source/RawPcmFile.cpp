#include "aquila/global.h"
#include "aquila/source/RawPcmFile.h"
#include "constants.h"
#include <cstdint>
#include <unittestpp.h>


SUITE(RawPcmFile)
{
    TEST(SampleFrequency)
    {
        Aquila::RawPcmFile<std::uint16_t> pcm(Aquila_TEST_PCMFILE, 22050);
        CHECK_EQUAL(pcm.getSampleFrequency(), 22050);
    }

    TEST(SamplesCount)
    {
        Aquila::RawPcmFile<std::uint16_t> pcm(Aquila_TEST_PCMFILE, 22050);
        CHECK_EQUAL(pcm.getSamplesCount(), 4);
    }

    TEST(Sample)
    {
        Aquila::RawPcmFile<std::uint16_t> pcm(Aquila_TEST_PCMFILE, 22050);
        CHECK_CLOSE(pcm.sample(0), 1.0, 0.000001);
        CHECK_CLOSE(pcm.sample(1), 2.0, 0.000001);
        CHECK_CLOSE(pcm.sample(2), 3.0, 0.000001);
        CHECK_CLOSE(pcm.sample(3), 4.0, 0.000001);
    }
}
