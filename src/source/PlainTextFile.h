/**
 * @file PlainTextFile.h
 *
 * Reading samples from a plain text file.
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

#ifndef PLAINTEXTFILE_H
#define PLAINTEXTFILE_H

#include "../global.h"
#include "SignalSource.h"
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

namespace Aquila
{
    /**
     * Plain text file, where each sample is in new line.
     *
     * No headers are allowed in the file, only a simple list of numbers
     * will work at the moment.
     *
     * Any numeric type will be converted on the fly to SampleType. Sample
     * rate must be known prior to opening the file as the constructor expects
     * sample frequency as its second argument.
     */
    class AQUILA_EXPORT PlainTextFile : public SignalSource
    {
    public:
        PlainTextFile(std::string filename, FrequencyType sampleFrequency);

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
         * Returns number of samples in the file.
         *
         * @return length of samples vector
         */
        virtual std::size_t getSamplesCount() const
        {
            return m_data.size();
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
         * Uses the same vector trick as WaveFile.
         *
         * @return C-style array containing sample data
         */
        virtual const SampleType* toArray() const
        {
            return &(m_data)[0];
        }

    private:
        /**
         * Actual sample data.
         */
        std::vector<SampleType> m_data;

        /**
         * Sample frequency of the data.
         */
        FrequencyType m_sampleFrequency;
    };
}

#endif // PLAINTEXTFILE_H
