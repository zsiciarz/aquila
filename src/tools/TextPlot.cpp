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
#include <algorithm>
#include <vector>

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
        m_out << m_title << std::endl;

        const SampleType max = *std::max_element(source.begin(), source.end());
        const SampleType min = *std::min_element(source.begin(), source.end());
        const SampleType range = max - min;
        const std::size_t length = source.length();
        const std::size_t columnSize = 10; // todo: make this customizable

        std::vector< std::vector<char> > plot(length);
        for (std::size_t xPos = 0; xPos < length; ++xPos)
        {
            plot[xPos].resize(columnSize, ' ');
            double normalizedValue = (source.sample(xPos) - min) /
                                      static_cast<double>(range);
            std::size_t yPos = columnSize -
                               static_cast<std::size_t>(columnSize * normalizedValue);
            // bound the value so it stays within vector dimension
            if (yPos >= columnSize)
                yPos = columnSize - 1;
            plot[xPos][yPos] = '*';
        }

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
