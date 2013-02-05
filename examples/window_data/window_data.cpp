#include "aquila/transform/Window.h"
#include <cstdlib>
#include <iostream>

int main(int argc, char *argv[])
{
    int length = 0;
    if (argc >= 3)
    {
        length = std::atoi(argv[2]);
    }
    if (0 == length)
    {
        length = 64;
    }

    Aquila::WindowType type = Aquila::WIN_HAMMING;
    if (argc >= 2)
    {
        type = static_cast<Aquila::WindowType>(std::atoi(argv[1]));
    }

    Aquila::Window window(type, length);
    auto data = window.getData();
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        std::cout << i << " " << data[i] << std::endl;
    }

    return 0;
}

