#ifndef SETTINGPAGE_H
#define SETTINGPAGE_H

#include <QWidget>
#include <QtGui>
#include "Global.h"
#include "configitem.h"

class SettingPage : public QWidget
{
    Q_OBJECT
public:
    explicit SettingPage(QWidget *parent = 0);

signals:
    void settingChangeSignal(ConfigItem *conf);
public slots:
    void chooseFileSlot();
    void setConfigSlot();
    void setDefaultConfigSlot();
private:
    QCheckBox *jpgBox;
    QCheckBox *pngBox;
    QCheckBox *bmpBox;
    QSpinBox *widthBox;
    QSpinBox *heightBox;
    QLineEdit *cascadeFileEdit;

    void setDefault();
    void readyToSet();

};

#endif // SETTINGPAGE_H
