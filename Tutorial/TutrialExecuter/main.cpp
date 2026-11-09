#include "TutrialExecuter.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TutrialExecuter window;
    window.show();
    return app.exec();
}
