#ifndef GLOBAL_H
#define GLOBAL_H
#include <QString>
#include <QStringList>
#include <iostream>
using namespace std;
namespace Global{
    static const QString APPName="Face Searcher";
    static const QString CHOOSETAB="Choose a Directory";
    static const QString SEARCH="Search";
    static const QString IMAGETABLE="Result List";
    static const QString IMAGEVIEW="Image View";
    static const QString SearchImg=":/images/Search.png";
    static const QString SettingImg=":/images/Setting.png";
    static const QString AboutImg=":/images/Home.png";
    static QStringList ImageTypeList;

    static string cascadeName="/usr/local/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
    static const QString GROUPSTYLESHEET="QGroupBox {\
                                       border-width:1px;\
                                       border-style:solid;\
                                       border-color:lightGray;\
                                       margin-top: 1ex;\
                                       }\
                                       QGroupBox::title {\
                                       subcontrol-origin: margin;\
                                       subcontrol-position: top left;\
                                       left:20px; \
                                       margin-left: 0px;\
                                       padding:0 1px;\
                                       }";
};

#endif // GLOBAL_H
