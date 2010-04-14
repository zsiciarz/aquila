#include "aquila/tools/TextPlot.h"
#include <cstddef>

int main(int argc, char *argv[])
{
    const std::size_t SIZE = 64;
    int arr[SIZE];
    for (std::size_t i = 0; i < SIZE; ++i)
    {
        arr[i] = i % 10;
    }

    Aquila::TextPlot plot("Example plot");
    plot.plot(arr, SIZE);

    return 0;
}
