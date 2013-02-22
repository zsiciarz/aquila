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
#include "aquila/wrappers/SoundBufferAdapter.h"
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

/**
 * Very simple guitar synthesizer using Karplus-Strong algorithm.
 */
class GuitarSynthesizer
{
public:
    GuitarSynthesizer(Aquila::FrequencyType sampleFrequency):
        m_sampleFrequency(sampleFrequency),
        m_generator(sampleFrequency)
    {
    }

    /**
     * Plays a single note.
     *
     * @param frequency frequency of the generated note
     * @param duration duration in milliseconds
     */
    void pluck(Aquila::FrequencyType frequency, unsigned int duration = 500)
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
        //
        for (std::size_t i = delay + 1; i < totalSamples; ++i)
        {
            // average two consecutive delayed samples and dampen by alpha
             arr[i] = alpha * (0.5 * (arr[i - delay] + arr[i - delay - 1]));
        }

        buffer.LoadFromSamples(arr, totalSamples, 1, m_sampleFrequency);
        sf::Sound sound(buffer);
        sound.Play();
        sf::Sleep(duration / 1000.0f);

        delete [] arr;
    }

private:
    const Aquila::FrequencyType m_sampleFrequency;
    Aquila::WhiteNoiseGenerator m_generator;
    Aquila::SoundBufferAdapter buffer;
};


int main(int argc, char** argv)
{
    std::cout << "Plucked string synthesis using Karplus-Strong algorithm\n";
    const Aquila::FrequencyType SAMPLE_FREQUENCY = 44100;

    GuitarSynthesizer synth(SAMPLE_FREQUENCY);
    // play the C major scale up and down
    synth.pluck(c);
    synth.pluck(d);
    synth.pluck(e);
    synth.pluck(f);
    synth.pluck(g);
    synth.pluck(a);
    synth.pluck(b);
    synth.pluck(cH);
    sf::Sleep(0.5f);
    synth.pluck(cH);
    synth.pluck(b);
    synth.pluck(a);
    synth.pluck(g);
    synth.pluck(f);
    synth.pluck(e);
    synth.pluck(d);
    synth.pluck(c);

    return 0;
}
