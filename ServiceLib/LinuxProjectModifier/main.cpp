#include "LinuxProjectModifier.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LinuxProjectModifier w;
    w.show();
    return a.exec();
}
