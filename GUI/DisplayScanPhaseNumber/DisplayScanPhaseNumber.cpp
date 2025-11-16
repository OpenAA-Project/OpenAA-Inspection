#include "DisplayScanPhaseNumberResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayScanPhaseNumber\DisplayScanPhaseNumber.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayScanPhaseNumber.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

static	const	char	*sRoot=/**/"Display";
static	const	char	*sName=/**/"ScanPhaseNumber";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display number of ScanPhase");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdRewindInspection(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayScanPhaseNumber(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"ScanPhaseNames";
	Data[0].Pointer				 =&((DisplayScanPhaseNumber *)Instance)->ScanPhaseNames;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((DisplayScanPhaseNumber *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"NormalColor";
	Data[2].Pointer				 =&((DisplayScanPhaseNumber *)Instance)->NormalColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"ActiveColor";
	Data[3].Pointer				 =&((DisplayScanPhaseNumber *)Instance)->ActiveColor;	
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((DisplayScanPhaseNumber *)Instance)->CFont;
	Data[5].Type				 =/**/"Horizontal,Vertical";
	Data[5].VariableNameWithRoute=/**/"OrientationStr";
	Data[5].Pointer				 =&((DisplayScanPhaseNumber *)Instance)->OrientationStr;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayScanPhaseNumber.png")));
}

static	bool	MacroDisplayScanPhaseNumber(GUIFormBase *Instance ,QStringList &Args)
{
	DisplayScanPhaseNumber	*V=dynamic_cast<DisplayScanPhaseNumber *>(Instance);
	if(V==NULL){
		return false;
	}

	V->SlotClicked(true);
	return false;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DisplayScanPhaseNumber";
		Functions[ret].Explain.append(/**/"Display number of ScanPhase");
		Functions[ret].DLL_ExcuteMacro	=MacroDisplayScanPhaseNumber;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
DisplayScanPhaseNumber::DisplayScanPhaseNumber(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Buttons			=NULL;
	AllocatedCount	=0;
	CharColor		=Qt::white;
	NormalColor		=Qt::gray;
	ActiveColor		=Qt::red;
	OrientationStr	="Horizontal";

	resize(80,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

DisplayScanPhaseNumber::~DisplayScanPhaseNumber(void)
{
	for(int ph=0;ph<AllocatedCount;ph++){
		delete	Buttons[ph];
	}
	delete	[]Buttons;
	Buttons=NULL;
	AllocatedCount=0;
}

void	DisplayScanPhaseNumber::Prepare(void)
{
	AllocatedCount	=GetParamGlobal()->GetScanPhaseCount();
	Buttons=new mtToolButtonColored*[AllocatedCount];
	for(int ph=0;ph<AllocatedCount;ph++){
		Buttons[ph]=new mtToolButtonColored(false,this);
		if(ScanPhaseNames.count()>ph){
			Buttons[ph]->setText(ScanPhaseNames[ph]);
		}
		Buttons[ph]->setFont (CFont);
		Buttons[ph]->setColor(NormalColor);
		Buttons[ph]->setPressedColor(ActiveColor);
		Buttons[ph]->setAutoExclusive(true);
		Buttons[ph]->setAutoRaise(true);
		Buttons[ph]->setCheckable(true);
		connect(Buttons[ph],SIGNAL(clicked(bool)),this,SLOT(SlotClicked(bool)));
	}
	ResizeAction();
	ShowInPlayer();
}

void	DisplayScanPhaseNumber::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	DisplayScanPhaseNumber::ResizeAction()
{
	if(AllocatedCount>0){
		if(OrientationStr=="Horizontal"){
			int	W=width()/AllocatedCount;
			int	X=0;
			for(int ph=0;ph<AllocatedCount;ph++){
				Buttons[ph]->move(X,0);
				Buttons[ph]->resize(W,height());
				X+=W;
			}
		}
		else{
			int	H=height()/AllocatedCount;
			int	Y=0;
			for(int ph=0;ph<AllocatedCount;ph++){
				Buttons[ph]->move(0,Y);
				Buttons[ph]->resize(width(),H);
				Y+=H;
			}
		}
	}
}


void	DisplayScanPhaseNumber::SlotClicked (bool checked)
{
	if(AllocatedCount>0){
		int	Ph=0;
		for(int ph=0;ph<AllocatedCount;ph++){
			if(Buttons[ph]->isChecked()==true){
				Ph=ph;
				break;
			}
		}
		GetLayersBase()->TF_SetCurrentScanPhaseNumber(Ph);
		BroadcastShowInEdit();
	}
}
bool DisplayScanPhaseNumber::OnIdle(void)
{
	static	int	LastPh=-1;
	if(AllocatedCount>0){
		int	ph=GetLayersBase()->GetCurrentScanPhaseNumber();
		if(LastPh!=ph && ph<AllocatedCount){
			Buttons[ph]->setChecked(true);
			LastPh=ph;
		}
	}
	return true;
}