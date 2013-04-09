#include "aquila/global.h"
#include "aquila/filter/MelFilterBank.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/Dct.h"
#include "aquila/transform/FftFactory.h"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>

int main(int argc, char *argv[])
{
    const std::size_t SIZE = 1024;
    const Aquila::FrequencyType sampleFrequency = 1024;

    Aquila::SineGenerator input(sampleFrequency);
    input.setAmplitude(5).setFrequency(64).generate(SIZE);

    // FFT
    auto fft = Aquila::FftFactory::getFft(SIZE);
    auto spectrum = fft->fft(input.toArray());

    // Mel-frequency filtering
    Aquila::MelFilterBank bank(sampleFrequency, SIZE);
    auto filterOutput = bank.applyAll(spectrum);

    // DCT
    Aquila::Dct dct;
    auto mfcc = dct.dct(filterOutput, 12);

    std::cout << "MFCC coefficients: \n";
    std::copy(
        std::begin(mfcc),
        std::end(mfcc),
        std::ostream_iterator<double>(std::cout, " ")
    );
    std::cout << "\n";

    return 0;
}
