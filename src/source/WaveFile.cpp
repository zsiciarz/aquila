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
 * @date 2007-2010
 * @license http://www.opensource.org/licenses/mit-license.php MIT
 * @since 0.0.7
 */

#include "WaveFile.h"
#include "../Exceptions.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <stdexcept>

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

        // first we read header from the stream
        // then as we know now the data size, we create a temporary
        // buffer and read raw data into that buffer
        std::fstream fs;
        fs.open(filename.c_str(), std::ios::in | std::ios::binary);
        loadHeader(fs);
        short* data = new short[hdr.WaveSize/2];
        loadRawData(fs, data, hdr.WaveSize);
        fs.close();

        // initialize data channels (using right channel only in stereo mode)
        unsigned int channelSize = hdr.WaveSize/hdr.BytesPerSamp;
        LChTab.resize(channelSize);
        if (2 == hdr.Channels)
            RChTab.resize(channelSize);

        // most important conversion happens right here
        if (16 == hdr.BitsPerSamp)
        {
            if (2 == hdr.Channels)
                convert16Stereo(data, channelSize);
            else
                convert16Mono(data, channelSize);
        }
        else
        {
            if (2 == hdr.Channels)
                convert8Stereo(data, channelSize);
            else
                convert8Mono(data, channelSize);
        }

        // clear the buffer
        delete [] data;

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
        // start with preparing a .wav file header
        boost::uint32_t frequency = static_cast<boost::uint32_t>(
            source.getSampleFrequency());
        // saving only mono files at the moment
        boost::uint16_t channels = 1;
        boost::uint16_t bitsPerSample = source.getBitsPerSample();
        // higher dynamic sources will be converted down to 16 bits per sample
        if (bitsPerSample > 16)
        {
            bitsPerSample = 16;
        }
        //boost::uint16_t bitsPerSample = source.getBitsPerSample();
        boost::uint32_t bytesPerSec = frequency * channels * bitsPerSample / 8;
        boost::uint32_t waveSize = source.getSamplesCount() * channels * bitsPerSample / 8;

        WaveHeader header;
        strncpy(header.RIFF, "RIFF", 4);
        // DataLength is the file size excluding first two header fields -
        // - RIFF and DataLength itself, which together take 8 bytes to store
        header.DataLength = waveSize + sizeof(WaveHeader) - 8;
        strncpy(header.WAVE, "WAVE", 4);
        strncpy(header.fmt_, "fmt ", 4);
        header.SubBlockLength = 16;
        header.formatTag = 1;
        header.Channels = channels;
        header.SampFreq = frequency;
        header.BytesPerSec = bytesPerSec;
        header.BytesPerSamp = header.Channels * bitsPerSample / 8;
        header.BitsPerSamp = bitsPerSample;
        strncpy(header.data, "data", 4);
        header.WaveSize = waveSize;

        std::ofstream fs;
        fs.open(filename.c_str(), std::ios::out | std::ios::binary);
        fs.write((const char*)(&header), sizeof(WaveHeader));

        short* data = new short[waveSize/2];
        if (16 == bitsPerSample)
        {
            save16Mono(source, data, waveSize/2);
        }
        else
        {
            save8Mono(source, data, waveSize/2);
        }
        fs.write((const char*)data, waveSize);

        delete [] data;
        fs.close();
    }

    /**
     * Saves the source data to an array of 16-bit values.
     *
     * @param source original signal source
     * @param data the data buffer to be written
     * @param dataSize size of the buffer
     */
    void WaveFile::save16Mono(const SignalSource& source, short* data, unsigned int dataSize)
    {
        for (unsigned int i = 0; i < dataSize; ++i)
        {
            short sample = static_cast<short>(source.sample(i));
            data[i] = sample;
        }
    }

    /**
     * Saves the source data to an array of 8-bit values encoded as shorts.
     *
     * @param source original signal source
     * @param data the data buffer to be written
     * @param dataSize size of the buffer
     */
    void WaveFile::save8Mono(const SignalSource& source, short* data, unsigned int dataSize)
    {
        for (unsigned int i = 0; i < dataSize; ++i)
        {
            unsigned char sample1 = static_cast<unsigned char>(source.sample(2 * i) + 128);
            unsigned char sample2 = static_cast<unsigned char>(source.sample(2 * i + 1) + 128);
            short hb = sample1, lb = sample2;
            data[i] = ((hb << 8) & 0xFF00) | (lb & 0x00FF);
        }
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
     * Reads file header into the struct.
     *
     * @param fs input file stream
     * @see WaveFile::hdr
     */
    void WaveFile::loadHeader(std::fstream& fs)
    {
        fs.read((char*)(&hdr), sizeof(WaveHeader));
    }

    /**
     * Reads raw data into the buffer.
     *
     * @param fs input file stream
     * @param buffer pointer to data array
     * @param bufferLength data buffer size
     */
    void WaveFile::loadRawData(std::fstream& fs, short* buffer,
            int bufferLength)
    {
        fs.read((char*)buffer, bufferLength);
    }

    /**
     * Converts the buffer to 16b stereo channels.
     *
     * @param data pointer to data buffer
     * @param channelSize length of the channels
     */
    void WaveFile::convert16Stereo(short *data, unsigned int channelSize)
    {
        for (unsigned int i = 0; i < channelSize; ++i)
        {
            LChTab[i] = data[2*i];
            RChTab[i] = data[2*i+1];
        }
    }

    /**
     * Converts the buffer to 16b mono channel.
     *
     * @param data pointer to data buffer
     * @param channelSize length of the channel
     */
    void WaveFile::convert16Mono(short *data, unsigned int channelSize)
    {
        for (unsigned int i = 0; i < channelSize; ++i)
        {
            LChTab[i] = data[i];
        }
    }

    /**
     * Converts the buffer to 8b stereo channels.
     *
     * @param data pointer to data buffer
     * @param channelSize length of the channels
     */
    void WaveFile::convert8Stereo(short *data, unsigned int channelSize)
    {
        // low byte and high byte of a 16b word
        unsigned char lb, hb;
        for (unsigned int i = 0; i < channelSize; ++i)
        {
            splitBytes(data[i/2], lb, hb);
            // left channel is in low byte, right in high
            // values are unipolar, so we move them by half
            // of the dynamic range
            LChTab[i] = lb-128;
            RChTab[i] = hb-128;
        }
    }

    /**
     * Converts the buffer to 8b mono channel.
     *
     * @param data pointer to data buffer
     * @param channelSize length of the channel
     */
    void WaveFile::convert8Mono(short *data, unsigned int channelSize)
    {
        // low byte and high byte of a 16b word
        unsigned char lb, hb;
        for (unsigned int i = 0; i < channelSize; ++i)
        {
            splitBytes(data[i/2], lb, hb);
            // only the left channel collects samples
            LChTab[i] = lb-128;
        }
    }

    /**
     * Splits a 16-b number to lower and upper byte.
     *
     * @param twoBytes number to split
     * @param lb lower byte (by reference)
     * @param hb upper byte (by reference)
     */
    void WaveFile::splitBytes(short twoBytes, unsigned char& lb,
            unsigned char& hb)
    {
        lb = twoBytes & 0x00FF;
        hb = (twoBytes >> 8) & 0x00FF;
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



