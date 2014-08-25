#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/AquilaFft.h"
#include "UnitTest++/UnitTest++.h"


SUITE(AquilaFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::AquilaFft, 8>();
        deltaSpectrumTest<Aquila::AquilaFft, 16>();
        deltaSpectrumTest<Aquila::AquilaFft, 128>();
        deltaSpectrumTest<Aquila::AquilaFft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::AquilaFft, 8>();
        constSpectrumTest<Aquila::AquilaFft, 16>();
        constSpectrumTest<Aquila::AquilaFft, 128>();
        constSpectrumTest<Aquila::AquilaFft, 1024>();
    }

    TEST(Identity)
    {
        identityTest<Aquila::AquilaFft, 8>();
        identityTest<Aquila::AquilaFft, 16>();
        identityTest<Aquila::AquilaFft, 128>();
        identityTest<Aquila::AquilaFft, 1024>();
    }
}
