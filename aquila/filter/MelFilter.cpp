/**
 * @file MelFilter.cpp
 *
 * Triangular filters in Mel frequency scale.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2013
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 0.3.3
 */

#include "MelFilter.h"

namespace Aquila
{
    /**
     * Creates the filter and sets sample frequency.
     *
     * @param sampleFrequency sample frequency in Hz
     */
    MelFilter::MelFilter(FrequencyType sampleFrequency):
        m_sampleFrequency(sampleFrequency)
    {
    }

    /**
     * Designs the Mel filter and creates triangular spectrum.
     *
     * @param filterNum which filter in a sequence it is
     * @param melFilterWidth filter width in Mel scale (eg. 200)
     * @param N filter spectrum size (must be the same as filtered spectrum)
     */
    void MelFilter::createFilter(unsigned short filterNum,
                                 std::size_t melFilterWidth, std::size_t N)
    {
        // calculate frequencies in Mel scale
        FrequencyType melMinFreq = filterNum * melFilterWidth / 2.0;
        FrequencyType melCenterFreq = melMinFreq + melFilterWidth / 2.0;
        FrequencyType melMaxFreq = melMinFreq + melFilterWidth;

        // convert frequencies to linear scale
        FrequencyType minFreq = melToLinear(melMinFreq);
        FrequencyType centerFreq = melToLinear(melCenterFreq);
        FrequencyType maxFreq = melToLinear(melMaxFreq);

        // generate filter spectrum in linear scale
        generateFilterSpectrum(minFreq, centerFreq, maxFreq, N);
    }

    /**
     * Returns a single value computed by multiplying signal spectrum with
     * Mel filter spectrum and summing all the products.
     *
     * @param dataSpectrum complex signal spectrum
     * @return dot product of the spectra
     */
    double MelFilter::apply(const SpectrumType& dataSpectrum) const
    {
        double value = 0.0;
        const std::size_t N = dataSpectrum.size();
        // iteration over first half of the spectrum
        for (unsigned int i = 0; i < N / 2 - 1; ++i)
        {
            value += std::abs(dataSpectrum[i]) * m_spectrum[i];
        }
        return value;
    }

    void MelFilter::generateFilterSpectrum(FrequencyType minFreq,
                                           FrequencyType centerFreq,
                                           FrequencyType maxFreq, std::size_t N)
    {
        m_spectrum.clear();
        m_spectrum.resize(N);

        // scale the frequencies according to spectrum size
        minFreq *= N / m_sampleFrequency;
        centerFreq *= N / m_sampleFrequency;
        maxFreq *= N / m_sampleFrequency;

        double max = 1.0, value;

        for (unsigned int k = 0; k < N; ++k)
        {
            // outside the triangle spectrum values are 0
            if (k < minFreq || k > maxFreq)
            {
                value = 0.0;
            }
            else
            {
                // in the triangle on the ascending slope
                if (k < centerFreq)
                {
                    value = k * max / (centerFreq - minFreq) -
                        minFreq * max / (centerFreq - minFreq);
                }
                // in the triangle on the descending slope
                else
                {
                    value = k * max / (centerFreq - maxFreq) -
                        maxFreq * max / (centerFreq - maxFreq);
                }
            }

            m_spectrum[k] = value;
        }
    }
}
