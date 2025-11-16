#include "PopupWindow.h"
#include "XGeneralFunc.h"

PopupWindow::PopupWindow(QString MessageStr,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::WindowStaysOnTopHint);
	
	SetWidgetCenter(this);
}

PopupWindow::~PopupWindow()
{

}
void	PopupWindow::ShowMessage(QString Msg)
{
	ui.label->setText(Msg);
}
