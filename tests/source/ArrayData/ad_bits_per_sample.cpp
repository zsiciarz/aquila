#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include <boost/cstdint.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    const int SIZE = 1;
    boost::int8_t a0[SIZE] = {0};
    Aquila::ArrayData<boost::int8_t> d0(a0, SIZE, 22050);

    boost::int16_t a1[SIZE] = {0};
    Aquila::ArrayData<boost::int16_t> d1(a1, SIZE, 22050);

    boost::int32_t a2[SIZE] = {0};
    Aquila::ArrayData<boost::int32_t> d2(a2, SIZE, 22050);

    boost::int64_t a3[SIZE] = {0};
    Aquila::ArrayData<boost::int64_t> d3(a3, SIZE, 22050);

    std::cout << (d0.getBitsPerSample() == 8 * sizeof(Aquila::SampleType)) << " "
              << (d1.getBitsPerSample() == 8 * sizeof(Aquila::SampleType)) << " "
              << (d2.getBitsPerSample() == 8 * sizeof(Aquila::SampleType)) << " "
              << (d3.getBitsPerSample() == 8 * sizeof(Aquila::SampleType));
    return 0;
}


