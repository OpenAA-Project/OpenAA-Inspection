#include "ButtonMonoBitmapForAlgorithmResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonMonoBitmapForAlgorithm\ButtonMonoBitmapForAlgorithm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonMonoBitmapForAlgorithm.h"
#include "XPointer.h"
#include "XGeneralFunc.h"
#include <QFile>
#include <QFileDialog>

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"SaveMonoBitmapForAlgorithm";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show dialog to save monochrome bitmap of Algorithm");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqMonoBitmapForAlgorithm	(Base,sRoot,sName);
	(*Base)=new GUICmdSendMonoBitmapForAlgorithm(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonMonoBitmapForAlgorithm(Base,parent));
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
	Data[0].Pointer				 =&((ButtonMonoBitmapForAlgorithm *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonMonoBitmapForAlgorithm *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonMonoBitmapForAlgorithm *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonMonoBitmapForAlgorithm *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"AlgorithmRoot";
	Data[4].Pointer				 =&((ButtonMonoBitmapForAlgorithm *)Instance)->AlgorithmRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"AlgorithmName";
	Data[5].Pointer				 =&((ButtonMonoBitmapForAlgorithm *)Instance)->AlgorithmName;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonMonoBitmapForAlgorithm.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonMonoBitmapForAlgorithm::ButtonMonoBitmapForAlgorithm(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Save bitmap of Algorithm";
	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonMonoBitmapForAlgorithm::~ButtonMonoBitmapForAlgorithm(void)
{
}

void	ButtonMonoBitmapForAlgorithm::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonMonoBitmapForAlgorithm::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonMonoBitmapForAlgorithm::SlotClicked (bool checked)
{
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	QString	FileName=GetLayersBase()->LGetSaveFileName (this
									, LangSolver.GetString(ButtonMonoBitmapForAlgorithm_LS,LID_0)/*"Save bitmap of Algorithm"*/
									, QString()
									, /**/"Algorithm bitmap(*.bxx);;All files (*.*)");
	if(FileName.isEmpty()==false){
		QFile	F(FileName);
		if(F.open(QIODevice::WriteOnly)==false)
			return;
		int	Page=0;
		//int32	N=0;
		int32	DotPerLine=GetDotPerLine(Page);
		if(::Save(&F,DotPerLine)==false)
			return;
		int32	MaxLines=GetMaxLines(Page);
		if(::Save(&F,MaxLines)==false)
			return;
		int32	PageNumb=GetPageNumb();
		if(::Save(&F,PageNumb)==false)
			return;
		int32	LayerNumb=GetLayerNumb(Page);
		if(::Save(&F,LayerNumb)==false)
			return;
		int32	XByte	=(DotPerLine+7)/8;
		for(int page=0;page<GetPageNumb();page++){
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdReqMonoBitmapForAlgorithm		RData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			GUICmdSendMonoBitmapForAlgorithm	SData(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
			RData.AlgorithmRoot	=AlgorithmRoot;
			RData.AlgorithmName	=AlgorithmName;
			RData.DotPerLine	=DotPerLine;
			RData.MaxLines		=MaxLines;
			RData.XByte			=XByte;
			RData.Send(globalPage,0,SData);
			if(SData.IsReceived()==true){
				int32	Len=SData.Data.size();
				if(::Save(&F,Len)==false)
					return;
				F.write(SData.Data.data());
			}
		}
	}
}
//==================================================================================================
GUICmdReqMonoBitmapForAlgorithm::GUICmdReqMonoBitmapForAlgorithm(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqMonoBitmapForAlgorithm::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,AlgorithmRoot)==false)
		return false;
	if(::Load(f,AlgorithmName)==false)
		return false;
	if(::Load(f,DotPerLine)==false)
		return false;
	if(::Load(f,MaxLines)==false)
		return false;
	if(::Load(f,XByte)==false)
		return false;
	return true;
}
bool	GUICmdReqMonoBitmapForAlgorithm::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,AlgorithmRoot)==false)
		return false;
	if(::Save(f,AlgorithmName)==false)
		return false;
	if(::Save(f,DotPerLine)==false)
		return false;
	if(::Save(f,MaxLines)==false)
		return false;
	if(::Save(f,XByte)==false)
		return false;
	return true;
}

void	GUICmdReqMonoBitmapForAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendMonoBitmapForAlgorithm	*SendBack=GetSendBack(GUICmdSendMonoBitmapForAlgorithm,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	AlgorithmBase	*AL=GetLayersBase()->GetAlgorithmBase(AlgorithmRoot ,AlgorithmName);
	if(AL!=NULL){
		BYTE    **P=MakeMatrixBuff(XByte ,MaxLines);
		MatrixBuffClear(P ,0 ,XByte ,MaxLines);
		SendBack->GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(localPage);
		SendBack->Data.open(QIODevice::ReadWrite);
		AL->DrawMonoBitmap(P);
		::Save(&SendBack->Data,P,XByte ,MaxLines);
		SendBack->Data.seek(0);
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendMonoBitmapForAlgorithm::GUICmdSendMonoBitmapForAlgorithm(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendMonoBitmapForAlgorithm::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	int64	DataSize;
	if(::Load(f,DataSize)==false)
		return false;
	QByteArray byteArray=f->read(DataSize);
	Data.setData(byteArray);
	return true;
}
bool	GUICmdSendMonoBitmapForAlgorithm::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	int64	DataSize=Data.size();
	if(::Save(f,DataSize)==false)
		return false;
	f->write(Data.data());
	return true;
}

void	GUICmdSendMonoBitmapForAlgorithm::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
