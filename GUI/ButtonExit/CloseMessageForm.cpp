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


#include "ButtonExitResource.h"
#include "CloseMessageForm.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XParamGlobal.h"
#include "XSyncGUI.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

CloseMessageForm::CloseMessageForm(LayersBase *Base,GUIFormBase *parentGUI,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);
	ParentGUI=dynamic_cast<GUIFormBase *>(parentGUI);

	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowStaysOnTopHint | windowFlags());
	if(GetLayersBase()->GetParamComm()->ConnectedPCNumb==0){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()==0){
			ui.pushButtonCloseAll->setVisible(false);
			ui.pushButtonCloseOne->setDefault(true);
		}
	}
	InstallOperationLog(this);
}

CloseMessageForm::~CloseMessageForm()
{

}

void CloseMessageForm::on_pushButtonCloseAll_clicked()
{
	CloseApplicationSpecifiedBroadcaster	SData;
	ParentGUI->BroadcastSpecifiedDirectly(&SData);
	
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	int	Cmd=1;
	::Save(&Buff,Cmd);
	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		if(ParentGUI!=NULL){
			ParentGUI->TxSync(Buff.buffer());
		}
	}
	GetLayersBase()->CloseAll();
	QCoreApplication::quit();	
}

void CloseMessageForm::on_pushButtonCloseOne_clicked()
{
	CloseApplicationSpecifiedBroadcaster	SData;
	ParentGUI->BroadcastSpecifiedDirectly(&SData);

	if(GetLayersBase()->GetBootingLevel()!=0){
		GetLayersBase()->GetMainWidget()->close();
		close();
		/*
		QWidget	*c=this;
		for(;;){
			if(c->parentWidget()==NULL){
				c->close();
				break;
			}
			c=c->parentWidget();
		}
		*/
	}
	else{
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int	Cmd=2;
			::Save(&Buff,Cmd);
			ParentGUI->TxSync(Buff.buffer());
		}
		GetLayersBase()->CloseOne();
		QCoreApplication::quit();	
	}
}

void CloseMessageForm::on_pushButtonCalcen_clicked()
{
	close();
}