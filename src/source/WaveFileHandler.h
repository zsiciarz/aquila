/**
 * @file WaveFileHandler.h
 *
 * A utility class to handle loading and saving of .wav files.
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

#ifndef WAVEFILEHANDLER_H
#define WAVEFILEHANDLER_H

#include "../global.h"
#include "SignalSource.h"
#include <boost/cstdint.hpp>
#include <cstddef>
#include <string>

namespace Aquila
{
    /**
     * Forward declaration to avoid including WaveFile.h header.
     */
    class WaveHeader;

    /**
     * A utility class to handle loading and saving of .wav files.
     */
    class AQUILA_EXPORT WaveFileHandler
    {
    public:
        WaveFileHandler();

        void save(const SignalSource& source, const std::string& filename);

        static void decode16bit(short* data, std::size_t channelSize);
        static void decode8bit(short* data, std::size_t channelSize);
        static void encode16bit(const SignalSource& source, short* data, std::size_t dataSize);
        static void encode8bit(const SignalSource& source, short* data, std::size_t dataSize);

    private:
        void createHeader(const SignalSource& source, WaveHeader& header);
    };
}

#endif // WAVEFILEHANDLER_H
