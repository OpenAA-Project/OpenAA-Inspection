#include "LEDControl16GRP.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LEDControl16GRP w;
    w.show();

    return a.exec();
}
