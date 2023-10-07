#include "databaseplot.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Real-time Histogram Plotting App");
    DatabasePlot w;
    w.show();
    return a.exec();
}
