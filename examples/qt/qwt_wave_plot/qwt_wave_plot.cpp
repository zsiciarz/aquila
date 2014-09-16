#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include <algorithm>
#include <QApplication>
#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

int main(int argc, char *argv[])
{
    const std::size_t SIZE = 256;
    const Aquila::FrequencyType sampleFrequency = 1024;

    Aquila::SineGenerator generator(sampleFrequency);
    generator.setAmplitude(5).setFrequency(64).generate(SIZE);
    double x_data[SIZE] = {0};
    double acc = 0.0;
    std::generate_n(x_data, SIZE, [&] () {
        acc += 1.0;
        return acc;
    });
    auto y_data = generator.toArray();

    QApplication a(argc, argv);

    auto plot = new QwtPlot();
    plot->setTitle("Wave plot");
    auto curve = new QwtPlotCurve();
    curve->setPen(Qt::blue, 1);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    curve->setSamples(x_data, y_data, SIZE);
    curve->attach(plot);
    plot->show();
    return a.exec();
}
