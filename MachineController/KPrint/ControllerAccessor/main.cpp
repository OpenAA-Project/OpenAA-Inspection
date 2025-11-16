#include "ControllerAccessor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControllerAccessor w;
    w.show();
    return a.exec();
}
