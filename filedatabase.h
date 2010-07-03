#ifndef FILEDATABASE_H
#define FILEDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QList>
#include "elementfile.h"
#include "element.h"
#include "filter.h"
#include "QFreeDesktopMime/src/freedesktopmime.h"



class FileDatabase : public QObject
{
Q_OBJECT
public:
    explicit FileDatabase(QObject *parent = 0);
    void appendFilter(QString f);
    void setLocation(QString tag);
    void clearFilters();
    QList<Element*> Elements();
    QList<Element*> filtredElements();

private:
    QSqlQuery myQuery;
    QSqlDatabase db;
    QFreeDesktopMime mime;
    QList <QString> filters;
    QString location;

signals:

public slots:

};

#endif // FILEDATABASE_H
