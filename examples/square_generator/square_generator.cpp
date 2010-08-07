#include "aquila/source/generator/SquareGenerator.h"
#include "aquila/tools/TextPlot.h"

int main(int argc, char *argv[])
{
    Aquila::SquareGenerator generator(1000);
    generator.setFrequency(125).setAmplitude(255).generate(64);
    Aquila::TextPlot plot("Square wave");
    plot.plot(generator);

    generator.setDuty(0.25).generate(64);
    plot.setTitle("Square wave, duty cycle = 25%");
    plot.plot(generator);

    generator.setDuty(0.75).generate(64);
    plot.setTitle("Square wave, duty cycle = 75%");
    plot.plot(generator);

    return 0;
}
