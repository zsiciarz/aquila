#include "aquila/global.h"
#include "aquila/tools/TextPlot.h"
#include "UnitTest++/UnitTest++.h"
#include <cstddef>


SUITE(TextPlot)
{
    TEST(DefaultTitle)
    {
        Aquila::TextPlot plot;
        CHECK_EQUAL(plot.getTitle(), "Data plot");
    }

    TEST(CustomTitle)
    {
        Aquila::TextPlot plot;
        plot.setTitle("My plot");
        CHECK_EQUAL(plot.getTitle(), "My plot");
    }
}
