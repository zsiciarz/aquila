/**
 * @file ArrayData.h
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
 * @date 2007-2013
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#ifndef ARRAYDATA_H
#define ARRAYDATA_H

#include "../global.h"
#include "SignalSource.h"
#include <algorithm>
#include <cstddef>

namespace Aquila
{
    /**
     * Wrapper around a C-style array.
     *
     * This is a very simple wrapper for a traditional C-style array,
     * providing a way to use the arrays in Aquila DSP algorithms which
     * require SignalSource-derived objects. The class is a template,
     * parametrized by the type of numeric data stored in the array.
     *
     * A plain array does not carry any information about sample rate,
     * so ArrayData's constructor expects sample frequency as its third
     * argument.
     *
     * ArrayData doesn't take ownership of the original array. However,
     * if the data is of some different type than SampleType, it is copied
     * and converted to SampleType, and that copy is owned by object.
     * If the data is an array of SampleType values, no copying occurs
     * and the data are immediately accessible.
     *
     * ArrayData also lacks any array bounds checking in the sample()
     * method - for performance reasons. (A future version may conditionally
     * check the position argument.)
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
            m_data(0), m_dataLength(dataLength), m_owns(false),
            m_sampleFrequency(sampleFrequency)
        {
            convertArray(data);
        }

        /**
         * Releases the memory if the object owns its data.
         */
        ~ArrayData()
        {
            if (m_owns)
                delete [] m_data;
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
            return 8 * sizeof(SampleType);
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
         * Doesn't check that the position is valid array index.
         *
         * @param position sample position (from 0 to array length - 1)
         * @return sample value
         */
        virtual SampleType sample(std::size_t position) const
        {
            return m_data[position];
        }

        /**
         * Returns sample data (read-only!) as a const C-style array.
         *
         * This is the simplest implementation as it just exposes the data
         * member.
         *
         * @return C-style array containing sample data
         */
        virtual const SampleType* toArray() const
        {
            return m_data;
        }

    private:
        /**
         * Pointer to the data array - not owned by the object!
         */
        SampleType* m_data;

        /**
         * Array size.
         */
        std::size_t m_dataLength;

        /**
         * Whether the object owns its data table.
         */
        bool m_owns;

        /**
         * Sample frequency of the data.
         */
        FrequencyType m_sampleFrequency;

        void convertArray(Numeric* data);
    };

    /**
     * Converts a general numeric array to SampleType array.
     *
     * Converted data are owned by the object and are freed in the destructor.
     *
     * @param data array to convert
     */
    template <typename Numeric>
    void ArrayData<Numeric>::convertArray(Numeric* data)
    {
        m_data = new SampleType[m_dataLength];
        m_owns = true;
        std::copy(data, data + m_dataLength, m_data);
    }

    template <>
    void ArrayData<SampleType>::convertArray(SampleType* data);
}

#endif // ARRAYDATA_H
