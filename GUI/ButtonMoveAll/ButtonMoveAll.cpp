/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonMoveAll\ButtonMoveAll.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonMoveAll.h"
#include "MoveAllForm.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "MoveAllFormResource.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"MoveAll";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for moving all");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdMoveAll(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonMoveAll(Base,parent));
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
	Data[0].Pointer				 =&((ButtonMoveAll *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonMoveAll *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonMoveAll *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonMoveAll *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonMoveAll.png")));
}

static	bool	MacroMoveAll(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Move";
		Functions[ret].Explain.append(/**/"Move all");
		Functions[ret].ArgName.append(/**/"Master image(true/false)");
		Functions[ret].ArgName.append(/**/"Target image(true/false)");
		Functions[ret].ArgName.append(/**/"Dx");
		Functions[ret].ArgName.append(/**/"Dy");
		Functions[ret].ArgName.append(/**/"Pages(-1:All or 0,1,2)");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveAll;
		ret++;
	}

	return ret;
}


static	bool	MacroMoveAll(GUIFormBase *Instance ,QStringList &Args)
{
	if(Args.count()<5){
		return false;
	}
	bool	MoveMasterImage=true;
	bool	MoveTargetImage=true;

	if(Args[0].toUpper()==/**/"TRUE")
		MoveMasterImage=true;
	else if(Args[0].toUpper()==/**/"false")
		MoveMasterImage=false;
	else
		return false;

	if(Args[1].toUpper()==/**/"TRUE")
		MoveTargetImage=true;
	else if(Args[1].toUpper()==/**/"false")
		MoveTargetImage=false;
	else
		return false;

	bool	ok;
	int	Dx=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Dy=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	ButtonMoveAll	*V=dynamic_cast<ButtonMoveAll *>(Instance);
	if(V==NULL)
		return false;

	IntList	Pages;
	QStringList	List=Args[4].split(',');
	for(int i=0;i<List.count();i++){
		QString	s=List[i];
		int	k=s.toInt(&ok);
		if(ok==false){
			return false;
		}
		if(k==-1){
			Pages.RemoveAll();
			for(int page=0;page<V->GetPageNumb();page++){
				Pages.Add(page);
			}
			break;
		}
		if(0<=k && k<V->GetPageNumb()){
			Pages.Add(k);
		}
	}

	V->ExecuteMove(Pages,MoveMasterImage ,MoveTargetImage ,Dx,Dy);
	return true;
}
//==================================================================================================

ButtonMoveAll::ButtonMoveAll(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Move all";
	resize(100,25);
	bool Ret1=(connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked())))?true:false;
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

ButtonMoveAll::~ButtonMoveAll(void)
{
}

void	ButtonMoveAll::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonMoveAll::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonMoveAll::SlotClicked()
{
	GetLayersBase()->TmpHideProcessingForm();
	MoveAllForm	D(GetLayersBase(),NULL);
	if(D.exec()==(int)true){
		ExecuteMove(D.AppliedPages,D.MoveMasterImage ,D.MoveTargetImage ,D.MovX,D.MovY);
	}
	GetLayersBase()->TmpRercoverProcessingForm();
}

void	ButtonMoveAll::ExecuteMove(IntList &AppliedPages,bool MoveMasterImage ,bool MoveTargetImage ,int Dx,int Dy)
{
	for(IntClass *d=AppliedPages.GetFirst();d!=NULL;d=d->GetNext()){
		int	page=d->GetValue();
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMoveAll	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.MovX	=Dx;
		RCmd.MovY	=Dy;
		RCmd.MoveMasterImage	=MoveMasterImage;
		RCmd.MoveTargetImage	=MoveTargetImage;
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void	ButtonMoveAll::TransmitDirectly(GUIDirectMessage *packet)
{

}
void	ButtonMoveAll::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,/**/"Tool","Move All",this);
	p->SetMenuNumber(120);
	Info.AppendList(p);
}
void	ButtonMoveAll::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked();
	}
}

//==============================================================================================

GUICmdMoveAll::GUICmdMoveAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	
}
bool	GUICmdMoveAll::Load(QIODevice *f)
{
	if(::Load(f,MovX)==false)
		return false;
	if(::Load(f,MovY)==false)
		return false;
	if(::Load(f,MoveMasterImage)==false)
		return false;
	if(::Load(f,MoveTargetImage)==false)
		return false;
	return true;
}
bool	GUICmdMoveAll::Save(QIODevice *f)
{
	if(::Save(f,MovX)==false)
		return false;
	if(::Save(f,MovY)==false)
		return false;
	if(::Save(f,MoveMasterImage)==false)
		return false;
	if(::Save(f,MoveTargetImage)==false)
		return false;
	return true;
}

void	GUICmdMoveAll::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*P=GetLayersBase()->GetPageData(localPage);
	for(int i=0;i<GetLayerNumb(localPage);i++){
		DataInLayer	*L=P->GetLayerData(i);
		if(MoveMasterImage==true){
			L->GetMasterBuff().MoveImage(MovX,MovY);
		}
		if(MoveTargetImage==true){
			L->GetTargetBuff().MoveImage(MovX,MovY);
		}
	}
	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext()){
		AlgorithmBase	*ABase=L->GetInstance();
		AlgorithmInPageRoot	*APage=ABase->GetPageData(localPage);
		APage->ExecuteMove(MovX,MovY,true);
	}
}
