#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WavePropertiesWidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void loadWaveFile();

private:
    Ui::MainWindow *ui;
    WavePropertiesWidget* waveWidget;
};

#endif // MAINWINDOW_H
