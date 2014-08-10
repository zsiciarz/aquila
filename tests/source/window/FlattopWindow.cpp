#include "aquila/global.h"
#include "aquila/source/window/FlattopWindow.h"
#include "aquila/source/generator/SquareGenerator.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>

SUITE(FlattopWindow)
{
    TEST(NonZeroAtEnds)
    {
        const std::size_t SIZE = 4;
        Aquila::FlattopWindow w(SIZE);
        CHECK(w.sample(0) > 0.000001);
        CHECK(w.sample(SIZE - 1) > 0.000001);
    }
}

