#ifndef CHECKKEYCODE_H
#define CHECKKEYCODE_H

#include <QMainWindow>
#include "ui_CheckKeyCode.h"
#include <QKeyEvent>

class CheckKeyCode : public QMainWindow
{
	Q_OBJECT

public:
	CheckKeyCode(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~CheckKeyCode();

private:
	Ui::CheckKeyCodeClass ui;

	virtual	void	keyPressEvent ( QKeyEvent * event )	override;
};

#endif // CHECKKEYCODE_H
