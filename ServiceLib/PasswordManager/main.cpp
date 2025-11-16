#include <QApplication>

#include "PasswordManager.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PasswordManager pwm;

	pwm.show();

	return a.exec();
}