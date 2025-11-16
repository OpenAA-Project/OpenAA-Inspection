/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\HookOverlapImage\HookOverlapImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "HookOverlapImageForm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"HookOverlapImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Hook to overlap image");
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
	return(new HookOverlapImageForm(Base,parent));
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
	Data[0].Pointer				 =&((HookOverlapImageForm *)Instance)->HookTargetListInst;
	Data[1].Type				 =/**/"MasterImage,TargetImage,BitImage,CameraRawImage";
	Data[1].VariableNameWithRoute=/**/"ImageType";
	Data[1].Pointer				 =&((HookOverlapImageForm *)Instance)->ImageType;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowNGMarkInTarget";
	Data[2].Pointer				 =&((HookOverlapImageForm *)Instance)->ShowNGMarkInTarget;
	Data[3].Type				 =/**/"RightFaint,LeftFaint";
	Data[3].VariableNameWithRoute=/**/"SliderDirection";
	Data[3].Pointer				 =&((HookOverlapImageForm *)Instance)->SliderDirection;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/HookOverlapImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}