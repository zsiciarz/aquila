/**
 * @file WaveFile.cpp
 *
 * WAVE file handling as a signal source.
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
 * @since 0.0.7
 */

#include "WaveFile.h"
#include "WaveFileHandler.h"

namespace Aquila
{
    /**
     * Creates a wave file object and immediately loads data from file.
     *
     * @param filename full path to .wav file
     * @param channel LEFT or RIGHT (the default setting is LEFT)
     */
    WaveFile::WaveFile(const std::string& filename, StereoChannel channel):
        SignalSource()
    {
        load(filename, channel);
    }

    /**
     * Deletes the WaveFile object.
     */
    WaveFile::~WaveFile()
    {
    }

    /**
     * Reads the header and channel data from given .wav file.
     *
     * Data are read into a temporary buffer and then converted to
     * channel sample vectors. If source is a mono recording, samples
     * are written to left channel.
     *
     * To improve performance, no format checking is performed.
     *
     * @param file full path to .wav file
     */
    void WaveFile::load(const std::string& file, StereoChannel channel)
    {
        filename = file;
        m_data.clear();
        ChannelType dummy;
        WaveFileHandler handler(file);
        if (LEFT == channel)
        {
            handler.readHeaderAndChannels(hdr, m_data, dummy);
        }
        else
        {
            handler.readHeaderAndChannels(hdr, dummy, m_data);
        }
        m_sampleFrequency = hdr.SampFreq;
    }

    /**
     * Saves the given signal source as a .wav file.
     *
     * @param source source of the data to save
     * @param filename destination file
     */
    void WaveFile::save(const SignalSource& source, const std::string& filename)
    {
        WaveFileHandler handler(filename);
        handler.save(source);
    }

    /**
     * Returns the audio recording length
     *
     * @return recording length in milliseconds
     */
    unsigned int WaveFile::getAudioLength() const
    {
        return static_cast<unsigned int>(hdr.WaveSize /
                static_cast<double>(hdr.BytesPerSec) * 1000);
    }
}
