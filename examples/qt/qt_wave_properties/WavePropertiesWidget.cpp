#include "WavePropertiesWidget.h"

#include <QFileInfo>
#include <QHeaderView>
#include <QMessageBox>
#include <QStringList>

/**
 * Creates a widget and prepares the table layout.
 *
 * @param parent parent object
 */
WavePropertiesWidget::WavePropertiesWidget(QWidget* parent):
    QTableWidget(8, 1, parent)
{
    // row labels
    QStringList labels;
    labels << tr("Filename")
           << tr("Full path")
           << tr("Length")
           << tr("Channels")
           << tr("Bits per sample")
           << tr("Sample frequency")
           << tr("Bytes per sample")
           << tr("Bytes per sec");
    setVerticalHeaderLabels(labels);
    setAlternatingRowColors(true);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setSelectionMode(QAbstractItemView::SingleSelection);
    QHeaderView* header =  horizontalHeader();
    header->setStretchLastSection(true);
    header->hide();
    setEnabled(false);
}

/**
 * Sets the WaveFile object to be displayed.
 *
 * @param wav the object to display
 */
void WavePropertiesWidget::setWaveFile(Aquila::WaveFile* wav)
{
    QString path = QString::fromStdString(wav->getFilename());
    QFileInfo fi(path);
    setItem(0, 0, new QTableWidgetItem(fi.fileName()));
    setItem(1, 0, new QTableWidgetItem(path));
    setItem(2, 0, new QTableWidgetItem(tr("%1 ms").arg(wav->getAudioLength())));
    QString channels = wav->getChannelsNum() == 2 ? tr("2 (stereo)") : tr("1 (mono)");
    setItem(3, 0, new QTableWidgetItem(channels));
    setItem(4, 0, new QTableWidgetItem(tr("%1 bits").arg(wav->getBitsPerSample())));
    setItem(5, 0, new QTableWidgetItem(tr("%1 Hz").arg(wav->getSampleFrequency())));
    setItem(6, 0, new QTableWidgetItem(tr("%1 bytes").arg(wav->getBytesPerSample())));
    setItem(7, 0, new QTableWidgetItem(tr("%1 bytes").arg(wav->getBytesPerSec())));
    setEnabled(true);
}
