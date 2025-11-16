#include "xmlserver2.h"

#include <QtGui>
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	clsParamDef *prm = clsParamDef::GetInstance();
	prm->readParam();
	XMLServer2 w;
	w.show();
	return a.exec();
}
