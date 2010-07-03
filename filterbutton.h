#ifndef FILTERBUTTON_H
#define FILTERBUTTON_H

#include <QToolButton>
#include <QPaintEvent>

class FilterButton : public QToolButton
{
Q_OBJECT
public:
    explicit FilterButton(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // FILTERBUTTON_H
