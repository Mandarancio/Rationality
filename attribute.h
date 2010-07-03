#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QObject>

class Attribute : public QObject
{
Q_OBJECT
public:
    explicit Attribute(QObject *parent = 0);
protected:
    QString name;
    int visualization;
    QList <Attribute> parents;
signals:

public slots:

};

#endif // ATTRIBUTE_H
