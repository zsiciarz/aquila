#include "aquila/source/WaveFile.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: wave_iteration <FILENAME> [<FRAMELENGTH>]" << std::endl;
        return 1;
    }

    int frameLength = 0; // frame length in milliseconds
    if (argc >= 3)
    {
        frameLength = std::atoi(argv[2]);
    }
    if (0 == frameLength)
    {
        frameLength = 20;
    }

    Aquila::WaveFile wav(argv[1]);

    return 0;
}
