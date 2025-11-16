#include "EditStatisticBlockLibraryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyStatisticBlock\PropertyStatisticBlock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyStatisticBlock.h"
#include "PropertyStatisticBlockForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XGUIPacketGeneral.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyStatisticBlockForm";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Statistic Block Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	//new GUICmdPickupTestList					(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdGenerateStatisticBlocks			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualStatisticBlock		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendModifySelectedStatisticBlock(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqStatisticBlockInfoList		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendStatisticBlockInfoList		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqStatisticBlockFromList		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckStatisticBlockFromList		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdPickupTestList					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdTestClear						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSelectedStatisticBlockItemAttr	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSelectedStatisticBlockItemAttr	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel			(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"StatisticBlock");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}
	return(new PropertyStatisticBlockForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyStatisticBlock.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"StatisticBlock"));
}
