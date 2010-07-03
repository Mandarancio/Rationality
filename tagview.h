#ifndef TAGVIEW_H
#define TAGVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>

class TagView : public QWidget
{
Q_OBJECT
public:
    explicit TagView(QString name,int priority=1,QWidget *parent = 0);
    void setPriority(int p);
protected:
    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
private:
    QFont font;
    QString name;
    int nrow;
    int priority;
signals:
    void openTag(QString name);

public slots:

};

#endif // TAGVIEW_H
