#ifndef PROPERTYBAR_H
#define PROPERTYBAR_H

#include <QWidget>
#include <QPaintEvent>
#include "element.h"

class PropertyBar : public QWidget
{
Q_OBJECT
public:
    explicit PropertyBar(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
private:
    int nselected;
    QList <Element*> elements;

signals:

public slots:

};

#endif // PROPERTYBAR_H
