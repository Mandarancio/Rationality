#include "relationbar.h"
#include <QPainter>
#include <QLinearGradient>

RelationBar::RelationBar(QWidget *parent) :
    QWidget(parent)
{
}


void RelationBar::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.setRenderHint(p.Antialiasing);
    QColor g1(67,67,67);
    QColor g2(77,77,77);
    QLinearGradient lg(0,0,0,this->height());
    lg.setColorAt(0,g1);
    lg.setColorAt(0.5,g2);
    lg.setColorAt(1,g2);
    p.setPen(Qt::transparent);
    p.setBrush(lg);
    p.drawRect(0,0,width(),height());
    e->accept();
}
