#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/transform/Dft.h"
#include <unittestpp.h>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>


SUITE(Dft)
{
    TEST(Delta)
    {
        const std::size_t SIZE = 8;
        Aquila::SampleType testArray[SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};
        Aquila::ArrayData<> data(testArray, SIZE, 22050);
        Aquila::Dft fft(SIZE);
        Aquila::SpectrumType spectrum = fft.fft(data.toArray());

        double absSpectrum[SIZE] = {0};
        std::transform(std::begin(spectrum), std::end(spectrum), absSpectrum, [] (Aquila::ComplexType x) {
            return std::abs(x);
        });

        double expected[SIZE] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        CHECK_ARRAY_CLOSE(expected, absSpectrum, SIZE, 0.0001);
    }

    TEST(ConstSignal)
    {
        const std::size_t SIZE = 8;
        Aquila::SampleType testArray[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};
        Aquila::ArrayData<> data(testArray, SIZE, 22050);
        Aquila::Dft fft(SIZE);
        Aquila::SpectrumType spectrum = fft.fft(data.toArray());

        double absSpectrum[SIZE] = {0};
        std::transform(std::begin(spectrum), std::end(spectrum), absSpectrum, [] (Aquila::ComplexType x) {
            return std::abs(x);
        });

        double expected[SIZE] = {SIZE * 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        CHECK_ARRAY_CLOSE(expected, absSpectrum, SIZE, 0.0001);
    }

    TEST(DeltaInverse)
    {
        const std::size_t SIZE = 8;
        Aquila::ComplexType spectrum[SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};
        Aquila::SampleType output[SIZE];
        Aquila::Dft fft(SIZE);
        fft.ifft(spectrum, output);

        double expected[SIZE] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
        CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
    }

    TEST(ConstInverse)
    {
        const std::size_t SIZE = 8;
        Aquila::ComplexType spectrum[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};
        Aquila::SampleType output[SIZE];
        Aquila::Dft fft(SIZE);
        fft.ifft(spectrum, output);

        double expected[SIZE] = {SIZE * 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
        CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
    }
}
