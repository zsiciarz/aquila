#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/Frame.h"
#include "aquila/source/FramesCollection.h"
#include <unittestpp.h>
#include <algorithm>

bool equalSamples(Aquila::Frame frame, Aquila::SampleType arr[])
{
    return std::equal(std::begin(frame), std::end(frame), arr);
}

SUITE(FramesCollection)
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::FrequencyType sampleFrequency  = 100;
    Aquila::ArrayData<> data(testArray, SIZE, sampleFrequency);

    TEST(Empty)
    {
        Aquila::FramesCollection frames;
        CHECK_EQUAL(0, frames.count());
    }

    TEST(FiveSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 5);
        CHECK_EQUAL(2, frames.count());
        Aquila::SampleType arr0[5] = {0, 1, 2, 3, 4};
        CHECK(equalSamples(frames.frame(0), arr0));
        Aquila::SampleType arr1[5] = {5, 6, 7, 8, 9};
        CHECK(equalSamples(frames.frame(1), arr1));
    }

    TEST(TwoSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 2);
        CHECK_EQUAL(5, frames.count());
        Aquila::SampleType arr[2] = {0, 1};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(OneSamplePerFrame)
    {
        Aquila::FramesCollection frames(data, 1);
        CHECK_EQUAL(10, frames.count());
        Aquila::SampleType arr[1] = {0};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(AllSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 10);
        CHECK_EQUAL(1, frames.count());
        Aquila::SampleType arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(MoreThanHalfSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 7);
        CHECK_EQUAL(1, frames.count());
        Aquila::SampleType arr[7] = {0, 1, 2, 3, 4, 5, 6};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(TooManySamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 11);
        CHECK_EQUAL(0, frames.count());
    }

    TEST(Duration)
    {
        // sampling at 100 Hz -> 10 miliseconds is 1 sample
        auto frames = Aquila::FramesCollection::createFromDuration(data, 10);
        CHECK_EQUAL(10, frames.count());
    }

    TEST(Duration2)
    {
        // sampling at 100 Hz -> 50 miliseconds is 5 samples
        auto frames = Aquila::FramesCollection::createFromDuration(data, 50);
        CHECK_EQUAL(2, frames.count());
    }

    TEST(DurationWithOverlap)
    {
        // sampling at 100 Hz -> 50 miliseconds is 5 samples
        // 80% overlap -> 4 common samples between consecutive frames
        // frame data:  0  1  2  3  4  5  6  7  8  9
        // frame 0:    |             |
        // frame 1:       |             |
        // frame 2:          |             |
        // frame 3:             |             |
        // frame 4:                |             |
        // frame 5:                   |              |
        auto frames = Aquila::FramesCollection::createFromDuration(data, 50, 0.8);
        CHECK_EQUAL(6, frames.count());
    }
}
