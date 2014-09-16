#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/FramesCollection.h"
#include "aquila/transform/Spectrogram.h"
#include <QApplication>
#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>


int main(int argc, char *argv[])
{
    const Aquila::FrequencyType sampleFrequency = 44100;
    const std::size_t SIZE = sampleFrequency * 2;

    Aquila::SineGenerator generator(sampleFrequency);
    generator.setAmplitude(5).setFrequency(1000).generate(SIZE);
    Aquila::FramesCollection frames(generator, 1024);
    Aquila::Spectrogram spectrogram(frames);

    QApplication a(argc, argv);
    auto plot = new QwtPlot();
    plot->setTitle("Spectrogram");

    auto plotSpectrogram = new QwtPlotSpectrogram();
    plotSpectrogram->attach(plot);

    plot->show();
    return a.exec();
}
