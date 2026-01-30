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

#include "IntegrationShowConnectionStateResource.h"
#include "WaitingConnectionForm.h"
#include "ui_WaitingConnectionForm.h"
#include "IntegrationShowConnectionState.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationComm.h"
#include "XGeneralFunc.h"
#include "IntegrationLoadMaster.h"

WaitingConnectionForm::WaitingConnectionForm(LayersBase *base ,IntegrationShowConnectionState *p,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(base)
 	,Parent(p)
	,ui(new Ui::WaitingConnectionForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	Count=0;
	CheckBox=NULL;

	if(Parent->GetEditMode()==false
	&& GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		Count=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		CheckBox=new QCheckBox*[Count];
		int	Y=0;
		for(int i=0;i<Count;i++){
			CheckBox[i]=new QCheckBox();
			CheckBox[i]->setParent(ui->frame);
			CheckBox[i]->setGeometry(100,Y,200,16);
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(i);
			if(m!=NULL){
				CheckBox[i]->setText(m->GetMachineName());
			}
			Y+=20;
		}
	}
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalAllSlaveConnected())		,this,SLOT(SlotConnectedAll())	,Qt::QueuedConnection);

	TM.setSingleShot(false);
	TM.setInterval(500);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();
}

WaitingConnectionForm::~WaitingConnectionForm()
{
    delete ui;
	if(CheckBox!=NULL){
		for(int i=0;i<Count;i++){
			delete	CheckBox[i];
		}
		delete	[]CheckBox;
		CheckBox=NULL;
		Count=0;
	}
}

void	WaitingConnectionForm::SlotTimeOut()
{
	int	Row=0;
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		IntegrationCommPack		*C=GetLayersBase()->GetIntegrationCommPointer();
		if(C!=NULL){
			for(IntegrationShowConnectionState::SlaveLine *L=Parent->SlaveLines.GetFirst();L!=NULL && Row<Count;L=L->GetNext(),Row++){
				IntegrationCommPipe	*s=C->GetSocket(Row);
				if(s==NULL || s->IsConnected()==false){
					CheckBox[Row]->setChecked(false);
				}
				else{
					CheckBox[Row]->setChecked(true);
				}
			}
		}
	}
}
void	WaitingConnectionForm::SlotConnectedAll()
{
	close();
}

void WaitingConnectionForm::on_toolButtonStopLoading_clicked()
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"LoadMaster",/**/"");
	if(f!=NULL){
		CmdEnableLoadAtFirst	RCmd(GetLayersBase());
		RCmd.EnableLoadAtFirst=!ui->toolButtonStopLoading->isChecked();
		f->TransmitDirectly(&RCmd);
	}
}