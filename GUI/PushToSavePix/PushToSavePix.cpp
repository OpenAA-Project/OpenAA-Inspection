/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PushToSavePix\PushToSavePix.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PushToSavePix.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "SaveImageTargetButton.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PushToSavePix";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Push to Save Pix image data");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdReqRelease	(Base ,sRoot,sName ,-1);
	//(*Base)=new GUICmdReqLoad		(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PushToSavePix(Base,parent));
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
	Data[0].Pointer				 =&((PushToSavePix *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((PushToSavePix *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((PushToSavePix *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((PushToSavePix *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PushToSavePix.png")));
}

//==================================================================================================

PushToSavePix::PushToSavePix(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setCheckable(false);
	Msg=/**/"SavePix";
	PathToSave	=/**/"c:\\Data";

	resize(100,25);

	bool Ret1=(connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool))))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;

	GetParamGUI()->SetParam(&PathToSave, /**/"PushToSavePix", /**/"PathToSave"		
											 , "Path to Save"		);
}

PushToSavePix::~PushToSavePix(void)
{
}

void	PushToSavePix::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	PushToSavePix::ResizeAction()
{
	Button.resize(width(),height());
}

void PushToSavePix::SlotClicked(bool checked)
{
	CmdReqSaveImage	Cmd(GetLayersBase());
	
	ForceDirectories(PathToSave);
	Cmd.FileName	=PathToSave
					+GetSeparator()
					+QString(/**/"TargetImage")
					+QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss")
					+QString(/**/".pix");
	Cmd.UsageImageMode=CmdReqSaveImage::_SaveTargetImage;
	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"SaveImageTargetButton" ,/**/"");
	f->TransmitDirectly(&Cmd);
}

void	PushToSavePix::TransmitDirectly(GUIDirectMessage *packet)
{

}
void	PushToSavePix::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,/**/"File"
										,"PushToSavePix"
										,this);
	p->SetMenuNumber(257);
	Info.AppendList(p);
}
void	PushToSavePix::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

//==========================================================================================================