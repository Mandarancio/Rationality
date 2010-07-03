#include "folderview.h"
#include <QPainter>
#include <QDebug>
#include <QLinearGradient>

#include "filedatabase.h"
#include "filter.h"

FolderView::FolderView(QWidget *parent) :
    QWidget(parent)
{
    location="Root";

  //  this->setStyleSheet("Background: trasparent;");
    fdb = new FileDatabase(this);

//    QList <Element*> els;
//    fdb->setLocation(location);
//    els=fdb->Elements();
//    int x,y;
//    x=10;
//    y=5;
//
//    for (int i=0; i<els.length();i++){
//        Relation * r;
//        if (!i)
//            r = new Relation(els[i],true,false,this);
//        else
//            r = new Relation(els[i],false,false,this);
//        if (x+150 > this->width() && i>0 ) {
//            x=10;
//            y+=102;
//        }
//        r->setGeometry(x,y,150,82);
//        x+=15+150;
//        relations.push_back(r);
//        connect(r,SIGNAL(updateGrid()),this,SLOT(updateGrid()));
//        connect(r,SIGNAL(open(QString)),this,SLOT(open(QString)));
//        connect(r,SIGNAL(skip(QString)),this,SLOT(skip(QString)));
//    }


    open("Root",false);
}


void FolderView::paintEvent(QPaintEvent *e ){
    QPainter p(this);
    QColor c(215,215,215);
    QLinearGradient l1(0,0,0,height());
    l1.setColorAt(0,Qt::lightGray);
    l1.setColorAt(1,c);
    p.setBrush(l1);
    p.setPen(Qt::transparent);

    p.drawRect(0,0,this->width(),this->height());
    e->accept();
    filtre=false;
}


void FolderView::updateGrid(){
    int x=10;
    int y=5;
    for (int i=0; i<relations.length();i++){
           if (x+150 > this->width() && i>0 ) {
                x=10;
                y+=102;
            //    QScrollBar * sb= new QScrollBar(this);
            //    if ((y+102)>this->height()) this->setVerticalScrollBar(sb);
           }
           relations[i]->setGeometry(x,y,150,82);
           x+=150+15;
    }
}

void FolderView::open(QString tag,bool emitSignal){
    filtre=false;
    emit this->isFiltred(filtre);
    filters.clear();
    fdb->clearFilters();
    for (int i=0; i<relations.length();i++){
        delete relations[i];
    }
    relations.clear();

    //qWarning()<<"Open "<<tag;
    location=tag;
    //FileDatabase * fdb = new FileDatabase(this);

    QList <Element*> els;
    fdb->setLocation(location);
    els=fdb->Elements();

    relations.clear();
    int x,y;
    x=10;
    y=5;
    for (int i=0; i<els.length();i++){
        Relation * r;
        if (i==0)
            r = new Relation(els[i],true,false,this);
        else
            r = new Relation(els[i],false,false,this);
        if (x+160 > this->width() && i>0 ) {
            x=10;
            y+=170;
        }
        r->setGeometry(x,y,160,130);
        x+=15+160;
        r->setFixedWidth(160);
        r->setFixedHeight(130);
        r->show();
        relations.push_back(r);
        connect(r,SIGNAL(updateGrid()),this,SLOT(updateGrid()));
        connect(r,SIGNAL(open(QString)),this,SLOT(open(QString)));
        connect(r,SIGNAL(skip(QString)),this,SLOT(skip(QString)));
        connect(r,SIGNAL(filter(QString)),this,SLOT(filter(QString)));
    }
    this->updateGeometry();
    if (emitSignal) emit currentDir(tag);
}

void FolderView::skip(QString tag){
    emit currentDir(tag);
}

void FolderView::filter(QString f){
    filtre=true;
    emit this->isFiltred(filtre);
    emit this->setFilter(f);
    if (filters.isEmpty()){/*
        filter f0;
        filter f1;
        f0.tag=location;
        f0.type=INTERSECT;
        f1.tag=f;
        f1.type=INTERSECT;*/
        filters.push_back(location);
        filters.push_back(f);
        fdb->appendFilter(location);
        fdb->appendFilter(f);
    }
    else {
//        filter f0;
//        f0.tag=f;
//        f0.type=INTERSECT;
        filters.push_back(f);
        fdb->appendFilter(f);
    }
    showFiltred();
}

void FolderView::showFiltred(){
    for (int i=0; i<relations.length();i++){
        delete relations[i];
    }
    relations.clear();


    QList <Element*> els;
    els=fdb->filtredElements();

    relations.clear();
    int x,y;
    x=10;
    y=5;
    for (int i=0; i<els.length();i++){
        Relation * r;
        if (i==0)
            r = new Relation(els[i],true,false,this);
        else
            r = new Relation(els[i],false,false,this);
        if (x+160+15 > this->width() && i>0 ) {
            x=10;
            y+=170;
        }
        r->setGeometry(x,y,150,180);
        r->setFixedHeight(180);
        x+=15+160;
        r->show();
        relations.push_back(r);
        connect(r,SIGNAL(updateGrid()),this,SLOT(updateGrid()));
        connect(r,SIGNAL(open(QString)),this,SLOT(open(QString)));
        connect(r,SIGNAL(skip(QString)),this,SLOT(skip(QString)));
        connect(r,SIGNAL(filter(QString)),this,SLOT(filter(QString)));
    }
    this->updateGeometry();

}
