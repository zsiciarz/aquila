#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/transform/Mfcc.h"
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

    Aquila::Mfcc mfcc(input.getSamplesCount());
    auto mfccValues = mfcc.calculate(input);
    std::cout << "MFCC coefficients: \n";
    std::copy(
        std::begin(mfccValues),
        std::end(mfccValues),
        std::ostream_iterator<double>(std::cout, " ")
    );
    std::cout << "\n";

    return 0;
}
