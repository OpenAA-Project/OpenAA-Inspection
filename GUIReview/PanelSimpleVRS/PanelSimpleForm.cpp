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