#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>
#include <cstdint>
#include <vector>


SUITE(SignalSource)
{
    const std::size_t SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::SignalSource data(testArray, SIZE, 22050);

    TEST(InitializeFromVector)
    {
        std::vector<Aquila::SampleType> vec(testArray, testArray + SIZE);
        Aquila::SignalSource source(vec, 22050);
        CHECK_EQUAL(SIZE, source.length());
    }

    TEST(InitializeFromTempVector)
    {
        Aquila::SignalSource source(
            std::vector<Aquila::SampleType>(testArray, testArray + SIZE),
            22050
        );
        CHECK_EQUAL(SIZE, source.length());
    }

    TEST(SampleFrequency)
    {
        CHECK_EQUAL(22050, data.getSampleFrequency());
    }

    TEST(DefaultSampleFrequency)
    {
        Aquila::SignalSource data2(testArray, SIZE);
        CHECK_EQUAL(0, data2.getSampleFrequency());
        data2.setSampleFrequency(22050);
        CHECK_EQUAL(22050, data2.getSampleFrequency());
    }

    TEST(LengthAlias)
    {
        CHECK_EQUAL(data.getSamplesCount(), data.length());
    }

    TEST(Iteration)
    {
        std::size_t i = 0;
        for (auto it = data.begin(); it != data.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i], *it);
        }
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
        Aquila::SignalSource data2(testArray, SIZE, 22050);
        auto it1 = data.begin(), it2 = data2.begin();
        CHECK(it1 != it2);
    }

    TEST(SumWithConstant)
    {
        const Aquila::SampleType offset = 99.0;
        auto result = data + offset;
        std::size_t i = 0;
        for (auto it = result.begin(); it != result.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i] + offset, result.sample(i));
        }
    }

    TEST(SumWithConstantRhs)
    {
        const Aquila::SampleType offset = 99.0;
        auto result = offset + data;
        std::size_t i = 0;
        for (auto it = result.begin(); it != result.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i] + offset, result.sample(i));
        }
    }

    TEST(MultiplyByConstant)
    {
        const Aquila::SampleType scale = 10.0;
        auto result = data * scale;
        std::size_t i = 0;
        for (auto it = result.begin(); it != result.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i] * scale, result.sample(i));
        }
    }

    TEST(MultiplyByConstantRhs)
    {
        const Aquila::SampleType scale = 10.0;
        auto result = scale * data;
        std::size_t i = 0;
        for (auto it = result.begin(); it != result.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i] * scale, result.sample(i));
        }
    }

    TEST(SimpleSum)
    {
        Aquila::SignalSource data2(testArray, SIZE, 22050);
        auto result = data + data2;
        std::size_t i = 0;
        for (auto it = result.begin(); it != result.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i] + testArray[i], result.sample(i));
        }
    }

    TEST(SimpleMultiplication)
    {
        Aquila::SignalSource data2(testArray, SIZE, 22050);
        auto result = data * data2;
        std::size_t i = 0;
        for (auto it = result.begin(); it != result.end(); it++, i++)
        {
            CHECK_EQUAL(testArray[i] * testArray[i], result.sample(i));
        }
    }

    TEST(ComplexExpression)
    {
        Aquila::SignalSource data2(testArray, SIZE, 22050);
        auto result = data2 + data2 * (3.0 + 2.0 * (1.0 + data + 5.0)) * 2.0 * data2;
        std::size_t i = 0;
        for (auto it = result.begin(); it != result.end(); it++, i++)
        {
            CHECK_EQUAL(
                testArray[i] +
                    testArray[i] *
                    (3.0 + 2.0 * (1.0 + testArray[i] + 5.0)) * 2.0 *
                    testArray[i],
                result.sample(i)
            );
        }
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
