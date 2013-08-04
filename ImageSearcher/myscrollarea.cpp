#include "myscrollarea.h"

MyScrollArea::MyScrollArea(QWidget *parent) :
    QScrollArea(parent)
{
}
void MyScrollArea::keyPressEvent(QKeyEvent *e){
    emit keyPressSignal(e->key());
    QScrollArea::keyPressEvent(e);
}
