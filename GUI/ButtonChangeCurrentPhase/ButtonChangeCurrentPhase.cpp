#include "ButtonChangeCurrentPhaseResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonChangeCurrentPhase\ButtonChangeCurrentPhase.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonChangeCurrentPhase.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ChangeCurrentPhase";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Buttons to Change current phase number");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeCurrentPhase(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonChangeCurrentPhase(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"PhaseTitles";
	Data[0].Pointer				 =&((ButtonChangeCurrentPhase *)Instance)->PhaseTitles;
	Data[1].Type				 =/**/"QFont";
	Data[1].VariableNameWithRoute=/**/"ButtonFont";
	Data[1].Pointer				 =&((ButtonChangeCurrentPhase *)Instance)->ButtonFont;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"UncheckedColor";
	Data[2].Pointer				 =&((ButtonChangeCurrentPhase *)Instance)->UncheckedColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"ActiveColor";
	Data[3].Pointer				 =&((ButtonChangeCurrentPhase *)Instance)->ActiveColor;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"CurrentPhase";
	Data[4].Pointer				 =&((ButtonChangeCurrentPhase *)Instance)->CurrentPhase;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"UsePhaseName";
	Data[5].Pointer				 =&((ButtonChangeCurrentPhase *)Instance)->UsePhaseName;
	Data[6].Type				 =/**/"Horizontal,Vertical";
	Data[6].VariableNameWithRoute=/**/"OrientationStr";
	Data[6].Pointer				 =&((ButtonChangeCurrentPhase *)Instance)->OrientationStr;

	
	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonChangeCurrentPhase.png")));
}

