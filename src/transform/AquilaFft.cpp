/**
 * @file AquilaFft.cpp
 *
 * A custom implementation of FFT radix-2 algorithm.
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

#include "AquilaFft.h"
#include <algorithm>
#include <cmath>

namespace Aquila
{
    /**
     * Complex unit.
     */
    const ComplexType AquilaFft::j(0, 1);

    /**
     * Applies the transformation to the signal.
     *
     * @param x input signal
     * @param spectrum output specturm
     */
    void AquilaFft::fft(double x[], ComplexType spectrum[])
    {
        // bit-reversing the samples - a requirement of radix-2
        // instead of reversing in place, put the samples to result array
        unsigned int a = 1, b = 0, c = 0;
        std::copy(x, x + N, spectrum);
        for (b = 1; b < N; ++b)
        {
            if (b < a)
            {
                spectrum[a - 1] = x[b - 1];
                spectrum[b - 1] = x[a - 1];
            }
            c = N / 2;
            while (c < a)
            {
                a -= c;
                c /= 2;
            }
            a += c;
        }

        // FFT calculation using "butterflies"
        // code ported from Matlab, based on book by Tomasz P. Zieliñski

        // FFT stages count
        unsigned int numStages = static_cast<unsigned int>(
                std::log(double(N)) / LN_2);

        // L = 2^k - DFT block length and offset
        // M = 2^(k-1) - butterflies per block, butterfly width
        // p - butterfly index
        // q - block index
        // r - index of sample in butterfly
        // Wi - starting value of Fourier base coefficient
        unsigned int L = 0, M = 0, p = 0, q = 0, r = 0;
        ComplexType Wi(0, 0), Temp(0, 0);

        ComplexType** Wi_cache = getCachedFftWi(numStages);

        // iterate over the stages
        for (unsigned int k = 1; k <= numStages; ++k)
        {
            L = 1 << k;
            M = 1 << (k - 1);
            Wi = Wi_cache[k][0];

            // iterate over butterflies
            for (p = 1; p <= M; ++p)
            {
                // iterate over blocks
                for (q = p; q <= N; q += L)
                {
                    r = q + M;
                    Temp = spectrum[r - 1] * Wi;
                    spectrum[r - 1] = spectrum[q - 1] - Temp;
                    spectrum[q - 1] = spectrum[q - 1] + Temp;
                }
                Wi = Wi_cache[k][p];
            }
        }
    }

    /**
     * Returns a table of Wi (twiddle factors) stored in cache.
     *
     * @param numStages the FFT stages count
     * @return pointer to an array of pointers to arrays of complex numbers
     */
    ComplexType** AquilaFft::getCachedFftWi(unsigned int numStages)
    {
        fftWiCacheKeyType key = numStages;
        // cache hit, return immediately
        if (fftWiCache.find(key) != fftWiCache.end())
        {
            return fftWiCache[key];
        }

        // nothing in cache, calculate twiddle factors
        ComplexType** Wi = new ComplexType*[numStages+1];
        for (unsigned int k = 1; k <= numStages; ++k)
        {
            // L = 2^k - DFT block length and offset
            // M = 2^(k-1) - butterflies per block, butterfly width
            // W - Fourier base multiplying factor
            unsigned int L = 1 << k;
            unsigned int M = 1 << (k-1);
            ComplexType W = exp((-j) * 2.0 * M_PI / double(L));
            Wi[k] = new ComplexType[M+1];
            Wi[k][0] = ComplexType(1.0);
            for (unsigned int p = 1; p <= M; ++p)
            {
                Wi[k][p] = Wi[k][p-1] * W;
            }
        }

        // store in cache and return
        fftWiCache[key] = Wi;

        return Wi;
    }

    /**
     * Clears the twiddle factor cache.
     */
    void AquilaFft::clearFftWiCache()
    {
        fftWiCacheType::const_iterator it;
        for (it = fftWiCache.begin(); it != fftWiCache.end(); it++)
        {
            ComplexType** c = it->second;
            unsigned int numStages = it->first;
            for (unsigned int i = 1; i <= numStages; ++i)
            {
                delete [] c[i];
            }

            delete [] c;
        }
    }
}
