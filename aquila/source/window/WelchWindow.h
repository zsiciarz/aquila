/**
 * @file WelchWindow.h
 *
 * Welch window.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2014
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#ifndef WELCHWINDOW_H
#define WELCHWINDOW_H

#include "../../global.h"
#include "../SignalSource.h"
#include <cstddef>

namespace Aquila
{
    /**
     * Welch window.
     */
    class AQUILA_EXPORT WelchWindow : public SignalSource
    {
    public:
        WelchWindow(std::size_t size);
    };
}

#endif // WELCHWINDOW_H
