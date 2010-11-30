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
#include "FramesCollection.h"
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
     * Binary files in WAVE format (.wav extension) can serve as data input for
     * Aquila. With this class, you can read the metadata and the actual
     * waveform data from the file. The supported formats are:
     *
     * - 8-bit mono
     * - 8-bit stereo*
     * - 16-bit mono
     * - 16-bit stereo*
     *
     * *For stereo data, both channels are read into memory, but only one
     * of them can be processed at a time. By default this is the left channel,
     * but you can switch to the other one by calling setSourceChannel().
     *
     * There are no requirements for sample frequency of the data.
     *
     * The actual data can be accessed per sample, or per frame. Frames are
     * stored in a FramesCollection object, a reference to which can be
     * obtained by calling WaveFile::frames(). This method takes care of
     * dividing the signal into frames of correct length and overlap and
     * therefore is the most convenient way to handle data in a per-frame
     * approach.
     */
    class AQUILA_EXPORT WaveFile : public SignalSource
    {
    public:
        /**
         * Audio channel representation as a vector.
         */
        typedef std::vector<SampleType> ChannelType;

        explicit WaveFile(const std::string& filename);
        ~WaveFile();

        void load(const std::string& file);
        static void save(const SignalSource& source, const std::string& file);

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
         * Checks if this is a mono recording.
         *
         * @return true if there is only one channel
         */
        bool isMono() const
        {
            return 1 == getChannelsNum();
        }

        /**
         * Checks if this is a stereo recording.
         *
         * @return true if there are two channels
         */
        bool isStereo() const
        {
            return 2 == getChannelsNum();
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
        unsigned int getBytesPerSample() const
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
         * @todo remove this method and replace all uses with toArray()
         *
         * @return address of the first element
         */
        const SampleType* getData()
        {
            return &(getDataVector())[0];
        }

        /**
         * Returns sample data (read-only!) as a const C-style array.
         *
         * Because vector guarantees to be contiguous in memory, we can
         * return the address of the first element in the vector.
         * It is valid only before next operation which modifies the vector,
         * but as we use it only to copy that memory to another buffer,
         * we can do that safely.
         *
         * Will replace the getData() method above.
         *
         * @return C-style array containing sample data
         */
        virtual const SampleType* toArray() const
        {
            return &(getDataVector())[0];
        }

        /**
         * Returns a const reference to channel source.
         *
         * @return source vector
         */
        const ChannelType& getDataVector() const
        {
            return (LEFT == m_sourceChannel) ? LChTab : RChTab;
        }

        /**
         * Sets new frame length.
         *
         * @param frameLength new frame length in milliseconds
         */
        void setFrameLength(unsigned int frameLength)
        {
            m_frameLength = frameLength;
        }

        /**
         * Sets new frame overlap.
         *
         * @param overlap overlap between adjacent frames (0 < overlap < 1)
         */
        void setFrameOverlap(double overlap)
        {
            m_overlap = overlap;
        }

        /**
         * Determines which channel (stereo only) will be used as data source.
         *
         * @param whichChannel LEFT or RIGHT (the default setting is LEFT)
         */
        void setSourceChannel(StereoChannel whichChannel)
        {
            if (!isStereo())
                return;

            m_sourceChannel = whichChannel;
        }

        /**
         * Returns number of frames in the file.
         *
         * @return frame vector length
         */
        std::size_t getFramesCount()
        {
            return frames().count();
        }

        /**
         * Gives read-only access to frames collection.
         *
         * Ensures that the frame division happens before accessing frames
         * collection.
         *
         * @return a reference to frames collection
         */
        const FramesCollection& frames()
        {
            // no frames yet, but the frame length is set
            if (0 == m_frames.count() && m_frameLength != 0)
                divideFrames();

            return m_frames;
        }

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
         * Data from both channels.
         */
        ChannelType LChTab, RChTab;

        /**
         * Frame length (in milliseconds).
         */
        unsigned int m_frameLength;

        /**
         * Overlap between frames - fraction of frame length (0 < overlap < 1).
         */
        double m_overlap;

        /**
         * Which channel will be used in stereo recordings as data source.
         */
        StereoChannel m_sourceChannel;

        /**
         * Frames collection.
         */
        FramesCollection m_frames;

        void loadHeader(std::fstream& file);
        void loadRawData(std::fstream& file, short* buffer, int bufferLength);
        void convert16Stereo(short* data, unsigned int channelSize);
        void convert16Mono(short* data, unsigned int channelSize);
        void convert8Stereo(short* data, unsigned int channelSize);
        void convert8Mono(short* data, unsigned int channelSize);
        void splitBytes(short twoBytes, unsigned char& lb, unsigned char& hb);
        void divideFrames();
    };
}

#endif // WAVEFILE_H
