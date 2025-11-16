#include "LoadAlgorithmWithMachineResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\LoadAlgorithmWithMachine\LoadAlgorithmWithMachine.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "LoadAlgorithmWithMachine.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ButtonLoadAlgorithmWithMachine";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to load one Algorithm with machine id");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdWriteAlgorithmDataWithMachine(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonLoadAlgorithmWithMachine(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLoadAlgorithmWithMachine *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLoadAlgorithmWithMachine *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLoadAlgorithmWithMachine *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLoadAlgorithmWithMachine *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"AlgorithmRoot";
	Data[4].Pointer				 =&((ButtonLoadAlgorithmWithMachine *)Instance)->AlgorithmRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgorithmName";
	Data[5].Pointer				 =&((ButtonLoadAlgorithmWithMachine *)Instance)->AlgorithmName;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/LoadAlgorithmWithMachine.png")));
	//return NULL;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonLoadAlgorithmWithMachine::ButtonLoadAlgorithmWithMachine(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Load Algorithm";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLoadAlgorithmWithMachine::~ButtonLoadAlgorithmWithMachine(void)
{
}

void	ButtonLoadAlgorithmWithMachine::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLoadAlgorithmWithMachine::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonLoadAlgorithmWithMachine::SlotClicked (bool checked)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	QString	FileName=GetLayersBase()->LGetOpenFileName (0, LangSolver.GetString(LoadAlgorithmWithMachine_LS,LID_0)/*"Load Algorithm with machine"*/, QString()
						, LangSolver.GetString(LoadAlgorithmWithMachine_LS,LID_1)/*"Algorithm (*.alm);;All files (*.*)"*/);
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::ReadOnly)==false)
			return;
		int32 machinecode;
		if(::Load(&F,machinecode)==false)
			return;
		GetLayersBase()->SetMachineID(machinecode);
		GetLayersBase()->BroadcastMachineID();

		int	N;
		if(::Load(&F,N)==false)
			return;

		for(int i=0;i<N;i++){
			int32	globalPage;
			if(::Load(&F,globalPage)==false)
				return;
			int32	Len;
			if(::Load(&F,Len)==false)
				return;
			GUICmdWriteAlgorithmDataWithMachine	RData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			RData.AlgorithmRoot	=AlgorithmRoot;
			RData.AlgorithmName	=AlgorithmName;
			RData.Data.close();
			QByteArray	M=F.read(Len);
			RData.Data.setData(M);
			RData.Data.open(QIODevice::ReadWrite);
			RData.Send(NULL,globalPage,0);
		}
		BroadcastDirectly(_BC_BuildForShow,GetLayersBase()->GetCurrentInspectIDForDisplay());
	}
}

//==================================================================================================

GUICmdWriteAlgorithmDataWithMachine::GUICmdWriteAlgorithmDataWithMachine(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base ,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
	Data.open(QIODevice::ReadWrite);
}

bool	GUICmdWriteAlgorithmDataWithMachine::Load(QIODevice *f)
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
bool	GUICmdWriteAlgorithmDataWithMachine::Save(QIODevice *f)
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

void	GUICmdWriteAlgorithmDataWithMachine::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot ,AlgorithmName);
	if(AL!=NULL){
		if(Data.seek(0)==true){
			if(AL->LoadOnlyBase(&Data)==false)
				return;
			AlgorithmInPageRoot	*AP=AL->GetPageData(localPage);
			if(AP->Load(&Data)==false)
				return;
		}
	}
	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit	(EInfo);
}

