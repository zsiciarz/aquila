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
    WaveFile::WaveFile(const std::string& filename):
        frameLength(0), overlap(0.66)
    {
        load(filename);
    }

    /**
     * Creates the WaveFile object.
     *
     * By default, no frame division will be performed after loading data
     * from file.
     * If frameLengthMs is given and is not 0, all calls to load() will
     * perform frame division.
     * Adjacent frames can overlap each other, the default overlap length
     * is 66% of frame length.
     *
     * @param frameLengthMs frame length in milliseconds (0 - dont use frames)
     * @param frameOverlap overlap between adjacent frames
     */
    WaveFile::WaveFile(unsigned int frameLengthMs, double frameOverlap):
        frameLength(frameLengthMs), overlap(frameOverlap)
    {
    }

    /**
     * Deletes the WaveFile object.
     *
     * If there was any frame division, deletes all frames.
     */
    WaveFile::~WaveFile()
    {
        if (frameLength != 0)
            clearFrames();
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
        if (frameLength != 0)
            clearFrames();

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
        if (frameLength != 0)
            divideFrames(LChTab);
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
     * Saves selected frame span to a new file.
     *
     * @param filename where to save frames
     * @param begin number of the first frame
     * @param end number of the last frame
     * @throw FormatException not allowed to save 8b-mono files
     */
    void WaveFile::saveFrames(const std::string& filename, unsigned int begin,
            unsigned int end) const
    {
        if (1 == hdr.Channels && 8 == hdr.BitsPerSamp)
        {
            throw FormatException("Save error: 8-bit mono files are not supported yet!");
        }
        unsigned int samples = getSamplesPerFrame();

        // calculate the boundaries of a fragment of the source channel
        // which correspond to given frame numbers
        unsigned int startPos = static_cast<unsigned int>(
                begin * samples * (1 - overlap));
        unsigned int endPos = static_cast<unsigned int>(
                (end + 1) * samples * (1 - overlap) + samples * overlap);
        if (endPos > LChTab.size())
            endPos = LChTab.size();

        // number of data bytes in the resulting wave file
        unsigned int waveSize = (endPos - startPos) * hdr.BytesPerSamp;

        // prepare a new header and write it to file stream
        WaveHeader newHdr;
        std::strncpy(newHdr.RIFF, hdr.RIFF, 4);
        newHdr.DataLength = waveSize + sizeof(WaveHeader);
        std::strncpy(newHdr.WAVE, hdr.WAVE, 4);
        std::strncpy(newHdr.fmt_, hdr.fmt_, 4);
        newHdr.SubBlockLength = hdr.SubBlockLength;
        newHdr.formatTag = hdr.formatTag;
        newHdr.Channels = hdr.Channels;
        newHdr.SampFreq = hdr.SampFreq;
        newHdr.BytesPerSec = hdr.BytesPerSec;
        newHdr.BytesPerSamp = hdr.BytesPerSamp;
        newHdr.BitsPerSamp = hdr.BitsPerSamp;
        std::strncpy(newHdr.data, hdr.data, 4);
        newHdr.WaveSize = waveSize;

        std::fstream fs;
        fs.open(filename.c_str(), std::ios::out | std::ios::binary);
        fs.write((char*)&newHdr, sizeof(WaveHeader));

        // convert our data from source channels to a temporary buffer
        short* data = new short[waveSize/2];
        for (unsigned int i = startPos, di = 0; i < endPos; ++i, ++di)
        {
            if (16 == hdr.BitsPerSamp)
            {
                if (2 == hdr.Channels)
                {
                    data[2*di] = LChTab[i];
                    data[2*di+1] = RChTab[i];
                }
                else
                {
                    data[di] = LChTab[i];
                }
            }
            else
            {
                if (2 == hdr.Channels)
                {
                    data[di/2] = ((RChTab[i] + 128) << 8) | (LChTab[i] + 128);
                }
            }
        }

        // write the raw data to file and clean the buffer
        fs.write((char*)data, waveSize);
        fs.close();
        delete [] data;
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
            frameLength = newFrameLength;

        overlap = newOverlap;

        clearFrames();
        divideFrames(LChTab);
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
     *
     * @param source const reference to source chanel
     */
    void WaveFile::divideFrames(const WaveFile::ChannelType& source)
    {
        // calculate how many samples are in the part of the frame
        // which does NOT overlap, and use that value to find out
        // total number of frames; also set zero-padded length
        samplesPerFrame = getSamplesPerFrame();
        unsigned int samplesPerNonOverlap =
            static_cast<unsigned int>(samplesPerFrame * (1 - overlap));
        unsigned int framesCount =
            (hdr.WaveSize / hdr.BytesPerSamp) / samplesPerNonOverlap;
        unsigned int power =
            static_cast<unsigned int>(std::log(double(samplesPerFrame))/log(2.0));
        zeroPaddedLength = 1 << (power + 1);

        frames.reserve(framesCount);
        unsigned int indexBegin = 0, indexEnd = 0;
        for (unsigned int i = 0, size = source.size(); i < framesCount; ++i)
        {
            // calculate frame boundaries in the source channel
            // when frame end exceeds channel size, break out
            indexBegin = i * samplesPerNonOverlap;
            indexEnd = indexBegin + samplesPerFrame;
            if (indexEnd < size)
                frames.push_back(new Frame(*this, indexBegin, indexEnd));
            else
                break;
        }
    }

    /**
     * Deletes all frame objects and clears the vector.
     */
    void WaveFile::clearFrames()
    {
        for(unsigned int i = 0, size = frames.size(); i < size; ++i)
        {
            delete frames[i];
        }

        frames.clear();
    }
}



