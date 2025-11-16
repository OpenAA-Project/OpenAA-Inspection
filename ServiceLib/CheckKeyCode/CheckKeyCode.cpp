#include "CheckKeyCode.h"

CheckKeyCode::CheckKeyCode(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	grabKeyboard();
}

CheckKeyCode::~CheckKeyCode()
{

}

void	CheckKeyCode::keyPressEvent ( QKeyEvent * event )
{
	int	Key=event->key();

	ui.lineEditDec	->setText(QString::number(Key,10));
	ui.lineEditHex	->setText(QString::number(Key,16));
	ui.lineEditBin	->setText(QString::number(Key,2));
}

