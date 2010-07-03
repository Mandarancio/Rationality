#include "relation.h"


#include <QPainter>
#include <QFontMetrics>
#include <QDebug>
#include <tagview.h>
#include <QDesktopServices>
#include <QUrl>

Relation::Relation(bool first, bool last, QWidget *parent) :
        QWidget(parent)
{
    relations=false;
    this->parent=parent;
    element= new Element(this);
    element->setName("");

    this->first=first;
    //  this->relations=relation;
    this->last=last;

    if (first && last) {
        this->first=false;
        this->last=false;
    }
}

Relation::Relation(Element *e,bool first, bool last, QWidget *parent) :
        QWidget(parent)
{
    relations=false;
    this->parent=parent;
    element=e;
    this->first=first;
    this->last=last;

    if (first && last) {
        this->first=false;
        this->last=false;
    }

}

Relation::~Relation(){
    for (int i=0; i< tags.length();i++){
        tags[i]->hide();
        delete tags[i];
    }
    tags.clear();

}

void Relation::paintEvent(QPaintEvent * e){
    QPainter p(this);
    p.setRenderHint(p.Antialiasing);
    p.setPen(Qt::transparent);
    QColor icon(255,255,255,255);
    if (!element->isARelation()) icon.setRgb(190,255,190);
    QColor white(255,255,255,100);
    QColor bgSelected(255,255,255,65);


    if (relations) {
        p.setBrush(bgSelected);
        p.setPen(Qt::transparent);
        p.drawRoundedRect(0,0,width(),height(),4,4);
    }
    p.setBrush(icon);
    if (element->isARelation()){
        QImage icon= QImage("/home/martino/Progetti/Rationality/Resource/tagIcon.png");
        p.drawImage(0,0,icon);
    }
    else {
        QImage icon= QImage("/home/martino/Progetti/Rationality/Resource/fileIcon.png");
        p.drawImage(0,0,icon);
    }
    p.setBrush(white);


    p.setPen(Qt::black);
    QFont font;
    font.setPixelSize(14);
    font.setBold(true);
    font.setFamily("URW Gothic L");
    //font.setBold(true);
    QFontMetrics fm(font);
    int size=14;
    while ( fm.width(element->Name())>this->width()-62){
        size--;
        font.setPixelSize(size);
        fm= QFontMetrics(font);
    }
    QRect trect(80,7,fm.width(element->Name()),fm.height());
    p.setFont(font);
    p.drawText(trect,element->Name());
    font.setBold(false);
    if (element->isARelation()){
        int h=fm.height();
        font.setPixelSize(12);
        p.setFont(font);
        QString s="Has "+QString::number(element->Tags().length())+" child";
        fm=QFontMetrics(font);
        QRect rr(80,7+h-4,fm.width(s),h);
        p.drawText(rr,s);
    }
    else {
        QString descr=element->Description();
        int h=fm.height();
        font.setPixelSize(12);
        p.setFont(font);
        fm=QFontMetrics(font);
        QRect r1(80,7+h-3,fm.width(descr),fm.height());
        p.drawText(r1,descr);
    }
    //    }
    e->accept();
}

void Relation::mouseDoubleClickEvent(QMouseEvent *e){
    if (element->isARelation()){
        for (int i=0; i< tags.length();i++){
            tags[i]->hide();
            delete tags[i];
        }
        tags.clear();
        emit open(element->Name());
        e->accept();
    }
    else {
        QDesktopServices::openUrl(QUrl(element->Path()+element->Name()));
    }
}

void Relation::mousePressEvent(QMouseEvent *m){
    qWarning()<<"Click";
    if (!relations) {
        if (m->button()==Qt::LeftButton && (m->pos().x()>=7 && m->pos().x()<=64+7) && (m->y()>=7 && m->y()<=64+7))  {
            relations=true;
            int l=element->Tags().length();
            if (l>4) l=4;
            if (l>0){
                TagView * tg;
                for (int i=0; i<l;i++){
                    tg = new TagView(element->Tags()[i],i,this->parent);
                    connect(tg,SIGNAL(openTag(QString)),this, SLOT(tagEventM(QString)));
                    tg->show();
                    tags.push_back(tg);
                    switch(i){
                    case 0:
                        tg->setGeometry(x()-5,y()+60,100,20);
                        break;
                    case 1:
                        tg->setGeometry(x()+60,y()+25,100,20);
                        break;
                    case 2:
                        tg->setGeometry(x()+100,y()+48,100,20);
                        break;
                    case 3:
                        tg->setGeometry(x()+60,y()+50,100,20);
                    }
                }
            }
            emit updateGrid();
            m->accept();

        }
        else m->ignore();
    }
    else {
        if (m->button()==Qt::LeftButton && (m->pos().x()>=5 && m->pos().x()<=52+5) && (m->y()>=5 && m->y()<=52+5))  {
            relations=false;
            for (int i=0; i< tags.length();i++){
                tags[i]->hide();
                delete tags[i];
            }
            tags.clear();
            emit updateGrid();

            m->accept();
        }
        else m->ignore();
    }
    this->update();
}

void Relation::tagEventM(QString tag){
    if (element->isARelation()){
        emit skip(element->Name());
        emit open(tag);
    }
    else {
        emit filter(tag);
    }
}

void Relation::moveEvent(QMoveEvent *e){
    QPoint op=e->oldPos();
    QPoint np=e->pos();
    if (relations){
        for (int i=0; i<tags.length();i++){
            tags[i]->setGeometry(op.x()-tags[i]->x()+np.x(),op.y()-tags[i]->y()+np.y(),tags[i]->width(),tags[i]->height());
        }
    }
}
