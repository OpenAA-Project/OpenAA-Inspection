#ifndef REPAIRGUIMAIN_H
#define REPAIRGUIMAIN_H

#include <QMainWindow>
#include "ui_RepairGUIMain.h"

class RepairGUIMain : public QMainWindow
{
	Q_OBJECT

public:
	RepairGUIMain(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~RepairGUIMain();

private:
	Ui::RepairGUIMainClass ui;
};

#endif // REPAIRGUIMAIN_H
