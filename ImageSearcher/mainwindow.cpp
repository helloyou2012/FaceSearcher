#include "mainwindow.h"
#include <QtGui>
#include "searcherpage.h"
#include "settingpage.h"
#include "aboutpage.h"

MainWindow::MainWindow()
{
    QLabel *topLabel=new QLabel;
    topLabel->setFixedHeight(70);
    setObjectName("mainframe");
    setStyleSheet("QFrame#mainframe{background:url(:/images/top.png) top no-repeat;}" );

    contentsWidget = new QListWidget;
    contentsWidget->setViewMode(QListView::IconMode);
    contentsWidget->setIconSize(QSize(96, 84));
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    contentsWidget->setSpacing(12);

    searcherPage=new SearcherPage;
    settingPage=new SettingPage;
    aboutPage=new AboutPage;
    connect(settingPage,SIGNAL(settingChangeSignal(ConfigItem *)),this,SLOT(settingChangeSlot(ConfigItem*)));
    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(searcherPage);
    pagesWidget->addWidget(settingPage);
    pagesWidget->addWidget(aboutPage);

    createIcons();
    contentsWidget->setCurrentRow(0);

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(topLabel);
    mainLayout->addLayout(horizontalLayout);
    setLayout(mainLayout);

    setWindowTitle(Global::APPName);
    int x=(QApplication::desktop()->width() - this->width())/2;
    int y=(QApplication::desktop()->height() - this->height())/2;
    move(x,y);
}

MainWindow::~MainWindow()
{
}

void MainWindow::createIcons()
{
    QListWidgetItem *searchButton = new QListWidgetItem(contentsWidget);
    searchButton->setIcon(QIcon(Global::SearchImg));
    searchButton->setToolTip(trUtf8("搜索人脸图片"));
    searchButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *settingButton = new QListWidgetItem(contentsWidget);
    settingButton->setIcon(QIcon(Global::SettingImg));
    settingButton->setToolTip(trUtf8("设置参数"));
    settingButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *aboutButton = new QListWidgetItem(contentsWidget);
    aboutButton->setIcon(QIcon(Global::AboutImg));
    aboutButton->setToolTip(trUtf8("关于我们"));
    aboutButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(contentsWidget,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void MainWindow::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;
    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}
void MainWindow::settingChangeSlot(ConfigItem *conf){
    searcherPage->setConfigure(conf);
}
void MainWindow::closeEvent(QCloseEvent *e){
    int result=QMessageBox::question(this,trUtf8("提示"),trUtf8("是否退出程序？"),QMessageBox::Ok|QMessageBox::Cancel,QMessageBox::Cancel);
    if(result==QMessageBox::Ok)
        e->accept();
    else
        e->ignore();
}
