#ifndef ELEMENTFILE_H
#define ELEMENTFILE_H

#include "element.h"
#include <QDate>
#include <QtGlobal>

class ElementFile : public Element
{
public:
    ElementFile();
    QString humanSize();
    QString getCDate();
    QString getLDate();
    QString getOwner();
private:
    void getInfo();
    bool haveInfo;
    QDate creationDate,lastDate;
    qint64 size;
    QString owner;    
};

#endif // ELEMENTFILE_H
