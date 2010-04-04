#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include <algorithm>
#include <iostream>
#include <boost/lambda/lambda.hpp>

using namespace boost::lambda;

int main(int argc, char *argv[])
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);
    std::for_each(data.begin(), data.end(), std::cout << 2 * _1);
    return 0;
}
