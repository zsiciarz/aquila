#include "aquila/global.h"
#include "aquila/source/WaveFile.h"
#include <algorithm>
#include <cstdlib>
#include <functional>
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
    std::cout << "Loaded file: " << wav.getFilename()
              << " (" << wav.getBitsPerSample() << "b)" << std::endl;
    Aquila::SampleType maxValue = 0, minValue = 0;

    // simple index-based iteration
    for (std::size_t i = 0; i < wav.getSamplesCount(); ++i)
    {
        if (wav.sample(i) > maxValue)
            maxValue = wav.sample(i);
    }
    std::cout << "Maximum sample value: " << maxValue << std::endl;

    // iterator usage
    for (Aquila::WaveFile::iterator it = wav.begin(); it != wav.end(); ++it)
    {
        if (*it < minValue)
            minValue = *it;
    }
    std::cout << "Minimum sample value: " << minValue << std::endl;

    // STL algorithms work too, so the previous examples could be rewritten
    // using max/min_element.
    int limit = 5000;
    int aboveLimit = std::count_if(wav.begin(), wav.end(),
                                   std::bind2nd(std::greater<int>(), limit));
    std::cout << "There are " << aboveLimit << " samples greater than "
              << limit << std::endl;

    return 0;
}
