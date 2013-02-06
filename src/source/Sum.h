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
            SignalSource(source1.getSampleFrequency()),
            m_source1(source1), m_source2(source2)
        {
            std::size_t maxLength = std::min(source1.length(), source2.length());
            m_data.reserve(maxLength);
            for (std::size_t i = 0; i < maxLength; ++i)
            {
                m_data.push_back(source1.sample(i) + source2.sample(i));
            }
        }

    private:
        const SignalSource& m_source1;
        const SignalSource& m_source2;
    };
}

#endif // SUM_H
