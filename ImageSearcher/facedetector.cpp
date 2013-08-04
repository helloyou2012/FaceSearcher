#include "facedetector.h"

FaceDetector::FaceDetector(QString &basepath,ConfigItem *conf)
{
    this->basePath=basepath;
    this->conf=conf;
    isGoing=true;
}
void FaceDetector::run(){
    string filename(qPrintable(conf->cascadeFile));
    cascade.load(filename);
    detectRun(basePath);
    emit detectChanged(0,trUtf8("处理完毕！"));
}
void FaceDetector::stopDetect(){
    mutex.lock();
    isGoing=false;
    mutex.unlock();
}

void FaceDetector::detectRun(const QString &path){
    if(!isGoing)
        return;
    QDir dir(path);
    if (!dir.exists())
        return;
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    int i=0;
    do{
        QFileInfo fileInfo = list.at(i);
        emit detectChanged(0,trUtf8("当前文件：")+fileInfo.absoluteFilePath());
        bool bisDir=fileInfo.isDir();
        if(bisDir)
        {
            detectRun(fileInfo.filePath());
        }
        else{
            QString temp=fileInfo.suffix().toLower();
            if(conf->imageTypeList.contains(temp)){
                string filename(qPrintable(fileInfo.absoluteFilePath()));
                DetectObject* obj=detectImage(filename);
                if(obj!=NULL)
                    emit detectChanged(obj,trUtf8("正在处理：")+fileInfo.absoluteFilePath());
            }
        }
        i++;
    }while(i<list.size());
    return;
}

DetectObject* FaceDetector::detectImage(string &filename){
    if(isGoing){
        Mat img = imread(filename, 1 );
        if(img.empty())
            return NULL;
        vector<Rect> faces;
        Mat gray, smallImg(img.rows, img.cols, CV_8UC1 );
        cvtColor( img, gray, CV_BGR2GRAY );
        resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
        equalizeHist( smallImg, smallImg );
        cascade.detectMultiScale( smallImg, faces,
                1.1, 2, 0
                |CV_HAAR_SCALE_IMAGE,
                Size(conf->minWidth, conf->minHeight) );
        if(!faces.empty()){
            DetectObject *obj=new DetectObject;
            obj->filename=trUtf8(filename.c_str());
            for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++){
                QRect rect;
                rect.setX(r->x);
                rect.setY(r->y);
                rect.setWidth(r->width);
                rect.setHeight(r->height);
                obj->detectRect<<rect;
            }
            gray.release();
            smallImg.release();
            img.release();
            return obj;
        }
        gray.release();
        smallImg.release();
        img.release();
    }
    return NULL;
}
