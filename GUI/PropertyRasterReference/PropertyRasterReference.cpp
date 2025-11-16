/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyRasterReference\PropertyRasterReference.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PropertyRasterReferenceResource.h"
#include "PropertyRasterReference.h"
#include "PropertyRasterReferenceForm.h"
#include "XGUIRasterPacket.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyRasterReference";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for RasterReference");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdMakeRasterReferenceItem	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRasterReference		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckRasterReference		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAutoRasterReference	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSaveDefaultColorProfile	(Base,QString(sRoot),QString(sName));

	//(*Base)=new GUICmdMsgRasterSelectAll			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterDraw					(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdMsgRasterExtendWithCenter		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdMsgRasterRotateWithCenter		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdMsgRasterSlopeXWithCenter		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdMsgRasterSlopeYWithCenter		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdMsgRasterPaste				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterDrawArea				(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdRasterExec3PointAlignment		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterExecAddAlignmentPoint	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRasterCenterize			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendRasterCenterize			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSendImagePointXY				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterSetAlignmentPoint		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterSendShowingLayerInfo	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdMakeImage						(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdMakeBitImage					(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAlgoPipeOut					(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqSaveConstruct				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqLoadConstruct				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRasterInfo					(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRasterInfo					(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSelectItemsRaster				(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdLoadRaster				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdDeliverRasterToOtherPhases(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckLoadRaster				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdTransferInfo				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRasterArea				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRasterArea				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdClearRaster				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterMove				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterRotate				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterZoom				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterShear				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterMirror				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterCenterize			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterCenterizeOnly		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSetDrawAttr				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdChangeCurrentPhase		(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdDrawAllSelected			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSelectLine				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRemoveLine				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSwapNext					(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdDuplicateLine				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckDuplicateLine			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterPickupByColor		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdRasterPickupByColorArea	(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdReqRasterElements			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRasterElements			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRasterElementData		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRasterElementData		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSetRasterElementData		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRefreshLines			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRefreshLines			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUIRasterCmdDelMaskByCAD		(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdReqPickRasterColor		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckPickRasterColor		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSetPickupArea				(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdReqPickRasterColorProfile	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqRasterColorProfiles	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRasterColorProfiles	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSetRasterColorProfiles	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdConvertColorProfiles		(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdAddMaskArea				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdDelMaskArea				(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqEnumMaskArea			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckEnumMaskArea			(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSetPDFWithSelfTransform	(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdReqRasterTransformInfo	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRasterTransformInfo	(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdSetRasterTransformInfo	(Base,QString(sRoot),QString(sName));
	//
	//(*Base)=new GUICmdReqRasterProfileValue		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdAckRasterProfileValue		(Base,QString(sRoot),QString(sName));
	//(*Base)=new GUICmdReqMakeProfileByImage		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyRasterReferenceForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyRasterReference.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Raster"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

//	if(MaxBuffer>ret){
//		Functions[ret].FuncName	=/**/"SelectArea";
//		Functions[ret].ArgName.append(/**/"AreaCenterX");
//		Functions[ret].ArgName.append(/**/"AreaCenterY");
//		Functions[ret].Explain.append(/**/"Select area in position");
//		Functions[ret].DLL_ExcuteMacro	=MacroSelectArea;
//		ret++;
//	}

	return ret;
}


