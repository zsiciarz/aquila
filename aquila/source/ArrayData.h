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
            SignalSource(sampleFrequency)
        {
            m_data.assign(data, data + dataLength);
        }
    };
}

#endif // ARRAYDATA_H
