#include "leftbar.h"
#include <QPainter>


LeftBar::LeftBar(QWidget *parent) :
    QWidget(parent)
{
}

void LeftBar::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.setRenderHint(p.Antialiasing);
    QColor lightBlue(223,228,235);
    p.setBrush(lightBlue);
    p.setPen(Qt::transparent);
    p.drawRect(0,0,this->width(),this->height());


   /* QLinearGradient lg1(this->width()-4,0,this->width()-1,0);
    QColor c1(0,0,0,85);
    QColor c2(0,0,0,0);
    lg1.setColorAt(0,c1);
    lg1.setColorAt(1,c2);
    p.setPen(Qt::transparent);
    p.setBrush(lg1);
    p.drawRect(this->width()-5,0,this->width(),this->height());*/
    e->accept();
}
