#include "propertybar.h"
#include <QPainter>

PropertyBar::PropertyBar(QWidget *parent) :
    QWidget(parent)
{
}

void PropertyBar::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.setRenderHint(p.Antialiasing);

    e->accept();
}
