#include "xmldb_makedatthread.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMLDB_MakeDatThread w;
    w.show();
    return a.exec();
}
