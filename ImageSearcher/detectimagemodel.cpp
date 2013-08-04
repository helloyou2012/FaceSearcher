#include "detectimagemodel.h"
#include <iostream>
using namespace std;

DetectImageModel::DetectImageModel()
{
    header<<tr("Image List")<<tr("Face Count");
}
int DetectImageModel::rowCount(const QModelIndex &parent) const{
    return objects.size();
}
int DetectImageModel::columnCount(const QModelIndex &parent) const{
    return 2;
}
QVariant DetectImageModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();
    int row=index.row();
    int col=index.column();
    if(role==Qt::DisplayRole){
        switch(col){
        case 0:
            return objects.at(row).filename;
        case 1:
            return objects.at(row).detectRect.size();
        default:
            return QVariant();
        }
    }
    if(role==Qt::CheckStateRole)
        return QVariant();
    if(role==Qt::TextAlignmentRole&&col==1)
        return Qt::AlignCenter;
    return QVariant();
}
QVariant DetectImageModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role==Qt::DisplayRole&&orientation==Qt::Horizontal)
        return header[section];
    return QAbstractTableModel::headerData(section,orientation,role);
}

void DetectImageModel::addRow(DetectObject *obj){
    int first=rowCount(QModelIndex())-1;
    beginInsertRows(QModelIndex(),first,first);
    objects<<*obj;
    endInsertRows();
}

void DetectImageModel::clearData(){
    int last=rowCount(QModelIndex())-1;
    beginRemoveRows(QModelIndex(),0,last);
    objects.clear();
    endRemoveRows();
}
DetectObject DetectImageModel::getDetectObject(int index){
    return objects.at(index);
}
