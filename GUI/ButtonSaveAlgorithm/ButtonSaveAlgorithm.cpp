/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveAlgorithm\ButtonSaveAlgorithm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSaveAlgorithmResource.h"
#include "ButtonSaveAlgorithm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveAlgorithm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to save one Algorithm");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAlgorithmData	(Base,sRoot,sName);
	(*Base)=new GUICmdSendAlgorithmData	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSaveAlgorithm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonSaveAlgorithm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveAlgorithm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveAlgorithm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveAlgorithm *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"AlgorithmRoot";
	Data[4].Pointer				 =&((ButtonSaveAlgorithm *)Instance)->AlgorithmRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgorithmName";
	Data[5].Pointer				 =&((ButtonSaveAlgorithm *)Instance)->AlgorithmName;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"WaitingMilisec";
	Data[6].Pointer				 =&((ButtonSaveAlgorithm *)Instance)->WaitingMilisec;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveAligorithm.png")));
}

//==================================================================================================
ButtonSaveAlgorithm::ButtonSaveAlgorithm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save Algorithm";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
	WaitingMilisec=60*1000;
}

ButtonSaveAlgorithm::~ButtonSaveAlgorithm(void)
{
}

void	ButtonSaveAlgorithm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveAlgorithm::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSaveAlgorithm::SlotClicked (bool checked)
{
	int32	Ver=20000;

	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	QString	FileName=GetLayersBase()->LGetSaveFileName (this
													, LangSolver.GetString(ButtonSaveAlgorithm_LS,LID_0)/*"Save Algorithm"*/, QString()
													, /**/"Algorithm (*.alg);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::WriteOnly)==false)
			return;
		SaveAlgo(AlgorithmRoot ,AlgorithmName
									,&F);
	}
}

bool	ButtonSaveAlgorithm::SaveAlgo(const QString &AlgoRoot ,const QString &AlgoName
									,QIODevice *F)
{
	int32	Ver=20000;
	if(::Save(F,Ver)==false)
		return false;

	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(AlgoRoot ,AlgoName);
	if(AL!=NULL){
		AL->SaveOnlyBase(F);
	}

	GUICmdReqAlgorithmData  **RData=new GUICmdReqAlgorithmData *[GetParamGlobal()->PageNumb];
	GUICmdSendAlgorithmData	**SData=new GUICmdSendAlgorithmData*[GetParamGlobal()->PageNumb];
	int32	N=0;
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		RData[page]=new GUICmdReqAlgorithmData (GetLayersBase(),sRoot,sName,globalPage);
		SData[page]=new GUICmdSendAlgorithmData(GetLayersBase(),sRoot,sName,globalPage);
		RData[page]->AlgorithmRoot	=AlgoRoot;
		RData[page]->AlgorithmName	=AlgoName;
		RData[page]->Send(globalPage,0,*SData[page],WaitingMilisec);
		if(SData[page]->IsReceived()==true){
			N++;
		}
	}

//	if(::Save(&F,AlgorithmRoot)==false)
//		return;
//	if(::Save(&F,AlgorithmName)==false)
//		return;

	if(::Save(F,N)==true){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			if(SData[page]->IsReceived()==true){
				int32	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				if(::Save(F,globalPage)==false)
					break;
				int32	Len=SData[page]->Data.size();
				if(::Save(F,Len)==false)
					break;
				F->write(SData[page]->Data.data());
			}
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	RData[page];
		delete	SData[page];
	}
	delete	[]RData;
	delete	[]SData;
	return true;
}
void	ButtonSaveAlgorithm::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonSaveAlgorithm_LS,LID_1)/*"FILE"*/
										,LangSolver.GetString(ButtonSaveAlgorithm_LS,LID_2)/*"Save AlgorithmData"*/
										,this);
	p->SetMenuNumber(2010);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	ButtonSaveAlgorithm::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	ButtonSaveAlgorithm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqAlgorithmData	*CmdReqAlgorithmDataVar=dynamic_cast<CmdReqAlgorithmData *>(packet);
	if(CmdReqAlgorithmDataVar!=NULL){
		CmdReqAlgorithmDataVar->RetSuccessful=SaveAlgo(CmdReqAlgorithmDataVar->AlgorithmRoot ,CmdReqAlgorithmDataVar->AlgorithmName
									,CmdReqAlgorithmDataVar->Data);
		return;
	}
}

//==================================================================================================
GUICmdReqAlgorithmData::GUICmdReqAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqAlgorithmData::Load(QIODevice *f)
{
	if(::Load(f,AlgorithmRoot)==false)
		return false;
	if(::Load(f,AlgorithmName)==false)
		return false;
	return true;
}
bool	GUICmdReqAlgorithmData::Save(QIODevice *f)
{
	if(::Save(f,AlgorithmRoot)==false)
		return false;
	if(::Save(f,AlgorithmName)==false)
		return false;
	return true;
}

void	GUICmdReqAlgorithmData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendAlgorithmData	*SendBack=GetSendBack(GUICmdSendAlgorithmData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
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

GUICmdSendAlgorithmData::GUICmdSendAlgorithmData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendAlgorithmData::Load(QIODevice *f)
{
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdSendAlgorithmData::Save(QIODevice *f)
{
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdSendAlgorithmData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
