#include "ButtonSelectLearningTargetImageResource.h"
#include "XSelectLearningPacketResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectLearningTargetImage\ButtonSelectLearningTargetImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSelectLearningTargetImage.h"
#include "XGeneralDialog.h"
#include "SelectLearningImageForm.h"
#include "XSelectLearningPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"SelectLearningTargetImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to select learning image to target");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqLearningStockerList	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendLearningStockerList	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSetLearningImage		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSetLearningImage	(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSelectLearningTargetImage(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSelectLearningTargetImage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSelectLearningTargetImage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSelectLearningTargetImage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSelectLearningTargetImage *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"DisplayImageRoot";
	Data[4].Pointer				 =&((ButtonSelectLearningTargetImage *)Instance)->DisplayImageRoot;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"DisplayImageName";
	Data[5].Pointer				 =&((ButtonSelectLearningTargetImage *)Instance)->DisplayImageName;
	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"DisplayImageInst";
	Data[6].Pointer				 =&((ButtonSelectLearningTargetImage *)Instance)->DisplayImageInst;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSelectLearningTargetImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonSelectLearningTargetImage::ButtonSelectLearningTargetImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Show Learning list";
	resize(60,25);

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSelectLearningTargetImage::~ButtonSelectLearningTargetImage(void)
{
}

void	ButtonSelectLearningTargetImage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSelectLearningTargetImage::ResizeAction()
{
	Button.resize(width(),height());
}


void ButtonSelectLearningTargetImage::SlotClicked (bool checked)
{
	SelectLearningImageForm	*D=new SelectLearningImageForm(GetLayersBase()
														,this
														,DisplayImageRoot
														,DisplayImageName
														,DisplayImageInst
														,NULL);
	D->show();
}
void	ButtonSelectLearningTargetImage::GetMenuInfo(MenuInfoContainer &Info)
{
//	MenuInfoList	*p=new MenuInfoList(1,"Tool","Add NG for learning",this);
//	p->SetMenuNumber(101);
//	Info.AppendList(p);
}
void	ButtonSelectLearningTargetImage::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
