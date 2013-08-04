#ifndef DETECTOBJECT_H
#define DETECTOBJECT_H
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <QString>
#include <QVector>
#include <QRect>

using namespace std;
using namespace cv;

class DetectObject
{
public:
    DetectObject();
public:
    QString filename;
    QVector<QRect> detectRect;
};

#endif // DETECTOBJECT_H
