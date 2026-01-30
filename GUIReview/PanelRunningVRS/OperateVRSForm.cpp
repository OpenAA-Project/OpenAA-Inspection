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