#include <QtGui/QApplication>
#include "mainwindow.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QObject>

using namespace cv;
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.setVisible(true);
    w.setFixedSize(800,600);
    return app.exec();
}
