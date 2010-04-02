/**
 * @file FramesCollection.h
 *
 * A lightweight wrapper for a vector of Frames.
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

#ifndef FRAMESCOLLECTION_H
#define FRAMESCOLLECTION_H

#include "../global.h"
#include "Frame.h"
#include "SignalSource.h"
#include <cstddef>
#include <vector>

namespace Aquila
{
    class AQUILA_EXPORT FramesCollection
    {
    public:
        FramesCollection();

        void divideFrames(const SignalSource& source,
                          unsigned int samplesPerFrame,
                          unsigned int samplesPerOverlap);
        void clear();

    private:
        /**
         * Frames vector.
         */
        std::vector<Frame*> m_frames;
    };
}

#endif // FRAMESCOLLECTION_H
