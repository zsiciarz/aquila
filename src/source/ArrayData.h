#ifndef ARRAYDATA_H
#define ARRAYDATA_H

#include "../global.h"
#include "SignalSource.h"
#include <cstddef>

namespace Aquila
{
    template <typename Numeric = SampleType>
    class ArrayData : public SignalSource
    {
    public:
        ArrayData(Numeric* data, std::size_t dataLength,
                  FrequencyType sampleFrequency):
            m_data(data), m_dataLength(dataLength),
            m_sampleFrequency(sampleFrequency)
        {
        }

        virtual FrequencyType getSampleFrequency() const
        {
            return m_sampleFrequency;
        }

        virtual unsigned short getBitsPerSample() const
        {
            return 8 * sizeof(Numeric);
        }

        virtual std::size_t getSamplesCount() const
        {
            return m_dataLength;
        }

        virtual SampleType sample(std::size_t position) const
        {
            return static_cast<SampleType>(m_data[position]);
        }

    private:
        Numeric* m_data;

        std::size_t m_dataLength;

        FrequencyType m_sampleFrequency;
    };
}

#endif // ARRAYDATA_H
