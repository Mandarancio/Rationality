#ifndef PANELBUTTON_H
#define PANELBUTTON_H

#include <QComboBox>
#include <QMouseEvent>
#include <QPaintEvent>

class PanelButton : public QComboBox
{
Q_OBJECT
public:
    explicit PanelButton(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
//    void mousePressEvent(QMouseEvent *);
private:
signals:

public slots:

};

#endif // PANELBUTTON_H
