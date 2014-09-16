#include "aquila/global.h"
#include "aquila/source/generator/SineGenerator.h"
#include <algorithm>
#include <QApplication>
#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_series_data.h>


class SignalSourceData : public QwtSeriesData<QPointF>
{
public:
    SignalSourceData(const Aquila::SignalSource& source):
        m_source(source)
    {
    }

    std::size_t size() const
    {
        return m_source.getSamplesCount();
    }

    QRectF boundingRect() const
    {
        return qwtBoundingRect(*this);
    }

    QPointF sample(std::size_t i) const
    {
        return QPointF(i / m_source.getSampleFrequency(), m_source.sample(i));
    }

private:
    const Aquila::SignalSource& m_source;
};


int main(int argc, char *argv[])
{
    const std::size_t SIZE = 256;
    const Aquila::FrequencyType sampleFrequency = 1024;

    Aquila::SineGenerator generator(sampleFrequency);
    generator.setAmplitude(5).setFrequency(64).generate(SIZE);

    QApplication a(argc, argv);
    auto plot = new QwtPlot();
    plot->setTitle("Wave plot");
    plot->setAxisTitle(QwtPlot::xBottom, "time [s]");
    plot->setAxisTitle(QwtPlot::yLeft, "sample value");

    auto curve = new QwtPlotCurve();
    curve->setPen(Qt::blue, 1);
    curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

    auto data = new SignalSourceData(generator);
    curve->setSamples(data);
    curve->attach(plot);

    plot->show();
    return a.exec();
}
