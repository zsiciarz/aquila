#include "aquila/transform/Window.h"
#include "aquila/tools/TextPlot.h"

int main(int argc, char *argv[])
{
    Aquila::WindowType types[] = {Aquila::WIN_RECT, Aquila::WIN_HAMMING,
                                  Aquila::WIN_HANN, Aquila::WIN_BARLETT,
                                  Aquila::WIN_BLACKMAN, Aquila::WIN_FLATTOP};
    const char* names[] = {"Rectangular", "Hamming",
                           "Hann", "Barlett",
                           "Blackman", "Flat-top"};
    const std::size_t length = 65;
    int num = sizeof(types) / sizeof(Aquila::WindowType);

    Aquila::TextPlot plot;
    for (int i = 0; i < num; ++i)
    {
        Aquila::Window window(types[i], length);
        plot.setTitle(names[i]);
        plot.plot(window.getData());
    }

    return 0;
}
