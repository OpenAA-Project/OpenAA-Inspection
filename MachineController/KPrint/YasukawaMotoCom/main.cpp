#include "YasukawaMotoCom.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YasukawaMotoCom w;
    w.show();
    return a.exec();
}
