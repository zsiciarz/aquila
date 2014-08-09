#include "aquila/global.h"
#include "aquila/filter/MelFilter.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>


SUITE(MelFilter)
{
    TEST(Roundtrip)
    {
        Aquila::FrequencyType frequency = 1000.0;
        auto melFrequency = Aquila::MelFilter::linearToMel(frequency);
        auto linearFrequency = Aquila::MelFilter::melToLinear(melFrequency);
        CHECK_CLOSE(frequency, linearFrequency, 0.00001);
    }

    TEST(SampleFrequency)
    {
        Aquila::FrequencyType sampleFrequency = 44100.0;
        Aquila::MelFilter filter(sampleFrequency);
        CHECK_EQUAL(sampleFrequency, filter.getSampleFrequency());
    }

    TEST(Assignment)
    {
        Aquila::FrequencyType sampleFrequency = 44100.0;
        Aquila::MelFilter filter(sampleFrequency);
        Aquila::MelFilter other(1000.0);
        other = filter;
        CHECK_EQUAL(44100.0, other.getSampleFrequency());
    }

    TEST(OutsideTriangle)
    {
        Aquila::FrequencyType sampleFrequency = 44100.0;
        const std::size_t N = 2048;

        // single spectral peak at highest frequency
        Aquila::SpectrumType spectrum(N);
        spectrum[N / 2 - 1] = 5000;

        // 0-th filter for lowest frequencies
        Aquila::MelFilter filter(sampleFrequency);
        filter.createFilter(0, 200, N);
        double output = filter.apply(spectrum);
        CHECK_CLOSE(0.0, output, 0.000001);
    }

    TEST(InsideTriangle)
    {
        Aquila::FrequencyType sampleFrequency = 44100.0;
        const std::size_t N = 2048;

        // create a single spectral peak at middle frequency of 0-th Mel filter
        Aquila::SpectrumType spectrum(N);
        Aquila::FrequencyType melFrequency = 100.0;
        Aquila::FrequencyType linearFrequency = Aquila::MelFilter::melToLinear(melFrequency);
        std::size_t peakNumber = N  * (linearFrequency / sampleFrequency);
        spectrum[peakNumber] = 5000.0;

        // 0-th filter for lowest frequencies
        Aquila::MelFilter filter(sampleFrequency);
        filter.createFilter(0, 200, N);
        double output = filter.apply(spectrum);
        CHECK_CLOSE(5000.0, output, 100);
    }
}
