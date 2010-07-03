#include <QtGui/QApplication>
#include "rationality.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Rationality w;
    w.show();
    return a.exec();
}
