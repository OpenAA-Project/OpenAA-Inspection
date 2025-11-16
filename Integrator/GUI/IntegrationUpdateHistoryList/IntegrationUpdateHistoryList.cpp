/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationUpdateHistoryList\IntegrationUpdateHistoryList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationUpdateHistoryList.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationComm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"UpdateHistoryList";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Update History List");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationUpdateHistoryList(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationUpdateHistoryList *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationUpdateHistoryList *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"NormalColor";
	Data[2].Pointer				 =&((IntegrationUpdateHistoryList *)Instance)->NormalColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"PushedColor";
	Data[3].Pointer				 =&((IntegrationUpdateHistoryList *)Instance)->PushedColor;	
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((IntegrationUpdateHistoryList *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationUpdateHistoryList.png")));
}

//==================================================================================================================
IntegrationUpdateHistoryList::IntegrationUpdateHistoryList(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Update";

	CharColor	=Qt::white;
	NormalColor	=Qt::gray;
	PushedColor	=Qt::yellow;

	resize(80,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	IntegrationUpdateHistoryList::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	connect(GetLayersBase()->GetIntegrationBasePointer(),SIGNAL(SignalInspectionDone(int,int64,bool))
				, this ,SLOT(SlotInspectionDone(int,int64,bool)),Qt::QueuedConnection);
}
void	IntegrationUpdateHistoryList::ResizeAction()
{
	Button.resize(width(),height());
}

void	IntegrationUpdateHistoryList::SlotClicked()
{
	CmdReqUpdateHistory	RCmd;
	BroadcastSpecifiedDirectly(&RCmd);
}

void	IntegrationUpdateHistoryList::SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK)
{
	CmdReqUpdateHistory	RCmd;
	RCmd.SlaveNo=SlaveNo;
	BroadcastSpecifiedDirectly(&RCmd);

	EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
	if(m!=NULL){
		InspectionList *L=m->GetCurrentInspection().GetLast();
		if(L!=NULL){
			CmdAppendResult	Cmd;
			Cmd.ResultID=L->ID;
			Cmd.SlaveNo	=SlaveNo;
			BroadcastSpecifiedDirectly(&Cmd);
		}
	}

	CmdReqUpdateCurrentInspection	R2Cmd;
	R2Cmd.SlaveNo=SlaveNo;
	BroadcastSpecifiedDirectly(&R2Cmd);
}

//============================================================================