/**
 * @file WaveFileHandler.cpp
 *
 * A utility class to handle loading and saving of .wav files.
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

#include "WaveFileHandler.h"
#include "WaveFile.h"
#include <cstring>
#include <fstream>

namespace Aquila
{
    WaveFileHandler::WaveFileHandler()
    {
    }

    /**
     * Saves the given signal source as a .wav file.
     *
     * @param source source of the data to save
     * @param filename destination file
     */
    void WaveFileHandler::save(const SignalSource& source, const std::string& filename)
    {
        WaveHeader header;
        createHeader(source, header);
        std::ofstream fs;
        fs.open(filename.c_str(), std::ios::out | std::ios::binary);
        fs.write((const char*)(&header), sizeof(WaveHeader));

        std::size_t waveSize = header.WaveSize;
        short* data = new short[waveSize/2];
        if (16 == header.BitsPerSamp)
        {
            encode16bit(source, data, waveSize/2);
        }
        else
        {
            encode8bit(source, data, waveSize/2);
        }
        fs.write((const char*)data, waveSize);

        delete [] data;
        fs.close();
    }

    /**
     * Populates a .wav file header with values obtained from the source.
     *
     * @param source data source
     * @param header the header which will be filled with correct parameters
     */
    void WaveFileHandler::createHeader(const SignalSource &source, WaveHeader &header)
    {
        boost::uint32_t frequency = static_cast<boost::uint32_t>(source.getSampleFrequency());
        // saving only mono files at the moment
        boost::uint16_t channels = 1;
        boost::uint16_t bitsPerSample = source.getBitsPerSample();
        // higher dynamic sources will be converted down to 16 bits per sample
        if (bitsPerSample > 16)
            bitsPerSample = 16;
        boost::uint32_t bytesPerSec = frequency * channels * bitsPerSample / 8;
        boost::uint32_t waveSize = source.getSamplesCount() * channels * bitsPerSample / 8;

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
    }

    void WaveFileHandler::decode16bit(short *data, std::size_t channelSize)
    {
        for (std::size_t i = 0; i < channelSize; ++i)
        {
            //LChTab[i] = data[i];
        }
    }

    void WaveFileHandler::decode8bit(short *data, std::size_t channelSize)
    {
        for (std::size_t i = 0; i < channelSize; ++i)
        {
            //LChTab[i] = data[i];
        }
    }

    /**
     * Encodes the source data as an array of 16-bit values.
     *
     * @param source original signal source
     * @param data the data buffer to be written
     * @param dataSize size of the buffer
     */
    void WaveFileHandler::encode16bit(const SignalSource& source, short* data, unsigned int dataSize)
    {
        for (unsigned int i = 0; i < dataSize; ++i)
        {
            short sample = static_cast<short>(source.sample(i));
            data[i] = sample;
        }
    }

    /**
     * Encodes the source data as an array of 8-bit values stored in shorts.
     *
     * @param source original signal source
     * @param data the data buffer to be written
     * @param dataSize size of the buffer
     */
    void WaveFileHandler::encode8bit(const SignalSource& source, short* data, unsigned int dataSize)
    {
        for (unsigned int i = 0; i < dataSize; ++i)
        {
            unsigned char sample1 = static_cast<unsigned char>(source.sample(2 * i) + 128);
            unsigned char sample2 = static_cast<unsigned char>(source.sample(2 * i + 1) + 128);
            short hb = sample1, lb = sample2;
            data[i] = ((hb << 8) & 0xFF00) | (lb & 0x00FF);
        }
    }
}
