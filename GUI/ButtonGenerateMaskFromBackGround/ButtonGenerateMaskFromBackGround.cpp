/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonGenerateMaskFromBackGround\ButtonGenerateMaskFromBackGround.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonGenerateMaskFromBackGround.h"
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"
#include "XMasking.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"GenerateMaskFromBackGround";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to generate mask from BackGround");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdGenerateMaskFromBackGround(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonGenerateMaskFromBackGround(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"DiffBrightness";
	Data[4].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->DiffBrightness;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"MinObjectDotCount";
	Data[5].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->MinObjectDotCount;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"BoundaryWidth";
	Data[6].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->BoundaryWidth;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"CombineArea";
	Data[7].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->CombineArea;
	Data[8].Type				 =/**/"int32";
	Data[8].VariableNameWithRoute=/**/"SearchDot";
	Data[8].Pointer				 =&((ButtonGenerateMaskFromBackGround *)Instance)->SearchDot;
	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonGenerateMaskFromBackGround.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonGenerateMaskFromBackGround::ButtonGenerateMaskFromBackGround(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Edit FilterBank";
	DiffBrightness		=15;
	MinObjectDotCount	=500;
	Effective			=true;
	BoundaryWidth		=10;
	CombineArea			=true;
	SearchDot			=10;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonGenerateMaskFromBackGround::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonGenerateMaskFromBackGround::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonGenerateMaskFromBackGround::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdGenerateMaskFromBackGround	RCmd(GetLayersBase() ,sRoot,sName,page);
		RCmd.DiffBrightness		=DiffBrightness		;
		RCmd.MinObjectDotCount	=MinObjectDotCount	;
		RCmd.Effective			=Effective	;
		RCmd.LimitedLib			=LimitedLib	;
		RCmd.BoundaryWidth		=BoundaryWidth	;
		RCmd.CombineArea		=CombineArea;
		RCmd.SearchDot			=SearchDot;
		RCmd.Send(NULL,page ,0);
	}
}
void	ButtonGenerateMaskFromBackGround::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGenerateMaskFromBackGround	*CmdGenerateMaskFromBackGroundVar=dynamic_cast<CmdGenerateMaskFromBackGround *>(packet);
	if(CmdGenerateMaskFromBackGroundVar!=NULL){
		SlotClicked(true);
		return;
	}
}
//======================================================================================

GUICmdGenerateMaskFromBackGround::GUICmdGenerateMaskFromBackGround(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdGenerateMaskFromBackGround::Load(QIODevice *f)
{
	if(::Load(f,DiffBrightness	)	==false)	return false;
	if(::Load(f,MinObjectDotCount)	==false)	return false;
	if(::Load(f,Effective		)	==false)	return false;
	if(LimitedLib.Load(f)			==false)	return false;
	if(::Load(f,BoundaryWidth	)	==false)	return false;
	if(::Load(f,CombineArea		)	==false)	return false;
	if(::Load(f,SearchDot		)	==false)	return false;
	return true;
}
bool	GUICmdGenerateMaskFromBackGround::Save(QIODevice *f)
{
	if(::Save(f,DiffBrightness	)	==false)	return false;
	if(::Save(f,MinObjectDotCount)	==false)	return false;
	if(::Save(f,Effective		)	==false)	return false;
	if(LimitedLib.Save(f)			==false)	return false;
	if(::Save(f,BoundaryWidth	)	==false)	return false;
	if(::Save(f,CombineArea		)	==false)	return false;
	if(::Save(f,SearchDot		)	==false)	return false;
	return true;
}

void	GUICmdGenerateMaskFromBackGround::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Masking");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*Ap=ABase->GetPageData(localPage);
		CmdGenerateMaskFromBackGround	Cmd(GetLayersBase());
		Cmd.DiffBrightness		=DiffBrightness		;
		Cmd.MinObjectDotCount	=MinObjectDotCount	;
		Cmd.Effective			=Effective	;
		Cmd.LimitedLib			=LimitedLib	;
		Cmd.BoundaryWidth		=BoundaryWidth	;
		Cmd.CombineArea			=CombineArea;
		Cmd.SearchDot			=SearchDot;
		Ap->TransmitDirectly(&Cmd);
	}
}
