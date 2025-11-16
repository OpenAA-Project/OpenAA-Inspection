#include "GeneralDisplayWholeImageForm.h"
#include "XGUIFormBase.h"

GeneralDisplayWholeImageForm::GeneralDisplayWholeImageForm(LayersBase *Base ,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	LBase=Base;
}

GeneralDisplayWholeImageForm::~GeneralDisplayWholeImageForm()
{
}

void GeneralDisplayWholeImageForm::keyPressEvent(QKeyEvent *event)
{
	GUIFormBase	*DisplayNGList=LBase->FindByName("Button" ,"DisplayNGListButton" ,"");
	if(DisplayNGList==NULL){
		return;
	}
	QCoreApplication::sendEvent(DisplayNGList,event);
}

void GeneralDisplayWholeImageForm::closeEvent(QCloseEvent *event)
{
	event->ignore();
}
