#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/source/FramesCollection.h"
#include <unittestpp.h>


SUITE(FramesCollection)
{
    const int SIZE = 10;
    Aquila::SampleType testArray[SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    Aquila::ArrayData<> data(testArray, SIZE, 22050);

    TEST(Empty)
    {
        Aquila::FramesCollection frames;
        CHECK_EQUAL(0, frames.count());
    }
}
