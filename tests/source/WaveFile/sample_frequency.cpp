#include "aquila/source/WaveFile.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    Aquila::WaveFile wav(argv[1]);
    std::cout << wav.getSampleFrequency();
    return 0;
}
