#include "aquila/global.h"
#include "aquila/functions.h"
#include "aquila/source/WaveFile.h"
#include "aquila/source/generator/SineGenerator.h"
#include "aquila/source/FramesCollection.h"
#include "aquila/transform/Spectrogram.h"
#include <QApplication>
#include <QMainWindow>
#include <QVector>
#include <qwt_color_map.h>
#include <qwt_matrix_raster_data.h>
#include <qwt_plot.h>
#include <qwt_plot_spectrogram.h>

class SpectrogramData : public QwtMatrixRasterData
{
public:
    SpectrogramData(const Aquila::Spectrogram& spectrogram):
        m_spectrogram(spectrogram)
    {
        const std::size_t width = m_spectrogram.getFrameCount();
        const std::size_t height = m_spectrogram.getSpectrumSize() / 2;
        QVector<double> values;
        double maxValue = 0.0;
        for (std::size_t y = 0; y < height; ++y)
        {
            for (std::size_t x = 0; x < width; ++x)
            {
                auto val = Aquila::dB(m_spectrogram.getPoint(x, y));
                values << val;
                if (val > maxValue)
                {
                    maxValue = val;
                }
            }
        }
        setValueMatrix(values, width);
        setInterval(Qt::XAxis, QwtInterval(0.0, width));
        setInterval(Qt::YAxis, QwtInterval(0.0, height));
        setInterval(Qt::ZAxis, QwtInterval(0.0, maxValue));
    }

private:
    const Aquila::Spectrogram& m_spectrogram;
};


int main(int argc, char *argv[])
{
    const Aquila::FrequencyType sampleFrequency = 44100;
    const std::size_t SIZE = sampleFrequency * 2;

    Aquila::SignalSource* source = nullptr;
    if (argc >= 2)
    {
        source = new Aquila::WaveFile(argv[1]);
    }
    else
    {
        auto generator = new Aquila::SineGenerator(sampleFrequency);
        generator->setAmplitude(5).setFrequency(1000).generate(SIZE);
        source = generator;
    }

    Aquila::FramesCollection frames(*source, 1024);
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
