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
#include "FftFactory.h"
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
         * Constructor creates the FFT object to reuse between calculations.
         *
         * @param inputSize input length (common to all inputs)
         */
        Mfcc(std::size_t inputSize):
            m_inputSize(inputSize), m_fft(FftFactory::getFft(inputSize))
        {
        }

        std::vector<double> calculate(const SignalSource& source,
                                      std::size_t numFeatures = 12);

    private:
        /**
         * Number of samples in each processed input.
         */
        const std::size_t m_inputSize;

        /**
         * FFT calculator.
         */
        std::shared_ptr<Fft> m_fft;
    };
}

#endif // MFCC_H
