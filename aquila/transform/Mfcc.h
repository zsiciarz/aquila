/**
 * @file Mfcc.h
 *
 * Calculation of MFCC signal features.
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

#ifndef MFCC_H
#define MFCC_H

#include "../global.h"
#include <cstddef>
#include <vector>

namespace Aquila
{
    class SignalSource;

    /**
     * The Mfcc class implements calculation of MFCC features from input signal.
     *
     * MFCC coefficients are commonly used in speech recognition.
     */
    class AQUILA_EXPORT Mfcc
    {
    public:
        /**
         * No-op default constructor.
         */
        Mfcc()
        {
        }

        std::vector<double> calculate(const SignalSource& source,
                                      std::size_t numFeatures = 12);
    };
}

#endif // MFCC_H
