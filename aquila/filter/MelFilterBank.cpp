/**
 * @file MelFilterBank.cpp
 *
 * A bank of number of Mel frequency triangular filters.
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

#include "MelFilterBank.h"

namespace Aquila
{
    /**
     * Creates all the filters in the bank.
     *
     * @param sampleFrequency sample frequency in Hz
     * @param melFilterWidth filter width in Mel frequency scale
     * @param N spectrum size of each filter
     */
    MelFilterBank::MelFilterBank(FrequencyType sampleFrequency,
                                 std::size_t length,
                                 std::size_t melFilterWidth
                                 ):
        m_sampleFrequency(sampleFrequency), N(length)
    {
        filters.reserve(MELFILTERS);
        for (unsigned int i = 0; i < MELFILTERS; ++i)
        {
            filters.push_back(MelFilter(m_sampleFrequency));
            filters[i].createFilter(i, melFilterWidth, N);
        }
    }

    /**
     * Processes frame spectrum through all filters.
     *
     * @param frameSpectrum frame spectrum
     * @return vector of results (one value per each filter)
     */
    std::vector<double> MelFilterBank::applyAll(const SpectrumType& frameSpectrum) const
    {
        std::vector<double> output(MELFILTERS, 0.0);
        for (unsigned int i = 0; i < MELFILTERS; ++i)
        {
            output[i] = filters[i].apply(frameSpectrum);
        }
        return output;
    }
}
