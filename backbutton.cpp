#include "backbutton.h"
#include <QPainter>

BackButton::BackButton(QWidget *parent) :
    QToolButton(parent)
{
}

void BackButton::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.setRenderHint(p.Antialiasing);
    int xc=this->width()/2;
    int yc=this->height()/2;

    QColor c1(54,102,164);
    QPen p1;

    if (this->isEnabled()){
        c1.setRgb(54,102,164);
    }
    else {
        c1= Qt::darkGray;
    }

    p1.setCapStyle(Qt::RoundCap);
    p1.setWidth(3);
    p1.setColor(c1);
    p.setPen(p1);
    p.drawLine(xc-5,yc+1,xc,yc-4);
    p.drawLine(xc-5,yc+1,xc,yc+6);
    p.setPen(Qt::transparent);
    p.setBrush(c1);
    p.drawEllipse(xc+1,yc-1,4,4);
    p.drawEllipse(xc+6,yc-1,4,4);


    e->accept();
}
