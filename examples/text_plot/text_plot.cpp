#include "aquila/source/ArrayData.h"
#include "aquila/tools/TextPlot.h"
#include <cstddef>
#include <cmath>

int main(int argc, char *argv[])
{
    const std::size_t SIZE = 64;
    int arr[SIZE];
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        arr[i] = i % 10;
    }

    Aquila::ArrayData<int> data(arr, SIZE, 44100);
    Aquila::TextPlot plot("Example plot");
    plot.plot(data);

    return 0;
}
