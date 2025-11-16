#include "ControllerAccessorRPI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControllerAccessorRPI w;
    w.show();
    return a.exec();
}
