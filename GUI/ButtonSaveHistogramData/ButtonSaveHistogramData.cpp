#include "ButtonSaveHistogramDataResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSaveHistogramData\ButtonSaveHistogramData.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSaveHistogramData.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveHistogramData";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show the window to save HistogramData");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqHistogramData	(Base,sRoot,sName);
	(*Base)=new GUICmdSendHistogramData	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSaveHistogramData(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSaveHistogramData *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSaveHistogramData *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSaveHistogramData *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSaveHistogramData *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSaveHistogramData.png")));
}

//==================================================================================================
ButtonSaveHistogramData::ButtonSaveHistogramData(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save Histogram";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSaveHistogramData::~ButtonSaveHistogramData(void)
{
}

void	ButtonSaveHistogramData::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSaveHistogramData::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSaveHistogramData::SlotClicked (bool checked)
{
	int32	Ver=1;

	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	QString	FileName=GetLayersBase()->LGetSaveFileName (this
														, LangSolver.GetString(ButtonSaveHistogramData_LS,LID_0)/*"Save Histogram"*/, QString()
														, /**/"Histgramdata (*.hst);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::WriteOnly)==false)
			return;

		if(::Save(&F,Ver)==false)
			return;

		GUICmdReqHistogramData  **RData=new GUICmdReqHistogramData *[GetParamGlobal()->PageNumb];
		GUICmdSendHistogramData	**SData=new GUICmdSendHistogramData*[GetParamGlobal()->PageNumb];
		int32	N=0;
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			RData[page]=new GUICmdReqHistogramData (GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			SData[page]=new GUICmdSendHistogramData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
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
void	ButtonSaveHistogramData::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonSaveHistogramData_LS,LID_1)/*"FILE"*/
										,LangSolver.GetString(ButtonSaveHistogramData_LS,LID_2)/*"Save HistogramData"*/
										,this);
	p->SetMenuNumber(2010);
	p->SetShowingAttributeAsSwicthInTab();
	Info.AppendList(p);
}
void	ButtonSaveHistogramData::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

//==================================================================================================
GUICmdReqHistogramData::GUICmdReqHistogramData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqHistogramData::Load(QIODevice *f)
{
	return true;
}
bool	GUICmdReqHistogramData::Save(QIODevice *f)
{
	return true;
}

void	GUICmdReqHistogramData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendHistogramData	*SendBack=GetSendBack(GUICmdSendHistogramData,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	SendBack->Data.open(QIODevice::ReadWrite);
	GetLayersBase()->SaveHistgram(&SendBack->Data);

	SendBack->Data.seek(0);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendHistogramData::GUICmdSendHistogramData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendHistogramData::Load(QIODevice *f)
{
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdSendHistogramData::Save(QIODevice *f)
{
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdSendHistogramData::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
