#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/Frame.h"
#include <boost/cstdint.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    const int SIZE = 1;
    boost::int8_t a[SIZE] = {0};
    Aquila::ArrayData<boost::int8_t> d(a, SIZE, 22050);

    Aquila::Frame frame(d, 0, 1);
    std::cout << frame.getBitsPerSample();

    return 0;
}



