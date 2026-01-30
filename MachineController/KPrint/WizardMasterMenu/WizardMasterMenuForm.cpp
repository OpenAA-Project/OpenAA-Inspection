/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "WizardMasterMenuResource.h"
#include "WizardMasterMenuForm.h"
#include "ui_WizardMasterMenuForm.h"
#include "WizardMenuForm.h"
#include "EasyPropertyAlignmentForm.h"
#include "EasyPropertyDentMeasureForm.h"
#include "EasyPropertyDotColorMatchForm.h"
#include "EasyPropertyDXFOperationForm.h"
#include "EasyPropertyMaskingForm.h"
#include "EasyPropertySwitchPhaseForm.h"
#include "EasyGenerateMaskForm.h"
#include "EasyGenerateInspectionForm.h"
#include "EasyGenerateAlignmentForm.h"
#include "CartonMenuForm.h"
#include "ChangeNewMasterDialog.h"

WizardMasterMenuForm::WizardMasterMenuForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::WizardMasterMenuForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	Window=NULL;
	Msg=/**/"Master";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

WizardMasterMenuForm::~WizardMasterMenuForm()
{
	if(Window!=NULL){
		Window->deleteLater();
	}
	Window=NULL;
    delete ui;
}
void	WizardMasterMenuForm::Prepare(void)
{
	ui->PushButtonMasterData->setText(Msg);
	ui->PushButtonMasterData->setFont (CFont);
	ResizeAction();
}
void	WizardMasterMenuForm::ReadyParam(void)
{
	GUIFormBase	*GUIDim[1000];
	int	N;

	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyAlignment",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertyAlignmentForm	*f=dynamic_cast<EasyPropertyAlignmentForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDentMeasure",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertyDentMeasureForm	*f=dynamic_cast<EasyPropertyDentMeasureForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDotColorMatch",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertyDotColorMatchForm	*f=dynamic_cast<EasyPropertyDotColorMatchForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyDXFOperation",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertyDXFOperationForm	*f=dynamic_cast<EasyPropertyDXFOperationForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyMasking",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertyMaskingForm	*f=dynamic_cast<EasyPropertyMaskingForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertySwitchPhase",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyPropertySwitchPhaseForm	*f=dynamic_cast<EasyPropertySwitchPhaseForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyGenerateAlignment",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyGenerateAlignmentForm	*f=dynamic_cast<EasyGenerateAlignmentForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyGenerateInspection",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyGenerateInspectionForm	*f=dynamic_cast<EasyGenerateInspectionForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
	N=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyGenerateMask",GUIDim,1000);
	for(int i=0;i<N;i++){
		EasyGenerateMaskForm	*f=dynamic_cast<EasyGenerateMaskForm *>(GUIDim[i]);
		if(f!=NULL){
			connect(f,SIGNAL(SignalBusy()),this,SLOT(SlotBusy()));
			connect(f,SIGNAL(SignalIdle()),this,SLOT(SlotIdle()));
		}
	}
}
void	WizardMasterMenuForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdClearMasterData	*CmdClearMasterDataVar=dynamic_cast<CmdClearMasterData *>(v);
	if(CmdClearMasterDataVar!=NULL){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f!=NULL){
			CartonMenuForm	*Cf=(CartonMenuForm *)f;
			Cf->ParamInMaster.ClearInInitial();
		}
		return;
	}
}

void WizardMasterMenuForm::on_PushButtonMasterData_clicked()
{
	if(Window==NULL){
		Window=new WizardMenuForm(this,GetLayersBase());
	}
	Window->show();
}
void	WizardMasterMenuForm::ResizeAction()
{
	ui->PushButtonMasterData->resize(width(),height());
}

void	WizardMasterMenuForm::SlotBusy()
{
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(WizardMasterMenuForm_LS,LID_0)/*"蜃ｦ逅ｸｭ"*/,false,0);
	QApplication::processEvents();
}
void	WizardMasterMenuForm::SlotIdle()
{
	GetLayersBase()->CloseProcessingForm();
}

void	WizardMasterMenuForm::ExecuteSwitchImage(void)
{
	ChangeNewMasterDialog	D;
	int	Ret=D.exec();
	if(Ret==1){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"CopyImage",/**/"");
		if(f!=NULL){
			QStringList Args;
			bool ExeReturn;
			f->ExecuteMacro(/**/"ExecuteCopy", Args, ExeReturn);
		}
		GUIFormBase	*fa=GetLayersBase()->FindByName(/**/"Integration",/**/"NewMaster",/**/"");
		if(fa!=NULL){
			QStringList Args;
			bool ExeReturn;
			fa->ExecuteMacro(/**/"ClearAlgorithm", Args, ExeReturn);
		}
		GUIFormBase	*f2=GetLayersBase()->FindByName(/**/"Integration",/**/"SaveMaster",/**/"");
		if(f2!=NULL){
			QStringList Args;
			bool ExeReturn;
			f2->ExecuteMacro(/**/"CreateMasterDialog", Args, ExeReturn);
		}
	}
	else if(Ret==2){
		//GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"CopyImage",/**/"");
		//if(f!=NULL){
		//	QStringList Args;
		//	bool ExeReturn;
		//	f->ExecuteMacro(/**/"ExecuteCopy", Args, ExeReturn);
		//}
		GUIFormBase	*f2=GetLayersBase()->FindByName(/**/"KidaPrint",/**/"CartonMenu",/**/"");
		if(f2!=NULL){
			QStringList Args;
			bool ExeReturn;
			f2->ExecuteMacro(/**/"MoveForAlignment", Args, ExeReturn);
		}
	}
}