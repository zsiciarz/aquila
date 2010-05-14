#include "aquila/functions.h"
#include "aquila/global.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main(int argc, char *argv[])
{
    std::srand(std::time(0));
    double value = 100.0;
    // convert a value to decibels
    std::cout << value << " is " << Aquila::dB(value) << " dB" << std::endl;
    std::cout << value << " is " << Aquila::dB(value, 0.001) << " dBm" << std::endl;
    // convert a complex number to decibels
    Aquila::ComplexType c(346.43, -125.1);
    std::cout << "Magnitude in decibels is " << Aquila::dB(c) << " dB" << std::endl;

    for (int i = 0; i < 10; ++i)
    {
        // generate random integer from a range
        int num = Aquila::random(10, 40);
        // clamp (bound) the values between min and max
        std::cout << num << " clamped between 20 and 30 is "
                  << Aquila::clamp(20, num, 30) << std::endl;
    }

    return 0;
}
