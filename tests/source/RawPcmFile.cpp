#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "aquila/source/RawPcmFile.h"
#include "constants.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>
#include <cstdint>

template <typename Numeric> void savePcmTest()
{
    const std::size_t SIZE = 10;
    Numeric testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::SignalSource data(testArray, SIZE, 22050);
    Aquila::RawPcmFile<Numeric>::save(data, Aquila_TEST_PCMFILE_OUTPUT);

    Aquila::RawPcmFile<Numeric> pcm(Aquila_TEST_PCMFILE_OUTPUT, 22050);
    CHECK_EQUAL(SIZE, pcm.getSamplesCount());
    for (unsigned int i = 0; i < SIZE; ++i)
    {
        CHECK_CLOSE(testArray[i], pcm.sample(i), 0.000001);
    }
}


SUITE(RawPcmFile)
{
    TEST(SampleFrequency)
    {
        Aquila::RawPcmFile<std::uint16_t> pcm(Aquila_TEST_PCMFILE, 22050);
        CHECK_EQUAL(22050, pcm.getSampleFrequency());
    }

    TEST(SamplesCount)
    {
        Aquila::RawPcmFile<std::uint16_t> pcm(Aquila_TEST_PCMFILE, 22050);
        CHECK_EQUAL(4u, pcm.getSamplesCount());
    }

    TEST(Sample)
    {
        Aquila::RawPcmFile<std::uint16_t> pcm(Aquila_TEST_PCMFILE, 22050);
        CHECK_CLOSE(1.0, pcm.sample(0), 0.000001);
        CHECK_CLOSE(2.0, pcm.sample(1), 0.000001);
        CHECK_CLOSE(3.0, pcm.sample(2), 0.000001);
        CHECK_CLOSE(4.0, pcm.sample(3), 0.000001);
    }

    TEST(SaveArrayU8)
    {
        savePcmTest<std::uint8_t>();
    }

    TEST(SaveArrayS8)
    {
        savePcmTest<std::int8_t>();
    }

    TEST(SaveArrayU16)
    {
        savePcmTest<std::uint16_t>();
    }

    TEST(SaveArrayS16)
    {
        savePcmTest<std::int16_t>();
    }

    TEST(SaveArrayU32)
    {
        savePcmTest<std::uint32_t>();
    }

    TEST(SaveArrayS32)
    {
        savePcmTest<std::int32_t>();
    }

    TEST(SaveArrayU64)
    {
        savePcmTest<std::uint64_t>();
    }

    TEST(SaveArrayS64)
    {
        savePcmTest<std::int64_t>();
    }
}
