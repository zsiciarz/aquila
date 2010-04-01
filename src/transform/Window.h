/**
 * @file WaveFile.h
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
 * @date 2007-2010
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 0.5.4
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "../global.h"
#include <cstddef>
#include <map>
#include <utility>
#include <vector>

namespace Aquila
{
	/**
     * Possible window functions.
	 */
    enum WindowType {WIN_RECT, WIN_HAMMING, WIN_HANN, WIN_BARLETT, WIN_BLACKMAN,
                     WIN_FLATTOP };


	/**
     * Class defining different window types as static methods.
     *
     * Windows are cached with window type combined with its length
     * as a key. It is an efficient way to reduce calls to math functions.
	 */
    class AQUILA_EXPORT Window
	{
	public:
        /**
         *  Window vector type.
         */
        typedef std::vector<double> WindowDataType;

        Window(WindowType type, unsigned int length);

        const WindowDataType& getWindowData();

		static double apply(WindowType type, unsigned int n, unsigned int N);

	private:
        /**
         * Window function type.
         */
        WindowType m_type;

        /**
         * Window length.
         */
        std::size_t m_length;

        /**
         * Key type for the window cache.
         */
        typedef std::pair<WindowType, unsigned int> KeyType;

        /**
         * Cache type.
         */
        typedef std::map<KeyType, WindowDataType> WindowsCacheType;

        /**
         * Window cache implemented as a static map.
         */
        static WindowsCacheType windowsCache;

        static void createWindow(const KeyType& windowKey);

        static double hamming(unsigned int n, unsigned int N);
        static double hann(unsigned int n, unsigned int N);
        static double barlett(unsigned int n, unsigned int N);
        static double blackman(unsigned int n, unsigned int N);
        static double flattop(unsigned int n, unsigned int N);

        /**
         * Private functor class for window generation.
         */
        class WinGenerator
        {
        public:
            WinGenerator(WindowType type, unsigned int N);
            double operator()() const;

        private:
            /**
             * Window size.
             */
            unsigned int _N;

            /**
             * Pointer to window function.
             */
            double (*windowMethod)(unsigned int, unsigned int);
        };
	};
}

#endif
