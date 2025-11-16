#ifndef MAKELOCKSTARKEY_H
#define MAKELOCKSTARKEY_H

#include <QMainWindow>
#include "ui_MakeLockStarKey.h"

class MakeLockStarKey : public QMainWindow
{
	Q_OBJECT

public:
	MakeLockStarKey(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~MakeLockStarKey();

private:
	Ui::MakeLockStarKeyClass ui;
};

#endif // MAKELOCKSTARKEY_H
