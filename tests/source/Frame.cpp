#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/Frame.h"
#include <unittestpp.h>


SUITE(Frame)
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);

    TEST(BitsPerSample)
    {
        Aquila::Frame frame(data, 0, 1);
        CHECK_EQUAL(8 * sizeof(Aquila::SampleType), frame.getBitsPerSample());
    }

    TEST(SampleFrequency)
    {
        Aquila::Frame frame(data, 0, 1);
        CHECK_EQUAL(data.getSampleFrequency(), frame.getSampleFrequency());
    }

    TEST(Sample1)
    {
        Aquila::Frame frame(data, 0, 10);
        CHECK_EQUAL(0, frame.sample(0));
    }

    TEST(Sample2)
    {
        Aquila::Frame frame(data, 1, 10);
        CHECK_EQUAL(1, frame.sample(0));
    }

    TEST(Sample3)
    {
        Aquila::Frame frame(data, 2, 10);
        CHECK_EQUAL(4, frame.sample(2));
    }

    TEST(Sample4)
    {
        Aquila::Frame frame(data, 9, 10);
        CHECK_EQUAL(9, frame.sample(0));
    }

    TEST(Sample5)
    {
        Aquila::Frame frame(data, 6, 7);
        CHECK_EQUAL(7, frame.sample(1));
    }

    TEST(SampleCount1)
    {
        Aquila::Frame frame(data, 0, 1);
        CHECK_EQUAL(1, frame.getSamplesCount());
    }

    TEST(SampleCount2)
    {
        Aquila::Frame frame(data, 0, 4);
        CHECK_EQUAL(4, frame.getSamplesCount());
    }

    TEST(SampleCount3)
    {
        Aquila::Frame frame(data, 0, 10);
        CHECK_EQUAL(10, frame.getSamplesCount());
    }

    TEST(SampleCount4)
    {
        Aquila::Frame frame(data, 0, 15);
        CHECK_EQUAL(10, frame.getSamplesCount());
    }

    TEST(SampleCount5)
    {
        Aquila::Frame frame(data, 9, 20);
        CHECK_EQUAL(1, frame.getSamplesCount());
    }
}
