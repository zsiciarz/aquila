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
        std::size_t length() const { return getSamplesCount(); }
    };
}

#endif // SIGNALSOURCE_H
