#include "ButtonLearningOKResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonLearningOK\ButtonLearningOK.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonLearningOK.h"
#include "XGeneralDialog.h"
#include "XDisplayImage.h"
#include "LearningLibResource.h"
#include "XDataInLayerCommander.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"LearningOK";

extern	LangSolverNew	LangSolverGUI;


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to add OK for learning");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
	LangSolverGUI.SetLanguage(Pkg,LanguageCode);
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
	return(new ButtonLearningOK(Base,parent));
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
	Data[0].Pointer				 =&((ButtonLearningOK *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonLearningOK *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonLearningOK *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonLearningOK *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"RelatedImagePanel";
	Data[4].Pointer				 =&((ButtonLearningOK *)Instance)->RelatedImagePanel;
	Data[5].Type				 =/**/"QString";
	Data[5].VariableNameWithRoute=/**/"NGListInst";
	Data[5].Pointer				 =&((ButtonLearningOK *)Instance)->NGListInst;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonLearningOK.png")));
}

//==================================================================================================
ButtonLearningOK::ButtonLearningOK(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"ButtonLearningOK");
	Button.move(0,0);
	Msg=/**/"Add OK";
	resize(60,25);
	LForm=NULL;

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonLearningOK::~ButtonLearningOK(void)
{
	if(LForm!=NULL){
		delete	LForm;
		LForm=NULL;
	}
}

void	ButtonLearningOK::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonLearningOK::ResizeAction()
{
	Button.resize(width(),height());
}


void ButtonLearningOK::SlotClicked (bool checked)
{
	GUIFormBase	*g=GetLayersBase()->FindByName(NGListInst);
	if(g!=NULL){
		CmdGetCurrentInfo	TCmd(GetLayersBase());
		g->TransmitDirectly(&TCmd);
		if(TCmd.ItemID<0 || TCmd.LibID<0 || TCmd.RepresentativeItem==NULL){
			return;
		}
		GUIFormBase	*f=GetLayersBase()->FindByName(RelatedImagePanel);
		if(f!=NULL){
			DisplayImage	*DImage=dynamic_cast<DisplayImage *>(f);
			if(DImage!=NULL){
				int GlobalX1,GlobalY1,GlobalX2,GlobalY2;
				DImage->GetDrawingArea(GlobalX1,GlobalY1,GlobalX2,GlobalY2);
				int	GlobalCx=(GlobalX1+GlobalX2)/2;
				int	GlobalCy=(GlobalY1+GlobalY2)/2;
				if(LForm!=NULL){
					delete	LForm;
					LForm=NULL;
				}
				LForm=new LearningPanelForm(GlobalCx,GlobalCy
											,true
											,TCmd.RepresentativeItem
											,sRoot,sName,GetLayersBase());
				LForm->show();
			}
		}
	}
}
void	ButtonLearningOK::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(ButtonLearningOK_LS,LID_0)/*"Tool"*/,LangSolver.GetString(ButtonLearningOK_LS,LID_1)/*"Add OK for learning"*/,this);
	p->SetMenuNumber(100);
	Info.AppendList(p);
}
void	ButtonLearningOK::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
