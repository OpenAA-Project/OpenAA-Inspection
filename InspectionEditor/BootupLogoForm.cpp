#include "InspectionEditorResource.h"
#include "BootupLogoForm.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"

BootupLogoForm::BootupLogoForm(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
	FileRegistry	FRegistry(/**/"MachineInfo.dat");
	int	LanguageCode=FRegistry.LoadRegInt(/**/"Language",0);
	switch(LanguageCode){
		case 1:
			ui.label->setText(/**/"On booting...");
			break;
	}
}

BootupLogoForm::~BootupLogoForm()
{

}
