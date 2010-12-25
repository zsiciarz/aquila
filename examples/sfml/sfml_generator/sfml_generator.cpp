#include "aquila/source/generator/SineGenerator.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>

int main(int argc, char** argv)
{
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;
    Aquila::SineGenerator generator(SAMPLE_FREQUENCY);
    generator.setFrequency(440).setAmplitude(8192).generate(2 * SAMPLE_FREQUENCY);

    sf::Int16* samples = new sf::Int16[generator.getSamplesCount()];
    std::copy(generator.begin(), generator.end(), samples);

    sf::SoundBuffer buffer;
    buffer.LoadFromSamples(samples,
                           generator.getSamplesCount(),
                           1,
                           static_cast<unsigned int>(SAMPLE_FREQUENCY));
    delete [] samples;

    sf::Sound sound;
    sound.SetBuffer(buffer);
    sound.Play();
    while (sound.GetStatus() == sf::Sound::Playing)
    {
        sf::Sleep(0.1f);
    }

    return 0;
}
