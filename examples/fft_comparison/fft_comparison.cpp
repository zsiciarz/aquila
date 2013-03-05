#include "aquila/global.h"
#include "aquila/source/generator/WhiteNoiseGenerator.h"
#include "aquila/transform/Dft.h"
#include "aquila/transform/AquilaFft.h"
#include "aquila/transform/OouraFft.h"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>

double difference(Aquila::SpectrumType correct, Aquila::SpectrumType checked)
{
    double val = 0.0;
    for (std::size_t i = 0; i < correct.size(); ++i)
    {
        val += std::abs(correct[i] - checked[i]);
    }

    return std::abs(val);
}

int main()
{
    const Aquila::FrequencyType sampleFrequency = 8000.0;

    std::cout << "    N    |    Aquila FFT    |     Ooura      \n"
                 "---------+------------------+----------------\n";
    for (int power = 1; power <= 10; ++power)
    {
        std::size_t N = 1 << power;
        Aquila::WhiteNoiseGenerator source(sampleFrequency);
        source.setAmplitude(1024).generate(N);

        // reference spectrum calculated using DFT
        Aquila::Dft dft(N);
        Aquila::SpectrumType dftSpectrum = dft.fft(source.toArray());

        // Aquila custom algorithm
        Aquila::AquilaFft myFft(N);
        Aquila::SpectrumType aquilaSpectrum = myFft.fft(source.toArray());

        // Ooura algorithm
        Aquila::OouraFft oouraFft(N);
        Aquila::SpectrumType oouraSpectrum = oouraFft.fft(source.toArray());

        std::cout << "  " << std::left << std::setw(7) << N <<
                     "|  " << std::setw(16) <<
                     difference(dftSpectrum, aquilaSpectrum) <<
                     "|  " << std::setw(16) <<
                     difference(dftSpectrum, oouraSpectrum) << "\n";
    }

    return 0;
}
