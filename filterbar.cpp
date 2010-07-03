#include "filterbar.h"
#include <QPainter>
#include <QFont>
#include <QFontMetrics>
#include <QDebug>

void paintIntersection(QPainter &p){

    QColor c(60,60,60);
    QPen p1;
    p1.setColor(c);
    p1.setWidth(2);

    p.setPen(p1);
    p.setBrush(Qt::transparent);

    p.drawEllipse(-5,-5,10,10);
    p.drawEllipse(0,-5,10,10);

    p.setPen(Qt::transparent);
    p.setBrush(c);

    p.drawChord(-5,-5,10,10,(360-60)*16,120*16);
    p.drawChord(0,-5,10,10,(180-60)*16,120*16);

    p.setPen(p1);
    p.drawLine(3,-2,3,2);

}

void paintSum(QPainter &p){

    QColor c(60,60,60);
    p.setBrush(c);

    p.drawEllipse(-5,-5,10,10);
    p.drawEllipse(0,-5,10,10);

}

void paintXOR(QPainter &p){
    QColor g(191,191,191);

    QColor c(60,60,60);
    QPen p1;
    p1.setColor(c);
    p1.setWidth(2);

    p.setPen(p1);
    p.setBrush(c);

    p.drawEllipse(-5,-5,10,10);
    p.drawEllipse(0,-5,10,10);

    p.setPen(Qt::transparent);
    p.setBrush(g);

    p.drawChord(-5,-5,10,10,(360-60)*16,120*16);
    p.drawChord(0,-5,10,10,(180-60)*16,120*16);

    p.setPen(g);
    p.drawLine(3,-2,3,2);

}

FilterBar::FilterBar(QWidget * parent) :
        QWidget(parent)
{
    index=0;
    add("Root");
    t=HISTORY;
}

void FilterBar::add(QString tag){
    history.push_back(tag);
    QFont f;
    f.setFamily("URW Gothic L");
    //f.setBold(true);
    f.setPixelSize(16);
    QFontMetrics fm(f);
    int h=fm.height();
    int w=fm.width(tag);
    int yc=(height()-(h+4))/2;
    int xc=15;
    if (historyButton.length()>0) xc=historyButton[historyButton.length()-1].x()+historyButton[historyButton.length()-1].width()+25;
    QRect R(xc,yc+4,w,h);
    historyButton.push_back(R);
}

void FilterBar::paintEvent(QPaintEvent *e){
    if (history.length()>0 && t==HISTORY){
        QPainter p(this);
        QColor fg(60,60,60);

        p.setRenderHint(p.Antialiasing);
        QFont f;
        f.setFamily("URW Gothic L");
//        f.setBold(true);
        f.setPixelSize(16);
        p.setFont(f);

        for (int i=0; i<history.length();i++){
            p.setPen(fg);

            if (index==i) {
                f.setBold(true);
                p.setFont(f);
                QFontMetrics fm(f);
                historyButton[i].setWidth(fm.width(history[i]));
            }
            else if (f.bold()) {
                f.setBold(false);
                p.setFont(f);

            }


            p.drawText(historyButton[i],Qt::AlignCenter,history[i]);
            if (i<history.length()-1) {
                QPen p1;

                p1.setColor(fg);
                p1.setWidth(3);
                p1.setCapStyle(Qt::RoundCap);

                p.setPen(p1);

                int xc,yc;
                xc=historyButton[i].x()+historyButton[i].width()+12;
                yc=height()/2-1;
                    
                p.drawLine(xc+2,yc+3,xc-1,yc);
                p.drawLine(xc+2,yc+3,xc-1,yc+6);
            }
        }

    }
    else {
        QPainter p(this);
        p.setRenderHint(p.Antialiasing);
        QFont f;
        f.setFamily("URW Gothic L");
//        f.setBold(true);
        f.setPixelSize(16);
        p.setFont(f);

        QColor fg(60,60,60);
        p.setPen(fg);
        QFontMetrics fm(f);
        int x=10;
        int y=height()/2-fm.height()/2;
        for (int i=0; i<filters.length();i++){
            QRect r(x,y,fm.width(filters[i]),fm.height());
            p.drawText(r,Qt::AlignCenter,filters[i]);
            if (i<filters.length()-1){
                p.save();
                p.translate(x+fm.width(filters[i])+19,height()/2+1);
                paintIntersection(p);
                p.restore();
            }
            x+=fm.width(filters[i])+40;
        }
    }
    e->accept();
}

void FilterBar::open(QString tag){

    if (history.contains(tag)){
        index=history.indexOf(tag);

        if (index==0) emit isFirst(!true);
        else emit isFirst(!false);
        if (index==history.length()-1) emit isLast(!true);
        else emit isLast(!false);

        emit currentDir(tag,false);
        this->update();
        return;
    }
    else {
        if (index==history.length()-1){
            add(tag);
            index++;
            this->update();
            emit isFirst(!false);
        }
        else {
            QList <QString> t1;
            QList <QRect> t2;
            for (int i=0; i<=index;i++){
                t1.push_back(history[i]);
                t2.push_back(historyButton[i]);
            }
            history.clear();
            historyButton.clear();
            for (int i=0; i<=index;i++){
                history.push_back(t1[i]);
                historyButton.push_back(t2[i]);
            }

            add(tag);
            index++;
            emit isLast(!true);
            emit isFirst(!false);
            this->update();
        }
    }


}

void FilterBar::back(){
    if (index>0 && t==HISTORY){
        index--;

        if (index == 0) emit isFirst(!true);
        if (index == history.length()-2) emit isLast(!false);
        emit currentDir(history[index],false);
        this->update();
        for (int i=0;i<history.length();i++)
            qWarning()<<history[i];
    }
}

void FilterBar::forward(){
    if (index<history.length()-1 && t==HISTORY){
        index++;
        if (index==1) emit isFirst(!false);
        if (index==history.length()-1) emit isLast(!true);
        emit currentDir(history[index],false);
        this->update();
    }
    else if (t!=HISTORY){
        t==HISTORY;
        this->update();
    }
}


void FilterBar::filter(QString filter){
    if (t!=FILTER) filters.clear();
    if (filters.isEmpty()){
        filters.push_back(history[index]);
        filters.push_back(filter);
        t=FILTER;

    }
    else {
        filters.push_back(filter);
    }
    this->update();
        emit isFirst(!false);
        emit isLast(!true);
}

void FilterBar::setHistory(){
    qWarning("HERE");
    t=HISTORY;
    filters.clear();
    this->update();
    emit currentDir(history[index],false);
}
