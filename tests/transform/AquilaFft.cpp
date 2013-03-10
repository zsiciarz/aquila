#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/AquilaFft.h"
#include <unittestpp.h>


SUITE(AquilaFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::AquilaFft>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::AquilaFft>();
    }
}
