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

#include "IntegrationCopyImageResource.h"
#include "IntegrationCopyImageForm.h"
#include "ui_IntegrationCopyImageForm.h"
#include "XDisplayImage.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


IntegrationCopyImageForm::IntegrationCopyImageForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationCopyImageForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SlaveNo=0;

	Msg=/**/"Copy image";
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationCopyImageForm::~IntegrationCopyImageForm()
{
    delete ui;
}
void	IntegrationCopyImageForm::Prepare(void)
{
	ui->PushButtonCopy->setText(Msg);
	ui->PushButtonCopy->setFont (CFont);
	ResizeAction();
}

void	IntegrationCopyImageForm::ResizeAction()
{
	ui->PushButtonCopy->resize(width(),height());
}
void	IntegrationCopyImageForm::ExecuteCopy(void)
{
	on_PushButtonCopy_clicked();
}
void IntegrationCopyImageForm::on_PushButtonCopy_clicked()
{
	if(SlaveNo==-1){
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		for(int n=0;n<N;n++){
			IntegrationCmdCopyImage	RCmd(GetLayersBase(),sRoot,sName,n);
			RCmd.Send(NULL,n,0);
		}
		for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
			m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
		}
	}
	else{
		IntegrationCmdCopyImage	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		if(RCmd.Send(NULL,SlaveNo,0)==true){
			EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
			m->RequireMasterImage(GetParamGlobal()->MixMasterForIntegration);
		}
	}
	BroadcastRepaintAll();
}

//===========================================================================

IntegrationCmdCopyImage::IntegrationCmdCopyImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationCmdCopyImage::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*GUIDim[1000];
	int	N=GetLayersBase()->EnumGUI(GUIDim,1000);
	for(int i=0;i<N;i++){
		DisplayImage	*d=dynamic_cast<DisplayImage *>(GUIDim[i]);
		if(d!=NULL){
			d->SlotCopyImageToMaster();
		}
	}
}