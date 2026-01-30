/*
 * Copyright (C) 2021
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

#include "SelectMachineForReviewResource.h"
#include "ButtonSelectMachineForReview.h"
#include "ui_ButtonSelectMachineForReview.h"
#include "SelectMachineForReviewDialog.h"
#include "XSelectMachineForReviewPacket.h"

#include "../XGUIReviewGlobal.h"
#include "XReviewCommon.h"
#include "ReviewStructurePacket.h"
#include "XReviewStructure.h"
#include "XReviewCommonPacket.h"

ButtonSelectMachineForReview::ButtonSelectMachineForReview(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base ,parent),
    ui(new Ui::ButtonSelectMachineForReview)
{
	LangSolver.SetUI(this);

	Msg=/**/"Select Machine";
    ui->setupUi(this);
	DefaultTopMachineID		=-1;
	DefaultBottomMachineID	=-1;

	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

ButtonSelectMachineForReview::~ButtonSelectMachineForReview()
{
    delete ui;
}


void	ButtonSelectMachineForReview::Prepare(void)
{
	ui->pushButton->setText(Msg);
	ui->pushButton->setFont (CFont);
	ResizeAction();
}

void	ButtonSelectMachineForReview::ResizeAction()
{
	ui->pushButton->resize(width(),height());
}

void ButtonSelectMachineForReview::on_pushButton_clicked()
{
	GetLayersBase()->TmpHideProcessingForm();
	SelectMachineForReviewDialog	D(GetLayersBase(),NULL);
	D.exec();
	GetLayersBase()->TmpRercoverProcessingForm();
}

void	ButtonSelectMachineForReview::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonSelectMachineForReview_LS,LID_0)/*"Review"*/,LangSolver.GetString(ButtonSelectMachineForReview_LS,LID_1)/*"Select Machine"*/,this);
	p->SetMenuNumber(120);
	Info.AppendList(p);
}

void	ButtonSelectMachineForReview::ExecuteMenu(int ID)
{
	if(ID==1){
		on_pushButton_clicked();
	}
}
void	ButtonSelectMachineForReview::BuildForShow(void)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdSetMachineID cMachineID(GetLayersBase());
	cMachineID.MachineIDFront	=DefaultTopMachineID;
	cMachineID.MachineIDBack	=DefaultBottomMachineID;
	if(cMachineID.MachineIDFront>=0 && cMachineID.MachineIDBack>=0){
		RBase->TransmitDirectly(&cMachineID);
	}
}

void ButtonSelectMachineForReview::TransmitDirectly(GUIDirectMessage *packet)
{
	GUICmdReqStaticMachineID	*GUICmdReqStaticMachineIDVar=dynamic_cast<GUICmdReqStaticMachineID *>(packet);
	if(GUICmdReqStaticMachineIDVar!=NULL){
		GUICmdReqStaticMachineIDVar->DefaultTopMachineID	=DefaultTopMachineID;
		GUICmdReqStaticMachineIDVar->DefaultBottomMachineID	=DefaultBottomMachineID;
		return;
	}
}