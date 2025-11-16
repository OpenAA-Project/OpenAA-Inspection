#ifndef LOTBINDER_H
#define LOTBINDER_H

#include <QMainWindow>
#include "ui_LotBinder.h"

class LotBinder : public QMainWindow
{
	Q_OBJECT

public:
	LotBinder(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LotBinder();

private:
	Ui::LotBinderClass ui;
};

#endif // LOTBINDER_H
