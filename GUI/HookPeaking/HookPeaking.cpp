/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HookPeaking\HookPeaking.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HookPeakingForm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"HookPeaking";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Hook to peak image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdMakePeakData(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new HookPeakingForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);

	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"HookTargetListInst";
	Data[0].Pointer				 =&((HookPeakingForm *)Instance)->HookTargetListInst;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ModeShowModeButton";
	Data[1].Pointer				 =&((HookPeakingForm *)Instance)->ModeShowModeButton;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ModeShowColorButton";
	Data[2].Pointer				 =&((HookPeakingForm *)Instance)->ModeShowColorButton;
	Data[3].Type				 =/**/"Target,Master,CamTarget";
	Data[3].VariableNameWithRoute=/**/"MemoryType";
	Data[3].Pointer				 =&((HookPeakingForm *)Instance)->MemoryType;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"InitialValue";
	Data[4].Pointer				 =&((HookPeakingForm *)Instance)->InitialValue;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/HookPeaking.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}