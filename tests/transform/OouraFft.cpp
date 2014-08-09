#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/OouraFft.h"
#include "UnitTest++/UnitTest++.h"


SUITE(OouraFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::OouraFft, 8>();
        deltaSpectrumTest<Aquila::OouraFft, 16>();
        deltaSpectrumTest<Aquila::OouraFft, 128>();
        deltaSpectrumTest<Aquila::OouraFft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::OouraFft, 8>();
        constSpectrumTest<Aquila::OouraFft, 16>();
        constSpectrumTest<Aquila::OouraFft, 128>();
        constSpectrumTest<Aquila::OouraFft, 1024>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Aquila::OouraFft, 8>();
        deltaInverseTest<Aquila::OouraFft, 16>();
        deltaInverseTest<Aquila::OouraFft, 128>();
        deltaInverseTest<Aquila::OouraFft, 1024>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Aquila::OouraFft, 8>();
        constInverseTest<Aquila::OouraFft, 16>();
        constInverseTest<Aquila::OouraFft, 128>();
        constInverseTest<Aquila::OouraFft, 1024>();
    }

    TEST(Identity)
    {
        identityTest<Aquila::OouraFft, 8>();
        identityTest<Aquila::OouraFft, 16>();
        identityTest<Aquila::OouraFft, 128>();
        identityTest<Aquila::OouraFft, 1024>();
    }
}
