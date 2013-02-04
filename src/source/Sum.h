/**
 * @file Sum.h
 *
 * A compound source - sum of two signals.
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
 * @since 3.0.0
 */

#ifndef SUM_H
#define SUM_H

#include "../global.h"
#include "SignalSource.h"
#include <algorithm>
#include <cstddef>
#include <vector>

namespace Aquila
{
    /**
     * A signal source representing addition of two signals.
     *
     * @todo other general algebraic operations
     */
    class AQUILA_EXPORT Sum : public SignalSource
    {
    public:
        Sum(const SignalSource& source1, const SignalSource& source2):
            m_source1(source1), m_source2(source2)
        {
            std::size_t maxLength = std::min(source1.length(), source2.length());
            m_data.reserve(maxLength);
            for (std::size_t i = 0; i < maxLength; ++i)
            {
                m_data.push_back(source1.sample(i) + source2.sample(i));
            }
        }

        /**
         * Returns signal sample frequency.
         *
         * @return sample frequency in Hz
         */
        virtual FrequencyType getSampleFrequency() const
        {
            return m_source1.getSampleFrequency();
        }

        /**
         * Returns number of bits per sample
         *
         * @return 8 * number of bytes per sample
         */
        virtual unsigned short getBitsPerSample() const
        {
            return m_source1.getBitsPerSample();
        }

        /**
         * Returns number of samples.
         *
         * @return length of the wrapped array
         */
        virtual std::size_t getSamplesCount() const
        {
            return m_source1.getBitsPerSample();
        }

        /**
         * Returns sum of sample values at a given position in both input sources.
         *
         * @param position sample position
         * @return sample value
         */
        virtual SampleType sample(std::size_t position) const
        {
            return m_data[position];
        }

        /**
         * Returns sample data (read-only!) as a const C-style array.
         *
         * Uses the same vector trick as WaveFile.
         *
         * @return C-style array containing sample data
         */
        virtual const SampleType* toArray() const
        {
            return &(m_data)[0];
        }

    private:
        const SignalSource& m_source1;
        const SignalSource& m_source2;

        /**
         * Actual sample data.
         */
        std::vector<SampleType> m_data;
    };
}

#endif // SUM_H
