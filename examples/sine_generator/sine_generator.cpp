#include "aquila/source/generator/SineGenerator.h"
#include "aquila/tools/TextPlot.h"

int main(int argc, char *argv[])
{
    Aquila::SineGenerator generator(1000, 64);
    generator.setFrequency(32);
    generator.setAmplitude(255);
    generator.generate();
    Aquila::TextPlot plot("Sine wave");
    plot.plot(generator);

    return 0;
}
