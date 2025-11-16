#include "ButtonClearHistogramResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonClearHistogram\ButtonClearHistogram.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonClearHistogram.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ClearHistogram";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Clear HistogramData");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqClearHistogramData	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonClearHistogram(Base,parent));
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
	Data[0].Pointer				 =&((ButtonClearHistogram *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonClearHistogram *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonClearHistogram *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonClearHistogram *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonClearHistogram.png")));
}

//==================================================================================================
ButtonClearHistogram::ButtonClearHistogram(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Clear Histogram";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonClearHistogram::~ButtonClearHistogram(void)
{
}

void	ButtonClearHistogram::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonClearHistogram::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonClearHistogram::SlotClicked (bool checked)
{
	if(QMessageBox::warning(NULL,LangSolver.GetString(ButtonClearHistogram_LS,LID_0)/*"Warning"*/,LangSolver.GetString(ButtonClearHistogram_LS,LID_1)/*"Clear histogram data?"*/,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdReqClearHistogramData	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.Send(NULL,globalPage,0);
		}
	}
}

void	ButtonClearHistogram::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonClearHistogram_LS,LID_2)/*"Data"*/
										,LangSolver.GetString(ButtonClearHistogram_LS,LID_3)/*"Clear HistogramData"*/
										,this);
	p->SetMenuNumber(2010);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	ButtonClearHistogram::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

//==================================================================================================
GUICmdReqClearHistogramData::GUICmdReqClearHistogramData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqClearHistogramData::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqClearHistogramData::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqClearHistogramData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->ClearHistgramData();
}
