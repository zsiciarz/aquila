#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/Dft.h"
#include <unittestpp.h>


SUITE(Dft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::Dft>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::Dft>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Aquila::Dft>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Aquila::Dft>();
    }
}
