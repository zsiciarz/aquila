#include "aquila/source/generator/SquareGenerator.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>

using std::count_if;
using std::bind2nd;
using std::greater;

int main(int argc, char *argv[])
{
    double duty = 0.5;
    if (argc > 1)
    {
        duty = std::atof(argv[1]);
    }

    // sample frequency is fixed at 1 kHz, signal frequency at 10 Hz
    Aquila::SquareGenerator gen(1000);
    gen.setDuty(duty).setAmplitude(1).setFrequency(10).generate(1000);

    // prints number of positive samples in generated signal
    std::cout << count_if(gen.begin(), gen.end(),
                          bind2nd(greater<Aquila::SampleType>(), 0));

    return 0;
}
