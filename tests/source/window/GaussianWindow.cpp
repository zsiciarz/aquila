#include "aquila/global.h"
#include "aquila/source/window/GaussianWindow.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>

SUITE(GaussianWindow)
{
    TEST(NonZeroAtEnds)
    {
        const std::size_t SIZE = 4;
        Aquila::GaussianWindow w(SIZE);
        CHECK(w.sample(0) > 0.000001);
        CHECK(w.sample(SIZE - 1) > 0.000001);
    }
}
