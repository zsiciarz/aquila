#include "aquila/transform/Window.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// I know, globals are evil ;)
std::size_t length = 65, scale = 16;

void plotWindow(const char* name, Aquila::WindowType type, std::size_t length);

int main(int argc, char *argv[])
{
    Aquila::WindowType types[] = {Aquila::WIN_RECT, Aquila::WIN_HAMMING,
                                  Aquila::WIN_HANN, Aquila::WIN_BARLETT,
                                  Aquila::WIN_BLACKMAN, Aquila::WIN_FLATTOP};
    const char* names[] = {"Rectangular", "Hamming",
                           "Hann", "Barlett",
                           "Blackman", "Flat-top"};
    int num = sizeof(types) / sizeof(Aquila::WindowType);

    for (int i = 0; i < num; ++i)
    {
        plotWindow(names[i], types[i], length);
    }

    return 0;
}

/**
 * Draws a simple text-mode plot of a window.
 *
 * @param name window function name (plot title)
 * @param type window type
 * @param length window length
 */
void plotWindow(const char* name, Aquila::WindowType type, std::size_t length)
{
    std::cout << "\n" << name << " window:\n";

    Aquila::Window window(type, length);
    const Aquila::Window::WindowDataType& data = window.getData();
    double max = *std::max_element(data.begin(), data.end());

    std::vector< std::vector<char> > plot(length);
    for (unsigned int i = 0; i < length; ++i)
    {
        std::vector<char> column(scale + 2, ' ');
        std::size_t y = scale -
                        static_cast<std::size_t>((scale - 1) * data[i] / max);
        column[y] = '*';
        plot[i] = column;
    }

    for (unsigned int i = 0; i < scale + 2; ++i)
    {
        for (unsigned int j = 0; j < length; ++j)
        {
            std::cout << plot[j][i];
        }
        std::cout << "\n";
    }
}
