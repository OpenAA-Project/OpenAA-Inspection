#include "ChangeCameraSettingInvisibleResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ChangeCameraSettingInvisible\ChangeCameraSettingInvisible.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ChangeCameraSettingInvisible.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XExecuteInspectBase.h"
#include "XEntryPoint.h"

static	const	char	*sRoot=/**/"Camera";
static	const	char	*sName=/**/"ChangeSettingInvisible";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Change Camera-Setting under blind");
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
	return(new ChangeCameraSettingInvisible(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);
	Data[0].Type				 =/**/"FileName";
	Data[0].VariableNameWithRoute=/**/"CameraSettingFileName";
	Data[0].Pointer				 =&((ChangeCameraSettingInvisible *)Instance)->CameraSettingFileName;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ChangeCameraSettingInvisible.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ChangeCameraSettingInvisible::ChangeCameraSettingInvisible(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Initialized=false;
}

ChangeCameraSettingInvisible::~ChangeCameraSettingInvisible(void)
{
}

void	ChangeCameraSettingInvisible::BuildForShow(void)
{
	if(Initialized==false){
		if(GetLayersBase()!=NULL && GetLayersBase()->GetEntryPoint()!=NULL){
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->LoadCameraSetting(CameraSettingFileName);
				Initialized=true;
			}
		}
	}
}