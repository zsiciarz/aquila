/**
 * @file Frame.h
 *
 * Handling signal frames.
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
 * @since 0.2.2
 */

#ifndef FRAME_H
#define FRAME_H

#include "../global.h"
#include "SignalSource.h"
#include <algorithm>

namespace Aquila
{
	/**
     * An ecapsulation of a single frame of the signal.
     *
     * The Frame class wraps a signal frame (short fragment of a signal).
     * It is a lightweight object which can be copied by value.
     * Frame samples are accessed by STL-compatible iterators.
	 */
    class AQUILA_EXPORT Frame : public SignalSource
	{
	public:
        Frame(const SignalSource& source, unsigned int indexBegin,
		        unsigned int indexEnd);
        Frame(const Frame& other);
        Frame& operator=(const Frame& other);

        /**
         * Returns the frame length.
         *
         * @return frame length as a number of samples
         */
        virtual std::size_t getSamplesCount() const
        {
            return m_end - m_begin;
        }

        /**
         * Returns signal sample frequency.
         *
         * @return sample frequency of the original signal
         */
        virtual FrequencyType getSampleFrequency() const
        {
            return m_source->getSampleFrequency();
        }

        /**
         * Returns number of bits per sample.
         */
        virtual unsigned short getBitsPerSample() const
        {
            return m_source->getBitsPerSample();
        }

        /**
         * Gives access to frame samples, indexed from 0 to length()-1.
         *
         * @param position index of the sample in the frame
         */
        virtual int sample(std::size_t position) const
        {
            return m_source->sample(m_begin + position);
        }

	private:
        /**
         * First and last sample of this frame in the data array/vector.
         */
        unsigned int m_begin, m_end;

        /**
         * A pointer to constant original source (eg. a WAVE file).
         */
        const SignalSource* m_source;

        /**
         * Swaps the frame with another one - cannot not throw!
         *
         * @param other reference to swapped frame
         */
        void swap(Frame& other) throw()
        {
            std::swap(m_begin,  other.m_begin);
            std::swap(m_end,    other.m_end);
            std::swap(m_source, other.m_source);
        }
	};
}

#endif // FRAME_H
