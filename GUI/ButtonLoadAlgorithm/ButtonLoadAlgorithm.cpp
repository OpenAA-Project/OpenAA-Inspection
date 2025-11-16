/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLoadAlgorithm\ButtonLoadAlgorithm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLoadAlgorithmResource.h"
#include "ButtonLoadAlgorithm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>


static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LoadAlgorithm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to load one Algorithm");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdWriteAlgorithmData(Base,sRoot,sName);
	(*Base)=new GUIAckWriteAlgorithmData(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadAlgorithm(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLoadAlgorithm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadAlgorithm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadAlgorithm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadAlgorithm *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"AlgorithmRoot";
	Data[4].Pointer				 =&((ButtonLoadAlgorithm *)Instance)->AlgorithmRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgorithmName";
	Data[5].Pointer				 =&((ButtonLoadAlgorithm *)Instance)->AlgorithmName;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLoadOneAligorithm.png")));
}

//==================================================================================================
ButtonLoadAlgorithm::ButtonLoadAlgorithm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load Algorithm";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLoadAlgorithm::~ButtonLoadAlgorithm(void)
{
}

void	ButtonLoadAlgorithm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadAlgorithm::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadAlgorithm::SlotClicked (bool checked)
{
	QString	FileName=GetLayersBase()->LGetOpenFileName (this, LangSolver.GetString(ButtonLoadAlgorithm_LS,LID_0)/*"Load Algorithm"*/, QString()
															, /**/"Algorithm (*.alg);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::ReadOnly)==false)
			return;

		ExecuteLoad(F  ,AlgorithmRoot ,AlgorithmName);
	}
}

void	ButtonLoadAlgorithm::TransmitDirectly(GUIDirectMessage *packet)
{
	ExecuteLoadAlgorithm	*ExecuteLoadAlgorithmVar=dynamic_cast<ExecuteLoadAlgorithm *>(packet);
	if(ExecuteLoadAlgorithmVar!=NULL){
		if(ExecuteLoadAlgorithmVar->FileName.isEmpty()==false){
			QFile	F(ExecuteLoadAlgorithmVar->FileName);
			if(F.open(QIODevice::ReadOnly)==false)
				return;
			ExecuteLoad(F
					,ExecuteLoadAlgorithmVar->AlgorithmRoot ,ExecuteLoadAlgorithmVar->AlgorithmName);
		}
		return;
	}
	ExecuteLoadAlgorithmByData	*ExecuteLoadAlgorithmByDataVar=dynamic_cast<ExecuteLoadAlgorithmByData *>(packet);
	if(ExecuteLoadAlgorithmByDataVar!=NULL){
		QBuffer	F(&ExecuteLoadAlgorithmByDataVar->Data);
		if(F.open(QIODevice::ReadOnly)==false)
			return;
		ExecuteLoad(F
					,ExecuteLoadAlgorithmByDataVar->AlgorithmRoot ,ExecuteLoadAlgorithmByDataVar->AlgorithmName);
		return;
	}
}

bool ButtonLoadAlgorithm::ExecuteLoad(QIODevice &F
									  ,QString _AlgorithmRoot ,QString _AlgorithmName)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;

	int32	Ver;

	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(_AlgorithmRoot ,_AlgorithmName);
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

	QString	tAlgorithmRoot=_AlgorithmRoot;
	QString	tAlgorithmName=_AlgorithmName;
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
		GUICmdWriteAlgorithmData	RData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		GUIAckWriteAlgorithmData	AData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		RData.AlgorithmRoot	=tAlgorithmRoot;
		RData.AlgorithmName	=tAlgorithmName;
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
		QMessageBox::critical ( NULL, LangSolver.GetString(ButtonLoadAlgorithm_LS,LID_1)/*"Load error"*/, ErrorMsg);
	}
	return Ok;
}
void	ButtonLoadAlgorithm::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLoadAlgorithm_LS,LID_2)/*"FILE"*/
										,LangSolver.GetString(ButtonLoadAlgorithm_LS,LID_3)/*"Load AlgorithmData"*/
										,this);
	p->SetMenuNumber(2000);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	ButtonLoadAlgorithm::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}


//==================================================================================================

GUICmdWriteAlgorithmData::GUICmdWriteAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdWriteAlgorithmData::Load(QIODevice *f)
{
	if(::Load(f,AlgorithmRoot)==false)
		return false;
	if(::Load(f,AlgorithmName)==false)
		return false;
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdWriteAlgorithmData::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmRoot)==false)
		return false;
	if(::Save(f,AlgorithmName)==false)
		return false;
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdWriteAlgorithmData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckWriteAlgorithmData	*SendBack=GetSendBack(GUIAckWriteAlgorithmData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot ,AlgorithmName);
	if(AL!=NULL){
		Data.open(QIODevice::ReadWrite);
		if(Data.seek(0)==true){
			QString	ErrorMsg;
			if(AL->LoadOnlyBase(&Data,ErrorMsg)==false){
				Data.close();
				SendBack->Ok=false;
				SendBack->ErrorMsg=ErrorMsg;
				SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
				CloseSendBack(SendBack);
				return;
			}
			AlgorithmInPageRoot	*AP=AL->GetPageData(localPage);
			if(AP!=NULL){
				if(AP->Load(&Data)==false){
					Data.close();
					SendBack->Ok=false;
					SendBack->ErrorMsg=LangSolver.GetString(ButtonLoadAlgorithm_LS,LID_4)/*"Load error"*/;
					SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
					CloseSendBack(SendBack);
					return;
				}
			}
		}
		Data.close();
	}
	//GetLayersBase()->ExecuteInitialAfterEdit	(GetLayersBase()->GetEntryPoint());
	SendBack->Ok=true;
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUIAckWriteAlgorithmData::GUIAckWriteAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Ok=true;
}

bool	GUIAckWriteAlgorithmData::Load(QIODevice *f)
{
	if(::Load(f,Ok)==false)
		return false;
	if(::Load(f,ErrorMsg)==false)
		return false;
	return true;
}
bool	GUIAckWriteAlgorithmData::Save(QIODevice *f)
{
	if(::Save(f,Ok)==false)
		return false;
	if(::Save(f,ErrorMsg)==false)
		return false;
	return true;
}

void	GUIAckWriteAlgorithmData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
