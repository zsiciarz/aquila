/**
 * @file SineGenerator.h
 *
 * Sine wave generator.
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

#ifndef SINEGENERATOR_H
#define SINEGENERATOR_H

#include "Generator.h"

namespace Aquila
{
    /**
     * Sine wave generator.
     */
    class AQUILA_EXPORT SineGenerator : public Generator
    {
    public:
        SineGenerator(FrequencyType sampleFrequency);

        virtual void generate(std::size_t samplesCount);

        /**
         * Sets phase shift of the generated sine wave.
         *
         * @param phase phase shift (0 < phase <= 1)
         * @return the current object for fluent interface
         */
        SineGenerator& setPhase(double phase)
        {
            m_phase = phase;

            return *this;
        }

    private:
        /**
         * Phase shift as a fraction of whole period (default = 0.0).
         */
        double m_phase;
    };
}

#endif // SINEGENERATOR_H
