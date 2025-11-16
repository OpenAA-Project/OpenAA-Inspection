#include "xmlserver_if.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMLServer_IF w;
    w.show();
    return a.exec();
}
