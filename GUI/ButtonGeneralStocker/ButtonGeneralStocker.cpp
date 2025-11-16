#include "ButtonGeneralStockerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonGeneralStocker\ButtonGeneralStocker.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonGeneralStocker.h"
#include <QFile>
#include <QFileDialog>
#include <QBuffer>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGeneralStocker.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"GeneralStocker";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show GeneralStocker");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendGeneralStockerData	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonGeneralStocker(Base,parent));
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
	Data[0].Pointer				 =&((ButtonGeneralStocker *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonGeneralStocker *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonGeneralStocker *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonGeneralStocker *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"Keyword";
	Data[4].Pointer				 =&((ButtonGeneralStocker *)Instance)->Keyword;
	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonGeneralStocker.png")));
}
static	bool	MacroTransfer(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Transfer";
		Functions[ret].Explain.append(/**/"Transfer loaded data");
		Functions[ret].DLL_ExcuteMacro	=MacroTransfer;
		ret++;
	}
	return ret;
}
static	bool	MacroTransfer(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonGeneralStocker	*V=dynamic_cast<ButtonGeneralStocker *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandTransfer();

	return true;
}
//==================================================================================================
ButtonGeneralStocker::ButtonGeneralStocker(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Show GeneralStocker";
	Keyword=/**/"Keyword";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonGeneralStocker::~ButtonGeneralStocker(void)
{
}

void	ButtonGeneralStocker::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonGeneralStocker::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonGeneralStocker::SlotClicked (bool checked)
{
	GeneralStockerContainer	*L=GetLayersBase()->GetGeneralStocker();

	if(L!=NULL && L->ShowDialog(Keyword,NULL)==true){
		struct	PropertyGeneralStocker	Prop;
		Prop.SynchronizeToSlave	=true;
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		if(L->Save(&Buff,Prop)==true){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				GUICmdSendGeneralStockerData	RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Data=Buff.buffer();
				RCmd.Send(NULL,globalPage,0);
			}
		}
	}
}

void ButtonGeneralStocker::CommandTransfer(void)
{
	GeneralStockerContainer	*L=GetLayersBase()->GetGeneralStocker();

	if(L!=NULL){
		struct	PropertyGeneralStocker	Prop;
		Prop.SynchronizeToSlave	=true;
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);
		if(L->Save(&Buff,Prop)==true){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				GUICmdSendGeneralStockerData	RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Data=Buff.buffer();
				RCmd.Send(NULL,globalPage,0);
			}
		}
	}
}

void	ButtonGeneralStocker::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonGeneralStocker_LS,LID_0)/*"GeneralStocker"*/
										,LangSolver.GetString(ButtonGeneralStocker_LS,LID_1)/*"Show GeneralStocker"*/
										,this);
	p->SetMenuNumber(2010);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	ButtonGeneralStocker::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

//==================================================================================================
GUICmdSendGeneralStockerData::GUICmdSendGeneralStockerData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendGeneralStockerData::Load(QIODevice *f)
{
	if(::Load(f,Data)==false)
		return false;
	return true;
}
bool	GUICmdSendGeneralStockerData::Save(QIODevice *f)
{
	if(::Save(f,Data)==false)
		return false;
	return true;
}

void	GUICmdSendGeneralStockerData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GeneralStockerContainer	*L=GetLayersBase()->GetGeneralStocker();

	if(L!=NULL && localPage==0){
		struct	PropertyGeneralStocker	Prop;
		Prop.SynchronizeToSlave	=true;
		QBuffer	Buff(&Data);
		Buff.open(QIODevice::ReadOnly);
		L->Load(&Buff,Prop);
	}
}
