#include "RunnerObjSettingForm.h"
#include "ui_RunnerObjSettingForm.h"
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"
#include "XExecuteVisualizerInterface.h"

RunnerObjSettingForm::RunnerObjSettingForm(RunnerObject *obj ,QWidget *parent) :
    QDialog(parent),
	Obj(obj),
    ui(new Ui::RunnerObjSettingForm)
{
    ui->setupUi(this);

	QString DLLRoot;
	QString DLLName;
	Obj->GetRootName(DLLRoot, DLLName);
	ui->lineEditDLLRoot		->setText(DLLRoot);
	ui->lineEditDLLName		->setText(DLLName);
	ui->lineEditUniqueName	->setText(Obj->GetUniqueName());
	ui->lineEditRemark		->setText(Obj->GetComment());

	RunnerObjDLL	*DLL=Obj->GetAccessDLL();
	if(DLL->IsSettingDialog()==true){
		ui->pushButtonSetting->setEnabled(true);
	}
	else{
		ui->pushButtonSetting->setEnabled(false);
	}
	switch(Obj->GetPosInput()){
		case RunnerObject::IOPos_Left	:
			ui->toolButtonPosInputLeft	->setChecked(true);
			break;
		case RunnerObject::IOPos_Top	:
			ui->toolButtonPosInputTop	->setChecked(true);
			break;
		case RunnerObject::IOPos_Right:
			ui->toolButtonPosInputRight	->setChecked(true);
			break;
		case RunnerObject::IOPos_Bottom:
			ui->toolButtonPosInputBottom->setChecked(true);
			break;
	}
	switch(Obj->GetPosOutput()){
		case RunnerObject::IOPos_Left	:
			ui->toolButtonPosOutputLeft	->setChecked(true);
			break;
		case RunnerObject::IOPos_Top	:
			ui->toolButtonPosOutputTop	->setChecked(true);
			break;
		case RunnerObject::IOPos_Right:
			ui->toolButtonPosOutputRight->setChecked(true);
			break;
		case RunnerObject::IOPos_Bottom:
			ui->toolButtonPosOutputBottom->setChecked(true);
			break;
	}
}

RunnerObjSettingForm::~RunnerObjSettingForm()
{
    delete ui;
}

void RunnerObjSettingForm::on_pushButtonSetting_clicked()
{
	RunnerObjDLL	*DLL=Obj->GetAccessDLL();
	if(DLL->IsSettingDialog()==true){
		DLL->ShowSettingDialog(Obj);
	}
}

void RunnerObjSettingForm::on_pushButtonOK_clicked()
{
	Obj->SetUniqueName	(ui->lineEditUniqueName	->text());
	Obj->SetComment		(ui->lineEditRemark		->text());

	if(ui->toolButtonPosInputLeft	->isChecked()==true)
		Obj->SetPosInput(RunnerObject::IOPos_Left);
	else if(ui->toolButtonPosInputTop	->isChecked()==true)
		Obj->SetPosInput(RunnerObject::IOPos_Top);
	else if(ui->toolButtonPosInputRight	->isChecked()==true)
		Obj->SetPosInput(RunnerObject::IOPos_Right);
	else if(ui->toolButtonPosInputBottom	->isChecked()==true)
		Obj->SetPosInput(RunnerObject::IOPos_Bottom);

	if(ui->toolButtonPosOutputLeft	->isChecked()==true)
		Obj->SetPosOutput(RunnerObject::IOPos_Left);
	else if(ui->toolButtonPosOutputTop	->isChecked()==true)
		Obj->SetPosOutput(RunnerObject::IOPos_Top);
	else if(ui->toolButtonPosOutputRight	->isChecked()==true)
		Obj->SetPosOutput(RunnerObject::IOPos_Right);
	else if(ui->toolButtonPosOutputBottom	->isChecked()==true)
		Obj->SetPosOutput(RunnerObject::IOPos_Bottom);

	done(true);
}

void RunnerObjSettingForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void RunnerObjSettingForm::on_pushButtonDelete_clicked()
{
	RunnerMap	*RMap=dynamic_cast<RunnerMap *>(Obj->parent());
	if(RMap!=NULL){
		RMap->DeleteRunnerObj(Obj);
	}
	done(true);
}
