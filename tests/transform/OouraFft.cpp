#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/OouraFft.h"
#include <unittestpp.h>


SUITE(OouraFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::OouraFft>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::OouraFft>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Aquila::OouraFft>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Aquila::OouraFft>();
    }
}
