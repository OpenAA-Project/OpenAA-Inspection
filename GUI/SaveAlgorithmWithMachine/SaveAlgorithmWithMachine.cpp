#include "SaveAlgorithmWithMachineResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveAlgorithmWithMachine\SaveAlgorithmWithMachine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SaveAlgorithmWithMachine.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveAlgorithmWithMachine";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to save one Algorithm with machine id");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAlgorithmDataWithMachine	(Base,sRoot,sName);
	(*Base)=new GUICmdSendAlgorithmDataWithMachine	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSaveAlgorithmWithMachine(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveAlgorithmWithMachine *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveAlgorithmWithMachine *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveAlgorithmWithMachine *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveAlgorithmWithMachine *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"AlgorithmRoot";
	Data[4].Pointer				 =&((ButtonSaveAlgorithmWithMachine *)Instance)->AlgorithmRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgorithmName";
	Data[5].Pointer				 =&((ButtonSaveAlgorithmWithMachine *)Instance)->AlgorithmName;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SaveAlgorithmWithMachine.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSaveAlgorithmWithMachine::ButtonSaveAlgorithmWithMachine(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save Algorithm";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSaveAlgorithmWithMachine::~ButtonSaveAlgorithmWithMachine(void)
{
}

void	ButtonSaveAlgorithmWithMachine::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveAlgorithmWithMachine::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSaveAlgorithmWithMachine::SlotClicked (bool checked)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	QString	FileName=GetLayersBase()->LGetSaveFileName (0
													, LangSolver.GetString(SaveAlgorithmWithMachine_LS,LID_0)/*"Save Algorithm with machine"*/
													, QString()
													, LangSolver.GetString(SaveAlgorithmWithMachine_LS,LID_1)/*"Algorithm (*.alm);;All files (*.*)"*/);
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::WriteOnly)==false)
			return;

		if(::Save(&F,GetLayersBase()->GetMachineID())==false)
			return;

		GUICmdReqAlgorithmDataWithMachine  **RData=new GUICmdReqAlgorithmDataWithMachine *[GetParamGlobal()->PageNumb];
		GUICmdSendAlgorithmDataWithMachine	**SData=new GUICmdSendAlgorithmDataWithMachine*[GetParamGlobal()->PageNumb];
		int32	N=0;
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			RData[page]=new GUICmdReqAlgorithmDataWithMachine (GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			SData[page]=new GUICmdSendAlgorithmDataWithMachine(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			RData[page]->AlgorithmRoot	=AlgorithmRoot;
			RData[page]->AlgorithmName	=AlgorithmName;
			RData[page]->Send(globalPage,0,*SData[page]);
			if(SData[page]->IsReceived()==true){
				N++;
			}
		}

		if(::Save(&F,N)==true){
			for(int page=0;page<GetParamGlobal()->PageNumb;page++){
				if(SData[page]->IsReceived()==true){
					int32	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
					if(::Save(&F,globalPage)==false)
						break;
					int32	Len=SData[page]->Data.size();
					if(::Save(&F,Len)==false)
						break;
					F.write(SData[page]->Data.data());
				}
			}
		}
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			delete	RData[page];
			delete	SData[page];
		}
		delete	[]RData;
		delete	[]SData;
	}
}
//==================================================================================================
GUICmdReqAlgorithmDataWithMachine::GUICmdReqAlgorithmDataWithMachine(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlgorithmDataWithMachine::Load(QIODevice *f)
{
	if(::Load(f,AlgorithmRoot)==false)
		return false;
	if(::Load(f,AlgorithmName)==false)
		return false;
	return true;
}
bool	GUICmdReqAlgorithmDataWithMachine::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmRoot)==false)
		return false;
	if(::Save(f,AlgorithmName)==false)
		return false;
	return true;
}

void	GUICmdReqAlgorithmDataWithMachine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlgorithmDataWithMachine	*SendBack=GetSendBack(GUICmdSendAlgorithmDataWithMachine,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot ,AlgorithmName);
	if(AL!=NULL){
		SendBack->Data.open(QIODevice::ReadWrite);
		AL->SaveOnlyBase(&SendBack->Data);
		AlgorithmInPageRoot		*AP=AL->GetPageData(localPage);
		AP->Save(&SendBack->Data);
	}
	SendBack->Data.seek(0);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendAlgorithmDataWithMachine::GUICmdSendAlgorithmDataWithMachine(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAlgorithmDataWithMachine::Load(QIODevice *f)
{
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdSendAlgorithmDataWithMachine::Save(QIODevice *f)
{
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdSendAlgorithmDataWithMachine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
