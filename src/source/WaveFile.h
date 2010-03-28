/**
 * @file WaveFile.h
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

#ifndef WAVEFILE_H
#define WAVEFILE_H

#include "../global.h"
#include "Frame.h"
#include "SignalSource.h"
#include <cstddef>
#include <string>
#include <vector>
#include <boost/cstdint.hpp>

namespace Aquila
{
    /**
     * Which channel to use when reading stereo recordings.
     */
    enum StereoChannel { LEFT, RIGHT };

    /**
     * Wave file data access.
     *
     * WaveFile class enables .wav file header and data access, either
     * per sample or per frame.
     */
    class AQUILA_EXPORT WaveFile : public SignalSource
    {
    public:
        /**
         * Audio channel representation as a vector.
         */
        typedef std::vector<SampleType> ChannelType;

        /**
         * Data from both channels.
         */
        ChannelType LChTab, RChTab;

        /**
         * Pointers to signal frames.
         */
        std::vector<Frame*> frames;

        explicit WaveFile(const std::string& filename);
        explicit WaveFile(unsigned int frameLengthMs = 0,
                double frameOverlap = 0.66);
        ~WaveFile();

        void load(const std::string& file);

        /**
         * Returns the filename.
         *
         * @return full path to currently loaded file
         */
        std::string getFilename() const
        {
            return filename;
        }

        /**
         * Returns number of channels.
         *
         * @return 1 for mono, 2 for stereo, other types are not recognized
         */
        unsigned short getChannelsNum() const
        {
            return hdr.Channels;
        }

        /**
         * Returns signal sample frequency.
         *
         * @return sample frequency in Hz
         */
        virtual FrequencyType getSampleFrequency() const
        {
            return hdr.SampFreq;
        }

        /**
         * Returns the number of bytes per second.
         *
         * @return product of sample frequency and bytes pare sample
         */
        unsigned int getBytesPerSec() const
        {
            return hdr.BytesPerSec;
        }

        /**
         * Returns number of bytes per sample.
         *
         * @return 1 for 8b-mono, 2 for 8b-stereo or 16b-mono, 4 dor 16b-stereo
         */
        unsigned int getBytesPerSamp() const
        {
            return hdr.BytesPerSamp;
        }

        /**
         * Returns number of bits per sample
         *
         * @return 8 or 16
         */
        virtual unsigned short getBitsPerSample() const
        {
            return hdr.BitsPerSamp;
        }

        /**
         * Returns the recording size (without header).
         *
         * The return value is a raw byte count. To know the real sample count,
         * it must be divided by bytes per sample.
         *
         * @return byte count
         */
        unsigned int getWaveSize() const
        {
            return hdr.WaveSize;
        }

        /**
         * Returns the real data length.
         *
         * @return left channel vector size
         */
        virtual std::size_t getSamplesCount() const
        {
            return getDataVector().size();
        }

        /**
         * Returns sample value at a given position in source channel.
         *
         * @param position sample position (from 0 to channel length)
         * @return sample value
         */
        virtual SampleType sample(std::size_t position) const
        {
            return getDataVector()[position];
        }

        unsigned int getAudioLength() const;

        /**
         * Returns a pointer to data table.
         *
         * Because vector guarantees to be contiguous in memory, we can
         * return the address of the first element in the vector.
         * It is valid only before next operation which modifies the vector,
         * but as we use it only to copy that memory to another buffer,
         * we can do that safely.
         *
         * @return address of the first element
         */
        const SampleType* getData()
        {
            return &(getDataVector())[0];
        }

        /**
         * Returns a const reference to channel source.
         *
         * @param source which channel to use as a source
         * @return source vector
         */
        const ChannelType& getDataVector(StereoChannel source = LEFT) const
        {
            return (LEFT == source) ? LChTab : RChTab;
        }

        void saveFrames(const std::string& filename, unsigned int begin,
                        unsigned int end) const;

        /**
         * Returns number of frames in the file.
         *
         * @return frame vector length
         */
        std::size_t getFramesCount() const
        {
            return frames.size();
        }


        /**
         * Returns number of samples in a single frame.
         *
         * @return samples per frame = bytes per frame / bytes per sample
         */
        unsigned int getSamplesPerFrame() const
        {
            unsigned int bytesPerFrame = static_cast<unsigned int>(
                    hdr.BytesPerSec * frameLength / 1000.0);

            return bytesPerFrame / hdr.BytesPerSamp;
        }

        /**
         * Returns frame length (in samples) after zero padding (ZP).
         *
         * @return padded frame length is a power of 2
         */
        unsigned int getSamplesPerFrameZP() const { return zeroPaddedLength; }

        void recalculate(unsigned int newFrameLength = 0,
                         double newOverlap = 0.66);

    private:
        /**
         * .wav file header structure.
         */
        struct WaveHeader
        {
            char   RIFF[4];
            boost::uint32_t DataLength;
            char   WAVE[4];
            char   fmt_[4];
            boost::uint32_t SubBlockLength;
            boost::uint16_t formatTag;
            boost::uint16_t Channels;
            boost::uint32_t SampFreq;
            boost::uint32_t BytesPerSec;
            boost::uint16_t BytesPerSamp;
            boost::uint16_t BitsPerSamp;
            char   data[4];
            boost::uint32_t WaveSize;
        };

        /**
         * Full path of the .wav file.
         */
        std::string filename;

        /**
         * Header structure.
         */
        WaveHeader hdr;

        /**
         * Number of samples per frame.
         */
        unsigned int samplesPerFrame;

        /**
         * Frame length (in milliseconds).
         */
        unsigned int frameLength;

        /**
         * Overlap between frames - fraction of frame length (0 < overlap < 1).
         */
        double overlap;

        /**
         * Next power of 2 larger than number of samples per frame.
         */
        unsigned int zeroPaddedLength;

        void loadHeader(std::fstream& file);
        void loadRawData(std::fstream& file, short* buffer, int bufferLength);
        void convert16Stereo(short* data, unsigned int channelSize);
        void convert16Mono(short* data, unsigned int channelSize);
        void convert8Stereo(short* data, unsigned int channelSize);
        void convert8Mono(short* data, unsigned int channelSize);
        void splitBytes(short twoBytes, unsigned char& lb, unsigned char& hb);

        void divideFrames(const ChannelType& source);
        void clearFrames();
    };
}

#endif // WAVEFILE_H
