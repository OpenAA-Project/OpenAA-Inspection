#include "cltSimulator.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    cltSimulator w;
    w.show();
    return a.exec();
}
