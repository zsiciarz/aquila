#include "aquila/global.h"
#include "aquila/filter/MelFilter.h"
#include <unittestpp.h>


SUITE(MelFilter)
{
    TEST(Roundtrip)
    {
        Aquila::FrequencyType frequency = 1000.0;
        auto melFrequency = Aquila::MelFilter::linearToMel(frequency);
        auto linearFrequency = Aquila::MelFilter::melToLinear(melFrequency);
        CHECK_CLOSE(frequency, linearFrequency, 0.00001);
    }
}
