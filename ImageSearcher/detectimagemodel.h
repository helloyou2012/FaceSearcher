#ifndef DETECTIMAGEMODEL_H
#define DETECTIMAGEMODEL_H
#include <QAbstractTableModel>
#include <QVector>
#include <QStringList>
#include "detectobject.h"

class DetectImageModel:public QAbstractTableModel
{
public:
    DetectImageModel();
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex& index,int role) const;
    QVariant headerData(int section,Qt::Orientation orientation,int role) const;
    void addRow(DetectObject *obj);
    void clearData();
    DetectObject getDetectObject(int index);
private:
    QStringList header;
    QVector<DetectObject> objects;
};

#endif // DETECTIMAGEMODEL_H
