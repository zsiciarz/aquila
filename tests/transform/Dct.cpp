#include "aquila/global.h"
#include "aquila/transform/Dct.h"
#include <unittestpp.h>
#include <cstddef>
#include <vector>


SUITE(Dct)
{
    TEST(AlternatingOnes)
    {
        const std::size_t SIZE = 4;
        const double testArray[SIZE] = {1.0, -1.0, 1.0, -1.0};
        std::vector<double> vec(testArray, testArray + SIZE);

        Aquila::Dct dct;
        auto output = dct.dct(vec, SIZE);

        double expected[SIZE] = {0.0, 0.76536686, 0.0, 1.84775907};
        CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
    }

    TEST(ConstantInput)
    {
        const std::size_t SIZE = 4;
        const double testArray[SIZE] = {1.0, 1.0, 1.0, 1.0};
        std::vector<double> vec(testArray, testArray + SIZE);

        Aquila::Dct dct;
        auto output = dct.dct(vec, SIZE);

        double expected[SIZE] = {2.0, 0.0, 0.0, 0.0};
        CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
    }
}
