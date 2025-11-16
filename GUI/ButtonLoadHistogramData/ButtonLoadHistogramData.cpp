#include "ButtonLoadHistogramDataResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadHistogramData\ButtonLoadHistogramData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLoadHistogramData.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>


static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LoadHistogramData";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to load all histogram data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdWriteHistogramData(Base,sRoot,sName);
	(*Base)=new GUIAckWriteHistogramData(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadHistogramData(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonLoadHistogramData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadHistogramData *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadHistogramData *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadHistogramData *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadHistogramData.png")));
}

//==================================================================================================
ButtonLoadHistogramData::ButtonLoadHistogramData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load Histogram";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLoadHistogramData::~ButtonLoadHistogramData(void)
{
}

void	ButtonLoadHistogramData::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadHistogramData::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadHistogramData::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this	, /**/"Load Histogram Data", QString()
															, /**/"Histogramdata (*.hst);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::ReadOnly)==false)
			return;

		ExecuteLoad(F);
	}
}

void	ButtonLoadHistogramData::TransmitDirectly(GUIDirectMessage *packet)
{
	ExecuteLoadHistogram	*ExecuteLoadHistogramVar=dynamic_cast<ExecuteLoadHistogram *>(packet);
	if(ExecuteLoadHistogramVar!=NULL){
		if(ExecuteLoadHistogramVar->FileName.isEmpty()==false){
			QFile	F(ExecuteLoadHistogramVar->FileName);
			if(F.open(QIODevice::ReadOnly)==false)
				return;
			ExecuteLoad(F);
		}
		return;
	}
}

void ButtonLoadHistogramData::ExecuteLoad(QIODevice &F)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;

	int32	Ver;

	if(::Load(&F,Ver)==false)
		return;

	int	N;
	if(::Load(&F,N)==false)
		return;

	bool	Ok=true;
	QString	ErrorMsg;
	for(int i=0;i<N;i++){
		int32	globalPage;
		if(::Load(&F,globalPage)==false)
			return;
		int32	Len;
		if(::Load(&F,Len)==false)
			return;
		GUICmdWriteHistogramData	RData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		GUIAckWriteHistogramData	AData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		RData.Data.close();
		QByteArray	M=F.read(Len);
		RData.Data.setData(M);

		RData.Data.open(QIODevice::ReadWrite);
		RData.Send(globalPage,0,AData,100000);
		if(AData.Ok==false){
			Ok=false;
			ErrorMsg=AData.ErrorMsg;
		}
	}
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
	if(Ok==false){
		QMessageBox::critical ( NULL, LangSolver.GetString(ButtonLoadHistogramData_LS,LID_0)/*"Load error"*/, ErrorMsg);
	}
}
void	ButtonLoadHistogramData::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLoadHistogramData_LS,LID_1)/*"FILE"*/
										,LangSolver.GetString(ButtonLoadHistogramData_LS,LID_2)/*"Load HistogramData"*/
										,this);
	p->SetMenuNumber(2000);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	ButtonLoadHistogramData::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}


//==================================================================================================

GUICmdWriteHistogramData::GUICmdWriteHistogramData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdWriteHistogramData::Load(QIODevice *f)
{
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdWriteHistogramData::Save(QIODevice *f)
{
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdWriteHistogramData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckWriteHistogramData	*SendBack=GetSendBack(GUIAckWriteHistogramData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	Data.open(QIODevice::ReadWrite);
	if(GetLayersBase()->LoadHistgram(&Data)==true){
		Data.close();
		SendBack->Ok=true;
		SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
		CloseSendBack(SendBack);
		return;
	}
	else{
		SendBack->Ok=false;
		SendBack->ErrorMsg=LangSolver.GetString(ButtonLoadHistogramData_LS,LID_3)/*"Load error"*/;
		SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
		CloseSendBack(SendBack);
		return;
	}
}

GUIAckWriteHistogramData::GUIAckWriteHistogramData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Ok=true;
}

bool	GUIAckWriteHistogramData::Load(QIODevice *f)
{
	if(::Load(f,Ok)==false)
		return false;
	if(::Load(f,ErrorMsg)==false)
		return false;
	return true;
}
bool	GUIAckWriteHistogramData::Save(QIODevice *f)
{
	if(::Save(f,Ok)==false)
		return false;
	if(::Save(f,ErrorMsg)==false)
		return false;
	return true;
}

void	GUIAckWriteHistogramData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
