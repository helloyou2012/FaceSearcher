#ifndef CONFIGITEM_H
#define CONFIGITEM_H

#include <QObject>
#include <QString>
#include <QStringList>

class ConfigItem : public QObject
{
    Q_OBJECT
public:
    explicit ConfigItem(QObject *parent = 0);

signals:

public slots:
public:
    int minWidth;
    int minHeight;
    QString cascadeFile;
    QStringList imageTypeList;
};

#endif // CONFIGITEM_H
