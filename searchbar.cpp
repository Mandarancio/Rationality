#include "searchbar.h"
#include <QPainter>

SearchBar::SearchBar(QWidget *parent) :
    QWidget(parent)
{
}

void SearchBar::paintEvent(QPaintEvent *e){
    QPainter p(this);
    QColor bg(54,102,164);
    QColor l1(102,157,206);

//    QLinearGradient lg1(0,height()-4,0,height());
//    QColor c1(0,0,0,85);
//    QColor c2(0,0,0,0);
//    lg1.setColorAt(0,c1);
//    lg1.setColorAt(1,c2);
//    p.setPen(Qt::transparent);
//    p.setBrush(lg1);
//    p.drawRect(8,height()-4,width()-5,4);
//
//    lg1.setStart(8,height()-7);
//    lg1.setFinalStop(4,height()-2);
//    p.setBrush(lg1);
//    p.drawRect(2,height()-10,6,10);

//    lg1.setStart(4,0);
//    lg1.setFinalStop(0,0);
//    p.setBrush(lg1);
//    p.drawRect(0,0,4,height()-10);

    p.setBrush(bg);
    p.setPen(Qt::transparent);
    p.setRenderHint(p.Antialiasing);

    p.setPen(l1);

    p.drawRoundedRect(5,0,width()-5,height()-5,6,6);
    p.drawRect(5,0,10,10);
    p.drawRect(width()-15,0,15,height()-5);

    p.setPen(Qt::transparent);
    p.drawRect(6,0,this->width()-6,12);
    p.drawRect(width()-16,0,16,height()-6);

    p.setPen(bg);
    p.drawLine(6,0,6,12);
    p.drawLine(width()-17,height()-6,width(),height()-6);
//
//    p.setPen(l1);
    //p.drawLine(0,height()-5,width(),height()-5);


    e->accept();
}
