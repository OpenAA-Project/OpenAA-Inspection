#include "PanelRunningVRSResource.h"
#include "OperateVRSForm.h"
#include "ui_OperateVRSForm.h"
#include "XVRSControlCommand.h"
#include "XAutofocusControl.h"

OperateVRSForm::OperateVRSForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::OperateVRSForm)
{
    ui->setupUi(this);
	VRSOpe=NULL;
}

OperateVRSForm::~OperateVRSForm()
{
    delete ui;
}
void	OperateVRSForm::Prepare(void)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(GProp!=NULL){
		VRSOpe=GProp;
	}
}
void OperateVRSForm::on_pushButtonOrigin_clicked()
{
	CmdMovePosition	RCmd(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"AutofocusChuo" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&RCmd);
	}
	if(VRSOpe!=NULL){
		CmdVRSOrigin	Cmd(GetLayersBase());
		VRSOpe->TransmitDirectly(&Cmd);
	}
		
}

void OperateVRSForm::on_pushButtonEscape_clicked()
{
	CmdMovePosition	RCmd(GetLayersBase());
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"AutofocusChuo" ,/**/"");
	if(GProp!=NULL){
		GProp->TransmitDirectly(&RCmd);
	}
	if(VRSOpe!=NULL){
		CmdVRSEscape	Cmd(GetLayersBase());
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonXP1_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=1;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonXP10_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=10;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonXP100_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=100;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonXM1_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=-1;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonXM10_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=-10;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonXM100_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=-100;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonYP1_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=1;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonYP10_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=10;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonYP100_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=100;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}


void OperateVRSForm::on_pushButtonYM1_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=-1;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonYM10_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=-10;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void OperateVRSForm::on_pushButtonYM100_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=-100;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}
