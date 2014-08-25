#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "aquila/source/Frame.h"
#include "aquila/source/FramesCollection.h"
#include "UnitTest++/UnitTest++.h"
#include <algorithm>

bool equalSamples(Aquila::Frame frame, Aquila::SampleType arr[])
{
    return std::equal(std::begin(frame), std::end(frame), arr);
}

SUITE(FramesCollection)
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::FrequencyType sampleFrequency = 100;
    Aquila::SignalSource data(testArray, SIZE, sampleFrequency);

    TEST(Empty)
    {
        Aquila::FramesCollection frames;
        CHECK_EQUAL(0u, frames.getSamplesPerFrame());
        CHECK_EQUAL(0u, frames.count());
    }

    TEST(EmptyWhenZeroSamples)
    {
        Aquila::FramesCollection frames(data, 0);
        CHECK_EQUAL(0u, frames.getSamplesPerFrame());
        CHECK_EQUAL(0u, frames.count());
    }

    TEST(FiveSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 5);
        CHECK_EQUAL(5u, frames.getSamplesPerFrame());
        CHECK_EQUAL(2u, frames.count());
        Aquila::SampleType arr0[5] = {0, 1, 2, 3, 4};
        CHECK(equalSamples(frames.frame(0), arr0));
        Aquila::SampleType arr1[5] = {5, 6, 7, 8, 9};
        CHECK(equalSamples(frames.frame(1), arr1));
    }

    TEST(TwoSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 2);
        CHECK_EQUAL(2u, frames.getSamplesPerFrame());
        CHECK_EQUAL(5u, frames.count());
        Aquila::SampleType arr[2] = {0, 1};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(OneSamplePerFrame)
    {
        Aquila::FramesCollection frames(data, 1);
        CHECK_EQUAL(1u, frames.getSamplesPerFrame());
        CHECK_EQUAL(10u, frames.count());
        Aquila::SampleType arr[1] = {0};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(AllSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 10);
        CHECK_EQUAL(10u, frames.getSamplesPerFrame());
        CHECK_EQUAL(1u, frames.count());
        Aquila::SampleType arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(MoreThanHalfSamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 7);
        CHECK_EQUAL(7u, frames.getSamplesPerFrame());
        CHECK_EQUAL(1u, frames.count());
        Aquila::SampleType arr[7] = {0, 1, 2, 3, 4, 5, 6};
        CHECK(equalSamples(frames.frame(0), arr));
    }

    TEST(TooManySamplesPerFrame)
    {
        Aquila::FramesCollection frames(data, 11);
        CHECK_EQUAL(0u, frames.count());
    }

    TEST(Iteration)
    {
        Aquila::FramesCollection frames(data, 2);
        for (auto it = frames.begin(); it != frames.end(); it++)
        {
            CHECK_EQUAL(2u, it->length());
        }
    }

    TEST(Duration)
    {
        // sampling at 100 Hz -> 10 miliseconds is 1 sample
        auto frames = Aquila::FramesCollection::createFromDuration(data, 10);
        CHECK_EQUAL(10u, frames.count());
    }

    TEST(Duration2)
    {
        // sampling at 100 Hz -> 50 miliseconds is 5 samples
        auto frames = Aquila::FramesCollection::createFromDuration(data, 50);
        CHECK_EQUAL(2u, frames.count());
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
        CHECK_EQUAL(6u, frames.count());
    }

    TEST(ApplySimpleFunction)
    {
        Aquila::FramesCollection frames(data, 5);
        auto energies = frames.apply<double>(Aquila::mean);
        double expected[2] = {2.0, 7.0};
        CHECK_ARRAY_CLOSE(expected, energies, 2, 0.000001);
    }

    TEST(ApplyLambda)
    {
        Aquila::FramesCollection frames(data, 5);
        auto maximums = frames.apply<Aquila::SampleType>(
            [&](const Aquila::SignalSource& s) {
                return *std::max_element(s.begin(), s.end());
            }
        );
        Aquila::SampleType expected[2] = {4.0, 9.0};
        CHECK_ARRAY_CLOSE(expected, maximums, 2, 0.000001);
    }

    TEST(ApplyMemberFunction)
    {
        Aquila::FramesCollection frames(data, 5);
        auto lengths = frames.apply<std::size_t>(
#ifdef _MSC_VER
            std::mem_fn(&Aquila::SignalSource::getSamplesCount)
#else
            &Aquila::SignalSource::getSamplesCount
#endif // _MSC_VER
        );
        std::size_t expected[2] = {5, 5};
        CHECK_ARRAY_EQUAL(expected, lengths, 2);
    }
}
