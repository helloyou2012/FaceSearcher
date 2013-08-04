#ifndef SEARCHERPAGE_H
#define SEARCHERPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QtGui>
#include <QMetaType>
#include <QPainter>
#include "detectimagemodel.h"
#include "facedetector.h"
#include "myscrollarea.h"
#include "mylineedit.h"
#include "configitem.h"

class SearcherPage : public QWidget
{
    Q_OBJECT
public:
    explicit SearcherPage(QWidget *parent = 0);
    void setImageLabel(DetectObject &obj);

signals:

public slots:
    void searchImage();
    void fileTextChange(const QString &text);
    void detectModelChanged(DetectObject *obj,QString status);
    void selectionChangedSlot(const QItemSelection &, const QItemSelection &);
    void currentChangedSlot(int index);
    void keyPressSlot(int key);
private:
    QGroupBox *chooseBox;//选择目录框
    QTabWidget *imageTab;//结果显示Tab框
    QTableView *imageTable;//结果列表
    QLabel *imageLabel;//图像显示
    MyLineEdit *fileEdit;//选择搜索目录
    QPushButton *searchButton;//搜索按钮
    DetectImageModel *detectModel;
    QLabel *statusLabel;
    FaceDetector *detector;
    int selectIndex;
    ConfigItem *conf;
public:
    void nextImage();
    void backImage();
    void setConfigure(ConfigItem *item);
};

#endif // SEARCHERPAGE_H
