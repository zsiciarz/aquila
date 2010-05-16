#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include <iostream>

int main(int argc, char *argv[])
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);
    std::cout << data.getSampleFrequency();
    return 0;
}
