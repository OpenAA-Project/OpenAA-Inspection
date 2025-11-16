#include "ChooseItemTypeFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyImageChecker\ImageCheckerPropertyForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyImageChecker.h"
#include "ImageCheckerPropertyForm.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyImageChecker";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for ImageChecker");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new 	GUICmdAddManual		(Base,QString(sRoot),QString(sName));
	(*Base)=new 	GUICmdSetRegData	(Base,QString(sRoot),QString(sName));
	(*Base)=new 	GUICmdReqRegData	(Base,QString(sRoot),QString(sName));
	(*Base)=new 	GUICmdSendRegData	(Base,QString(sRoot),QString(sName));
	(*Base)=new 	GUICmdReqValue		(Base,QString(sRoot),QString(sName));
	(*Base)=new 	GUICmdAckValue		(Base,QString(sRoot),QString(sName));
	(*Base)=new		GUICmdChangeDrawMode(Base,QString(sRoot),QString(sName));

	//new GUICmdAddDynamicMaskingPIArea	(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ImageCheckerPropertyForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ModeLightWhole";
	Data[0].Pointer				 =&((ImageCheckerPropertyForm *)Instance)->ModeLightWhole;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ModeParamEntry";
	Data[1].Pointer				 =&((ImageCheckerPropertyForm *)Instance)->ModeParamEntry;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ModeCamZ";
	Data[2].Pointer				 =&((ImageCheckerPropertyForm *)Instance)->ModeCamZ;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ModeResolution";
	Data[3].Pointer				 =&((ImageCheckerPropertyForm *)Instance)->ModeResolution;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ModeSlide";
	Data[4].Pointer				 =&((ImageCheckerPropertyForm *)Instance)->ModeSlide;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ModeIncline";
	Data[5].Pointer				 =&((ImageCheckerPropertyForm *)Instance)->ModeIncline;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PropertyImageChecker.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ImageChecker"));
}
