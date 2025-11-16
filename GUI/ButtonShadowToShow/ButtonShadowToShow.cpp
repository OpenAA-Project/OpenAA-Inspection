/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShadowToShow\ButtonShadowToShow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonShadowToShow.h"
#include "XGUI.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ShadowToShow";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show shadow");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSetCurrentShadow	(Base ,sRoot,sName ,-1);
	//(*Base)=new GUICmdReqLoad		(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonShadowToShow(Base,parent));
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
	Data[0].Pointer				 =&((ButtonShadowToShow *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonShadowToShow *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonShadowToShow *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonShadowToShow *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShadowToShow.png")));
}

//==================================================================================================
ShadowButton::ShadowButton(int n)
{
	Number=n;
	bool Ret1=(connect(this,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool))))?true:false;
}
ShadowButton::~ShadowButton()
{
}
void ShadowButton::SlotClicked (bool checked)
{
	emit	SignalClicked(Number);
}

ButtonShadowToShow::ButtonShadowToShow(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Msg	=/**/"Shadow";
	CharColor	=Qt::black;

	ButtonDim	=NULL;
	AllocatedButtonCount	=0;

	resize(100,25);
	bool Ret2=(connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction())))?true:false;
}

ButtonShadowToShow::~ButtonShadowToShow(void)
{
}

void	ButtonShadowToShow::Prepare(void)
{
	ShowButtons();
	ResizeAction();
}

void	ButtonShadowToShow::ResizeAction()
{
	if(AllocatedButtonCount!=0){
		int	W=width()/AllocatedButtonCount;
		for(int i=0;i<AllocatedButtonCount;i++){
			ButtonDim[i]->setGeometry(W*i,0,W,height());
		}
	}
}
void	ButtonShadowToShow::ShowInEdit(void)
{
	ShowButtons();
}
void	ButtonShadowToShow::BuildForShow(void)
{
	ShowButtons();
}

void	ButtonShadowToShow::ShowButtons(void)
{
	int	ShadowCount=GetParamGlobal()->ShadowParameterData.GetCount();
	if(ShadowCount!=AllocatedButtonCount){
		if(ButtonDim!=NULL){
			for(int i=0;i<AllocatedButtonCount;i++){
				delete	ButtonDim[i];
			}
			delete	[]ButtonDim;
		}
		AllocatedButtonCount=ShadowCount;
		if(ShadowCount!=0){		
			ButtonDim=new ShadowButton*[AllocatedButtonCount];
			for(int i=0;i<AllocatedButtonCount;i++){
				ButtonDim[i]=new ShadowButton(i);
				ButtonDim[i]->setParent(this);
				ButtonDim[i]->setCheckable(true);
				ButtonDim[i]->setFont (CFont);
				connect(ButtonDim[i],SIGNAL(SignalClicked(int)),this,SLOT(SlotClicked(int)));
				ButtonDim[i]->setText(Msg
									 +QString(/**/"-")
									 +QString::number(i+1));
				ButtonDim[i]->show();
			}
		}
	}
}
void ButtonShadowToShow::SlotClicked(int ButtonNumber)
{
	//if(ButtonNumber<0 || AllocatedButtonCount<=ButtonNumber)
	//	return;
	//if(ButtonDim[ButtonNumber]->isChecked()==true){
	//	for(int i=0;i<AllocatedButtonCount;i++){
	//		if(ButtonNumber!=i){
	//			ButtonDim[ButtonNumber]->setChecked(false);
	//		}
	//	}
	//	for(int page=0;page<GetPageNumb();page++){
	//		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	//		GUICmdSetCurrentShadow	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	//		RCmd.Shadow	=ButtonNumber;
	//		RCmd.Send(NULL,GlobalPage,0);
	//	}
	//}
	//else{
	//	for(int page=0;page<GetPageNumb();page++){
	//		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	//		GUICmdSetCurrentShadow	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	//		RCmd.Shadow	=-1;
	//		RCmd.Send(NULL,GlobalPage,0);
	//	}
	//}
	ShadowTree	*Sh=GetLayersBase()->GetShadowChildren(ButtonNumber);
	if(Sh!=NULL){
		Sh->ShowShadow();
	}
	
}


//==========================================================================================================

GUICmdSetCurrentShadow::GUICmdSetCurrentShadow(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSetCurrentShadow::Load(QIODevice *f)
{
	if(::Load(f,Shadow)==false)
		return false;

	return true;
}
bool	GUICmdSetCurrentShadow::Save(QIODevice *f)
{
	if(::Save(f,Shadow)==false)
		return false;

	return true;
}

void	GUICmdSetCurrentShadow::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetCurrentShadowNumber(Shadow);
	}
}