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
        CHECK_EQUAL(txt.getSampleFrequency(), 22050);
    }

    TEST(SamplesCount)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_EQUAL(txt.getSamplesCount(), 4);
    }

    TEST(Sample)
    {
        Aquila::PlainTextFile txt(Aquila_TEST_TXTFILE, 22050);
        CHECK_CLOSE(txt.sample(0), 1.0, 0.000001);
        CHECK_CLOSE(txt.sample(1), 2.0, 0.000001);
        CHECK_CLOSE(txt.sample(2), 3.0, 0.000001);
        CHECK_CLOSE(txt.sample(3), 3.141592, 0.000001);
    }
}
