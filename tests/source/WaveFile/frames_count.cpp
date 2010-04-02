#include "aquila/source/FramesCollection.h"
#include "aquila/source/WaveFile.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    unsigned int frameLength = 0;
    if (argc >= 3)
    {
        frameLength = std::atoi(argv[2]);
    }

    double overlap = 0.0;
    if (argc >= 4)
    {
        overlap = std::atof(argv[3]);
    }

    Aquila::WaveFile wav(argv[1]);
    wav.setFrameLength(frameLength);
    wav.setFrameOverlap(overlap);
    std::cout << wav.getFramesCount();
    return 0;
}
