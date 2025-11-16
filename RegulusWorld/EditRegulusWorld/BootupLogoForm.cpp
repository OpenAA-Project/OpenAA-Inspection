#include "BootupLogoForm.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"

BootupLogoForm::BootupLogoForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	int	LanguageCode=FRegistry.LoadRegInt(/**/"Language",0);
	switch(LanguageCode){
		case 1:
			ui.label->setText(/**/"On booting...");
			break;
		case 2:
			ui.label->setText(/**/"正在启动...");
			break;
		case 3:
			ui.label->setText(/**/"正在啟動...");
			break;
		case 4:
			ui.label->setText(/**/"부팅...");
			break;
	}
}

BootupLogoForm::~BootupLogoForm()
{

}
