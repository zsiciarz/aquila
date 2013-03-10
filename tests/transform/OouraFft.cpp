#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/OouraFft.h"
#include <unittestpp.h>


SUITE(OouraFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::OouraFft>();
        deltaSpectrumTest<Aquila::OouraFft, 16>();
        deltaSpectrumTest<Aquila::OouraFft, 128>();
        deltaSpectrumTest<Aquila::OouraFft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::OouraFft>();
        constSpectrumTest<Aquila::OouraFft, 16>();
        constSpectrumTest<Aquila::OouraFft, 128>();
        constSpectrumTest<Aquila::OouraFft, 1024>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Aquila::OouraFft>();
        deltaInverseTest<Aquila::OouraFft, 16>();
        deltaInverseTest<Aquila::OouraFft, 128>();
        deltaInverseTest<Aquila::OouraFft, 1024>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Aquila::OouraFft>();
        constInverseTest<Aquila::OouraFft, 16>();
        constInverseTest<Aquila::OouraFft, 128>();
        constInverseTest<Aquila::OouraFft, 1024>();
    }
}
