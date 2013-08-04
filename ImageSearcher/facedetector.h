#ifndef FACEDETECTOR_H
#define FACEDETECTOR_H
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <stdio.h>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QString>
#include <QtGlobal>
#include <QMutex>
#include <QThread>
#include <QtCore>
#include <QMessageBox>
#include "detectobject.h"
#include "Global.h"
#include "configitem.h"

using namespace std;
using namespace cv;

class FaceDetector:public QThread
{
    Q_OBJECT
public:
    FaceDetector(QString &basepath,ConfigItem *conf);
    DetectObject* detectImage(string &filename);
    void detectRun(const QString &path);
    void stopDetect();

signals:
    void detectChanged(DetectObject *obj,QString status);

protected:
    void run();

private:
    CascadeClassifier cascade;
    QMutex mutex;
    QString basePath;
    ConfigItem *conf;
    bool isGoing;
};

#endif // FACEDETECTOR_H
