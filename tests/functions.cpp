#include "aquila/global.h"
#include "aquila/functions.h"
#include "UnitTest++/UnitTest++.h"
#include <vector>


SUITE(Functions)
{
    const std::size_t SIZE = 3;
    double arr1[SIZE] = {0, 1, 2};
    std::vector<double> v1(arr1, arr1 + SIZE);
    double arr2[SIZE] = {1, 2, 3};
    std::vector<double> v2(arr2, arr2 + SIZE);

    TEST(DecibelConversion)
    {
        double decibel = Aquila::dB(10.0);
        CHECK_CLOSE(20.0, decibel, 0.000001);
    }

    TEST(ComplexDecibelConversion)
    {
        double decibel = Aquila::dB(Aquila::ComplexType(0.0, 10.0));
        CHECK_CLOSE(20.0, decibel, 0.000001);
    }

    TEST(ReferenceDecibelConversion)
    {
        double decibel = Aquila::dB(1000.0, 10.0);
        CHECK_CLOSE(40.0, decibel, 0.000001);
    }

    TEST(ClampToMax)
    {
        double value = Aquila::clamp(5.0, 9.0, 6.0);
        CHECK_CLOSE(6.0, value, 0.000001);
    }

    TEST(ClampToMin)
    {
        double value = Aquila::clamp(5.0, 1.0, 6.0);
        CHECK_CLOSE(5.0, value, 0.000001);
    }

    TEST(ClampUnchanged)
    {
        double value = Aquila::clamp(5.0, 5.5, 6.0);
        CHECK_CLOSE(5.5, value, 0.000001);
    }

    TEST(RandomRange)
    {
        for (std::size_t i = 0; i < 1000; ++i)
        {
            int x = Aquila::random(1, 2);
            CHECK_EQUAL(1, x);
        }
    }

    TEST(RandomDoubleRange)
    {
        for (std::size_t i = 0; i < 1000; ++i)
        {
            double x = Aquila::randomDouble();
            CHECK(x < 1.0);
        }
    }

    TEST(EuclideanDistanceToItself)
    {
        double distance = Aquila::euclideanDistance(v1, v1);
        CHECK_CLOSE(0.0, distance, 0.000001);
    }

    TEST(EuclideanDistance)
    {
        double distance = Aquila::euclideanDistance(v1, v2);
        CHECK_CLOSE(1.732051, distance, 0.000001);
    }

    TEST(ManhattanDistanceToItself)
    {
        double distance = Aquila::manhattanDistance(v1, v1);
        CHECK_CLOSE(0.0, distance, 0.000001);
    }

    TEST(ManhattanDistance)
    {
        double distance = Aquila::manhattanDistance(v1, v2);
        CHECK_CLOSE(3.0, distance, 0.000001);
    }

    TEST(ChebyshevDistanceToItself)
    {
        double distance = Aquila::chebyshevDistance(v1, v1);
        CHECK_CLOSE(0.0, distance, 0.000001);
    }

    TEST(ChebyshevDistance)
    {
        double distance = Aquila::chebyshevDistance(v1, v2);
        CHECK_CLOSE(1.0, distance, 0.000001);
    }

}
