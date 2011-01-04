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
 * @date 2007-2011
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
     */
    WaveFile::WaveFile(const std::string& filename):
        m_frameLength(0), m_overlap(0.0), m_sourceChannel(LEFT)
    {
        load(filename);
    }

    /**
     * Deletes the WaveFile object.
     *
     * If there was any frame division, deletes all frames.
     */
    WaveFile::~WaveFile()
    {
        if (m_frameLength != 0)
            m_frames.clear();
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
    void WaveFile::load(const std::string& file)
    {
        filename = file;
        LChTab.clear();
        RChTab.clear();
        if (m_frameLength != 0)
            m_frames.clear();

        WaveFileHandler handler(file);
        handler.readHeaderAndChannels(hdr, LChTab, RChTab);

        // when we have the data, it is possible to create frames
        if (m_frameLength != 0)
            divideFrames();
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

    /**
     * Recalculates frame division, taking new arguments into consideration.
     *
     * @param newFrameLength new frame length in milliseconds
     * @param newOverlap new overlap value
     */
    void WaveFile::recalculate(unsigned int newFrameLength, double newOverlap)
    {
        if (newFrameLength != 0)
            m_frameLength = newFrameLength;

        m_overlap = newOverlap;

        m_frames.clear();
        divideFrames();
    }

    /**
     * Executes frame division, using overlap.
     *
     * Number of samples in an individual frame does not depend on the
     * overlap value. The overlap affects total number of frames.
     */
    void WaveFile::divideFrames()
    {
        // calculate how many bytes are in the the frame
        // based on frame length in milliseconds and number of bytes per sec
        unsigned int bytesPerFrame = static_cast<unsigned int>(
                hdr.BytesPerSec * m_frameLength / 1000.0);

        unsigned int samplesPerFrame = bytesPerFrame / hdr.BytesPerSamp;
        unsigned int samplesPerOverlap =
            static_cast<unsigned int>(samplesPerFrame * m_overlap);

        m_frames.divideFrames(*this, samplesPerFrame, samplesPerOverlap);
    }
}
