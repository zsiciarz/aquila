#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/Frame.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);

    int from = 0, to = 1;
    if (argc > 1)
    {
        from = std::atoi(argv[1]);
    }
    if (argc > 2)
    {
        to = std::atoi(argv[2]);
    }
    Aquila::Frame frame(data, from, to);
    std::cout << frame.getSamplesCount();

    return 0;
}
