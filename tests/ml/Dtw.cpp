#include "aquila/global.h"
#include "aquila/functions.h"
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

    TEST(NonZeroDiagonalDistance)
    {
        const std::size_t SIZE = 3;
        double arr1[SIZE] = {0, 0, 0}, arr2[SIZE] = {1, 1, 1};
        std::vector<double> zeros(arr1, arr1 + SIZE), ones(arr2, arr2 + SIZE);

        Aquila::DtwDataType from, to;
        from.push_back(zeros);
        from.push_back(zeros);
        from.push_back(zeros);
        to.push_back(ones);
        to.push_back(ones);
        to.push_back(ones);

        /**
         * this will give the following distances (using Manhattan for local):
         *
         * local      accumulated
         *
         * 3 3 3         3 6 9
         * 3 3 3         3 6 6
         * 3 3 3         3 3 3
         *
         * and the lowest-cost path will still be on the diagonal, but this time
         * the distance is a non-zero value.
         */

        Aquila::Dtw dtw(Aquila::manhattanDistance);
        double distance = dtw.getDistance(from, to);

        CHECK_CLOSE(9.0, distance, 0.000001);
    }

    TEST(Similarity)
    {
        const std::size_t SIZE = 3;
        double arr1[SIZE] = {0, 0, 0}, arr2[SIZE] = {1, 1, 1};
        std::vector<double> zeros(arr1, arr1 + SIZE), ones(arr2, arr2 + SIZE);

        Aquila::DtwDataType from, to1, to2;
        from.push_back(zeros);
        from.push_back(zeros);
        from.push_back(zeros);
        to1.push_back(zeros);
        to1.push_back(zeros);
        to1.push_back(ones);
        to2.push_back(zeros);
        to2.push_back(ones);
        to2.push_back(ones);

        /**
         * 000 is more "similar" to 001 than 011, therefore distance between
         * from and to1 should be smaller
         */
        Aquila::Dtw dtw;
        double distance1 = dtw.getDistance(from, to1);
        double distance2 = dtw.getDistance(from, to2);

        CHECK(distance1 < distance2);
    }

    TEST(RectangularSimilarity)
    {
        const std::size_t SIZE = 3;
        double arr1[SIZE] = {0, 0, 0}, arr2[SIZE] = {1, 1, 1};
        std::vector<double> zeros(arr1, arr1 + SIZE), ones(arr2, arr2 + SIZE);

        Aquila::DtwDataType from, to1, to2;
        from.push_back(zeros);
        from.push_back(zeros);
        from.push_back(zeros);
        to1.push_back(zeros);
        to1.push_back(ones);
        to2.push_back(ones);
        to2.push_back(ones);

        /**
         * 000 is more "similar" to 01 than 11, therefore distance between
         * from and to1 should be smaller
         */
        Aquila::Dtw dtw;
        double distance1 = dtw.getDistance(from, to1);
        double distance2 = dtw.getDistance(from, to2);

        CHECK(distance1 < distance2);
    }

    TEST(TrivialPath)
    {
        const std::size_t SIZE = 3;
        double arr1[SIZE] = {0, 0, 0}, arr2[SIZE] = {1, 1, 1};
        std::vector<double> zeros(arr1, arr1 + SIZE), ones(arr2, arr2 + SIZE);

        Aquila::DtwDataType from, to;
        from.push_back(zeros);
        to.push_back(ones);

        Aquila::Dtw dtw;
        dtw.getDistance(from, to);
        auto path = dtw.getPath();

        CHECK_EQUAL(1ul, path.size());
    }
}

