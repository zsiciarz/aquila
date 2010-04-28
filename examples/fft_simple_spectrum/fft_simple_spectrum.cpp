#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/transform/OouraFft.h"
#include "aquila/tools/TextPlot.h"
#include <cmath>

int main()
{
    // input signal parameters
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFreq = 2000;
    const double dt = 1.0/sampleFreq;
    const Aquila::FrequencyType f1 = 125, f2 = 700;

    double x[SIZE];
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        x[i] = 32*std::sin(2*M_PI*f1*i*dt) + 8*std::sin(2*M_PI*f2*i*dt + 0.75*M_PI);
    }
    Aquila::TextPlot plt("Input signal");
    plt.plot(x, SIZE);

    // calculate the FFT
    Aquila::OouraFft fft(SIZE);
    Aquila::ComplexType spectrum[SIZE];
    fft.fft(x, spectrum);

    // prepare the spectrum for plotting (only half of it is important)
    double absSpectrum[SIZE/2];
    for (std::size_t i = 0; i < SIZE/2; ++i)
    {
        absSpectrum[i] = std::abs(spectrum[i]);
    }
    plt.setTitle("Spectrum");
    plt.plot(absSpectrum, SIZE/2);

    return 0;
}



