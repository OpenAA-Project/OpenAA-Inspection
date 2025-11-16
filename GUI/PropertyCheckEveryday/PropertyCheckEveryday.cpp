/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyCheckEveryday\PropertyCheckEveryday.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyCheckEverydayFormResource.h"
#include "PropertyCheckEveryday.h"
#include "PropertyCheckEverydayForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include "XDisplaySimPanel.h"
#include "XCheckEverydayGUIPacket.h"
#include "XGUIPacketGeneral.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyCheckEveryday";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for CheckEveryday");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqAddManualLight	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAddManualFocus	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqInfo				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckInfo				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqModifyManualLight(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqModifyManualFocus(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"CheckEveryday");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}

	return(new PropertyCheckEverydayForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyCheckEveryday.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"CheckEveryday"));
}
