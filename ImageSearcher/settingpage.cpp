#include "settingpage.h"

SettingPage::SettingPage(QWidget *parent) :
    QWidget(parent)
{
    QGroupBox *imageTypeGroup = new QGroupBox(trUtf8("设置搜索图像格式"));
    jpgBox = new QCheckBox(trUtf8("JPEG图像格式(*.jpg)"));
    pngBox = new QCheckBox(trUtf8("PNG图像格式(*.png)"));
    bmpBox = new QCheckBox(trUtf8("BMP图像格式(*.bmp)"));

    QGroupBox *sizeGroup = new QGroupBox(trUtf8("设置最小搜索区域"));
    widthBox=new QSpinBox();
    heightBox=new QSpinBox();

    QGroupBox *fileGroup = new QGroupBox(trUtf8("设置分类器文件"));
    cascadeFileEdit=new QLineEdit();
    QPushButton *chooseButton=new QPushButton(trUtf8("选择"));

    QPushButton *setButton=new QPushButton(trUtf8("设置"));
    QPushButton *defaultButton=new QPushButton(trUtf8("默认"));

    setDefault();

    QVBoxLayout *imageTypeLayout = new QVBoxLayout;
    imageTypeLayout->addWidget(jpgBox);
    imageTypeLayout->addWidget(pngBox);
    imageTypeLayout->addWidget(bmpBox);
    imageTypeGroup->setLayout(imageTypeLayout);
    imageTypeGroup->setStyleSheet(Global::GROUPSTYLESHEET);

    QHBoxLayout *sizeLayout = new QHBoxLayout;
    sizeLayout->addWidget(new QLabel(trUtf8("宽度：")));
    sizeLayout->addWidget(widthBox);
    sizeLayout->addWidget(new QLabel(trUtf8("高度：")));
    sizeLayout->addWidget(heightBox);
    sizeGroup->setLayout(sizeLayout);
    sizeGroup->setStyleSheet(Global::GROUPSTYLESHEET);

    QHBoxLayout *fileLayout = new QHBoxLayout;
    fileLayout->addWidget(cascadeFileEdit);
    fileLayout->addWidget(chooseButton);
    fileGroup->setLayout(fileLayout);
    fileGroup->setStyleSheet(Global::GROUPSTYLESHEET);

    QWidget *buttonWidget=new QWidget();
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacing(200);
    buttonLayout->addWidget(setButton);
    buttonLayout->addSpacing(30);
    buttonLayout->addWidget(defaultButton);
    buttonLayout->addSpacing(200);
    buttonWidget->setLayout(buttonLayout);

    connect(chooseButton, SIGNAL(clicked()), this, SLOT(chooseFileSlot()));
    connect(setButton, SIGNAL(clicked()), this, SLOT(setConfigSlot()));
    connect(defaultButton, SIGNAL(clicked()), this, SLOT(setDefaultConfigSlot()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(fileGroup);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(sizeGroup);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(imageTypeGroup);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(buttonWidget);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}
void SettingPage::setDefault(){
    jpgBox->setChecked(true);
    pngBox->setChecked(true);
    bmpBox->setChecked(true);
    widthBox->setMaximum(5000);
    widthBox->setValue(30);
    heightBox->setMaximum(5000);
    heightBox->setValue(30);
    cascadeFileEdit->setReadOnly(true);
    cascadeFileEdit->setText("/usr/local/share/opencv/haarcascades/haarcascade_frontalface_alt.xml");
}
void SettingPage::chooseFileSlot(){
    QFileDialog *fd=new QFileDialog(this,"Choose a HarrCascade File");
    fd->setNameFilter("*.xml *.XML");
    if(fd->exec()==QFileDialog::Accepted)
    {
        cascadeFileEdit->setText(fd->selectedFiles()[0]);
    }
}

void SettingPage::setConfigSlot(){
    readyToSet();
}

void SettingPage::setDefaultConfigSlot(){
    setDefault();
    readyToSet();
}
void SettingPage::readyToSet(){
    ConfigItem *item=new ConfigItem;
    item->minWidth=widthBox->value();
    item->minHeight=heightBox->value();
    item->cascadeFile=cascadeFileEdit->text();
    if(jpgBox->checkState()==Qt::Checked)
        item->imageTypeList<<"jpg";
    if(pngBox->checkState()==Qt::Checked)
        item->imageTypeList<<"png";
    if(bmpBox->checkState()==Qt::Checked)
        item->imageTypeList<<"bmp";
    emit settingChangeSignal(item);
    QMessageBox::information(this,trUtf8("提示"),trUtf8("设置成功！"));
}
