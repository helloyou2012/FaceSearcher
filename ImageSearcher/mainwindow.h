#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include "Global.h"
#include "searcherpage.h"
#include "settingpage.h"
#include "aboutpage.h"

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class MainWindow : public QFrame
{
    Q_OBJECT

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void settingChangeSlot(ConfigItem *conf);

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;
    SearcherPage *searcherPage;
    SettingPage *settingPage;
    AboutPage *aboutPage;

public:
    MainWindow();
    ~MainWindow();
protected:
    virtual void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
