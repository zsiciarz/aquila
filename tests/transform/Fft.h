/**
 * Test templates for various FFT implementations.
 */

#ifndef AQUILA_TEST_FFT_H
#define AQUILA_TEST_FFT_H

#include "aquila/global.h"
#include "aquila/transform/AquilaFft.h"
#include "UnitTest++/UnitTest++.h"
#include <algorithm>
#include <cstddef>

/**
 * Test that spectrum of a delta signal is constant.
 */
template <typename FftType, std::size_t SIZE>
void deltaSpectrumTest()
{
    // delta signal: 1, 0, 0, 0...
    Aquila::SampleType testArray[SIZE] = {0};
    testArray[0] = 1;

    FftType fft(SIZE);
    Aquila::SpectrumType spectrum = fft.fft(testArray);

    double absSpectrum[SIZE] = {0};
    std::transform(std::begin(spectrum), std::end(spectrum), absSpectrum, [] (Aquila::ComplexType x) {
        return std::abs(x);
    });

    double expected[SIZE];
    std::fill_n(expected, SIZE, 1.0);
    CHECK_ARRAY_CLOSE(expected, absSpectrum, SIZE, 0.0001);
}

/**
 * Test that spectrum of a constant signal is a scaled delta.
 */
template <typename FftType, std::size_t SIZE>
void constSpectrumTest()
{
    Aquila::SampleType testArray[SIZE];
    std::fill_n(testArray, SIZE, 1.0);

    FftType fft(SIZE);
    Aquila::SpectrumType spectrum = fft.fft(testArray);

    double absSpectrum[SIZE] = {0};
    std::transform(std::begin(spectrum), std::end(spectrum), absSpectrum, [] (Aquila::ComplexType x) {
        return std::abs(x);
    });

    // expecting a delta scaled by SIZE
    double expected[SIZE] = {0};
    expected[0] = SIZE * 1.0;
    CHECK_ARRAY_CLOSE(expected, absSpectrum, SIZE, 0.0001);
}

/**
 * Test that inverse of a delta spectrum is a constant signal.
 */
template <typename FftType, std::size_t SIZE>
void deltaInverseTest()
{
    Aquila::SpectrumType spectrum(SIZE, 0);
    spectrum[0] = SIZE * 1.0;
    Aquila::SampleType output[SIZE];
    FftType fft(SIZE);
    fft.ifft(spectrum, output);

    double expected[SIZE];
    std::fill_n(expected, SIZE, 1.0);
    CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
}

/**
 * Test that inverse of a constant spectrum is a delta signal.
 */
template <typename FftType, std::size_t SIZE>
void constInverseTest()
{
    Aquila::SpectrumType spectrum(SIZE, 1.0);
    Aquila::SampleType output[SIZE];
    FftType fft(SIZE);
    fft.ifft(spectrum, output);

    double expected[SIZE] = {0};
    expected[0] = 1.0;
    CHECK_ARRAY_CLOSE(expected, output, SIZE, 0.0001);
}

/**
 * Test that IFFT(FFT(x)) == x.
 */
template <typename FftType, std::size_t SIZE>
void identityTest()
{
    Aquila::SampleType testArray[SIZE];
    std::fill_n(testArray, SIZE, 1.0);

    FftType fft(SIZE);
    Aquila::SpectrumType spectrum = fft.fft(testArray);

    Aquila::SampleType output[SIZE];
    fft.ifft(spectrum, output);

    CHECK_ARRAY_CLOSE(testArray, output, SIZE, 0.0001);
}

#endif // AQUILA_TEST_FFT_H
