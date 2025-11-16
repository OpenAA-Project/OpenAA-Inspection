#include "ButtonImageTransformerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonImageTransformer\ButtonImageTransformer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonImageTransformer.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"
#include "ImageTransformerDialog.h"
#include "XDataInLayer.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ImageTransformer";




DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to transform image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdUpsideDown		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLeftsideRight	(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonImageTransformer(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonImageTransformer *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonImageTransformer *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"NormalColor";
	Data[2].Pointer				 =&((ButtonImageTransformer *)Instance)->NormalColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"PushedColor";
	Data[3].Pointer				 =&((ButtonImageTransformer *)Instance)->PushedColor;	
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((ButtonImageTransformer *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonImageTransformer.png")));
}

static	bool	MacroTransformImage(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonImageTransformer	*V=dynamic_cast<ButtonImageTransformer *>(Instance);
	if(V==NULL){
		return false;
	}

	V->SlotClicked();
	return false;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ImageTransformer";
		Functions[ret].Explain.append(/**/"Transform image");
		Functions[ret].DLL_ExcuteMacro	=MacroTransformImage;
		ret++;
	}
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ButtonImageTransformer::ButtonImageTransformer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Msg=/**/"Transform image";

	CharColor	=Qt::white;
	NormalColor	=Qt::gray;
	PushedColor	=Qt::yellow;

	resize(80,25);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ButtonImageTransformer::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	//Button.setCheckable(false);
	ResizeAction();
}

void	ButtonImageTransformer::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	ButtonImageTransformer::ResizeAction()
{
	Button.resize(width(),height());
}

void	ButtonImageTransformer::SlotClicked ()
{
	ImageTransformerDialog	Dlg(GetLayersBase());
	int	Ret=Dlg.exec();
	if(Ret==1){
		for(IntClass *c=Dlg.SelectedPages.GetFirst();c!=NULL;c=c->GetNext()){
			int	page=c->GetValue();
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdUpsideDown	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.MasterImage=Dlg.MasterImage;
			RCmd.TargetImage=Dlg.TargetImage;

			RCmd.SendOnly(GlobalPage ,0);
		}
	}
	else if(Ret==2){
		for(IntClass *c=Dlg.SelectedPages.GetFirst();c!=NULL;c=c->GetNext()){
			int	page=c->GetValue();
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdLeftsideRight	RCmd(GetLayersBase() ,sRoot,sName,GlobalPage);
			RCmd.MasterImage=Dlg.MasterImage;
			RCmd.TargetImage=Dlg.TargetImage;

			RCmd.SendOnly(GlobalPage ,0);
		}
	}
	BroadcastShowInEdit();
}

//=====================================================================================
GUICmdUpsideDown::GUICmdUpsideDown(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MasterImage=true;
	TargetImage=true;
}
bool	GUICmdUpsideDown::Load(QIODevice *f)
{
	if(::Load(f,MasterImage)==false)
		return false;
	if(::Load(f,TargetImage)==false)
		return false;
	return true;
}

bool	GUICmdUpsideDown::Save(QIODevice *f)
{
	if(::Save(f,MasterImage)==false)
		return false;
	if(::Save(f,TargetImage)==false)
		return false;
	return true;
}

void	GUICmdUpsideDown::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
	for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
		DataInLayer	*L=Pg->GetLayerData(Layer);
		if(MasterImage==true)
			L->GetMasterBuff().TopsideBottom();
		if(TargetImage==true)
			L->GetTargetBuff().TopsideBottom();
	}
	SendAck(localPage);
}

//=====================================================================================
GUICmdLeftsideRight::GUICmdLeftsideRight(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	MasterImage=true;
	TargetImage=true;
}

bool	GUICmdLeftsideRight::Load(QIODevice *f)
{
	if(::Load(f,MasterImage)==false)
		return false;
	if(::Load(f,TargetImage)==false)
		return false;
	return true;
}

bool	GUICmdLeftsideRight::Save(QIODevice *f)
{
	if(::Save(f,MasterImage)==false)
		return false;
	if(::Save(f,TargetImage)==false)
		return false;
	return true;
}

void	GUICmdLeftsideRight::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Pg=GetLayersBase()->GetPageData(localPage);
	for(int Layer=0;Layer<GetLayerNumb(localPage);Layer++){
		DataInLayer	*L=Pg->GetLayerData(Layer);
		if(MasterImage==true)
			L->GetMasterBuff().LeftsideRight();
		if(TargetImage==true)
			L->GetTargetBuff().LeftsideRight();
	}
	SendAck(localPage);
}


