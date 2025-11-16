#include "StartupDialog.h"
#include"XParamGlobal.h"


StartupDialog::StartupDialog(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	ui.lineEditDBHost		->setText(GetParamGlobal()->LocalDatabase_HostName);
	ui.spinBoxPortNumber	->setValue(GetParamGlobal()->LocalDatabase_Port);
	ui.lineEditDBFileName	->setText(GetParamGlobal()->LocalDatabase_FileName);
}

StartupDialog::~StartupDialog()
{

}


void StartupDialog::on_pushButtonOK_clicked()
{
	GetParamGlobal()->LocalDatabase_HostName	=ui.lineEditDBHost		->text();
	GetParamGlobal()->LocalDatabase_Port		=ui.spinBoxPortNumber	->value();
	GetParamGlobal()->LocalDatabase_FileName	=ui.lineEditDBFileName	->text();
	done(true);
}