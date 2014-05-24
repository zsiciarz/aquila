#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "aquila/source/generator/PinkNoiseGenerator.h"
#include "aquila/source/generator/WhiteNoiseGenerator.h"
#include "aquila/wrappers/SoundBufferAdapter.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>


void handleGeneratorOptions(Aquila::Generator* generator)
{
    Aquila::FrequencyType frequency, maxFrequency = generator->getSampleFrequency() / 2;
    std::cout << "\nSignal frequency in Hz: \n"
                 "Enter a number (0-" << maxFrequency << "): ";
    std::cin >> frequency;
    if (frequency < 0 || frequency > maxFrequency)
    {
        frequency = 1000;
    }
    generator->setFrequency(frequency);
}


Aquila::Generator* createGenerator(unsigned int whichGenerator,
                                   Aquila::FrequencyType sampleFrequency)
{
    Aquila::Generator* generator;
    switch (whichGenerator)
    {
    case 1:
        generator = new Aquila::SineGenerator(sampleFrequency);
        handleGeneratorOptions(generator);
        break;
    case 2:
        generator = new Aquila::SquareGenerator(sampleFrequency);
        handleGeneratorOptions(generator);
        break;
    case 3:
        generator = new Aquila::PinkNoiseGenerator(sampleFrequency);
        break;
    case 4:
        generator = new Aquila::WhiteNoiseGenerator(sampleFrequency);
        break;
    default:
        generator = new Aquila::SineGenerator(sampleFrequency);
        handleGeneratorOptions(generator);
        break;
    }
    generator->setAmplitude(8192);
    return generator;
}


int main(int argc, char** argv)
{
    std::cout << "Choose which kind of signal to play: \n"
                 "\t 1: Sine wave \n"
                 "\t 2: Square wave \n"
                 "\t 3: Pink noise \n"
                 "\t 4: White noise \n"
                 "Enter a number (1-4): ";
    unsigned int whichGenerator = 1;
    std::cin >> whichGenerator;
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;
    Aquila::Generator* generator = createGenerator(whichGenerator, SAMPLE_FREQUENCY);
    generator->generate(5 * SAMPLE_FREQUENCY);

    Aquila::SoundBufferAdapter buffer(*generator);
    sf::Sound sound(buffer);
    sound.play();
    std::cout << "Playing..." << std::endl;
    while (sound.getStatus() == sf::Sound::Playing)
    {
        std::cout << ".";
        sf::sleep(sf::milliseconds(100));
    }
    std::cout << "\nFinished." << std::endl;
    delete generator;

    return 0;
}
