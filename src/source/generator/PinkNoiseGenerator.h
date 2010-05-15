/**
 * @file PinkNoiseGenerator.h
 *
 * Pink noise generator.
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

#ifndef PINKNOISEGENERATOR_H
#define PINKNOISEGENERATOR_H

#include "Generator.h"

namespace Aquila
{
    /**
     * Pink noise generator.
     */
    class PinkNoiseGenerator : public Generator
    {
    public:
        PinkNoiseGenerator(FrequencyType sampleFrequency);

        virtual void generate(std::size_t samplesCount);

    private:
        double pinkSample();
        enum { whiteSamplesNum = 20 };
        double whiteSamples[whiteSamplesNum];
        int key;
        int maxKey;
    };
}

#endif // PINKNOISEGENERATOR_H
