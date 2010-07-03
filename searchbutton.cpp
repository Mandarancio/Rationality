    #include "searchbutton.h"
#include <QPainter>
#include <QPen>

SearchButton::SearchButton(QWidget *parent) :
    QToolButton(parent)
{
    this->setCheckable(true);
}

void SearchButton::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.setRenderHint(p.Antialiasing);
    QColor fg;
    if (this->isChecked()){
        QColor c1,c2;
        QLinearGradient lg1(0,0,0,this->height());
        c1.setRgb(54,102,164);
        c2.setRgb(102,157,206);
        p.setPen(c1);
        lg1.setColorAt(0,c2);
        lg1.setColorAt(1,c1);
        p.setBrush(lg1);
        p.drawRect(0,0,this->width(),this->height());
        fg.setRgb(255,255,255);
    }
    else fg.setRgb(60,60,60);
    QPen p1;
    p1.setColor(fg);
    p1.setWidth(4);
    p1.setCapStyle(Qt::RoundCap);
    p.setBrush(Qt::transparent);
    p.setPen(p1);
    int xc,yc;
    xc=this->width()/2;
    yc=this->height()/2;
    p.drawEllipse(xc-7,yc-6,10,10);
    p.drawLine(xc+2,yc+4,xc+5,yc+8);

    e->accept();
}
