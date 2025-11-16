#include "CameraChangeQuickPropertyResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\CameraChangeQuickProperty\CameraChangeQuickProperty.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "CameraChangeQuickPropertyForm.h"
#include <QIcon>
#include <QPixmap>

const	char	*sRoot=/**/"Camera";
const	char	*sName=/**/"ChangeQuickProperty";


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

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdCameraChangeQuickProperty	(Base,sRoot,sName);
	(*Base)=new GUICmdReqBrightness				(Base,sRoot,sName);
	(*Base)=new GUICmdAckBrightness				(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new CameraChangeQuickPropertyForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"Brighter,Faster,SideBrighter";
	Data[0].VariableNameWithRoute=/**/"CameraQuickPropertyStr";
	Data[0].Pointer				 =&((CameraChangeQuickPropertyForm *)Instance)->CameraQuickPropertyStr;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"TitleName";
	Data[1].Pointer				 =&((CameraChangeQuickPropertyForm *)Instance)->TitleName;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"LinkPanelInst";
	Data[2].Pointer				 =&((CameraChangeQuickPropertyForm *)Instance)->LinkPanelInst;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/CameraChangeQuickProperty.png")));
}
