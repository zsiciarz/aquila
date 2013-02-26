/**
 * Plucked string synthesis using Karplus-Strong algorithm.
 *
 * A short noise burst is fed through a feedback loop including delay and
 * a first-order lowpass filter (in this case a simple moving average).
 * Resulting waveform is played using SFML - the sound is similar to a
 * plucked guitar string.
 */

#include "aquila/source/ArrayData.h"
#include "aquila/source/generator/WhiteNoiseGenerator.h"
#include "aquila/synth/Synthesizer.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace Aquila;

/**
 * Very simple guitar synthesizer using Karplus-Strong algorithm.
 */
class KarplusStrongSynthesizer : public Synthesizer
{
public:
    KarplusStrongSynthesizer(FrequencyType sampleFrequency):
        Synthesizer(sampleFrequency), m_generator(sampleFrequency)
    {
    }

protected:
    /**
     * Plays a single note.
     *
     * @param frequency frequency of the generated note
     * @param duration duration in milliseconds
     */
    void playFrequency(Aquila::FrequencyType frequency, unsigned int duration = 500)
    {
        double alpha = 0.99;
        std::size_t delay = static_cast<std::size_t>(m_sampleFrequency / frequency);
        std::size_t totalSamples = static_cast<std::size_t>(m_sampleFrequency * duration / 1000.0);
        m_generator.setAmplitude(8192).generate(delay);

        // copy initial noise burst at the beginning of output array
        sf::Int16* arr = new sf::Int16[totalSamples];
        std::copy(std::begin(m_generator), std::end(m_generator), arr);
        // first sample that goes into feedback loop;
        // cannot be averaged with previous
        arr[delay] = alpha * arr[0];
        for (std::size_t i = delay + 1; i < totalSamples; ++i)
        {
            // average two consecutive delayed samples and dampen by alpha
             arr[i] = alpha * (0.5 * (arr[i - delay] + arr[i - delay - 1]));
        }

        m_buffer.LoadFromSamples(arr, totalSamples, 1, m_sampleFrequency);
        sf::Sound sound(m_buffer);
        sound.Play();
        sf::Sleep(duration / 1000.0f);

        delete [] arr;
    }

private:
    WhiteNoiseGenerator m_generator;
};


int main(int argc, char** argv)
{
    std::cout << "Plucked string synthesis using Karplus-Strong algorithm\n";
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;

    KarplusStrongSynthesizer synth(SAMPLE_FREQUENCY);
    // play the C major scale up and down
    synth.playNote("c");
    synth.playNote("d");
    synth.playNote("e");
    synth.playNote("f");
    synth.playNote("g");
    synth.playNote("a");
    synth.playNote("b");
    synth.playNote("cH");
    synth.playNote("pause");
    synth.playNote("cH");
    synth.playNote("b");
    synth.playNote("a");
    synth.playNote("g");
    synth.playNote("f");
    synth.playNote("e");
    synth.playNote("d");
    synth.playNote("c");

    return 0;
}
