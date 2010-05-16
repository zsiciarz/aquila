/**
 * @file Fft.h
 *
 * An interface for FFT calculation classes.
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

#ifndef FFT_H
#define FFT_H

#include "../global.h"
#include <cstddef>
#include <boost/noncopyable.hpp>

namespace Aquila
{
    /**
     * An interface for FFT calculation classes.
     */
    class AQUILA_EXPORT Fft : boost::noncopyable
    {
    public:
        /**
         * Initializes the transform for a given input length.
         *
         * @param length input signal size (usually a power of 2)
         */
        Fft(std::size_t length): N(length)
        {
        }

        /**
         * Destroys the transform object - does nothing.
         */
        virtual ~Fft()
        {
        }

        /**
         * Applies the transformation to the signal.
         *
         * @param x input signal
         * @param spectrum output spectrum
         */
        virtual void fft(double x[], ComplexType spectrum[]) = 0;

        /**
         * Applies the inverse transform to the spectrum.
         *
         * @param spectrum input spectrum
         * @param x output signal
         */
        virtual void ifft(ComplexType spectrum[], double x[]) = 0;

    protected:
        /**
         * Signal and spectrum length.
         */
        std::size_t N;
    };
}

#endif // FFT_H
