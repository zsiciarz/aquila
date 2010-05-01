#include "aquila/global.h"
#include "aquila/transform/OouraFft.h"
#include "aquila/tools/TextPlot.h"
#include <algorithm>
#include <cmath>
#include <functional>

void plotSpectrum(Aquila::ComplexType spectrum[], size_t SIZE, const char* title);

int main()
{
    // input signal parameters
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFreq = 2000;
    const double dt = 1.0/sampleFreq;
    const Aquila::FrequencyType f1 = 96, f2 = 813;
    const Aquila::FrequencyType f_lp = 500;

    double x[SIZE];
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        x[i] = 32*std::sin(2*M_PI*f1*i*dt) + 8*std::sin(2*M_PI*f2*i*dt + 0.75*M_PI);
    }
    Aquila::TextPlot plt("Signal waveform before filtration");
    plt.plot(x, SIZE);

    // calculate the FFT
    Aquila::OouraFft fft(SIZE);
    Aquila::ComplexType spectrum[SIZE];
    fft.fft(x, spectrum);
    plotSpectrum(spectrum, SIZE, "Signal spectrum before filtration");

    // generate a low-pass filter spectrum
    Aquila::ComplexType filterSpectrum[SIZE];
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        if (i < (SIZE * f_lp / sampleFreq))
        {
            // passband
            filterSpectrum[i] = 1.0;
        }
        else
        {
            // stopband
            filterSpectrum[i] = 0.0;
        }
    }
    plotSpectrum(filterSpectrum, SIZE, "Filter spectrum");

    // the following line does the multiplication of two spectra
    // (which is complementary to convolution in time domain)
    std::transform(spectrum, spectrum + SIZE, filterSpectrum, spectrum,
                   std::multiplies<Aquila::ComplexType>());
    plotSpectrum(spectrum, SIZE, "Signal spectrum after filtration");

    // Inverse FFT moves us back to time domain
    double x1[SIZE];
    fft.ifft(spectrum, x1);
    plt.setTitle("Signal waveform after filtration");
    plt.plot(x1, SIZE);

    return 0;
}

/**
 * This is a shortcut for plotting only the first half of the spectrum.
 */
void plotSpectrum(Aquila::ComplexType spectrum[], size_t SIZE, const char* title)
{
    // prepare the spectrum for plotting (only half of it is important)
    double absSpectrum[SIZE/2];
    for (std::size_t i = 0; i < SIZE/2; ++i)
    {
        absSpectrum[i] = std::abs(spectrum[i]);
    }
    Aquila::TextPlot plt(title);
    plt.plot(absSpectrum, SIZE/2);
}
