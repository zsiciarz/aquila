#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/Frame.h"
#include "aquila/source/FramesCollection.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    const int SIZE = 1024, FRAME_SIZE = 127;
    double* testArray = new double[SIZE];
    Aquila::ArrayData<double> data(testArray, SIZE, 44100);
    Aquila::FramesCollection frames(data, FRAME_SIZE);
    std::cout << "Signal size: " << SIZE
              << ", frame size: " << FRAME_SIZE
              << ", number of frames: " << frames.count() << std::endl;

    delete testArray;
    return 0;
}

