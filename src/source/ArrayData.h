/**
 * @file Frame.h
 *
 * Wrapper around a C-style array.
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

#ifndef ARRAYDATA_H
#define ARRAYDATA_H

#include "../global.h"
#include "SignalSource.h"
#include <cstddef>

namespace Aquila
{
    /**
     * Wrapper around a C-style array.
     */
    template <typename Numeric = SampleType>
    class AQUILA_EXPORT ArrayData : public SignalSource
    {
    public:
        /**
         * Creates the array-based source.
         *
         * @param data pointer to an array of samples (numeric values)
         * @param dataLength length of the array
         * @param sampleFrequency sample frequency of the data in array
         */
        ArrayData(Numeric* data, std::size_t dataLength,
                  FrequencyType sampleFrequency):
            m_data(data), m_dataLength(dataLength),
            m_sampleFrequency(sampleFrequency)
        {
        }

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
            return 8 * sizeof(Numeric);
        }

        /**
         * Returns number of samples in the array.
         *
         * @return length of the wrapped array
         */
        virtual std::size_t getSamplesCount() const
        {
            return m_dataLength;
        }

        /**
         * Returns sample value at a given position in the array.
         *
         * @param position sample position (from 0 to array length - 1)
         * @return sample value
         */
        virtual SampleType sample(std::size_t position) const
        {
            return static_cast<SampleType>(m_data[position]);
        }

    private:
        /**
         * Pointer to the data array - not owned by the object!
         */
        Numeric* m_data;

        /**
         * Array size.
         */
        std::size_t m_dataLength;

        /**
         * Sample frequency of the data.
         */
        FrequencyType m_sampleFrequency;
    };
}

#endif // ARRAYDATA_H
