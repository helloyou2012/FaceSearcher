#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    setReadOnly(true);
}
void MyLineEdit::mousePressEvent(QMouseEvent *){
    QFileDialog *fd=new QFileDialog(this,"Choose a Dir");
    fd->setFileMode(QFileDialog::DirectoryOnly);
    if(fd->exec()==QFileDialog::Accepted)
    {
        setText(fd->selectedFiles()[0]);
    }
}
