/**
 * @file TextPlot.cpp
 *
 * A simple console-based data plotter.
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

#include "TextPlot.h"

namespace Aquila
{
    /**
     * Creates the plot object.
     *
     * @param title plot title (optional, default is "Data plot")
     */
    TextPlot::TextPlot(const std::string &title):
        m_title(title)
    {
    }
}
