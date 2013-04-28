#include "aquila/global.h"
#include "aquila/ml/Dtw.h"
#include <unittestpp.h>
#include <vector>


SUITE(Dtw)
{
    TEST(DistanceToItself)
    {
        const std::size_t SIZE = 3;
        double arr1[SIZE] = {0, 1, 2}, arr2[SIZE] = {1, 2, 3};
        std::vector<double> v1(arr1, arr1 + SIZE), v2(arr2, arr2 + SIZE);

        Aquila::DtwDataType from, to;
        from.push_back(v1);
        from.push_back(v2);
        to.push_back(v1);
        to.push_back(v2);

        Aquila::Dtw dtw;
        double distance = dtw.getDistance(from, to);

        CHECK_CLOSE(0.0, distance, 0.000001);
    }

    TEST(ZeroDiagonalDistance)
    {
        const std::size_t SIZE = 3;
        double arr1[SIZE] = {0, 0, 0}, arr2[SIZE] = {1, 1, 1};
        std::vector<double> zeros(arr1, arr1 + SIZE), ones(arr2, arr2 + SIZE);

        Aquila::DtwDataType from, to;
        from.push_back(zeros);
        from.push_back(ones);
        from.push_back(ones);
        to.push_back(zeros);
        to.push_back(ones);
        to.push_back(ones);

        /**
         * this will give the following local Manhattan distances:
         *
         * 3 0 0
         * 3 0 0
         * 0 3 3
         *
         * and the lowest-cost path will be on the diagonal.
         */

        Aquila::Dtw dtw(Aquila::manhattanDistance);
        double distance = dtw.getDistance(from, to);

        CHECK_CLOSE(0.0, distance, 0.000001);
    }
}

