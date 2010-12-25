#include "aquila/source/generator/SineGenerator.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <iostream>


void convertSourceToBuffer(const Aquila::SignalSource& source, sf::SoundBuffer& buffer)
{
    sf::Int16* samples = new sf::Int16[source.getSamplesCount()];
    std::copy(source.begin(), source.end(), samples);
    buffer.LoadFromSamples(samples,
                           source.getSamplesCount(),
                           1,
                           static_cast<unsigned int>(source.getSampleFrequency()));
    delete [] samples;
}


int main(int argc, char** argv)
{
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;
    Aquila::SineGenerator generator(SAMPLE_FREQUENCY);
    generator.setFrequency(440).setAmplitude(8192).generate(2 * SAMPLE_FREQUENCY);

    sf::SoundBuffer buffer;
    convertSourceToBuffer(generator, buffer);

    sf::Sound sound;
    sound.SetBuffer(buffer);
    sound.Play();
    while (sound.GetStatus() == sf::Sound::Playing)
    {
        sf::Sleep(0.1f);
    }

    return 0;
}
