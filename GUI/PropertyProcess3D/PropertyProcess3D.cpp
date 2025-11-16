/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyProcess3D\PropertyProcess3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PropertyProcess3DResource.h"
#include "PropertyProcess3D.h"
#include "PropertyProcess3DForm.h"
#include "XDisplayImage.h"
#include "XGUIDLL.h"
#include "XPropertyProcess3DPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyProcess3D";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Process3D Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdReqAreaHistgramInMaster			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendAreaHistgramInMaster		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualProcess3D		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendModifySelectedProcess3D	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqSelectedProcess3DItemAttr	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendSelectedProcess3DItemAttr	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqProcess3DInfoList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendProcess3DInfoList			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqProcess3DFromList			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckProcess3DFromList			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqSetButtonMode				(Base,QString(sRoot),QString(sName));

	//(*Base)=new GUICmdChangeProcess3DsThreshold		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRemoveAllOriginal			(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyProcess3DForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyProcess3D.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Process3D"));
}
