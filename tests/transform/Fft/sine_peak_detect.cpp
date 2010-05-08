#include "aquila/global.h"
#include "aquila/transform/OouraFft.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cout << "Usage:\n"
                     "\tsine_peak_detect <SIZE> <SAMPLEFREQUENCY> <SIGNALFREQUENCY>\n";
        return 1;
    }

    std::size_t SIZE = std::atoi(argv[1]);
    Aquila::FrequencyType sampleFrequency = std::atoi(argv[2]);
    Aquila::FrequencyType signalFrequency = std::atoi(argv[3]);

    // generate test signal (a sine wave)
    double dt = 1.0 / sampleFrequency;
    double* x = new double[SIZE];
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        x[i] = 64 * std::sin(2 * M_PI * signalFrequency * i * dt);
    }

    // calculate the FFT and magnitude spectrum
    Aquila::ComplexType* spectrum = new Aquila::ComplexType[SIZE];
    Aquila::OouraFft fft(SIZE);
    fft.fft(x, spectrum);
    double* absSpectrum = new double[SIZE / 2];
    for (std::size_t i = 0; i < SIZE / 2; ++i)
    {
        absSpectrum[i] = std::abs(spectrum[i]);
    }
    // "iterator" pointing to highest spectrum peak
    // the pointer difference is the number of spectral peak
    double* peakPos = std::max_element(absSpectrum, absSpectrum + SIZE / 2);
    std::cout << std::distance(absSpectrum, peakPos);

    delete [] absSpectrum;
    delete [] spectrum;
    delete [] x;

    return 0;
}
