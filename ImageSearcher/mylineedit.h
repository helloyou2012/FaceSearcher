#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>
#include <QFileDialog>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);

signals:

public slots:
public:
    virtual void mousePressEvent(QMouseEvent *);

};

#endif // MYLINEEDIT_H
