#include "tagview.h"
#include <QPainter>
#include <QFont>
#include <QFontMetrics>


TagView::TagView(QString name,int priority,QWidget *parent) :
    QWidget(parent)
{
    this->name=name;
    this->priority=priority;

    switch (priority){
    case 1: font.setBold(true);
            font.setPixelSize(10);
            break;
    case 2:
            font.setBold(false);
            font.setPixelSize(10);
            break;
    case 3:
            font.setBold(true);
            font.setPixelSize(9);
            break;
    case 4:
            font.setBold(false);
            font.setPixelSize(9);
            break;
    default:
            font.setBold(false);
            font.setPixelSize(10);
    }
    QFontMetrics fm(font);
    if (fm.width(name)>100){ nrow=2;
    }
    else {this->nrow=1;
        this->setFixedSize(fm.width(name)+10,fm.height()+6);
    }
}

void TagView::setPriority(int p){
    priority=p;
}

void TagView::paintEvent(QPaintEvent *e){
    QPainter p(this);
    p.setRenderHints(p.Antialiasing);
    QFontMetrics fm(font);
    QColor white(255,255,255,100);
    if (nrow==1){
        p.setFont(font);
        p.setPen(Qt::transparent);
        p.setBrush(white);
        int w=fm.width(name)+10;
        int h=fm.height()+6;
        p.drawRoundedRect(0,0,w,h,3,3);
        QRect trect(5,3,w-10,h-6);
        p.setPen(Qt::darkGray);
        p.drawText(trect,Qt::AlignCenter,name);
    }
    else if (nrow==2){}
    else e->ignore();
    e->accept();
}

void TagView::mouseDoubleClickEvent(QMouseEvent *e){
    emit openTag(name);
    e->accept();
}


