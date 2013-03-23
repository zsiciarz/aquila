#include "aquila/global.h"
#include "aquila/source/SignalSource.h"
#include "aquila/source/Frame.h"
#include "aquila/source/FramesCollection.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>

int main(int argc, char *argv[])
{
    // seed the random number generator
    std::srand(std::time(0));
    const int SIZE = 1024, FRAME_SIZE = 127;

    // create an array and fill it with random numbers
    double* testArray = new double[SIZE];
    std::generate_n(testArray, SIZE, std::rand);

    // wrap the array with SignalSource and divide it into frames
    Aquila::SignalSource data(testArray, SIZE, 44100);
    Aquila::FramesCollection frames(data, FRAME_SIZE);
    std::cout << "Signal size: " << SIZE
              << ", frame size: " << FRAME_SIZE
              << ", number of frames: " << frames.count() << std::endl;

    unsigned int i = 0;
    // here, begin() and end() return iterators that point to frame objects
    for (auto it = frames.begin(); it != frames.end(); ++it, ++i)
    {
        // and here the iterators returned point to individual samples
        // in each frame
        double sum = std::accumulate(it->begin(), it->end(), 0.0);
        std::cout << "\nFrame #" << i << ", sum = " << sum;
    }

    delete [] testArray;
    return 0;
}

