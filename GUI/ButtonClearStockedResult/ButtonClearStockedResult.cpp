#include "ButtonClearStockedResultResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonClearStockedResult\ButtonClearStockedResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonClearStockedResult.h"
#include "XGeneralFunc.h"
#include "XCriticalFunc.h"
#include "XAlgorithmBase.h"
#include "XMacroFunction.h"
#include "XWriteResultThread.h"
#include "XSyncGUI.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ClearStockedResult";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to clear stocked result");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdPushedClearStockedResult(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonClearStockedResult(Base,parent));
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
	Data[0].Pointer				 =&((ButtonClearStockedResult *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonClearStockedResult *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonClearStockedResult *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonClearStockedResult *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonClearStockedResult.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonClearStockedResult::ButtonClearStockedResult(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	SyncMode		=false;
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonClearStockedResult");
	Msg=/**/"Clear Stocked Result";
	resize(120,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonClearStockedResult::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonClearStockedResult::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonClearStockedResult::SlotClicked (bool checked)
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(ButtonClearStockedResult_LS,LID_0)/*"Clear stocked results"*/);
	GetLayersBase()->AddMaxProcessing(-1,0);
	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdPushedClearStockedResult	PushRequester(GetLayersBase(),sRoot,sName);
			PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
		}
		GetLayersBase()->WaitAllAcknowledged(60*20);

		for(int i=0;i<3;i++){
			int	N=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==0){
				break;
			}
			GSleep(2000);
			int	M=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==M){
				break;
			}
		}
		GetLayersBase()->GetResultThread()->SetCastAll();
	}
	else{
		GUICmdPushedClearStockedResult	PushRequester(GetLayersBase(),sRoot,sName);
		PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(0),0);
	}
	GetLayersBase()->CloseProcessingForm ();

	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			TxSync(Buff.buffer());
		}
	}
	//‚±‚ê‚ðŽÀs‚·‚é‚ÆAÄŒŸ¸‚ÅXML‚Éo—Í‚³‚ê‚Ä‚µ‚Ü‚¤
	//GetLayersBase()->PutCurrentResult();

	BroadcastShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
	//BroadcastDirectly(_BC_Show			,GetLayersBase()->GetCurrentInspectIDForDisplay());
}

void	ButtonClearStockedResult::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonClearStockedResult_LS,LID_1)/*"Execute"*/,LangSolver.GetString(ButtonClearStockedResult_LS,LID_2)/*"Clear stocked result"*/,this);
	p->SetMenuNumber(1200);
	Info.AppendList(p);
}
void	ButtonClearStockedResult::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
void	ButtonClearStockedResult::RxSync(QByteArray &f)
{
	SyncMode=true;
	SlotClicked(true);
	SyncMode=false;
}


//======================================================================================
GUICmdPushedClearStockedResult::GUICmdPushedClearStockedResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdPushedClearStockedResult::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdPushedClearStockedResult::Save(QIODevice *f)
{
	return true;
}

void	GUICmdPushedClearStockedResult::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		for(int i=0;i<3;i++){
			int	N=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==0){
				break;
			}
			GSleep(2000);
			int	M=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==M){
				break;
			}
		}
		GetLayersBase()->GetResultThread()->SetCastAll();
		GetLayersBase()->SendAckToMaster(localPage);
	}
	else{
		SendAck(localPage);
	}
}
