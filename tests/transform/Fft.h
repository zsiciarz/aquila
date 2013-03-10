/**
 * Test templates for various FFT implementations.
 */

#ifndef AQUILA_TEST_FFT_H
#define AQUILA_TEST_FFT_H

#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/transform/AquilaFft.h"
#include <unittestpp.h>
#include <algorithm>
#include <cstddef>

/**
 * Test that spectrum of a delta signal is constant.
 */
template <typename FftType, std::size_t SIZE = 8>
void deltaSpectrumTest()
{
    Aquila::SampleType testArray[SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);
    FftType fft(SIZE);
    Aquila::SpectrumType spectrum = fft.fft(data.toArray());

    double absSpectrum[SIZE] = {0};
    std::transform(std::begin(spectrum), std::end(spectrum), absSpectrum, [] (Aquila::ComplexType x) {
        return std::abs(x);
    });

    double expected[SIZE] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    CHECK_ARRAY_CLOSE(expected, absSpectrum, SIZE, 0.0001);
}

/**
 * Test that spectrum of a constant signal is a scaled delta.
 */
template <typename FftType, std::size_t SIZE = 8>
void constSpectrumTest()
{
    Aquila::SampleType testArray[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);
    FftType fft(SIZE);
    Aquila::SpectrumType spectrum = fft.fft(data.toArray());

    double absSpectrum[SIZE] = {0};
    std::transform(std::begin(spectrum), std::end(spectrum), absSpectrum, [] (Aquila::ComplexType x) {
        return std::abs(x);
    });

    double expected[SIZE] = {SIZE * 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    CHECK_ARRAY_CLOSE(expected, absSpectrum, SIZE, 0.0001);
}

/**
 * Test that inverse of a delta spectrum is a constant signal.
 */
template <typename FftType, std::size_t SIZE = 8>
void deltaInverseTest()
{
    Aquila::ComplexType s[SIZE] = {SIZE, 0, 0, 0, 0, 0, 0, 0};
    Aquila::SpectrumType spectrum(s, s + SIZE);
    Aquila::SampleType output[SIZE];
    FftType fft(SIZE);
    fft.ifft(spectrum, output);

    double expected[SIZE] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
}

/**
 * Test that inverse of a constant spectrum is a delta signal.
 */
template <typename FftType, std::size_t SIZE = 8>
void constInverseTest()
{
    Aquila::ComplexType s[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};
    Aquila::SpectrumType spectrum(s, s + SIZE);
    Aquila::SampleType output[SIZE];
    FftType fft(SIZE);
    fft.ifft(spectrum, output);

    double expected[SIZE] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
}

#endif // AQUILA_TEST_FFT_H
