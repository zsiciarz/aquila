#include "aquila/global.h"
#include "aquila/source/PlainTextFile.h"
#include "constants.h"
#include <boost/cstdint.hpp>
#include <unittestpp.h>


SUITE(PlainTextFile)
{
    TEST(SampleFrequency)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_EQUAL(22050, txt.getSampleFrequency());
    }

    TEST(SamplesCount)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_EQUAL(4, txt.getSamplesCount());
    }

    TEST(Sample)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_CLOSE(1.0, txt.sample(0), 0.000001);
        CHECK_CLOSE(2.0, txt.sample(1), 0.000001);
        CHECK_CLOSE(3.0, txt.sample(2), 0.000001);
        CHECK_CLOSE(3.141592, txt.sample(3), 0.000001);
    }
}
