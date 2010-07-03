#ifndef FORWARDBUTTON_H
#define FORWARDBUTTON_H

#include <QToolButton>
#include <QPaintEvent>

class ForwardButton : public QToolButton
{
Q_OBJECT
public:
    explicit ForwardButton(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // FORWARDBUTTON_H
