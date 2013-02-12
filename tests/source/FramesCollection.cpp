#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/FramesCollection.h"
#include <unittestpp.h>


SUITE(FramesCollection)
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);

    TEST(Empty)
    {
        Aquila::FramesCollection frames;
        CHECK_EQUAL(0, frames.count());
    }

    TEST(FiveSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 5);
        CHECK_EQUAL(2, frames.count());
    }

    TEST(TwoSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 2);
        CHECK_EQUAL(5, frames.count());
    }

    TEST(OneSamplePerFrame)
    {
        Aquila::FramesCollection frames(data, 1);
        CHECK_EQUAL(10, frames.count());
    }

    TEST(AllSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 10);
        CHECK_EQUAL(1, frames.count());
    }

    TEST(MoreThanHalfSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 7);
        CHECK_EQUAL(1, frames.count());
    }

    TEST(TooManySamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 11);
        CHECK_EQUAL(0, frames.count());
    }
}
