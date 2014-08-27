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

    TEST(DefaultSize)
    {
        Aquila::TextPlot plot;
        CHECK_EQUAL(plot.getWidth(), 64);
        CHECK_EQUAL(plot.getHeight(), 16);
    }

    TEST(CustomSize)
    {
        Aquila::TextPlot plot;
        plot.setSize(80, 12);
        CHECK_EQUAL(plot.getWidth(), 80);
        CHECK_EQUAL(plot.getHeight(), 12);
    }
}
