/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyReplaceImage\PropertyReplaceImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyReplaceImage.h"
#include "PropertyReplaceImageForm.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"
#include "XGUIDLL.h"
#include "XPropertyReplaceImagePacket.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyReplaceImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for RepeatControl");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdSendAddManualRepeatControl	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendModifyRepeatControl		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqRepeatControlInfoList		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckRepeatControlInfoList		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdCreateWholeRepeatControl		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyReplaceImageForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PropertyReplaceImage.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ReplaceImage"));
}

