#include "aquila/source/generator/TriangleGenerator.h"
#include "aquila/tools/TextPlot.h"

int main(int argc, char *argv[])
{
    Aquila::TriangleGenerator generator(1000);
    generator.setFrequency(25).setAmplitude(255).generate(64);
    Aquila::TextPlot plot("Sawtooth wave");
    plot.plot(generator);

    generator.setWidth(0.5).generate(64);
    plot.setTitle("Triangle wave, slope width = 50%");
    plot.plot(generator);

    generator.setWidth(0.18).generate(64);
    plot.setTitle("Triangle wave, slope width = 18%");
    plot.plot(generator);

    return 0;
}
