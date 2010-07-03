#ifndef FILTER_H
#define FILTER_H

#include <QString>


enum filterType { SUM , INTERSECT, DIFFERENCE, XOR};

struct filter {
    QString tag;
    filterType type;
};


#endif // FILTER_H
