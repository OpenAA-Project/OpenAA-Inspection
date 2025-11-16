#ifndef STARTCLOSEONCE_H
#define STARTCLOSEONCE_H

#include <QMainWindow>
#include "ui_StartCloseOnce.h"

class StartCloseOnce : public QMainWindow
{
	Q_OBJECT

public:
	StartCloseOnce(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~StartCloseOnce();

private:
	Ui::StartCloseOnceClass ui;
};

#endif // STARTCLOSEONCE_H
