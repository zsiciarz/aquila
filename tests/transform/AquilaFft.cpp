#include "aquila/global.h"
#include "aquila/source/ArrayData.h"
#include "aquila/transform/AquilaFft.h"
#include <unittestpp.h>
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>


SUITE(AquilaFft)
{
    TEST(Delta)
    {
        const std::size_t SIZE = 8;
        Aquila::SampleType testArray[SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};
        Aquila::ArrayData<> data(testArray, SIZE, 22050);
        Aquila::ComplexType* spectrum = new Aquila::ComplexType[SIZE];
        Aquila::AquilaFft fft(SIZE);
        fft.fft(data.toArray(), spectrum);

        std::for_each(spectrum, spectrum + SIZE, [](Aquila::ComplexType x) {
            CHECK_CLOSE(1.0, std::abs(x), 0.000001);
        });

        delete [] spectrum;
    }

    TEST(ConstSignal)
    {
        const std::size_t SIZE = 8;
        Aquila::SampleType testArray[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};
        Aquila::ArrayData<> data(testArray, SIZE, 22050);
        Aquila::ComplexType* spectrum = new Aquila::ComplexType[SIZE];
        Aquila::AquilaFft fft(SIZE);
        fft.fft(data.toArray(), spectrum);

        CHECK_CLOSE(1.0 * SIZE, std::abs(spectrum[0]), 0.000001);
        std::for_each(spectrum + 1, spectrum + SIZE, [](Aquila::ComplexType x) {
            CHECK_CLOSE(0.0, std::abs(x), 0.000001);
        });

        delete [] spectrum;
    }
}
