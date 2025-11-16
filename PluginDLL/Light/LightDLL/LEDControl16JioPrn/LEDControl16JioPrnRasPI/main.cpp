#include "LEDControl16JioPrnRasPIMain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LEDControl16JioPrnRasPIMain w;
    w.show();

    return a.exec();
}
