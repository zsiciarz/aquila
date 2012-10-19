#include "aquila/global.h"
#include "aquila/transform/OouraFft.h"
#include <unittestpp.h>
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iterator>

unsigned int findPeak(std::size_t arraySize,
                      Aquila::FrequencyType sampleFrequency,
                      Aquila::FrequencyType signalFrequency)
{
    // generate test signal (a sine wave)
    double dt = 1.0 / sampleFrequency;
    double* x = new double[arraySize];
    for (std::size_t i = 0; i < arraySize; ++i)
    {
        x[i] = 64 * std::sin(2 * M_PI * signalFrequency * i * dt);
    }

    // calculate the FFT and magnitude spectrum
    Aquila::ComplexType* spectrum = new Aquila::ComplexType[arraySize];
    Aquila::OouraFft fft(arraySize);
    fft.fft(x, spectrum);
    double* absSpectrum = new double[arraySize / 2];
    for (std::size_t i = 0; i < arraySize / 2; ++i)
    {
        absSpectrum[i] = std::abs(spectrum[i]);
    }
    // "iterator" pointing to highest spectrum peak
    // the pointer difference is the number of spectral peak
    double* peakPos = std::max_element(absSpectrum, absSpectrum + arraySize / 2);
    unsigned int distance = std::distance(absSpectrum, peakPos);

    delete [] absSpectrum;
    delete [] spectrum;
    delete [] x;

    return distance;
}

SUITE(Fft)
{
    TEST(SinePeakDetect1)
    {
        unsigned int peakPosition = findPeak(64, 8000, 1000);
        CHECK_EQUAL(8, peakPosition);
    }

    TEST(SinePeakDetect2)
    {
        unsigned int peakPosition = findPeak(64, 8000, 2000);
        CHECK_EQUAL(16, peakPosition);
    }

    TEST(SinePeakDetect3)
    {
        unsigned int peakPosition = findPeak(64, 8000, 3999);
        CHECK_EQUAL(31, peakPosition);
    }

    TEST(SinePeakDetect4)
    {
        unsigned int peakPosition = findPeak(64, 8000, 1);
        CHECK_EQUAL(0, peakPosition);
    }

    TEST(SinePeakDetect5)
    {
        unsigned int peakPosition = findPeak(1024, 8000, 1000);
        CHECK_EQUAL(128, peakPosition);
    }

    TEST(SinePeakDetect6)
    {
        unsigned int peakPosition = findPeak(1024, 8000, 2000);
        CHECK_EQUAL(256, peakPosition);
    }

    TEST(SinePeakDetect7)
    {
        unsigned int peakPosition = findPeak(1024, 44100, 1000);
        CHECK_EQUAL(23, peakPosition);
    }

    TEST(SinePeakDetect8)
    {
        unsigned int peakPosition = findPeak(1024, 44100, 2000);
        CHECK_EQUAL(46, peakPosition);
    }

    TEST(SinePeakDetect9)
    {
        unsigned int peakPosition = findPeak(1024, 44100, 4567);
        CHECK_EQUAL(106, peakPosition);
    }

    TEST(SinePeakDetect10)
    {
        unsigned int peakPosition = findPeak(1024, 44100, 10000);
        CHECK_EQUAL(232, peakPosition);
    }

    TEST(SinePeakDetect11)
    {
        unsigned int peakPosition = findPeak(1024, 44100, 15000);
        CHECK_EQUAL(348, peakPosition);
    }

    TEST(SinePeakDetect12)
    {
        unsigned int peakPosition = findPeak(1024, 44100, 21204);
        CHECK_EQUAL(492, peakPosition);
    }
}
