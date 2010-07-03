#ifndef BACKBUTTON_H
#define BACKBUTTON_H

#include <QToolButton>
#include <QPaintEvent>

class BackButton : public QToolButton
{
Q_OBJECT
public:
    explicit BackButton(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // BACKBUTTON_H
