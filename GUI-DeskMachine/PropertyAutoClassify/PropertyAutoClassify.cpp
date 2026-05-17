/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-Desktop\PropertyAutoClassify\PropertyAutoClassify.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAutoClassify.h"
#include "PropertyAutoClassifyForm.h"
#include "XDisplayImage.h"
//#include "PropertyBlockFormResource.h"
#include "XDisplayImagePacket.h"



char	*sRoot=/**/"Button";
char	*sName=/**/"PropertyAutoClassify";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for AutoClassify");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	/*
	(*Base)=new GUICmdSendAddManualBlock			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendModifySelectedBlock		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSelectedBlockItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new	GUICmdSendSelectedBlockItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqBlockInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendBlockInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqBlockFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckBlockFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdPickupTestList				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateBlocks				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdTestClear					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSetButtonMode			(Base, QString(sRoot), QString(sName));
	*/

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	//AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"AutoClassify");
	/*
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}
	*/

	return(new PropertyAutoClassifyForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAutoClassify.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoClassify"));
}
