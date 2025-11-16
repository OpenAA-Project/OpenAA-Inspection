#include "xmldb_makedat.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XMLDB_MakeDat w;
    w.show();
    return a.exec();
}
