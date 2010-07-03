#ifndef LEFTBAR_H
#define LEFTBAR_H

#include <QWidget>
#include <QPaintEvent>

class LeftBar : public QWidget
{
Q_OBJECT
public:
    explicit LeftBar(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // LEFTBAR_H
