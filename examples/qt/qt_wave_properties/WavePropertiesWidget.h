#ifndef WAVEPROPERTIESWIDGET_H
#define WAVEPROPERTIESWIDGET_H

#include <QTableWidget>
#include "aquila/source/WaveFile.h"

/**
 * A simple table displaying metadata information of a WaveFile object.
 */
class WavePropertiesWidget : public QTableWidget
{
    Q_OBJECT

public:
    WavePropertiesWidget(QWidget* parent = 0);

    void setWaveFile(Aquila::WaveFile* wav);
};

#endif // WAVEPROPERTIESWIDGET_H
