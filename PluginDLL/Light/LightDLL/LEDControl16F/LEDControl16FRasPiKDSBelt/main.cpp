#include "LEDControl16FRasPiKDSBelt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LEDControl16FRasPiKDSBelt w;
    w.show();

    return a.exec();
}
