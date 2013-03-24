#include "aquila/source/window/HammingWindow.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/tools/TextPlot.h"

int main(int argc, char *argv[])
{
    const std::size_t LENGTH = 65;
    Aquila::TextPlot plot;

    Aquila::SineGenerator generator(1000);
    generator.setFrequency(84).setAmplitude(1024).generate(LENGTH);
    plot.setTitle("Sine wave before windowing");
    plot.plot(generator);

    Aquila::HammingWindow window(LENGTH);
    auto result = generator * window;
    plot.setTitle("Sine wave after windowing");
    plot.plot(result);

    return 0;
}
