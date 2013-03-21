#include "aquila/global.h"
#include "aquila/filter/MelFilter.h"
#include "aquila/filter/MelFilterBank.h"
#include <unittestpp.h>
#include <cstddef>

template <std::size_t N>
void testMelFilterBankOutput(const std::size_t k)
{
    Aquila::FrequencyType sampleFrequency = 44100.0;

    // create a single spectral peak at middle frequency of k-th Mel filter
    Aquila::SpectrumType spectrum(N);
    Aquila::FrequencyType melFrequency = 100.0 + k * 100.0;
    Aquila::FrequencyType linearFrequency = Aquila::MelFilter::melToLinear(melFrequency);
    std::size_t peakNumber = N  * (linearFrequency / sampleFrequency);
    spectrum[peakNumber] = 5000.0;

    Aquila::MelFilterBank filters(sampleFrequency, N);
    auto output = filters.applyAll(spectrum);

    double expected[Aquila::MELFILTERS] = {0};
    expected[k] = 5000.0;
    CHECK_ARRAY_CLOSE(expected, output, Aquila::MELFILTERS, 0.000001);
}


SUITE(MelFilter)
{
    TEST(SampleFrequency)
    {
        Aquila::MelFilterBank filters(22050, 2048);
        CHECK_EQUAL(22050, filters.getSampleFrequency());
    }

    TEST(SpectrumLength)
    {
        Aquila::MelFilterBank filters(22050, 2048);
        CHECK_EQUAL(2048u, filters.getSpectrumLength());
    }

    TEST(FilterOutput1024)
    {
        for (unsigned int i = 0; i < Aquila::MELFILTERS; ++i)
        {
            testMelFilterBankOutput<1024>(i);
        }
    }

    TEST(FilterOutput2048)
    {
        for (unsigned int i = 0; i < Aquila::MELFILTERS; ++i)
        {
            testMelFilterBankOutput<2048>(i);
        }
    }

    TEST(FilterOutput4096)
    {
        for (unsigned int i = 0; i < Aquila::MELFILTERS; ++i)
        {
            testMelFilterBankOutput<4096>(i);
        }
    }
}
