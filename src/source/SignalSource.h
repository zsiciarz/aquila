/**
 * @file SignalSource.h
 *
 * An abstract signal source interface.
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

#ifndef SIGNALSOURCE_H
#define SIGNALSOURCE_H

#include "../global.h"
#include <cstddef>
#include <iterator>

namespace Aquila
{
    class AQUILA_EXPORT SignalSource
    {
    public:
        SignalSource();
        virtual ~SignalSource() {}
        virtual FrequencyType getSampleFrequency() const = 0;
        virtual unsigned short getBitsPerSample() const = 0;
        virtual std::size_t getSamplesCount() const = 0;
        virtual int sample(std::size_t position) const = 0;
        std::size_t length() const
        {
            return getSamplesCount();
        }

        class iterator;

        /**
         * Returns an iterator pointing to the first sample in the source.
         */
        iterator begin() const
        {
            return iterator(this, 0);
        }

        /**
         * Returns an iterator pointing to the "one past last" sample.
         */
        iterator end() const
        {
            return iterator(this, getSamplesCount());
        }

        /**
         * Iterator class enabling sequential data access.
         *
         * It is a forward iterator with a range from the first sample in the
         * source to "one past last" sample.
         */
        class AQUILA_EXPORT iterator :
            public std::iterator<std::forward_iterator_tag, int>
        {
        public:
            /**
             * Creates an iterator associated with a given source.
             *
             * @param source pointer to a source on which the iterator will work
             * @param index index of the sample in the source
             */
            explicit iterator(const SignalSource* source, unsigned int i = 0):
                m_source(source), idx(i)
            {
            }

            /**
             * Assigns another iterator in a memberwise fashion.
             *
             * @param other right-hand value iterator
             * @return reference to self
             */
            iterator& operator=(const iterator& other)
            {
                m_source = other.m_source;
                idx = other.idx;
                return (*this);
            }

            /**
             * Compares two iterators for equality.
             *
             * Iterators are equal only when they belong to the same source
             * and point to the same sample in the source.
             *
             * @param other right-hand value iterator
             * @return true, if the iterators are equal
             */
            bool operator==(const iterator& other) const
            {
                return m_source == other.m_source && idx == other.idx;
            }

            /**
             * Compares two iterators for inequality.
             *
             * Negates the equality operator.
             *
             * @param other right-hand value iterator
             * @return true only when the iterators are not equal
             */
            bool operator!=(const iterator& other) const
            {
                return !operator==(other);
            }

            /**
             * Moves the iterator one sample to the right (prefix version).
             *
             * @return reference to self
             */
            iterator& operator++()
            {
                ++idx;
                return (*this);
            }

            /**
             * Moves the iterator one sample to the right (postfix version).
             *
             * @return a copy of self before incrementing
             */
            iterator operator++(int)
            {
                iterator tmp(*this);
                ++(*this);
                return tmp;
            }

            /**
             * Dereferences the iterator.
             *
             * @return signal sample value.
             */
            const int operator*() const
            {
                return m_source->sample(idx);
            }

            /**
             * Returns the distance from the beginning of the source.
             *
             * @return number of samples between beginning and current position
             */
            std::size_t getPosition() const
            {
                return idx;
            }

        private:
            /**
             * Signal source - as a pointer - the iterators must be copyable.
             */
            const SignalSource* m_source;

            /**
             * Iterator's position in the source.
             */
            std::size_t idx;
        };
    };
}

#endif // SIGNALSOURCE_H
