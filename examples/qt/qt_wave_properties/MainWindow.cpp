#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "aquila/source/WaveFile.h"
#include <QAction>
#include <QFileDialog>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    waveWidget(new WavePropertiesWidget(this))
{
    ui->setupUi(this);
    setCentralWidget(waveWidget);
    connect(ui->actionOpen, SIGNAL(triggered()), SLOT(loadWaveFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadWaveFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open a .wav file"),
                                                    "", tr("WAVE files (*.wav)"));
    if (filename.isEmpty())
        return;

    Aquila::WaveFile* wav = new Aquila::WaveFile(filename.toStdString());
    waveWidget->setWaveFile(wav);
}
