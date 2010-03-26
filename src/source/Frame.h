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
#include <iterator>
#include <vector>

namespace Aquila
{
	/**
     * An ecapsulation of a single frame of the signal.
     *
     * The Frame class wraps a signal frame (short fragment of a signal).
     * Frame samples are accessed by STL-compatible iterators.
	 */
    class AQUILA_EXPORT Frame
	{
	public:
	    class iterator;
	    friend class iterator;

	    /**
         * Iterator class enabling frame data access.
	     *
         * It is a forward iterator with a range from the first sample in the
         * frame to "one past last" sample.
	     */
        class AQUILA_EXPORT iterator :
            public std::iterator<std::forward_iterator_tag, int>
	    {
	    public:
            /**
             * Creates a frame iterator associated with a given frame.
             *
             * @param fr pointer to a frame on which the iterator will work
             * @param index sample index (in the global data source!)
             */
            explicit iterator(const Frame* fr, unsigned int index = 0):
                frame(fr), idx(index)
            {
            }

	        iterator& operator=(const iterator& other);
	        bool operator==(const iterator& other) const;
	        bool operator!=(const iterator& other) const;
	        iterator& operator++();
	        iterator operator++(int);
	        const int& operator*() const;

	        unsigned int getPosition() const;

	    private:
            const Frame* frame;
	        unsigned int idx;
	    };


		Frame(const std::vector<int>& source, unsigned int indexBegin,
		        unsigned int indexEnd);

        /**
         * Returns the frame length.
         *
         * @return frame length as a number of samples
         */
        unsigned int getLength() const { return m_end - m_begin; }

        /**
         * Returns an iterator pointing to the first sample in the frame.
         */
        iterator begin() const { return iterator(this, m_begin); }

        /**
         * Returns an iterator pointing to the "one past last" sample.
         */
        iterator end() const { return iterator(this, m_end + 1); }

	private:
        /**
         * First and last sample of this frame in the data array/vector.
         */
        unsigned int m_begin, m_end;

        /**
         * A const reference to signal source (audio channel).
         */
        const std::vector<int>& sourceChannel;
	};
}

#endif // FRAME_H
