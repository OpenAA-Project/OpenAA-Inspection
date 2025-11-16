/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyRasterInspection\PropertyRasterInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyRasterInspection.h"
#include "PropertyRasterInspectionForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include <QIcon>
#include <QPixmap>
#include "XPropertyRasterInspectionPacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyRasterInspection";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for RasterInspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualRasterInspection			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateRasterInspection				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqRasterInspectionInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new	GUICmdSendRasterInspectionInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqRasterInspectionInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendRasterInspectionInfoList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqRasterInspectionFromList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckRasterInspectionFromList			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSendAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReleaseSelectImagePanel				(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqItemListForPageContainer			(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckItemListForPageContainer			(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdAddRasterInspectionOK					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAddRasterInspectionNG					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdRegistInFlowON						(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdRegistInFlowOFF						(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdSetStatisticThreshold					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdClearFlowStack						(Base, QString(sRoot), QString(sName));
	//
	//(*Base)=new GUICmdReqFlowData							(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqReferencePDFData					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckReferencePDFData					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendReferencePDFData					(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyRasterInspectionForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyRasterInspection.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"RasterInspection"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"Raster"));
}
