#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QPaintEvent>

class SearchBar : public QWidget
{
Q_OBJECT
public:
    explicit SearchBar(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // SEARCHBAR_H
