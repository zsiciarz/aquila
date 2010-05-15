/**
 * @file Generator.cpp
 *
 * An interface for signal generators.
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

#include "Generator.h"

namespace Aquila
{
    /**
     * Creates the generator object.
     *
     * @param sampleFrequency sample frequency of the signal
     * @param bufferSize internal buffer length
     */
    Generator::Generator(FrequencyType sampleFrequency, std::size_t bufferSize):
        m_sampleFrequency(sampleFrequency), m_buffer(bufferSize),
        m_frequency(0), m_amplitude(0)
    {
    }
}
