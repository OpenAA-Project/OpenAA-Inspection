/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyColorCorrector\PropertyColorCorrector.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyColorCorrector.h"
#include "PropertyColorCorrectorForm.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"
#include "XGUIDLL.h"
#include "XPropertyColorCorrectorPacket.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyColorCorrector";

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


	(*Base)=new GUICmdSendAddManualColorCorrector	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqGridList					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckGridList					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqColorCorrectorItemData		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckColorCorrectorItemData		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetColorCorrectorItemData		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdDeleteColorCorrectorItem		(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyColorCorrectorForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyColorCorrector.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ReplaceImage"));
}

