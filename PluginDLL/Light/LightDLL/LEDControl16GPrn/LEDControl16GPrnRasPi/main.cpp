#include "LEDControl16GPrnRasPi.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LEDControl16GPrnRasPi w;
    w.show();

    return a.exec();
}
