/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyWorld3D\PropertyWorld3D.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyWorld3D.h"
#include "PropertyWorld3DForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include <QIcon>
#include <QPixmap>
#include "XPropertyWorld3DPacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyWorld3D";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for World3D");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdLoadStepFile			(Base, sRoot, sName);
	//(*Base)=new GUICmdSendModifySelectedPalletize		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqSelectedPalletizeItemAttr	(Base, QString(sRoot), QString(sName));
	//(*Base)=new	GUICmdSendSelectedPalletizeItemAttr	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqPalletizeInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendPalletizeInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqPalletizeFromList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckPalletizeFromList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReleaseSelectImagePanel				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqItemListForPageContainer			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckItemListForPageContainer			(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdAddPalletizeOK					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAddPalletizeNG					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdRegistInFlowON						(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdRegistInFlowOFF						(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSetStatisticThreshold					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdClearFlowStack						(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdReqFlowData							(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckFlowData							(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendFlowData							(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAutoGenerate							(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyWorld3DForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyWorld3D.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"World3D"));
}
