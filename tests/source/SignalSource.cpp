#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include <cstddef>
#include <cstdint>
#include <unittestpp.h>


SUITE(SignalSource)
{
    const std::size_t SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // any other SignalSource subclass would work here
    Aquila::ArrayData<> data(testArray, SIZE, 22050);

    TEST(LengthAlias)
    {
        CHECK_EQUAL(data.getSamplesCount(), data.length());
    }

    TEST(IteratorPosition)
    {
        auto it = data.begin();
        CHECK_EQUAL(0u, it.getPosition());
        it++;
        CHECK_EQUAL(1u, it.getPosition());
    }

    TEST(IteratorAssignment)
    {
        auto it1 = data.begin(), it2 = data.begin();
        it1++;
        it2 = it1;
        CHECK_EQUAL(1u, it2.getPosition());
    }

    TEST(IteratorsEqual)
    {
        auto it1 = data.begin(), it2 = data.begin();
        it1++;
        it2++;
        CHECK(it1 == it2);
    }

    TEST(IteratorsNotEqual)
    {
        auto it1 = data.begin(), it2 = data.begin();
        it1++;
        CHECK(it1 != it2);
    }

    TEST(IteratorsToDifferentSources)
    {
        Aquila::ArrayData<> data2(testArray, SIZE, 22050);
        auto it1 = data.begin(), it2 = data2.begin();
        CHECK(it1 != it2);
    }

    TEST(Mean)
    {
        CHECK_CLOSE(4.5, Aquila::mean(data), 0.000001);
    }

    TEST(Energy)
    {
        CHECK_CLOSE(285.0, Aquila::energy(data), 0.000001);
    }

    TEST(Power)
    {
        CHECK_CLOSE(28.5, Aquila::power(data), 0.000001);
    }

    TEST(Norm)
    {
        CHECK_CLOSE(16.881943, Aquila::norm(data), 0.000001);
    }

    TEST(Rms)
    {
        CHECK_CLOSE(5.338539, Aquila::rms(data), 0.000001);
    }
}
