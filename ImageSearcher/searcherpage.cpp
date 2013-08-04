#include "searcherpage.h"
#include "Global.h"

SearcherPage::SearcherPage(QWidget *parent) :
    QWidget(parent)
{
    selectIndex=-1;
    conf=new ConfigItem;
    conf->minWidth=30;
    conf->minHeight=30;
    conf->cascadeFile="/usr/local/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
    conf->imageTypeList<<"jpg"<<"png"<<"bmp";
    //FileEdit
    this->fileEdit=new MyLineEdit;
    connect(fileEdit, SIGNAL(textChanged(const QString &)),this, SLOT(fileTextChange(const QString &)));
    //SearchButton
    this->searchButton=new QPushButton(Global::SEARCH);
    searchButton->setEnabled(false);
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchImage()));
    //ChooseBox
    QHBoxLayout *chooseLayout = new QHBoxLayout;
    chooseLayout->addWidget(fileEdit);
    chooseLayout->addWidget(searchButton);
    this->chooseBox=new QGroupBox(Global::CHOOSETAB);
    chooseBox->setLayout(chooseLayout);
    chooseBox->setStyleSheet(Global::GROUPSTYLESHEET);
    //ImageLabel and ScrollArea
    this->imageLabel=new QLabel;
    MyScrollArea *scrollArea=new MyScrollArea;
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignCenter);
    connect(scrollArea, SIGNAL(keyPressSignal(int)), this, SLOT(keyPressSlot(int)));
    //ImageTable and DetectModel
    this->imageTable=new QTableView;
    this->detectModel=new DetectImageModel;
    imageTable->setModel(detectModel);
    imageTable->setColumnWidth(0,450);
    imageTable->setColumnWidth(1,150);
    QItemSelectionModel *selectionModel=imageTable->selectionModel();
    connect(selectionModel, SIGNAL(selectionChanged (const QItemSelection &, const QItemSelection &)),
            this, SLOT(selectionChangedSlot(const QItemSelection &, const QItemSelection &)));
    //ImageTab
    this->imageTab=new QTabWidget;
    imageTab->addTab(imageTable,Global::IMAGETABLE);
    imageTab->addTab(scrollArea,Global::IMAGEVIEW);
    connect(imageTab, SIGNAL(currentChanged(int)), this, SLOT(currentChangedSlot(int)));
    //MainLayout
    statusLabel=new QLabel();
    statusLabel->setFixedWidth(600);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(chooseBox);
    mainLayout->addWidget(imageTab);
    mainLayout->addWidget(statusLabel);
    setLayout(mainLayout);
}
void SearcherPage::selectionChangedSlot(const QItemSelection &, const QItemSelection &){
    selectIndex=imageTable->selectionModel()->currentIndex().row();
    if(imageTable->selectionModel()->currentIndex().column()==1)
        imageTab->setCurrentIndex(1);
}
void SearcherPage::currentChangedSlot(int index){
    if(index==1&&selectIndex!=-1){
        DetectObject obj=detectModel->getDetectObject(selectIndex);
        setImageLabel(obj);
    }
}
void SearcherPage::searchImage(){
    if(searchButton->text()=="Search"){
        searchButton->setText("Stop");
        detectModel->clearData();
        QString path=fileEdit->text();
        detector=new FaceDetector(path,conf);
        qRegisterMetaType<DetectObject>("DetectObject");
        connect(detector,SIGNAL(detectChanged(DetectObject *,QString)),this, SLOT(detectModelChanged(DetectObject *,QString)));
        detector->start();
    }else{
        detector->stopDetect();
        searchButton->setText("Search");
    }
}
void SearcherPage::fileTextChange(const QString &text){
    if(text.length()>0){
        searchButton->setEnabled(true);
    }else{
        searchButton->setEnabled(false);
    }
}
void SearcherPage::detectModelChanged(DetectObject *obj,QString status){
    if(obj!=NULL)
        detectModel->addRow(obj);
    if(status==trUtf8("处理完毕！")){
        searchButton->setText("Search");
    }
    statusLabel->setText(status);
}
void SearcherPage::setImageLabel(DetectObject &obj){
    QImage image;
    image.load(obj.filename);
    QPainter painter(&image);
    QPen pen(Qt::SolidLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    painter.setPen(pen);
    QVectorIterator<QRect> i(obj.detectRect);
    for(i.toFront();i.hasNext();){
        painter.drawEllipse(i.next());
    }
    painter.end();
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->resize(image.size());
}
void SearcherPage::keyPressSlot(int key){
    switch(key)
    {
    case Qt::Key_Left:
    case Qt::Key_Up:
    nextImage();
    break;
    case Qt::Key_Right:
    case Qt::Key_Down:
    backImage();
    break;
    }
}
void SearcherPage::backImage(){
    int rowcout=detectModel->rowCount(QModelIndex());
    selectIndex++;
    if(selectIndex>=rowcout){
        selectIndex=rowcout-1;
    }
    DetectObject obj=detectModel->getDetectObject(selectIndex);
    setImageLabel(obj);
}
void SearcherPage::nextImage(){
    if(selectIndex>=1){
        selectIndex--;
        DetectObject obj=detectModel->getDetectObject(selectIndex);
        setImageLabel(obj);
    }
}
void SearcherPage::setConfigure(ConfigItem *item){
    this->conf=item;
}
