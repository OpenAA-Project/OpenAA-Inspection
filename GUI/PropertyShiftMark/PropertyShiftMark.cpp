/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyShiftMark\PropertyShiftMark.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyShiftMarkResource.h"
#include "PropertyShiftMark.h"
#include "PropertyShiftMarkForm.h"
#include "XDisplayImage.h"
#include "XGUIDLL.h"
#include "XPropertyShiftMarkPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyShiftMark";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for ShiftMark Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualShiftMark(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddEdgeMark		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqItemList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendItemList			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqItemThreshold		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckItemThreshold		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetItemThreshold		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeDirection		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRotationPoint		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckRotationPoint		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyShiftMarkForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyShiftMark.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ShiftMark"));
}
