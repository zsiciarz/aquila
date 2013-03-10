#include "Fft.h"
#include "aquila/global.h"
#include "aquila/transform/AquilaFft.h"
#include <unittestpp.h>


SUITE(AquilaFft)
{
    TEST(Delta)
    {
        deltaSpectrumTest<Aquila::AquilaFft>();
        deltaSpectrumTest<Aquila::AquilaFft, 16>();
        deltaSpectrumTest<Aquila::AquilaFft, 128>();
        deltaSpectrumTest<Aquila::AquilaFft, 1024>();
    }

    TEST(ConstSignal)
    {
        constSpectrumTest<Aquila::AquilaFft>();
        constSpectrumTest<Aquila::AquilaFft, 16>();
        constSpectrumTest<Aquila::AquilaFft, 128>();
        constSpectrumTest<Aquila::AquilaFft, 1024>();
    }
}
