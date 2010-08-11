#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "aquila/source/generator/TriangleGenerator.h"
#include "aquila/source/FramesCollection.h"
#include "aquila/transform/Spectrogram.h"
#include "aquila/functions.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    const unsigned int SIGNAL_MS = 1000;
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100, SIGNAL_FREQUENCY = 1000;
    const unsigned int SAMPLES_PER_SIGNAL = SAMPLE_FREQUENCY * SIGNAL_MS / 1000;
    const unsigned int SAMPLES_PER_FRAME = 1024;

    std::cout << "Sample frequency: " << SAMPLE_FREQUENCY << " Hz\n"
              << "Signal length: " << SIGNAL_MS << " ms (" << SAMPLES_PER_SIGNAL << " samples)\n"
              << "Frame length: " << SAMPLES_PER_FRAME << " samples\n";

    const int SINE = 1, SQUARE = 2, TRIANGLE = 3;
    int generatorType = SINE;
    if (argc > 1)
    {
        generatorType = std::atoi(argv[1]);
    }
    Aquila::Generator* generator = 0;
    if (SQUARE == generatorType)
    {
        generator = new Aquila::SquareGenerator(SAMPLE_FREQUENCY);
    }
    else if (TRIANGLE == generatorType)
    {
        generator = new Aquila::TriangleGenerator(SAMPLE_FREQUENCY);
    }
    else
    {
        generator = new Aquila::SineGenerator(SAMPLE_FREQUENCY);
    }
    generator->setFrequency(SIGNAL_FREQUENCY).setAmplitude(255).generate(SAMPLES_PER_SIGNAL);

    Aquila::FramesCollection frames(*generator, SAMPLES_PER_FRAME);
    std::cout << frames.count() << " frames after division" << std::endl;

    Aquila::Spectrogram spectrogram(frames);

    for (std::size_t x = 0; x < spectrogram.getFrameCount(); ++x)
    {
        // output only half of the spectrogram, below Nyquist frequency
        for (std::size_t y = 0; y < spectrogram.getSpectrumSize() / 2; ++y)
        {
            Aquila::ComplexType point = spectrogram.getPoint(x, y);
            std::cout << Aquila::dB(point) << " ";
        }
        std::cout << "\n";
    }

    delete generator;

    return 0;
}
