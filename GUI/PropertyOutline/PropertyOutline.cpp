/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyOutline\PropertyOutline.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyOutlineResource.h"
#include "PropertyOutlineForm.h"
#include "XPropertyOutlinePacket.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XGUIPacketGeneral.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyOutlineForm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for outline Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdPickupTestList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdTestClear						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGenerateOutlines				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualOutline			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendModifySelectedOutline		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSelectedOutlineItemAttr	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSelectedOutlineItemAttr	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqOutlineInfoList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendOutlineInfoList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqOutlineFromList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckOutlineFromList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSetButtonMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRGBStockFromArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendRGBStockFromArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel		(Base, QString(sRoot), QString(sName));
	
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"OutlineInspection");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}
	return(new PropertyOutlineForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyOutline.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"OutlineInspection"));
}
