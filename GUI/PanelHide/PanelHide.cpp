/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelHide\PanelHide.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelHide.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"PanelHide";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Hide children");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdSendImagePartial	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PanelHide(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"HideMode";
	Data[0].Pointer				 =&((PanelHide *)Instance)->HideMode;
	return(1);
}
//==================================================================================================
PanelHide::PanelHide(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	HideMode=true;
	resize(100,100);
}

static	void	HideExecute(QObject *b ,bool mode)
{
	QWidget	*w=dynamic_cast<QWidget *>(b);
	if(w!=NULL){
		w->setVisible(mode);
	}
	const QObjectList	&Obj=b->children();
	for(int i=0;i<Obj.count();i++){
		QObject	*o=Obj[i];
		HideExecute(o ,mode);
	}
}

void	PanelHide::ReadyParam(void)
{
	if(GetEditMode()==false){
		HideExecute(this,!HideMode);
	}
}

void	PanelHide::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdShowPanel	*CmdShowPanelVar=dynamic_cast<CmdShowPanel *>(packet);
	if(CmdShowPanelVar!=NULL){
		HideExecute(this,CmdShowPanelVar->ModeShow);
		return;
	}
}