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

#include "ShowMatrixImageCenterResource.h"
#include "ShowMatrixImageCenterForm.h"
#include "ui_ShowMatrixImageCenterForm.h"
#include "ShowMatrixImageCenter.h"

ShowMatrixImageCenterForm::ShowMatrixImageCenterForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowMatrixImageCenterForm)
{
    ui->setupUi(this);

	CenterX=0;
	CenterY=0;

	GetParamGUI()->SetParam(&CenterX, /**/"ShowMatrixImageCenter",/**/"CenterX"		
							,LangSolver.GetString(ShowMatrixImageCenterForm_LS,LID_0)/*"Center X"*/);
	GetParamGUI()->SetParam(&CenterY, /**/"ShowMatrixImageCenter",/**/"CenterY"		
							,LangSolver.GetString(ShowMatrixImageCenterForm_LS,LID_1)/*"Center Y"*/);
}

ShowMatrixImageCenterForm::~ShowMatrixImageCenterForm()
{
    delete ui;
}

void	ShowMatrixImageCenterForm::Prepare(void)
{
	ui->spinBoxCenterX	->setValue(CenterY);
	ui->spinBoxCenterY	->setValue(CenterY);
}

void	ShowMatrixImageCenterForm::SetCenter(int x ,int y)
{
	ui->spinBoxCenterX	->setValue(x);
	ui->spinBoxCenterY	->setValue(y);
}

void	ShowMatrixImageCenterForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetCenterInImage	*CmdSetCenterInImageVar=dynamic_cast<CmdSetCenterInImage *>(packet);
	if(CmdSetCenterInImageVar!=NULL){
		SetCenter(CmdSetCenterInImageVar->x ,CmdSetCenterInImageVar->y);
		return;
	}
	CmdReqCenterInImage	*CmdReqCenterInImageVar=dynamic_cast<CmdReqCenterInImage *>(packet);
	if(CmdReqCenterInImageVar!=NULL){
		CmdReqCenterInImageVar->x=ui->spinBoxCenterX->value();
		CmdReqCenterInImageVar->y=ui->spinBoxCenterY->value();
		return;
	}
}