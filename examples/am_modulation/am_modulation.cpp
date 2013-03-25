#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/generator/TriangleGenerator.h"
#include "aquila/tools/TextPlot.h"
#include <cstddef>

int main(int argc, char *argv[])
{
    const std::size_t SIZE = 64;
    const Aquila::FrequencyType sampleFrequency = 10000;
    Aquila::TextPlot plot;

    Aquila::SineGenerator input(sampleFrequency);
    input.setAmplitude(3).setFrequency(160).generate(SIZE);
    plot.setTitle("Input signal - a \"slow\" sine wave");
    plot.plot(input);

    Aquila::SineGenerator carrier(sampleFrequency);
    carrier.setFrequency(1000).setAmplitude(10).generate(SIZE);
    plot.setTitle("Carrier wave");
    plot.plot(carrier);

    // double-sideband, suppressed carrier AM modulation
    auto modulated = carrier * input;
    plot.setTitle("Modulated signal");
    plot.plot(modulated);

    return 0;
}
