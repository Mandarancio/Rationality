#include "panelbutton.h"
#include <QPainter>
#include <QLinearGradient>

PanelButton::PanelButton(QWidget *parent) :
    QComboBox(parent)
{
   // active=false;
}

void PanelButton::paintEvent(QPaintEvent * e){
    QPainter p(this);
    p.setRenderHint(p.Antialiasing);
    QColor lB(223,228,235);
    QColor lB2(203,208,215);
    QLinearGradient lg(0,0,0,height());


        lg.setColorAt(0,lB);
        lg.setColorAt(1,lB2);



    p.setBrush(lg);
    p.setPen(Qt::transparent);

    p.drawRect(0,0,width()-5,height());

    QColor lB3(183,188,195);
    p.setPen(lB3);
    p.drawLine(0,this->height(),this->width()-5,this->height());

    if (count()>0) {
        QColor fc(60,60,60);
        p.setPen(fc);
        QFont font;
        //font.setBold(true);
        font.setFamily("URW Gothic L");

        p.setFont(font);

        QRect trect(0,0,width()-5,height());
        p.drawText(trect,Qt::AlignCenter,this->itemText(currentIndex()));
    }
    e->accept();
}


