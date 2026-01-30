/*
 * Copyright (C) 2024
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

#include "ButtonExecuteAreaFilterResource.h"

#include "ButtonExecuteAreaFilter.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "XGeneralFunc.h"


static	const	char	*sRoot=/**/"Action";
static	const	char	*sName=/**/"ButtonExecuteAreaFilter";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for execution off AreaFilter");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdExecuteAreaFilterPushed(Base,QString(sRoot),QString(sName));
	(*Base)=new CmdExecuteAreaFilterReplied(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonExecuteAreaFilter(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonExecuteAreaFilter *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonExecuteAreaFilter *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonExecuteAreaFilter *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonExecuteAreaFilter *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonExecuteAreaFilter.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AreaFilter"));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonExecuteAreaFilter::ButtonExecuteAreaFilter(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Area Filter";
	resize(40,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonExecuteAreaFilter::~ButtonExecuteAreaFilter(void)
{
}

void	ButtonExecuteAreaFilter::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonExecuteAreaFilter::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonExecuteAreaFilter::SlotClicked (bool checked)
{
	GetLayersBase()->ClearAllAckFlag();
	//GetLayersBase()->ShowProcessingForm("Executing area filter");
	GetLayersBase()->AddMaxProcessing(-1,0);
	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdExecuteAreaFilterPushed	PushRequester(GetLayersBase(),sRoot,sName);
			PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
		}
		GetLayersBase()->WaitAllAcknowledged(60*10);
	}
	else{
		GUICmdExecuteAreaFilterPushed	PushRequester(GetLayersBase(),sRoot,sName);
		PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(0),0);
	}
	//GetLayersBase()->CloseProcessingForm ();
	BroadcastShowInEdit();
}

GUICmdExecuteAreaFilterPushed::GUICmdExecuteAreaFilterPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdExecuteAreaFilterPushed::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdExecuteAreaFilterPushed::Save(QIODevice *f)
{
	return true;
}

void	GUICmdExecuteAreaFilterPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->AddMaxProcessing(localPage,2);
		
	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit	(EInfo);
	GetLayersBase()->StepProcessing(localPage);
	GetLayersBase()->ExecutePreProcessing		(GetLayersBase()->GetEntryPoint());
	GetLayersBase()->StepProcessing(localPage);

	GetLayersBase()->SendAckToMaster(localPage);

	CmdExecuteAreaFilterReplied	PacketReplied(GetLayersBase(),QString(sRoot),QString(sName));
	PacketReplied.SendFromSlaveToMaster(
					GetLayersBase()->GetGlobalPageFromLocal(localPage)
					,0);
}

CmdExecuteAreaFilterReplied::CmdExecuteAreaFilterReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	CmdExecuteAreaFilterReplied::Load(QIODevice *f)
{
	return true;
}
bool	CmdExecuteAreaFilterReplied::Save(QIODevice *f)
{
	return true;
}

void	CmdExecuteAreaFilterReplied::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}