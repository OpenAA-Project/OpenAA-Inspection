/*
 * Copyright (C) 2023
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

#include "IntegrationOutputControlButtonResource.h"
#include "IntegrationOutputControlButtonForm.h"
#include "ui_IntegrationOutputControlButtonForm.h"
#include "XResultDLLManager.h"


extern	const	char	*sRoot;
extern	const	char	*sName;

IntegrationOutputControlButtonForm::IntegrationOutputControlButtonForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationOutputControlButtonForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	CurrentMode	=_FreeForResult;
	ReEntrant	=false;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationOutputControlButtonForm::~IntegrationOutputControlButtonForm()
{
    delete ui;
}

void	IntegrationOutputControlButtonForm::ResizeAction()
{
	ui->stackedWidget		->resize(width(),height());
	ui->label_FreeForResult	->resize(width(),height());
	ui->label_Abs_OK		->resize(width(),height());
	ui->label_Abs_NG		->resize(width(),height());
	ui->label_Abs_Blade		->resize(width(),height());
}
void	IntegrationOutputControlButtonForm::ReadyParam(void)
{
	ui->stackedWidget->setCurrentIndex((int)CurrentMode);
}

void	IntegrationOutputControlButtonForm::TransmitDirectly(GUIDirectMessage *packet)
{
	IntegrationSetControlOutput	*IntegrationSetControlOutputVar=dynamic_cast<IntegrationSetControlOutput *>(packet);
	if(IntegrationSetControlOutputVar!=NULL){
		if(ReEntrant==false){
			ReEntrant=true;
			CurrentMode	=IntegrationSetControlOutputVar->ControlMode;
			ui->stackedWidget->setCurrentIndex((int)IntegrationSetControlOutputVar->ControlMode);
			int	N=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetCount();
			for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
				GUICmdIntegrationSetControlOutput	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.ControlMode=IntegrationSetControlOutputVar->ControlMode;
				RCmd.Send(NULL,SlaveNo,0);
			}
			ReEntrant=false;
		}
		return;
	}
}

//===============================================================================================
GUICmdIntegrationSetControlOutput::GUICmdIntegrationSetControlOutput(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	GUICmdIntegrationSetControlOutput::Load(QIODevice *f)
{
	BYTE	d;
	if(::Load(f,d)==false)	return false;
	ControlMode=(_OutputControlMode)d;
	return true;
}
bool	GUICmdIntegrationSetControlOutput::Save(QIODevice *f)
{
	BYTE	d=(BYTE)ControlMode;
	if(::Save(f,d)==false)	return false;
	return true;
}
void	GUICmdIntegrationSetControlOutput::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationSetControlOutput	Cmd(GetLayersBase());
	Cmd.ControlMode	=ControlMode;
	for(ResultDLL *R=GetLayersBase()->GetResultDLLBase()->GetFirst();R!=NULL;R=R->GetNext()){
		if(R->GetDLLPoint()!=NULL){
			R->GetDLLPoint()->TransmitDirectly(&Cmd);
		}
	}
	GUIFormBase	*f=GetLayersBase()->FindByName(EmitterRoot,EmitterName,/**/"");
	if(f!=NULL){
		f->TransmitDirectly(&Cmd);
	}
}