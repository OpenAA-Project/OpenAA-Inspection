//#include "CopyMirroredTransferResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonGenerateFromGerber\ButtonGenerateFromGerber.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonGenerateFromGerber.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "SelectLibraryWithTypeDialog.h"
#include "XPropertyGerberFastPacket.h"
#include "SelectGerberAlgoTYpeDialog.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"GenerateFromGerber";

const	char	*AlgoRoot	=/**/"Basic";
const	char	*AlgoName	=/**/"GerberFast";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to transfer copied data with mirrored");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdGenerate	(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonGenerateFromGerber(Base,parent));
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
	Data[0].Pointer				 =&((ButtonGenerateFromGerber *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonGenerateFromGerber *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonGenerateFromGerber *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonGenerateFromGerber *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonGenerateFromGerber.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(AlgoRoot,AlgoName));
}

//==================================================================================================
ButtonGenerateFromGerber::ButtonGenerateFromGerber(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonGenerateFromGerber");
	Msg=/**/"GenerateFromGerber";

	GenLibType			=-1;
	GenLibID			=-1;
	GenGerberLayerNo	=-1;
	GerberAlgoType		=-1;
	GenGerberLib		=-1;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	GetParamGUI()->SetParam(&GenLibType			, /**/"ButtonGenerateFromGerber",/**/"GenLibType"			,"LibType ID to generate");
	GetParamGUI()->SetParam(&GenLibID			, /**/"ButtonGenerateFromGerber",/**/"GenLibID"				,"LibID to generate");
	GetParamGUI()->SetParam(&GenGerberLayerNo	, /**/"ButtonGenerateFromGerber",/**/"GenGerberLayerNo"		,"Gerber layer No");
	GetParamGUI()->SetParam(&GerberAlgoType		, /**/"ButtonGenerateFromGerber",/**/"GerberAlgoType"		,"Gerber algo type code to be generated");
	GetParamGUI()->SetParam(&GenGerberLib		, /**/"ButtonGenerateFromGerber",/**/"GenGerberLib"			,"Gerber LibID to be generated");
}

ButtonGenerateFromGerber::~ButtonGenerateFromGerber(void)
{
}
void	ButtonGenerateFromGerber::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}
void	ButtonGenerateFromGerber::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonGenerateFromGerber::SlotClicked (bool checked)
{
	int32	iGenLibType			=GenLibType			;
	int32	iGenLibID			=GenLibID			;
	int32	iGenGerberLayerNo	=GenGerberLayerNo	;
	int32	iGerberAlgoType		=GerberAlgoType		;
	int32	iGenGerberLib		=GenGerberLib		;

	if(GenLibType<0 || GenLibID<0){
		SelectLibraryWithTypeDialog	D(GetLayersBase());
		D.setWindowTitle("Item library to be generated");
		D.CurrentLibType=GenLibType;
		D.SelectedLibID	=GenLibID;
		D.Initial();
		if(D.exec()==true){
			iGenLibType	=D.CurrentLibType;
			iGenLibID	=D.SelectedLibID;
		}
	}
	else{
		iGenLibType	=GenLibType;
		iGenLibID	=GenLibID;
	}
	if(GenGerberLayerNo<0 && GenGerberLib<0){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyGerberFast",/**/"");
		if(f!=NULL){
			CmdGerberSelectLayerNo	RCmd(GetLayersBase());
			f->TransmitDirectly(&RCmd);
			iGenGerberLayerNo	=RCmd.GenGerberLayerNo;
			iGenGerberLib		=RCmd.GenGerberLib;
		}
	}
	if(iGenGerberLib<0){
		SelectLibraryWithTypeDialog	D(GetLayersBase());
		D.setWindowTitle("Gerber library on selected layer");
		D.CurrentLibType=DefLibTypeGerberFast;
		D.SelectedLibID	=iGenGerberLib;
		D.Initial();
		if(D.exec()==true){
			if(D.CurrentLibType==DefLibTypeGerberFast){
				iGenGerberLib	=D.SelectedLibID;
			}
		}
	}
	iGerberAlgoType=GerberAlgoType;
	if(iGerberAlgoType<0){
		SelectGerberAlgoTYpeDialog	D(GetLayersBase());
		if(D.exec()==true){
			iGerberAlgoType	=D.GerberAlgoType;
		}
	}
	if(iGerberAlgoType>=0 && (iGenGerberLayerNo>=0 || iGenGerberLib>=0) && iGenLibType>=0 && iGenLibID>=0){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyGerberFast",/**/"");
		if(f!=NULL){
			GUICmdSetGenerateAlgo	RCmd(GetLayersBase());
			RCmd.GenLibType			=iGenLibType;
			RCmd.GenLibID			=iGenLibID;
			RCmd.GenGerberLayerNo	=iGenGerberLayerNo;
			RCmd.GerberAlgoType		=iGerberAlgoType;
			RCmd.GenGerberLib		=iGenGerberLib;
			f->TransmitDirectly(&RCmd);
		}
	}
	if(iGerberAlgoType>=0 && (iGenGerberLayerNo>=0 || iGenGerberLib>=0) && iGenLibType>=0 && iGenLibID>=0){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyGerberFast",/**/"");
		if(f!=NULL){
			GUICmdGenerateAlgo	RCmd(GetLayersBase());
			f->TransmitDirectly(&RCmd);
		}
		/*
		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdGenerate	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Send(NULL,GlobalPage,0);
		}
		*/
	}
}

//======================================================================================

GUICmdGenerate::GUICmdGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdGenerate::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyGerberFast",/**/"");
	if(f!=NULL){
		GUICmdGenerateAlgo	RCmd(GetLayersBase());
		f->TransmitDirectly(&RCmd);
	}
}

