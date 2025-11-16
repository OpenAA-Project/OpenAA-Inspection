#include "DynamicClassifyImagePanelResource.h"
#include "SelectAreaDialog.h"
#include "XGeneralFunc.h"


bool	SelectAreaMode::Load(QIODevice *f)
{
	if(::Load(f,CopyModeItem)==false)
		return false;
	if(::Load(f,CopyModeCore)==false)
		return false;
	if(::Load(f,CopyModeMaxZone)==false)
		return false;
	if(::Load(f,CopyModeMinZone)==false)
		return false;
	if(::Load(f,CopyModeBare)==false)
		return false;
	if(::Load(f,CopyModeInside)==false)
		return false;
	if(::Load(f,CopyModeOutlineI)==false)
		return false;
	if(::Load(f,CopyModeOutlineT)==false)
		return false;
	if(::Load(f,CopyModeOutlineO)==false)
		return false;
	return true;
}
bool	SelectAreaMode::Save(QIODevice *f)
{
	if(::Save(f,CopyModeItem)==false)
		return false;
	if(::Save(f,CopyModeCore)==false)
		return false;
	if(::Save(f,CopyModeMaxZone)==false)
		return false;
	if(::Save(f,CopyModeMinZone)==false)
		return false;
	if(::Save(f,CopyModeBare)==false)
		return false;
	if(::Save(f,CopyModeInside)==false)
		return false;
	if(::Save(f,CopyModeOutlineI)==false)
		return false;
	if(::Save(f,CopyModeOutlineT)==false)
		return false;
	if(::Save(f,CopyModeOutlineO)==false)
		return false;
	return true;
}


SelectAreaDialog::SelectAreaDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SelectAreaDialog::~SelectAreaDialog()
{

}


void SelectAreaDialog::on_pushButtonCopy_clicked()
{
	Mode.CopyModeItem		=ui.toolButtonItemArea		->isChecked();
	Mode.CopyModeCore		=ui.toolButtonCoreArea		->isChecked();
	Mode.CopyModeMaxZone	=ui.toolButtonMaxZone		->isChecked();
	Mode.CopyModeMinZone	=ui.toolButtonMinZone		->isChecked();
	Mode.CopyModeBare		=ui.toolButtonBareArea		->isChecked();
	Mode.CopyModeInside		=ui.toolButtonInsideArea	->isChecked();
	Mode.CopyModeOutlineI	=ui.toolButtonOutlineIArea	->isChecked();
	Mode.CopyModeOutlineT	=ui.toolButtonOutlineTArea	->isChecked();
	Mode.CopyModeOutlineO	=ui.toolButtonOutlineOArea	->isChecked();

	done(true);
}

void SelectAreaDialog::on_pushButtonCancel_clicked()
{
	done(false);
}