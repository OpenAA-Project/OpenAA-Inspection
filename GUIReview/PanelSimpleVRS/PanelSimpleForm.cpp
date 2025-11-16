#include "PanelSimpleVRSResource.h"
#include "PanelSimpleForm.h"
#include "ui_PanelSimpleForm.h"
#include "XVRSControlCommand.h"

PanelSimpleForm::PanelSimpleForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::PanelSimpleForm)
{
    ui->setupUi(this);

	StepPulse=60;
}

PanelSimpleForm::~PanelSimpleForm()
{
    delete ui;
}
void	PanelSimpleForm::Prepare(void)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Review" ,/**/"ShowVRSOperation" ,/**/"");
	if(GProp!=NULL){
		VRSOpe=GProp;
	}
}
void PanelSimpleForm::on_pushButtonUp_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=-StepPulse;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void PanelSimpleForm::on_pushButtonDown_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveY	Cmd(GetLayersBase());
		Cmd.Dy	=StepPulse;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void PanelSimpleForm::on_pushButtonLeft_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=StepPulse;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void PanelSimpleForm::on_pushButtonRight_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSMoveX	Cmd(GetLayersBase());
		Cmd.Dx	=-StepPulse;
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void PanelSimpleForm::on_pushButtonOrg_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSOrigin	Cmd(GetLayersBase());
		VRSOpe->TransmitDirectly(&Cmd);
	}
}

void PanelSimpleForm::on_pushButtonHome_clicked()
{
	if(VRSOpe!=NULL){
		CmdVRSEscape	Cmd(GetLayersBase());
		VRSOpe->TransmitDirectly(&Cmd);
	}
}
