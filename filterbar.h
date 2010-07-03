#ifndef FILTERBAR_H
#define FILTERBAR_H

#include <QWidget>
#include <QPaintEvent>
#include <QRect>
#include <QList>
enum type {HISTORY, FILTER, SEARCH, EDIT};

class FilterBar : public QWidget
{
    Q_OBJECT
public:
    FilterBar(QWidget * parent);
    void add(QString tag);
    void setType(type t);
protected:
    void paintEvent(QPaintEvent *);
private:
    QList <QString> history;
    QList <QRect> historyButton;
    QList <QString> filters;
    QString search;
    int index;
    type t;

signals:
    void currentDir(QString tag,bool signal);
    void isLast(bool E);
    void isFirst(bool E);

public slots:
    void setHistory();
    void open(QString tag);
    void back();
    void forward();
    void filter(QString filter);

};

#endif // FILTERBAR_H
