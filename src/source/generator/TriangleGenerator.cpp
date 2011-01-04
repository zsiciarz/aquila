/**
 * @file TriangleGenerator.cpp
 *
 * Triangle (and sawtooth) wave generator.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2011
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "TriangleGenerator.h"
#include <cmath>

namespace Aquila
{
    /**
     * Creates the generator object.
     *
     * @param sampleFrequency sample frequency of the signal
     */
    TriangleGenerator::TriangleGenerator(FrequencyType sampleFrequency):
        Generator(sampleFrequency), m_width(1.0)
    {
    }

    /**
     * Fills the buffer with generated triangle wave samples.
     *
     * The default behaviour is to generate a sawtooth wave. To change that
     * to a triangle wave, call setWidth() with some value between 0 and 1.
     *
     * @param samplesCount how many samples to generate
     */
    void TriangleGenerator::generate(std::size_t samplesCount)
    {
        m_buffer.resize(samplesCount);
        std::size_t samplesPerPeriod = static_cast<std::size_t>(
            m_sampleFrequency / static_cast<double>(m_frequency));
        std::size_t risingLength = static_cast<std::size_t>(m_width *
                                                            samplesPerPeriod);

        double risingIncrement =  2.0 * m_amplitude / risingLength;
        double fallingDecrement = 2.0 * m_amplitude /
                                  (samplesPerPeriod - risingLength);

        for (std::size_t i = 0; i < samplesCount; ++i)
        {
            std::size_t t = i % samplesPerPeriod;
            if (t < risingLength)
            {
                m_buffer[i] = -m_amplitude + t * risingIncrement;
            }
            else
            {
                m_buffer[i] = m_amplitude -
                              (t - risingLength) * fallingDecrement;
            }
        }
    }
}
