#ifndef ELEMENT_H
#define ELEMENT_H

#include <QObject>
#include <QList>

//#include "QFreeDesktopMime/src/freedesktopmime.h"


class Element : public QObject
{
    Q_OBJECT
public:
    Element(QObject *parent = 0);
    void setKey(int k);
    void setRelation(bool r);
    void setName(QString name);
    void setPath(QString p);
    void clearTags();
    void addTag(QString tag);
    void setType(QString t);
    void setDescription(QString d);
    int Key();
    bool isARelation();
    QString Type();
    QString Name();
    QString Path();
    QString Description();
    QList<QString> Tags();


private:
    bool isRelation;
    int key;
//    QFreeDesktopMime mime;
    QString name;
    QString path;
    QString type;
    QString description;
    QList <QString> tags;

};

#endif // ELEMENT_H
