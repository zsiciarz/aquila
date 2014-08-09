#include "aquila/global.h"
#include "aquila/source/window/RectangularWindow.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>

SUITE(RectangularWindow)
{
    TEST(SampleValue)
    {
        const std::size_t SIZE = 4;
        Aquila::RectangularWindow w(SIZE);
        Aquila::SampleType expected[SIZE] = {1.0, 1.0, 1.0, 1.0};
        CHECK_ARRAY_CLOSE(expected, w.toArray(), SIZE, 0.000001);
    }

    TEST(Multiplication)
    {
        const std::size_t SIZE = 1024;
        Aquila::SquareGenerator generator(44100);
        generator.setFrequency(1000).setAmplitude(500).generate(SIZE);
        Aquila::RectangularWindow w(SIZE);
        auto result = generator * w;
        CHECK_ARRAY_CLOSE(generator.toArray(), result.toArray(), SIZE, 0.00001);
    }
}
