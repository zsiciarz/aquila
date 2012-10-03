/**
 * @file ArrayData.cpp
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
 * @date 2007-2012
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "ArrayData.h"

namespace Aquila
{
    /**
     * "Converts" a SampleType array to SampleType array.
     *
     * This specialization exists for faster handling of SampleType arrays of
     * data. It merely copies the pointer and does not make the ArrayData
     * object an owner of the data.
     *
     * @param data array to "convert"
     */
    template <>
    void ArrayData<SampleType>::convertArray(SampleType* data)
    {
        m_owns = false;
        m_data = data;
    }
}
