/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyHoleWallInspection\PropertyHoleWallInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyHoleWallInspection.h"
#include "PropertyHoleWallInspectionForm.h"
#include "XDisplayImage.h"
#include "XGUIDLL.h"
#include "XPropertyHoleWallPacket.h"
#include "XGUIPacketGeneral.h"


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyHoleWall";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for HoleWall Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdPickupTestList					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdTestClear						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGenerateHoleWalls				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualHoleWall			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendModifySelectedHoleWall		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSelectedHoleWallItemAttr		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSelectedHoleWallItemAttr	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqHoleWallInfoList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendHoleWallInfoList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqHoleWallFromList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckHoleWallFromList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSetButtonMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel		(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdChangeHoleWallsThreshold		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRemoveAllOriginal			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeBitBuff						(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyHoleWallInspectionForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyHoleWallInspection.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"HoleWall"));
}
