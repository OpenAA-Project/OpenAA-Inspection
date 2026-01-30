/*
 * Copyright (C) 2017
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

#include "ShowReviewMasterNameResource.h"
#include "ShowReviewMasterNameForm.h"
#include "ui_ShowReviewMasterNameForm.h"
#include "ReviewStructurePacket.h"
#include "..\XGUIReviewGlobal.h"
#include "XReviewStructure.h"

ShowReviewMasterNameForm::ShowReviewMasterNameForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowReviewMasterNameForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowReviewMasterNameForm::~ShowReviewMasterNameForm()
{
    delete ui;
}
void	ShowReviewMasterNameForm::Prepare(void)
{
	ResizeAction();
}

void	ShowReviewMasterNameForm::BuildForShow(void)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	CmdReqMasterDataInfo LoadedMaster(GetLayersBase());
	RBase->TransmitDirectly(&LoadedMaster);

	CmdReqCurrentLotInfoData	LoadedLot(GetLayersBase());
	RBase->TransmitDirectly(&LoadedLot);

	ui->lineEditMasterCode1	->setText(QString::number(LoadedMaster.FrontMasterDataInfo.MasterCode));
	ui->lineEditMasterName1	->setText(LoadedMaster.FrontMasterDataInfo.MasterName);
	ui->lineEditLotID1	->setText(LoadedLot.FrontLotName);
	ui->lineEditLotName1->setText(LoadedLot.FrontLotID);

	ui->lineEditMasterCode2	->setText(QString::number(LoadedMaster.BackMasterDataInfo.MasterCode));
	ui->lineEditMasterName2	->setText(LoadedMaster.BackMasterDataInfo.MasterName);
	ui->lineEditLotID2	->setText(LoadedLot.BackLotName);
	ui->lineEditLotName2->setText(LoadedLot.BackLotID);
}

void	ShowReviewMasterNameForm::ResizeAction()
{
	ui->WholeLayout->resize(width(),height());
}