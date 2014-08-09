#include "aquila/global.h"
#include "aquila/filter/MelFilter.h"
#include "aquila/filter/MelFilterBank.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>
#include <vector>

template <std::size_t N>
void testMelFilterBankOutput()
{
    Aquila::FrequencyType sampleFrequency = 44100.0;
    Aquila::MelFilterBank filters(sampleFrequency, N);

    for (std::size_t k = 0; k < filters.size(); ++k)
    {
        // create a single spectral peak at middle frequency of k-th Mel filter
        Aquila::SpectrumType spectrum(N);
        Aquila::FrequencyType melFrequency = 100.0 + k * 100.0;
        Aquila::FrequencyType linearFrequency = Aquila::MelFilter::melToLinear(melFrequency);
        std::size_t peakNumber = N  * (linearFrequency / sampleFrequency);
        spectrum[peakNumber] = 5000.0;

        auto output = filters.applyAll(spectrum);
        CHECK(output[k] > 0);
    }
}


SUITE(MelFilterBank)
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
        testMelFilterBankOutput<1024>();
    }

    TEST(FilterOutput2048)
    {
        testMelFilterBankOutput<2048>();
    }

    TEST(FilterOutput4096)
    {
        testMelFilterBankOutput<4096>();
    }
}
