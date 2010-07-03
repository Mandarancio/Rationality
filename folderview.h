#ifndef FOLDERVIEW_H
#define FOLDERVIEW_H

#include <QFrame>
#include <QScrollArea>
#include <QList>
#include <QPaintEvent>
#include "relation.h"
#include "filedatabase.h"


class FolderView : public QWidget
{
Q_OBJECT
public:
    explicit FolderView(QWidget *parent = 0);

private:
    void showFiltred();
    QString location;
    QList <Relation*> relations;
    QList <QString> filters;
    FileDatabase * fdb;
    bool filtre;
protected:
    void paintEvent(QPaintEvent *);

signals:
    void isFiltred(bool f);
    void setFilter(QString f);
    void currentDir(QString tag);

public slots:
    void skip(QString tag);
    void updateGrid();
    void filter(QString f);
    void open(QString tag,bool emitSignal=true);
};

#endif // FOLDERVIEW_H
