#include <QApplication>
#include <QMainWindow>
#include <qwt_plot.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    QwtPlot plot;
    plot.show();
    return a.exec();
}
