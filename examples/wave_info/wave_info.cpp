#include "aquila/source/WaveFile.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: wave_info <FILENAME>" << std::endl;
        return 1;
    }
    Aquila::WaveFile wav(argv[1]);
    std::cout << "Filename: "           << wav.getFilename();
    std::cout << "\nLength: "           << wav.getAudioLength()     << " ms";
    std::cout << "\nSample frequency: " << wav.getSampleFrequency() << " Hz";
    std::cout << "\nChannels: "         << wav.getChannelsNum();
    std::cout << "\nByte rate: "        << wav.getBytesPerSec()/1024 << " kB/s";
    std::cout << "\nBits per sample: "  << wav.getBitsPerSample() << "b\n";

    return 0;
}
