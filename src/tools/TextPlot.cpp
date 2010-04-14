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
    TextPlot::TextPlot(const std::string &title, std::ostream &out):
        m_title(title), m_out(out)
    {
    }

    /**
     * Plots all data from a given source.
     *
     * @param source data source
     */
    void TextPlot::plot(const SignalSource& source)
    {
        PlotMatrixType plot(source.length());
        doPlot(plot, source.begin(), source.end());
    }

    /**
     * "Draws" the plot to the output stream.
     *
     * @param plot internal plot data
     */
    void TextPlot::drawPlotMatrix(const PlotMatrixType &plot)
    {
        const std::size_t length = plot.size();
        const std::size_t columnSize = plot[0].size();

        m_out << "\n" << m_title << "\n";
        // output the plot data, flushing only at the end
        for (unsigned int y = 0; y < columnSize; ++y)
        {
            for (unsigned int x = 0; x < length; ++x)
            {
                m_out << plot[x][y];
            }
            m_out << "\n";
        }
        m_out.flush();
    }
}