//==================================================================================================
ButtonChangeCurrentPhase::ButtonChangeCurrentPhase(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	CurrentPhase	=-1;
	for(int i=0;i<MaxButtonPhaseNumb;i++){
		Buttons[i]=NULL;
	}
	IconSizeW		=48;
	IconSizeH		=32;
	UsePhaseName	=true;
	UncheckedColor	=Qt::green;
	ActiveColor		=Qt::red;
	OrientationStr	="Horizontal";

	resize(150,32);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonChangeCurrentPhase::~ButtonChangeCurrentPhase(void)
{
	Release();
}

void	ButtonChangeCurrentPhase::Release(void)
{
	for(int i=0;i<MaxButtonPhaseNumb;i++){
		if(Buttons[i]!=NULL){
			delete	Buttons[i];
			Buttons[i]=NULL;
		}
	}
}

void	ButtonChangeCurrentPhase::Prepare(void)
{
	connect(GetLayersBase(),SIGNAL(SignalChangedPhasePageLayer())	,this,SLOT(SlotChangedPhasePageLayer()));
	connect(GetLayersBase(),SIGNAL(SignalChangeCurrentPhase())		,this,SLOT(SlotChangeCurrentPhase())	,Qt::QueuedConnection);
	ShowButtons();
	ResizeAction();
}
void	ButtonChangeCurrentPhase::ResizeAction()
{
	int	ButtonCount=GetPhaseNumb();
	if(ButtonCount>0){
		if(OrientationStr=="Horizontal"){
			int	W=width()/ButtonCount;
			int	X=0;
			for(int ph=0;ph<ButtonCount;ph++){
				Buttons[ph]->move(X,0);
				Buttons[ph]->resize(W,height());
				X+=W;
			}
			for(int ph=ButtonCount;ph<MaxButtonPhaseNumb;ph++){
				Buttons[ph]->move(X+10,0);
				Buttons[ph]->resize(W,height());
			}
		}
		else{
			int	H=height()/ButtonCount;
			int	Y=0;
			for(int ph=0;ph<ButtonCount;ph++){
				Buttons[ph]->move(0,Y);
				Buttons[ph]->resize(width(),H);
				Y+=H;
			}
			for(int ph=ButtonCount;ph<MaxButtonPhaseNumb;ph++){
				Buttons[ph]->move(0,Y+10);
				Buttons[ph]->resize(width(),H);
			}
		}

		for(int ph=0;ph<ButtonCount;ph++){
			if(ph<PhaseTitles.count()){
				Buttons[ph]->setText(PhaseTitles[ph]);
			}
			else{
				if(UsePhaseName==true){
					Buttons[ph]->setText(GetParamGlobal()->GetPhaseString(ph));
				}
				else{
					Buttons[ph]->setText(QString::number(ph+1));
				}
			}
			Buttons[ph]->setFont (ButtonFont);
			Buttons[ph]->setColor(UncheckedColor);
			Buttons[ph]->setPressedColor(ActiveColor);
			//Buttons[i]->setInvertMode(true);
			disconnect(Buttons[ph],SIGNAL(clicked(bool)),this,SLOT(SlotButtonDown(bool)));
			connect(Buttons[ph],SIGNAL(clicked(bool)),this,SLOT(SlotButtonDown(bool)));
			Buttons[ph]->setAutoExclusive(true);
			Buttons[ph]->setCheckable(true);
			Buttons[ph]->setAutoRaise(true);
			if(GetLayersBase()->GetCurrentPhase()==ph){
				Buttons[ph]->setChecked(true);
			}
		}
	}
}
void	ButtonChangeCurrentPhase::SlotChangedPhasePageLayer()
{
	ResizeAction();
}
void	ButtonChangeCurrentPhase::SlotChangeCurrentPhase()
{
	//if(CurrentPhase<0){
		int	phase=GetLayersBase()->GetCurrentPhase();
		if(0<=phase && phase<MaxButtonPhaseNumb){
			Buttons[phase]->setChecked(true);
		}
	//}
}
void	ButtonChangeCurrentPhase::ShowButtons(void)
{
	Release();
	if(CurrentPhase>=0){
		GetLayersBase()->SetCurrentPhase(CurrentPhase);
	}
	for(int i=0;i<MaxButtonPhaseNumb;i++){
		Buttons[i]=new mtToolButtonColored(false,this);
		if(i<PhaseTitles.count()){
			Buttons[i]->setText(PhaseTitles[i]);
		}
		else{
			if(UsePhaseName==true){
				Buttons[i]->setText(GetParamGlobal()->GetPhaseString(i));
			}
			else{
				Buttons[i]->setText(QString::number(i+1));
			}
		}
		Buttons[i]->setParent(this);
		Buttons[i]->setFont (ButtonFont);
		Buttons[i]->setColor(UncheckedColor);
		Buttons[i]->setPressedColor(ActiveColor);
		//Buttons[i]->setInvertMode(true);
		connect(Buttons[i],SIGNAL(clicked(bool)),this,SLOT(SlotButtonDown(bool)));
		Buttons[i]->setAutoExclusive(true);
		Buttons[i]->setCheckable(true);
		Buttons[i]->setAutoRaise(true);
		if(GetLayersBase()->GetCurrentPhase()==i){
			Buttons[i]->setChecked(true);
		}
	}
}
void	ButtonChangeCurrentPhase::BuildForShow(void)
{
	ResizeAction();
}
void	ButtonChangeCurrentPhase::ShowInEdit(void)
{
	if(0<=GetLayersBase()->GetCurrentPhase()){
		Buttons[GetLayersBase()->GetCurrentPhase()]->setChecked(true);
	}
}
void	ButtonChangeCurrentPhase::SlotButtonDown(bool)
{
	int	NewPhase=0;
	int	ButtonCount=GetPhaseNumb();
	for(int i=0;i<ButtonCount;i++){
		if(Buttons[i]->isChecked()==true){
			NewPhase=i;
			GetLayersBase()->SetCurrentPhase(NewPhase);
			BroadcastShowInEdit();
			break;
		}
	}
	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdChangeCurrentPhase	PushRequester(GetLayersBase(),sRoot,sName);
			PushRequester.NewPhase=NewPhase;
			PushRequester.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
		}
		GetLayersBase()->WaitAllAcknowledged(60*20);
	}
	BroadcastShowInEdit();
}
void	ButtonChangeCurrentPhase::ShowInPlayer(int64 shownInspectionID)
{
	int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
	if(0<=CurrentPhase){
		Buttons[CurrentPhase]->setChecked(true);
	}
}
//======================================================================================
GUICmdChangeCurrentPhase::GUICmdChangeCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeCurrentPhase::Load(QIODevice *f)
{
	if(::Load(f,NewPhase)==false)
		return false;
	return true;
}
bool	GUICmdChangeCurrentPhase::Save(QIODevice *f)
{
	if(::Save(f,NewPhase)==false)
		return false;
	return true;
}

void	GUICmdChangeCurrentPhase::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->SetCurrentPhase(NewPhase);
	}
	SendAck(localPage);
}