#include "AutoReStart.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AutoReStart w;
    w.show();
    return a.exec();
}
