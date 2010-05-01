/**
 * @file OouraFft.cpp
 *
 * A wrapper for the FFT algorithm found in Ooura mathematical packages.
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

#include "OouraFft.h"
#include <cmath>
#include <boost/static_assert.hpp>

namespace Aquila
{
    /**
     * Initializes the transform for a given input length.
     *
     * Prepares the work area for Ooura's algorithm.
     *
     * @param length input signal size (usually a power of 2)
     */
    OouraFft::OouraFft(std::size_t length):
        Fft(length)
    {
        // according to the description: "length of ip >= 2+sqrt(n)"
        ip = new int[static_cast<std::size_t>(
                     2 + std::sqrt(static_cast<double>(N)))];
        ip[0] = 0;
        w = new double[N / 2];
    }

    /**
     * Destroys the transform object and cleans up working area.
     */
    OouraFft::~OouraFft()
    {
        delete [] w;
        delete [] ip;
    }

    /**
     * Applies the transformation to the signal.
     *
     * @param x input signal
     * @param spectrum output spectrum
     */
    void OouraFft::fft(double x[], ComplexType spectrum[])
    {
        // We assume here that a complex<double> has the same
        // representation in memory as two consecutive doubles
        BOOST_STATIC_ASSERT(sizeof(ComplexType[2]) == sizeof(double[4]));
        double* a = reinterpret_cast<double*>(spectrum);

        // copying input data to even elements of the array (real values)
        for (size_t i = 0; i < N; ++i)
        {
            a[2*i] = x[i];
        }

        // let's call the C function from Ooura's package
        cdft(2*N, -1, a, ip, w);
    }

    /**
     * Applies the inverse transform to the spectrum.
     *
     * @param spectrum input spectrum
     * @param x output signal
     */
    void OouraFft::ifft(ComplexType spectrum[], double x[])
    {
        // We assume here that a complex<double> has the same
        // representation in memory as two consecutive doubles
        BOOST_STATIC_ASSERT(sizeof(ComplexType[2]) == sizeof(double[4]));
        double* a = reinterpret_cast<double*>(spectrum);

        // Ooura's function
        cdft(2*N, 1, a, ip, w);

        // copy the data to the double array and scale it
        for (size_t i = 0; i < N; ++i)
        {
            x[i] = a[2*i] / static_cast<double>(N);
        }
    }
}
