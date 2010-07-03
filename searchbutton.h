#ifndef SEARCHBUTTON_H
#define SEARCHBUTTON_H

#include <QToolButton>
#include <QPaintEvent>

class SearchButton : public QToolButton
{
Q_OBJECT
public:
    explicit SearchButton(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

};

#endif // SEARCHBUTTON_H
