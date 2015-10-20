#include "aquila/global.h"
#include "aquila/source/window/BlackmanNuttallWindow.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>

SUITE(BlackmanNuttallWindow)
{
    TEST(ZeroAtEnds)
    {
        const std::size_t SIZE = 4;
        Aquila::BlackmanNuttallWindow w(SIZE);
        // 0.0003628 has been manually calculated using:
        // 0.3635819 - 0.4891775 * cos(0) + 0.1365995 * cos(0) - 0.0106411 * cos(0)
        CHECK_CLOSE(0.0003628, w.sample(0), 0.000001);
        CHECK_CLOSE(0.0003628, w.sample(SIZE - 1), 0.000001);
    }

    TEST(Multiplication)
    {
        const std::size_t SIZE = 1024;
        Aquila::SquareGenerator generator(44100);
        generator.setFrequency(1000).setAmplitude(500).generate(SIZE);
        Aquila::BlackmanNuttallWindow w(SIZE);
        auto result = generator * w;
        // 0.1814 = 0.0003628 (see above) * 500 (amplitude)
        CHECK_CLOSE(0.1814, result.sample(0), 0.000001);
        CHECK_CLOSE(0.1814, result.sample(SIZE - 1), 0.000001);
    }
}

