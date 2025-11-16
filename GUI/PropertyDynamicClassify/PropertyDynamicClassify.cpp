#include "EditDynamicClassifyLibraryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDynamicClassify\PropertyDynamicClassify.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyDynamicClassify.h"
#include "XDisplayImage.h"
//#include "PropertyDynamicClassifyFormResource.h"
#include "XDisplayImagePacket.h"
#include "XDynamicClassifyPacket.h"
#include "PropertyDynamicClassifyForm.h"
#include "XGUIPacketGeneral.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyDynamicClassifyForm";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for DynamicClassify");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdSendAddManualDynamicClassify		(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendModifySelectedDynamicClassify	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqSelectedDynamicClassifyItemAttr	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendSelectedDynamicClassifyItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdPickupTestList						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateDynamicClassifys				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdTestClear								(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqRGBStockFromArea					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendRGBStockFromArea					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"DynamicClassify");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}

	return(new PropertyDynamicClassifyForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyDynamicClassify.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DynamicClassify"));
}
