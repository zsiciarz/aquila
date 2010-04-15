/**
 * @file Generator.h
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

#ifndef GENERATOR_H
#define GENERATOR_H

#include "../SignalSource.h"
#include "../../global.h"
#include <cstddef>
#include <vector>

namespace Aquila
{
    class Generator : public SignalSource
    {
    public:
        /**
         * Creates the generator object.
         *
         * @param sampleFrequency sample frequency of the data in array
         * @param bufferSize the size of an internal sample buffer
         */
        Generator(FrequencyType sampleFrequency, std::size_t bufferSize);

        /**
         * Returns signal sample frequency.
         *
         * @return sample frequency in Hz
         */
        virtual FrequencyType getSampleFrequency() const
        {
            return m_sampleFrequency;
        }

        /**
         * Returns number of bits per sample
         *
         * @return 8 * number of bytes per sample
         */
        virtual unsigned short getBitsPerSample() const
        {
            return 8 * sizeof(SampleType);
        }

        /**
         * Returns the length of generator's internal buffer.
         *
         * @return samples count
         */
        virtual std::size_t getSamplesCount() const
        {
            return m_buffer.size();
        }

        /**
         * Returns sample value at a given position in the buffer.
         *
         * @param position sample position (from 0 to buffer length - 1)
         * @return sample value
         */
        virtual SampleType sample(std::size_t position) const
        {
            return m_buffer[position];
        }

        /**
         * Sets frequency of the generated signal.
         *
         * @param frequency signal frequency
         * @return the current object for fluent interface
         */
        Generator& setFrequency(FrequencyType frequency)
        {
            m_frequency = frequency;

            return *this;
        }

        /**
         * Sets amplitude of the generated signal.
         *
         * @param amplitude signal amplitude
         * @return the current object for fluent interface
         */
        Generator& setAmplitude(SampleType amplitude)
        {
            m_amplitude = amplitude;

            return *this;
        }

        virtual void generate() = 0;

    protected:
        /**
         * Sample frequency of the data.
         */
        FrequencyType m_sampleFrequency;

        /**
         * Internal data buffer.
         */
        std::vector<SampleType> m_buffer;

        /**
         * Frequency of the generated signal (not always used).
         */
        FrequencyType m_frequency;

        /**
         * Amplitude of the generated signal (not always used).
         */
        SampleType m_amplitude;
    };
}

#endif // GENERATOR_H
