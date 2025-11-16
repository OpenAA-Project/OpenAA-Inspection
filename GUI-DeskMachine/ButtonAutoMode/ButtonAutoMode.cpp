#include "ButtonAutoModeResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonAutoMode\ButtonAutoMode.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonAutoMode.h"
#include "ThreadSequence.h"
//#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XFileRegistry.h"
#include "XLotInformation.h"
#include <QMessageBox>

static	char	*sRoot=/**/"Button";
static	char	*sName=/**/"AutoMode";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Auto Mode Button");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonAutoMode(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"PushedColor";
	Data[0].Pointer				 =&((ButtonAutoMode *)Instance)->PushedColor;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonAutoMode.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PixelInspection"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoMaskingPI"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"StatisticImager"));
}

//==================================================================================================
ButtonAutoMode::ButtonAutoMode(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent)
{
	//Œ¾Œê‘Î‰ž
	FileRegistry	*FRegistry=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);

	QString ImageBmpFile[5]={
		/**/":Resources/AutoModeImage.bmp",		//“ú–{Œê
		/**/":Resources/AutoModeImage-en.bmp",	//English
		/**/":Resources/AutoModeImage-en.bmp",	//ŠÈ‘Ì’†•¶
		/**/":Resources/AutoModeImage-en.bmp",	//”É‘Ì’†•¶
		/**/":Resources/AutoModeImage-en.bmp"	//Korean
	};
	Button.setImageBmpColored(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.setAutoExclusive(true);
	Button.setCheckable(true);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonAutoModeColored");
	PushedColor=Qt::red;
	resize(176,74);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));

	IsNecessaryLot=false;
	GetParamGUI()->SetParam(&IsNecessaryLot,/**/"ButtonAutoMode",/**/"IsNecessaryLot",LangSolver.GetString(ButtonAutoMode_LS,LID_0)/*"True if lot-id is necessary"*/);
}

ButtonAutoMode::~ButtonAutoMode(void)
{
}

void	ButtonAutoMode::Prepare(void)
{
	Button.setPressedColor(PushedColor);
	ResizeAction();
}

void	ButtonAutoMode::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonAutoMode::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetLot(0)->GetLotID()==/**/"-1" || GetLayersBase()->GetLot(0)->GetLotID().isEmpty()==true){
		if(IsNecessaryLot==true){
			QMessageBox::warning(NULL,/**/"Warning",LangSolver.GetString(ButtonAutoMode_LS,LID_1)/*"ƒƒbƒg‚ðÝ’è‚µ‚Ä‚­‚¾‚³‚¢"*/);
			Button.Cancel();
			return;
		}
	}

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		if(checked==true)
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_AutoCaptureInspect);
		else
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->SetAutoRepeat(ExecuteInspectBase::_NoAutoRepeat);
	}
}
