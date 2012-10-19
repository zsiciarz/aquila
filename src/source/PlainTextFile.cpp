/**
 * @file PlainTextFile.cpp
 *
 * Reading samples from a plain text file.
 *
 * This file is part of the Aquila DSP library.
 * Aquila is free software, licensed under the MIT/X11 License. A copy of
 * the license is provided with the library in the LICENSE file.
 *
 * @package Aquila
 * @version 3.0.0-dev
 * @author Zbigniew Siciarz
 * @date 2007-2012
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 3.0.0
 */

#include "PlainTextFile.h"
#include <algorithm>
#include <fstream>
#include <iterator>

namespace Aquila
{
    /**
     * Creates the data source.
     *
     * @param filename full path to .txt file
     * @param sampleFrequency sample frequency of the data in file
     */
    PlainTextFile::PlainTextFile(std::string filename,
                                 FrequencyType sampleFrequency):
        m_sampleFrequency(sampleFrequency)
    {
        std::fstream fs;
        fs.open(filename.c_str(), std::ios::in);
        std::copy(std::istream_iterator<SampleType>(fs),
                  std::istream_iterator<SampleType>(),
                  std::back_inserter(m_data));
        fs.close();
    }
}
