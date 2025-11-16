#ifndef CHANGEGUI_H
#define CHANGEGUI_H

#include <QMainWindow>
#include "ui_ChangeGUI.h"

class ChangeGUI : public QMainWindow
{
	Q_OBJECT

public:
	ChangeGUI(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ChangeGUI();

private:
	Ui::ChangeGUIClass ui;
};

#endif // CHANGEGUI_H
