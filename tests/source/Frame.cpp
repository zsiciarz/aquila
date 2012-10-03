#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/Frame.h"
#include <boost/cstdint.hpp>
#include <unittestpp.h>


SUITE(Frame)
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);

    TEST(BitsPerSample)
    {
        Aquila::Frame frame(data, 0, 1);
        CHECK_EQUAL(frame.getBitsPerSample(), 8 * sizeof(Aquila::SampleType));
    }

    TEST(SampleFrequency)
    {
        Aquila::Frame frame(data, 0, 1);
        CHECK_EQUAL(frame.getSampleFrequency(), data.getSampleFrequency());
    }

    TEST(Sample1)
    {
        Aquila::Frame frame(data, 0, 10);
        CHECK_EQUAL(frame.sample(0), 0);
    }

    TEST(Sample2)
    {
        Aquila::Frame frame(data, 1, 10);
        CHECK_EQUAL(frame.sample(0), 1);
    }

    TEST(Sample3)
    {
        Aquila::Frame frame(data, 2, 10);
        CHECK_EQUAL(frame.sample(2), 4);
    }

    TEST(Sample4)
    {
        Aquila::Frame frame(data, 9, 10);
        CHECK_EQUAL(frame.sample(0), 9);
    }

    TEST(Sample5)
    {
        Aquila::Frame frame(data, 6, 7);
        CHECK_EQUAL(frame.sample(1), 7);
    }

    TEST(SampleCount1)
    {
        Aquila::Frame frame(data, 0, 1);
        CHECK_EQUAL(frame.getSamplesCount(), 1);
    }

    TEST(SampleCount2)
    {
        Aquila::Frame frame(data, 0, 4);
        CHECK_EQUAL(frame.getSamplesCount(), 4);
    }

    TEST(SampleCount3)
    {
        Aquila::Frame frame(data, 0, 10);
        CHECK_EQUAL(frame.getSamplesCount(), 10);
    }

    TEST(SampleCount4)
    {
        Aquila::Frame frame(data, 0, 15);
        CHECK_EQUAL(frame.getSamplesCount(), 10);
    }

    TEST(SampleCount5)
    {
        Aquila::Frame frame(data, 9, 20);
        CHECK_EQUAL(frame.getSamplesCount(), 1);
    }
}
