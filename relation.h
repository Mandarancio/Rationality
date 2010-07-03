#ifndef RELATION_H
#define RELATION_H

#include <QWidget>
#include <QPaintEvent>
#include <QMoveEvent>

#include "element.h"
#include "tagview.h"


class Relation : public QWidget
{
Q_OBJECT
public:
    explicit Relation(bool first=false, bool last=false, QWidget *parent = 0);
    explicit Relation(Element *e,bool first=false, bool last=false, QWidget *parent = 0);
    ~Relation();
private:
    bool first,last;
    bool relations;
    QWidget * parent;
    QList <TagView*> tags;
    Element *element;
protected:
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void moveEvent(QMoveEvent *);
signals:
    void skip(QString name);
    void open(QString name);
    void updateGrid();
    void filter(QString filter);
private slots:
    void tagEventM(QString tag);
public slots:

};

#endif // RELATION_H
