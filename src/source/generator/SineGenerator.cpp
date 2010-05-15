/**
 * @file SineGenerator.cpp
 *
 * Sine wave generator.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2010
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "SineGenerator.h"
#include <cmath>
#include <iostream>

namespace Aquila
{
    /**
     * Creates the generator object.
     *
     * @param sampleFrequency sample frequency of the signal
     * @param bufferSize internal buffer length
     */
    SineGenerator::SineGenerator(FrequencyType sampleFrequency,
                                 std::size_t bufferSize):
        Generator(sampleFrequency, bufferSize)
    {
    }

    /**
     * Fills the buffer with generated sine samples.
     */
    void SineGenerator::generate()
    {
        double normalizedFrequency = m_frequency /
                                     static_cast<double>(m_sampleFrequency);
        for (std::size_t i = 0, size = m_buffer.size(); i < size; ++i)
        {
            m_buffer[i] = m_amplitude *
                          std::sin(2.0 * M_PI * normalizedFrequency * i);
        }
    }
}
