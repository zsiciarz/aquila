#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/Dft.h"
#include "UnitTest++/UnitTest++.h"


SUITE(Dft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::Dft, 8>();
        deltaSpectrumTest<Aquila::Dft, 16>();
        deltaSpectrumTest<Aquila::Dft, 128>();
        deltaSpectrumTest<Aquila::Dft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::Dft, 8>();
        constSpectrumTest<Aquila::Dft, 16>();
        constSpectrumTest<Aquila::Dft, 128>();
        constSpectrumTest<Aquila::Dft, 1024>();
    }

    TEST(DeltaInverse)
    {
        deltaInverseTest<Aquila::Dft, 8>();
        deltaInverseTest<Aquila::Dft, 16>();
        deltaInverseTest<Aquila::Dft, 128>();
        deltaInverseTest<Aquila::Dft, 1024>();
    }

    TEST(ConstInverse)
    {
        constInverseTest<Aquila::Dft, 8>();
        constInverseTest<Aquila::Dft, 16>();
        constInverseTest<Aquila::Dft, 128>();
        constInverseTest<Aquila::Dft, 1024>();
    }

    TEST(Identity)
    {
        identityTest<Aquila::Dft, 8>();
        identityTest<Aquila::Dft, 16>();
        identityTest<Aquila::Dft, 128>();
        identityTest<Aquila::Dft, 1024>();
    }
}
