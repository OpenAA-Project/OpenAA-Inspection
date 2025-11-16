/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonChange\ButtonChange.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonChange.h"
#include "XGeneralDialog.h"
#include "ChangeDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"Change";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Change phase/page/layer/Line count");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeCount	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonChange(Base,parent));
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
	Data[0].Pointer				 =&((ButtonChange *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonChange *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonChange *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonChange *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonChange.png")));
}

static bool	MacroChange(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Change";
		Functions[ret].Explain.append(/**/"Change phase/Layer/Line count");
		Functions[ret].ArgName.append(/**/"Phase count");
		Functions[ret].ArgName.append(/**/"Page count");
		Functions[ret].ArgName.append(/**/"Layer count");
		Functions[ret].ArgName.append(/**/"Line count");
		Functions[ret].DLL_ExcuteMacro	=MacroChange;
		ret++;
	}

	return ret;
}

static bool	MacroChange(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonChange	*V=dynamic_cast<ButtonChange *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()>=3){
		bool	ok;
		int	PhaseCount	=Args[0].toInt(&ok);
		if(ok==false)
			return false;
		int	PageCount	=Args[1].toInt(&ok);
		if(ok==false)
			return false;
		int	LayerCount	=Args[2].toInt(&ok);
		if(ok==false)
			return false;
		int	LineCount	=Args[3].toInt(&ok);
		if(ok==false)
			return false;

		V->SetChange(PhaseCount,PageCount,LayerCount,LineCount);
	}
	return true;
}

//==================================================================================================
ButtonChange::ButtonChange(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonChange");
	Msg=/**/"Button Change";


	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonChange::~ButtonChange(void)
{
}

void	ButtonChange::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonChange::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonChange::SlotClicked (bool checked)
{
	ChangeDialog	D(GetLayersBase());
	if(D.exec()==(int)true){
		SetChange(D.NewPhaseCount,D.NewPageCount,D.NewLayerCount,D.NewLineCount);
	}
}

void	ButtonChange::SetChange(int PhaseCount,int PageCount,int LayerCount,int LineCount)
{
	GetLayersBase()->Reallocate(PhaseCount,PageCount,LayerCount);
	//GetLayersBase()->ReallocXYPixels(GetDotPerLine(),D.NewLineCount);
	//if(GetParamComm()->GetConnectedPCNumb()!=0){
		for(int page=0;page<GetParamGlobal()->PageNumb;page++){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
			GUICmdChangeCount	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.NewPhaseCount	=PhaseCount;
			RCmd.NewLayerCount	=LayerCount;
			RCmd.NewLineCount	=LineCount;
			RCmd.Send(NULL,globalPage,0);
		}
	//}
}

//----------------------------------------------------------------------------------

GUICmdChangeCount::GUICmdChangeCount(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdChangeCount::Load(QIODevice *f)
{
	if(::Load(f,NewPhaseCount)==false)
		return false;
	if(::Load(f,NewLayerCount)==false)
		return false;
	if(::Load(f,NewLineCount)==false)
		return false;
	return true;
}
bool	GUICmdChangeCount::Save(QIODevice *f)
{
	if(::Save(f,NewPhaseCount)==false)
		return false;
	if(::Save(f,NewLayerCount)==false)
		return false;
	if(::Save(f,NewLineCount)==false)
		return false;
	return true;
}

void	GUICmdChangeCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		GetLayersBase()->Reallocate(NewPhaseCount,GetPageNumb(),NewLayerCount);
		GetLayersBase()->ReallocXYPixels(GetDotPerLine(localPage),NewLineCount);
	}
}