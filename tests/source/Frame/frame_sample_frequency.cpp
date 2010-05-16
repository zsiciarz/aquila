#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/Frame.h"
#include <iostream>

int main(int argc, char *argv[])
{
    const int SIZE = 1;
    Aquila::SampleType testArray[SIZE] = {0};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);
    Aquila::Frame frame(data, 0, 1);
    std::cout << frame.getSampleFrequency();

    return 0;
}

