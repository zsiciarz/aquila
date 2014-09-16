#include "aquila/global.h"
#include "aquila/functions.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/FramesCollection.h"
#include "aquila/transform/Spectrogram.h"
#include <QApplication>
#include <QMainWindow>
#include <qwt_color_map.h>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>
#include <qwt_raster_data.h>

class SpectrogramData : public QwtRasterData
{
public:
    SpectrogramData(const Aquila::Spectrogram& spectrogram):
        m_spectrogram(spectrogram)
    {
        setInterval(Qt::XAxis, QwtInterval(0.0, m_spectrogram.getFrameCount()));
        setInterval(Qt::YAxis, QwtInterval(0.0, m_spectrogram.getSpectrumSize() / 2));
        setInterval(Qt::ZAxis, QwtInterval(0.0, 50));
    }

    double value(double x, double y) const
    {
        std::size_t frame = Aquila::clamp(0ul, static_cast<std::size_t>(x), m_spectrogram.getFrameCount() - 1ul);
        std::size_t peak = Aquila::clamp(0ul, static_cast<std::size_t>(y), m_spectrogram.getSpectrumSize() - 1ul);
        return 20.0 * std::log10(std::abs(m_spectrogram.getPoint(frame, peak)));
    }

private:
    const Aquila::Spectrogram& m_spectrogram;
};


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
    QwtLinearColorMap colorMap(Qt::black, Qt::red);
    colorMap.addColorStop(0.3, Qt::darkBlue);
    colorMap.addColorStop(0.4, Qt::blue);
    colorMap.addColorStop(0.65, Qt::green);
    colorMap.addColorStop(0.85, Qt::yellow);
    plotSpectrogram->setColorMap(&colorMap);
    auto data = new SpectrogramData(spectrogram);
    plotSpectrogram->setData(data);
    plotSpectrogram->attach(plot);

    plot->show();
    return a.exec();
}
