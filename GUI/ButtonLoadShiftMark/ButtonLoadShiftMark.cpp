/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadShiftMark\ButtonLoadShiftMark.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLoadShiftMark.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>


static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LoadShiftMark";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load ShiftMark data and match");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdLoadShiftMarkData(Base,sRoot,sName);
	(*Base)=new GUIAckLoadShiftMarkData(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadShiftMark(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLoadShiftMark *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadShiftMark *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadShiftMark *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadShiftMark *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadShiftMark.png")));
}

//==================================================================================================
ButtonLoadShiftMark::ButtonLoadShiftMark(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load ShiftMark";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLoadShiftMark::~ButtonLoadShiftMark(void)
{
}

void	ButtonLoadShiftMark::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadShiftMark::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadShiftMark::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this, "Load ShiftMark", QString()
															, /**/"Algorithm (*.alg);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::ReadOnly)==false)
			return;

		ExecuteLoad(F);
	}
}

void	ButtonLoadShiftMark::TransmitDirectly(GUIDirectMessage *packet)
{
	ExecuteLoadShiftMarkByData	*ExecuteLoadShiftMarkByDataVar=dynamic_cast<ExecuteLoadShiftMarkByData *>(packet);
	if(ExecuteLoadShiftMarkByDataVar!=NULL){
		QBuffer	Buff(&ExecuteLoadShiftMarkByDataVar->Data);
		if(Buff.open(QIODevice::ReadWrite)==true){
			ExecuteLoad(Buff);
		}
		return;
	}
}

bool ButtonLoadShiftMark::ExecuteLoad(QIODevice &F)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;

	int32	Ver;

	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ShiftMark");
	char	PeekBuff[100];
	F.peek ( PeekBuff, sizeof(PeekBuff));
	QByteArray	PeekArray(PeekBuff,sizeof(PeekBuff));
	QBuffer	PeekBuffer(&PeekArray);
	PeekBuffer.open(QIODevice::ReadOnly);

	if(::Load(&PeekBuffer,Ver)==false)
			return false;

	int32	N;
	if(Ver>=20000){
		if(::Load(&F,Ver)==false){
			return false;
		}
		if(AL!=NULL){
			if(AL->LoadOnlyBase(&F)==false){
				return false;
			}
		}

		if(::Load(&F,N)==false)
			return false;
	}
	else{
		if(::Load(&F,N)==false)
			return false;
	}

	QString	tAlgorithmRoot=/**/"Basic";
	QString	tAlgorithmName=/**/"ShiftMark";
//	if(AlgorithmRoot.isEmpty()==true && AlgorithmName.isEmpty()==true){
//		tAlgorithmRoot=iAlgorithmRoot;
//		tAlgorithmName=iAlgorithmName;
//	}	
	bool	Ok=true;
	QString	ErrorMsg;
	for(int i=0;i<N;i++){
		int32	globalPage;
		if(::Load(&F,globalPage)==false)
			return false;
		int32	Len;
		if(::Load(&F,Len)==false)
			return false;
		GUICmdLoadShiftMarkData	RData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		GUIAckLoadShiftMarkData	AData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);

		RData.Data.close();
		QByteArray	M=F.read(Len);
		RData.Data.setData(M);
		RData.Data.open(QIODevice::ReadWrite);
		RData.Send(globalPage,0,AData,100000);
		if(AData.LoadingSuccessful==false){
			Ok=false;
			ErrorMsg=AData.ErrorMsg;
		}
	}
	BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
	if(Ok==false){
		QMessageBox::critical ( NULL, "Load error", ErrorMsg);
	}
	return Ok;
}
void	ButtonLoadShiftMark::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,"FILE"
										,"Load ShiftMark Data"
										,this);
	p->SetMenuNumber(2401);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	ButtonLoadShiftMark::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}


//==================================================================================================

GUICmdLoadShiftMarkData::GUICmdLoadShiftMarkData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdLoadShiftMarkData::Load(QIODevice *f)
{
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdLoadShiftMarkData::Save(QIODevice *f)
{
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdLoadShiftMarkData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckLoadShiftMarkData	*SendBack=GetSendBack(GUIAckLoadShiftMarkData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"ShiftMark");
	if(AL!=NULL){
		Data.open(QIODevice::ReadWrite);
		if(Data.seek(0)==true){
			QString	ErrorMsg;
			if(AL->LoadOnlyBase(&Data,ErrorMsg)==false){
				Data.close();
				SendBack->LoadingSuccessful=false;
				SendBack->ErrorMsg=ErrorMsg;
				SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
				CloseSendBack(SendBack);
				return;
			}
			AlgorithmInPageRoot	*AP=AL->GetPageData(localPage);
			if(AP!=NULL){
				if(AP->Load(&Data)==false){
					Data.close();
					SendBack->LoadingSuccessful=false;
					SendBack->ErrorMsg="Load error";
					SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
					CloseSendBack(SendBack);
					return;
				}
			}
		}
		Data.close();
	}
	//GetLayersBase()->ExecuteInitialAfterEdit	(GetLayersBase()->GetEntryPoint());
	SendBack->LoadingSuccessful=true;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckLoadShiftMarkData::GUIAckLoadShiftMarkData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	LoadingSuccessful=true;
}

bool	GUIAckLoadShiftMarkData::Load(QIODevice *f)
{
	if(::Load(f,LoadingSuccessful)==false)
		return false;
	if(::Load(f,ErrorMsg)==false)
		return false;
	return true;
}
bool	GUIAckLoadShiftMarkData::Save(QIODevice *f)
{
	if(::Save(f,LoadingSuccessful)==false)
		return false;
	if(::Save(f,ErrorMsg)==false)
		return false;
	return true;
}
