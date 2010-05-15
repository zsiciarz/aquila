#include "aquila/source/generator/SineGenerator.h"
#include "aquila/tools/TextPlot.h"

int main(int argc, char *argv[])
{
    Aquila::SineGenerator generator(1000);
    generator.setFrequency(32).setAmplitude(255).generate(64);
    Aquila::TextPlot plot("Sine wave");
    plot.plot(generator);

    // resize the generator
    generator.setFrequency(50).generate(32);
    plot.plot(generator);

    return 0;
}
