/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationCameraChangeQuickProperty\IntegrationCameraChangeQuickProperty.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationCameraChangeQuickPropertyResource.h"
#include "IntegrationCameraChangeQuickProperty.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "IntegrationCameraChangeQuickPropertyForm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"CameraChangeQuickProperty";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Change camera property quickly");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdCameraChangeQuickProperty	(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationCameraChangeQuickPropertyForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"MachineCode";
	Data[0].Pointer				 =&((IntegrationCameraChangeQuickPropertyForm *)Instance)->MachineCode;
	Data[1].Type				 =/**/"Brighter,Faster,SideBrighter";
	Data[1].VariableNameWithRoute=/**/"CameraQuickPropertyStr";
	Data[1].Pointer				 =&((IntegrationCameraChangeQuickPropertyForm *)Instance)->CameraQuickPropertyStr;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationCameraChangeQuickProperty.png")));
}