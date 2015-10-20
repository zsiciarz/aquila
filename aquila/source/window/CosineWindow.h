/**
 * @file CosineWindow.h
 *
 * Cosine window.
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

#ifndef COSINEWINDOW_H
#define COSINEWINDOW_H

#include "../../global.h"
#include "../SignalSource.h"
#include <cstddef>

namespace Aquila
{
    /**
     * Cosine window.
     */
    class AQUILA_EXPORT CosineWindow : public SignalSource
    {
    public:
        CosineWindow(std::size_t size);
    };
}

#endif // COSINEWINDOW_H
