#-------------------------------------------------
#
# Project created by QtCreator 2011-12-05T15:36:44
#
#-------------------------------------------------

QT       += core gui

TARGET = ImageSearcher
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    searcherpage.cpp \
    settingpage.cpp \
    aboutpage.cpp \
    mylineedit.cpp \
    facedetector.cpp \
    detectobject.cpp \
    detectimagemodel.cpp \
    myscrollarea.cpp \
    configitem.cpp

HEADERS  += mainwindow.h \
    searcherpage.h \
    settingpage.h \
    aboutpage.h \
    Global.h \
    mylineedit.h \
    facedetector.h \
    detectobject.h \
    detectimagemodel.h \
    myscrollarea.h \
    configitem.h

OTHER_FILES += \
    images/update.png \
    images/query.png

RESOURCES += \
    resources.qrc

INCLUDEPATH +=/usr/local/include/opencv
LIBS += /usr/local/lib/libopencv_core.so \
        /usr/local/lib/libopencv_calib3d.so \
        /usr/local/lib/libopencv_contrib.so \
        /usr/local/lib/libopencv_highgui.so \
        /usr/local/lib/libopencv_features2d.so \
        /usr/local/lib/libopencv_flann.so \
        /usr/local/lib/libopencv_gpu.so \
        /usr/local/lib/libopencv_imgproc.so \
        /usr/local/lib/libopencv_legacy.so \
        /usr/local/lib/libopencv_ml.so \
        /usr/local/lib/libopencv_objdetect.so \
        /usr/local/lib/libopencv_video.so
