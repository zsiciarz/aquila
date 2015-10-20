#include "aquila/global.h"
#include "aquila/source/window/WelchWindow.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>

SUITE(WelchWindow)
{
    TEST(ZeroAtEnds)
    {
        const std::size_t SIZE = 4;
        Aquila::WelchWindow w(SIZE);
        CHECK_CLOSE(0, w.sample(0), 0.000001);
        CHECK_CLOSE(0, w.sample(SIZE - 1), 0.000001);
    }

    TEST(Multiplication)
    {
        const std::size_t SIZE = 1024;
        Aquila::SquareGenerator generator(44100);
        generator.setFrequency(1000).setAmplitude(500).generate(SIZE);
        Aquila::WelchWindow w(SIZE);
        auto result = generator * w;
        // 0.1814 = 0.0003628 (see above) * 500 (amplitude)
        CHECK_CLOSE(0, result.sample(0), 0.000001);
        CHECK_CLOSE(0, result.sample(SIZE - 1), 0.000001);
    }
}

