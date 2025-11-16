#include "SetThresholdByHistogramResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SetThresholdByHistogram\SetThresholdByHistogram.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SetThresholdByHistogram.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "SetThresholdDialog.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SetThresholdByHistogram";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Set threshold by  Histogram Data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqEnumEffectiveHistgram	(Base,sRoot,sName);
	(*Base)=new GUICmdAckEnumEffectiveHistgram	(Base,sRoot,sName);
	(*Base)=new GUICmdReqExecuteAutoThreshold		(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SetThresholdByHistogram(Base,parent));
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
	Data[0].Pointer				 =&((SetThresholdByHistogram *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((SetThresholdByHistogram *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((SetThresholdByHistogram *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((SetThresholdByHistogram *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SetThresholdByHistogram.png")));
}

//==================================================================================================
SetThresholdByHistogram::SetThresholdByHistogram(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Set threshold";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

SetThresholdByHistogram::~SetThresholdByHistogram(void)
{
}

void	SetThresholdByHistogram::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	SetThresholdByHistogram::ResizeAction()
{
	Button.resize(width(),height());
}

void SetThresholdByHistogram::SlotClicked (bool checked)
{
	SetThresholdDialog	*D=new SetThresholdDialog(GetLayersBase());
	D->exec();
	D->deleteLater();
	/*
	if(QMessageBox::warning(NULL,"Warning"
								,"Set threshold by histogram data?"
								,QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdReqClearHistogramData	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.Send(NULL,globalPage,0);
		}
	}
	*/
}

void	SetThresholdByHistogram::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(19,LangSolver.GetString(SetThresholdByHistogram_LS,LID_0)/*"Data"*/
										,LangSolver.GetString(SetThresholdByHistogram_LS,LID_1)/*"Set threshold by HistogramData"*/
										,this);
	p->SetMenuNumber(2010);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	SetThresholdByHistogram::ExecuteMenu(int ID)
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