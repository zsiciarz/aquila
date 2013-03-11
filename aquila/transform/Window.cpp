/**
 * @file Window.cpp
 *
 * Window functions.
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
 * @since 0.5.4
 */

#include "Window.h"
#include <algorithm>
#include <cmath>

namespace Aquila
{
    Window::WindowsCacheType Window::windowsCache;

    /**
     * Creates a Window object of given type and size.
     *
     * @param type which window function to use
     * @param length how many samples to create
     */
    Window::Window(WindowType type, unsigned int length):
        m_type(type), m_length(length)
    {
    }

    /**
     * Returns window data vector.
     *
     * @return window data for current object, may be retrieved from cache
     */
    const Window::WindowDataType& Window::getData()
    {
        KeyType key = std::make_pair(m_type, m_length);
        if (windowsCache.find(key) == windowsCache.end())
            createWindow(key);

        return windowsCache[key];
    }

    /**
     * Generates new window vector for a given type and size.
     *
     * Rectangular window is handled separately because it does not need
     * any additional computation.
     *
     * @param windowKey a cache key
     */
    void Window::createWindow(const KeyType& windowKey)
	{
        WindowType type = windowKey.first;
        unsigned int N = windowKey.second;

        if (type != WIN_RECT)
        {
            WindowDataType data;
            data.reserve(N);
            std::generate_n(std::back_inserter(data), N, WinGenerator(type, N));
            windowsCache[windowKey] = data;
        }
        else
        {
            WindowDataType data(N, 1.0);
            windowsCache[windowKey] = data;
        }
	}

    /**
     * Hamming window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::hamming(unsigned int n, unsigned int N)
    {
        return 0.53836 - 0.46164 * std::cos(2.0 * M_PI * n / double(N - 1));
    }

    /**
     * Hann window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::hann(unsigned int n, unsigned int N)
    {
        return 0.5 * (1.0 - std::cos(2.0 * M_PI * n / double(N - 1)));
    }

    /**
     * Barlett (triangular) window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::barlett(unsigned int n, unsigned int N)
    {
        return 1.0 - (2.0 * std::fabs(n - (N - 1) / 2.0)) / (double(N - 1));
    }

    /**
     * Blackman window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::blackman(unsigned int n, unsigned int N)
    {
        return 0.42 - 0.5 * std::cos(2.0 * M_PI * n / double(N - 1)) +
                0.08 * std::cos(4.0 * M_PI * n / double(N - 1));
    }

    /**
     * Flat-top window.
     *
     * @param n sample position
     * @param N window size
     * @return n-th window sample value
     */
    double Window::flattop(unsigned int n, unsigned int N)
    {
        return 1.0 - 1.93 * std::cos(2.0 * M_PI * n / double(N - 1)) +
                1.29 * std::cos(4.0 * M_PI * n / double(N - 1)) -
                0.388 * std::cos(6.0 * M_PI * n / double(N - 1)) +
                0.0322 * std::cos(8.0 * M_PI * n / double(N - 1));
    }

    /**
     * Creates the generator functor.
     *
     * @param type window function type
     * @param N window size
     */
    Window::WinGenerator::WinGenerator(WindowType type, unsigned int N):
        N_(N), n(0)
    {
        switch (type)
        {
        case WIN_HAMMING:
            windowMethod = &Window::hamming;
            break;
        case WIN_HANN:
            windowMethod = &Window::hann;
            break;
        case WIN_BARLETT:
            windowMethod = &Window::barlett;
            break;
        case WIN_BLACKMAN:
            windowMethod = &Window::blackman;
            break;
        case WIN_FLATTOP:
            windowMethod = &Window::flattop;
            break;
        default:
            windowMethod = &Window::hamming;
            break;
        }
    }

    /**
     * Calculates next window sample.
     *
     * Each consecutive call will advance position by one sample.
     *
     * @return window sample
     */
    double Window::WinGenerator::operator()() const
    {
        return windowMethod(n++, N_);
    }
}
