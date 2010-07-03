#ifndef RELATIONBAR_H
#define RELATIONBAR_H

#include <QWidget>
#include <QPaintEvent>

class RelationBar : public QWidget
{
Q_OBJECT
public:
    explicit RelationBar(QWidget *parent = 0);


protected:
    void paintEvent(QPaintEvent *);
private:


public slots:

};

#endif // RELATIONBAR_H
