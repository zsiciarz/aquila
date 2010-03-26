/**
 * @file Frame.cpp
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

#include "Frame.h"

namespace Aquila
{
    /**
     * Assigns another iterator in a memberwise fashion.
     *
     * @param other right-hand value iterator
     * @return reference to self
     */
    Frame::iterator& Frame::iterator::operator=(const Frame::iterator& other)
    {
        frame = other.frame;
        idx = other.idx;
        return (*this);
    }

    /**
     * Compares two iterators for equality.
     *
     * Iterators are equal only when they belong to the same frame and point
     * to the same sample in the source.
     *
     * @param other right-hand value iterator
     * @return true, if the iterators are equal
     */
    bool Frame::iterator::operator==(const Frame::iterator& other) const
    {
        return frame == other.frame && idx == other.idx;
    }

    /**
     * Compares two iterators for inequality.
     *
     * Negates the equality operator.
     *
     * @param other right-hand value iterator
     * @return true only when the iterators are not equal
     */
    bool Frame::iterator::operator!=(const Frame::iterator& other) const
    {
        return !operator==(other);
    }

    /**
     * Moves the iterator one sample to the right (prefix version).
     *
     * @return reference to self
     */
    Frame::iterator& Frame::iterator::operator++()
    {
        ++idx;
        return (*this);
    }

    /**
     * Moves the iterator one sample to the right (postfix version).
     *
     * @return a copy of self before incrementing
     */
    Frame::iterator Frame::iterator::operator++(int)
    {
        iterator tmp(*this);
        ++(*this);
        return tmp;
    }

    /**
     * Dereferences the iterator.
     *
     * @return a const reference to signal sample value.
     */
    const int& Frame::iterator::operator*() const
    {
        return frame->sourceChannel[idx];
    }

    /**
     * Returns the distance between iterator and the beginning of the frame.
     *
     * @return number of samples between beginning and current position
     */
    unsigned int Frame::iterator::getPosition() const
    {
        return idx - frame->m_begin;
    }


    /**
     * Creates the frame object - sets signal source and frame boundaries.
     *
     * Frame should not change original data, so the source is a const
     * reference.
     *
     * @param source const reference to signal source
     * @param indexBegin position of first sample of this frame in the source
     * @param indexEnd position of last sample of this frame in the source
     */
	Frame::Frame(const std::vector<int>& source, unsigned int indexBegin,
	        unsigned int indexEnd):
		m_begin(indexBegin), m_end(indexEnd), sourceChannel(source)
	{
	}
}
