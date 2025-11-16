/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDXFOperation\PropertyDXFOperation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyDXFOperationResource.h"
#include "PropertyDXFOperation.h"
#include "PropertyDXFOperationForm.h"
#include "XDisplayImage.h"
#include "XGUIDLL.h"
#include "XPropertyDXFOperationPacket.h"
#include "AllocationLibByColorDialog.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyDXFOperation";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Dent Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdLoadDXF			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMove				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRotate			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdZoom				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdShear				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMirror			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdCenterize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdCenterizeOnly		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqDXFArea		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckDXFArea		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqDXFLayerInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckDXFLayerInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetLineWidth		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDXFDrawMode		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSelectInColor		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqColorFromDXF	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckColorFromDXF	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAlgo			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAlgoFillArea	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAlgoByColor	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDelMaskByCAD		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdExecuteInitialMask(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDXFDraw			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSelectFileNo		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeEffectiveMask	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendEffectiveMask	(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqAllocationLibByColor	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckAllocationLibByColor	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetAllocationLibByColor	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetDXFWithSelfTransform	(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqDXFTransformInfo(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckDXFTransformInfo(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetDXFTransformInfo(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	

	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyDXFOperationForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyDXFOperation.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DXFOperation"));
}
