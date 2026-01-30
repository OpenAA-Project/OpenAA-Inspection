/*
 * Copyright (C) 2022
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

#include "IntegrationCameraChangeQuickPropertyResource.h"
#include "IntegrationCameraChangeQuickPropertyForm.h"
#include "ui_IntegrationCameraChangeQuickPropertyForm.h"
#include "CameraChangeQuickPropertyForm.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

IntegrationCameraChangeQuickPropertyForm::IntegrationCameraChangeQuickPropertyForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationCameraChangeQuickPropertyForm)
{
    ui->setupUi(this);
    LangSolver.SetUI(this);
    VValue=0;
}

IntegrationCameraChangeQuickPropertyForm::~IntegrationCameraChangeQuickPropertyForm()
{
    delete ui;
}

void	IntegrationCameraChangeQuickPropertyForm::ReadyParam(void)
{
    if(CameraQuickPropertyStr==/**/"Brighter")
        Attr=CameraQuickProperty_Brighter;
    else
    if(CameraQuickPropertyStr==/**/"Faster")
        Attr=CameraQuickProperty_Faster;
    else
    if(CameraQuickPropertyStr==/**/"SideBrighter")
        Attr=CameraQuickProperty_SideBrighter;

    VValue=0;
    if(Attr==CameraQuickProperty_Brighter){
        ui->label   ->setText(LangSolver.GetString(IntegrationCameraChangeQuickPropertyForm_LS,LID_1)/*"���邳"*/);
    }
    if(Attr==CameraQuickProperty_Faster){
        ui->label   ->setText(LangSolver.GetString(IntegrationCameraChangeQuickPropertyForm_LS,LID_2)/*"���x"*/);
    }
    if(Attr==CameraQuickProperty_SideBrighter){
        ui->label   ->setText(LangSolver.GetString(IntegrationCameraChangeQuickPropertyForm_LS,LID_3)/*"���Ӗ��邳"*/);  
    }

    ui->spinBoxValue->setValue(VValue);
}

void IntegrationCameraChangeQuickPropertyForm::on_toolButtonDown_clicked()
{
    VValue--;
    ui->spinBoxValue->setValue(VValue);

    int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
	IntegrationCmdCameraChangeQuickProperty	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
    RCmd.Attr   =Attr;
    RCmd.VValue =VValue;
	RCmd.Send(NULL,SlaveNo,0);
}

void IntegrationCameraChangeQuickPropertyForm::on_toolButtonUp_clicked()
{
    VValue++;
    ui->spinBoxValue->setValue(VValue);

    int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
	IntegrationCmdCameraChangeQuickProperty	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
    RCmd.Attr   =Attr;
    RCmd.VValue =VValue;
	RCmd.Send(NULL,SlaveNo,0);
}

//===============================================================================

IntegrationCmdCameraChangeQuickProperty::IntegrationCmdCameraChangeQuickProperty(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdCameraChangeQuickProperty::Load(QIODevice *f)
{
	int32	d;
	if(::Load(f,d)==false)
		return false;
	Attr=(CameraQuickProperty)d;
	if(::Load(f,VValue)==false)
		return false;
	return true;
}
bool	IntegrationCmdCameraChangeQuickProperty::Save(QIODevice *f)
{
	int32	d=(int32)Attr;
	if(::Save(f,d)==false)
		return false;
	if(::Save(f,VValue)==false)
		return false;
	return true;
}

void	IntegrationCmdCameraChangeQuickProperty::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
    GUIFormBase *RetGUI[100];
    GUIFormBase *F=NULL;
    int N=GetLayersBase()->EnumGUIInst(/**/"Camera",/**/"ChangeQuickProperty",RetGUI ,sizeof(RetGUI)/sizeof(RetGUI[0]));
    for(int i=0;i<N;i++){
        CameraChangeQuickPropertyForm   *f=(CameraChangeQuickPropertyForm *)(RetGUI[i]);
        if(f->Attr==Attr){
            F=f;
            break;
        }
    }

    if(F!=NULL){
        CmdCameraChangeQuickProperty    Cmd(GetLayersBase());
        Cmd.Attr    =Attr;
        Cmd.VValue  =VValue;
        F->TransmitDirectly(&Cmd);
    }
}