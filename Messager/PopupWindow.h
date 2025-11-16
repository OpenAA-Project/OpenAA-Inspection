#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QWidget>
#include "ui_PopupWindow.h"

class PopupWindow : public QWidget
{
	Q_OBJECT

public:
	PopupWindow(QString MessageStr,QWidget *parent = 0);
	~PopupWindow();

	void	ShowMessage(QString Msg);
private:
	Ui::PopupWindowClass ui;
};

#endif // POPUPWINDOW_H
