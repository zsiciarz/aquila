#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "aquila/source/PlainTextFile.h"
#include "constants.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>


SUITE(PlainTextFile)
{
    TEST(SampleFrequency)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_EQUAL(22050, txt.getSampleFrequency());
    }

    TEST(SamplesCount)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_EQUAL(4u, txt.getSamplesCount());
    }

    TEST(Sample)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_CLOSE(1.0, txt.sample(0), 0.000001);
        CHECK_CLOSE(2.0, txt.sample(1), 0.000001);
        CHECK_CLOSE(3.0, txt.sample(2), 0.000001);
        CHECK_CLOSE(3.141592, txt.sample(3), 0.000001);
    }

    TEST(SaveArray)
    {
        const std::size_t SIZE = 10;
        Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Aquila::SignalSource data(testArray, SIZE, 22050);
        Aquila::PlainTextFile::save(data, Aquila_TEST_TXTFILE_OUTPUT);

        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE_OUTPUT, 22050);
        CHECK_EQUAL(SIZE, txt.getSamplesCount());
        for (unsigned int i = 0; i < SIZE; ++i)
        {
            CHECK_EQUAL(testArray[i], txt.sample(i));
        }
    }
}
