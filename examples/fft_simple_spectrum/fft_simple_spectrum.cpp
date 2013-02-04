#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/Sum.h"
#include "aquila/transform/FftFactory.h"
#include "aquila/tools/TextPlot.h"

int main()
{
    // input signal parameters
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFreq = 2000;
    const Aquila::FrequencyType f1 = 125, f2 = 700;

    Aquila::SineGenerator sineGenerator1 = Aquila::SineGenerator(sampleFreq);
    sineGenerator1.setAmplitude(32).setFrequency(f1).generate(SIZE);
    Aquila::SineGenerator sineGenerator2 = Aquila::SineGenerator(sampleFreq);
    sineGenerator2.setAmplitude(8).setFrequency(f2).setPhase(0.75).generate(SIZE);
    Aquila::Sum sum(sineGenerator1, sineGenerator2);

    Aquila::TextPlot plt("Input signal");
    plt.plot(sum);

    // calculate the FFT
    auto fft = Aquila::FftFactory::getFft(SIZE);
    Aquila::ComplexType spectrum[SIZE];
    fft->fft(sum.toArray(), spectrum);

    plt.setTitle("Spectrum");
    plt.plotSpectrum(spectrum, SIZE);

    return 0;
}
