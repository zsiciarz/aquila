/**
 * @file SignalSource.cpp
 *
 * A base signal source class.
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

#include "SignalSource.h"
#include <algorithm>
#include <cmath>
#include <numeric>


namespace Aquila
{
    /**
     * Calculates mean value of the signal.
     *
     * @param source signal source
     * @return signal mean
     */
    double mean(const SignalSource& source)
    {
        double sum = std::accumulate(std::begin(source), std::end(source), 0.0);
        return sum / source.getSamplesCount();
    }

    /**
     * Calculates energy of the signal.
     *
     * @param source signal source
     * @return signal energy
     */
    double energy(const SignalSource& source)
    {
        return std::accumulate(
            std::begin(source),
            std::end(source),
            0.0,
            [] (double acc, SampleType value) {
                return acc + value * value;
            }
        );
    }

    /**
     * Calculates power of the signal.
     *
     * @param source signal source
     * @return signal power
     */
    double power(const SignalSource& source)
    {
        return energy(source) / source.getSamplesCount();
    }

    /**
     * Calculates Euclidean (L2) norm of the signal.
     *
     * @param source signal source
     * @return norm
     */
    double norm(const SignalSource& source)
    {
        return std::sqrt(energy(source));
    }

    /**
     * Calculates root mean square level of the signal.
     *
     * @param source signal source
     * @return RMS level
     */
    double rms(const SignalSource& source)
    {
        return std::sqrt(power(source));
    }
}
