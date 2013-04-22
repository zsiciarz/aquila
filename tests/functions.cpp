#include "aquila/global.h"
#include "aquila/functions.h"
#include <unittestpp.h>
#include <vector>


SUITE(Functions)
{
    const std::size_t SIZE = 3;
    double arr1[SIZE] = {0, 1, 2};
    std::vector<double> v1(arr1, arr1 + SIZE);
    double arr2[SIZE] = {1, 2, 3};
    std::vector<double> v2(arr2, arr2 + SIZE);

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
