#ifndef MYSCROLLAREA_H
#define MYSCROLLAREA_H

#include <QScrollArea>
#include <QKeyEvent>

class MyScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit MyScrollArea(QWidget *parent = 0);

signals:
    void keyPressSignal(int key);
public slots:
protected:
    virtual void keyPressEvent(QKeyEvent *);

};

#endif // MYSCROLLAREA_H
