/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyGerberFast\PropertyGerberFast.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyGerberFastFormResource.h"
#include "PropertyGerberFast.h"
#include "PropertyGerberFastForm.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include"XPropertyGerberFastPacket.h"
#include"XGerberImagePacket.h"
#include "XMacroFunction.h"
#include "XGerberAperture.h"

static	bool	MacroLoadGerber(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGerberClear(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreateAutoMatchArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroStartAutoMatch(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroStartAutoMatchWithParam(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMoveOtherAlgorithm(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroBuildAlgorithm(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMoveItems(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroRotateItems(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroRotateItemsWithCenter(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroShearXItems(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroShearYItems(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroZoomItems(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroZoomItemsWithCenter(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroRoughMatch(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetGerberFileName(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMoveByMouse(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroRotateByMouse(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroZoomByMouse(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMirrorX(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMirrorY(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMakeImageToMaster(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroMakeBitImageToMaster(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLayerType(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroInitialAlgorithm(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroClearLibraryInMakeAlgorithmLine(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAppendLibraryInMakeAlgorithmLine(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreateClusterItem(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyGerberFast";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for GerberFast");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdGerberDrawMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberSelectAll			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberDraw					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberExtendWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberRotateWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberSlopeXWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberSlopeYWithCenter		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMsgGerberPaste				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberDrawWithPoints			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqApertureList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendApertureList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSetApertureList			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberExec3PointAlignment		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberExecAddAlignmentPoint	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqGerberCenterize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendGerberCenterize			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendImagePointXY				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberReqPointFromArea		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberSendPointFromArea		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGerberSendShowingLayerInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendGerberCompositeDefPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendLayerTypeList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddLayer					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeImage						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeBitImage					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAlgo						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSaveConstruct				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqLoadConstruct				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqGerberInfo					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckGerberInfo					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSelectItemsGerberFast			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdLoadGerber					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDeliverGerberToOtherPhases	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckLoadGerber					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdTransferInfo					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqGerberArea					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckGerberArea					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRegulateGerberArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdClearGerber					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMove							(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRotate						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdZoom							(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdShear							(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMirror						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdCenterize						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdCenterizeOnly					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMatchingRoughly				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeAutoMatch					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdClearAutoMatch				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdExecAutoMatch					(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqFlushMatrix				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckFlushMatrix				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeApertureInfo			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqApertureInfo				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckApertureInfo				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAlgoGenMap					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckAlgoGenMap					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetAlgoGenMap					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAllocateAutoMatching			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRemoveAutoMatchingPoint		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReflectOtherAlgorithm			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetAutoMatchButtons			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetDrawAttr					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeCurrentPhase			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdMatchingRoughlyReqShrinked	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMatchingRoughlyAckShrinked	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqMatchAutoLikeManual		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckMatchAutoLikeManual		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendMatchAutoLikeManual		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddMatchAutoLikeManualPoint	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddMatchingAlignmentPoint		(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdGenerateOutline				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdCreateEchingFactor			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdClearOutline					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDrawAllSelected				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSelectLine					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdRemoveLine					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSwapNext						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdDuplicateLine					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckDuplicateLine				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAddEmptyLayer					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckAddEmptyLayer				(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdMakeClusterItem				(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqOutsideOtherAlgorithm		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckOutsideOtherAlgorithm		(Base,QString(sRoot),QString(sName));
	
	(*Base)=new SlaveCommReqItemsOutside			(Base,sRoot,sName);
	(*Base)=new SlaveCommAckItemsOutside			(Base,sRoot,sName);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyGerberFastForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);

	Data[0].Type					=/**/"bool";
	Data[0].VariableNameWithRoute	=/**/"EnableMatching";
	Data[0].Pointer					=&((PropertyGerberFastForm *)Instance)->EnableMatching;
	Data[1].Type					=/**/"bool";
	Data[1].VariableNameWithRoute	=/**/"EnableAlgorithm";
	Data[1].Pointer					=&((PropertyGerberFastForm *)Instance)->EnableAlgorithm;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PropertyGerberFast.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"GerberFast"));
}


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"LoadGerber";
		Functions[ret].Explain.append(/**/"Push Load-Gerber button");
		Functions[ret].DLL_ExcuteMacro	=MacroLoadGerber;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateAutoMatchArea";
		Functions[ret].ArgName.append(/**/"Matching layer file name");
		Functions[ret].Explain.append(/**/"Create auto-matching area");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateAutoMatchArea;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"StartAutoMatch";
		Functions[ret].Explain.append(/**/"Start automatch");
		Functions[ret].DLL_ExcuteMacro	=MacroStartAutoMatch;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"StartAutoMatchWithParam";
		Functions[ret].Explain.append(/**/"Start automatch with parameter");
		Functions[ret].ArgName.append(/**/"pixel counts for rough search");
		Functions[ret].ArgName.append(/**/"pixel counts for palallel shift search");
		Functions[ret].ArgName.append(/**/"pixel counts for rotation search");
		Functions[ret].ArgName.append(/**/"pixel counts for zoom search");
		Functions[ret].ArgName.append(/**/"pixel counts for detail search");
		Functions[ret].ArgName.append(/**/"true/false Brighter in pattern");
		Functions[ret].DLL_ExcuteMacro	=MacroStartAutoMatchWithParam;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MoveOtherAlgorithm";
		Functions[ret].Explain.append(/**/"Move other algorithm");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveOtherAlgorithm;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetLayerType";
		Functions[ret].Explain.append(/**/"Set LayerType in gerber line");
		Functions[ret].ArgName.append(/**/"Line number");
		Functions[ret].ArgName.append(/**/"ID number of LayerType");
		Functions[ret].DLL_ExcuteMacro	=MacroSetLayerType;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"InitialAlgorithm";
		Functions[ret].Explain.append(/**/"Initial algorithm data");
		Functions[ret].DLL_ExcuteMacro	=MacroInitialAlgorithm;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearLibraryInMakeAlgorithmLine";
		Functions[ret].Explain.append(/**/"Clear library in Make-Algorithm line");
		Functions[ret].ArgName.append(/**/"Gerber line number");
		Functions[ret].ArgName.append(/**/"GenerationType(1:Gerber/2:Shiftable/6:Stable/5:Unstable)");
		Functions[ret].DLL_ExcuteMacro	=MacroClearLibraryInMakeAlgorithmLine;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AppendLibraryInMakeAlgorithmLine";
		Functions[ret].Explain.append(/**/"Append library in Make-Algorithm line");
		Functions[ret].ArgName.append(/**/"Gerber line number");
		Functions[ret].ArgName.append(/**/"GenerationType(1:Gerber/2:Shiftable/6:Stable/5:Unstable)");
		Functions[ret].ArgName.append(/**/"Algorithm DLLRoot");
		Functions[ret].ArgName.append(/**/"Algorithm DLLName");
		Functions[ret].ArgName.append(/**/"Algorithm Library ID");
		Functions[ret].DLL_ExcuteMacro	=MacroAppendLibraryInMakeAlgorithmLine;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"BuildAlgorithm";
		Functions[ret].Explain.append(/**/"Build algorithm data");
		Functions[ret].DLL_ExcuteMacro	=MacroBuildAlgorithm;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MoveItems";
		Functions[ret].Explain.append(/**/"Move items");
		Functions[ret].ArgName.append(/**/"Dx");
		Functions[ret].ArgName.append(/**/"Dy");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RotateItems";
		Functions[ret].Explain.append(/**/"Rotate items in Center");
		Functions[ret].ArgName.append(/**/"Angle(Degree)");
		Functions[ret].DLL_ExcuteMacro	=MacroRotateItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RotateItemsWithCenter";
		Functions[ret].Explain.append(/**/"Rotate items in Center");
		Functions[ret].ArgName.append(/**/"Angle(Degree)");
		Functions[ret].ArgName.append(/**/"Center X");
		Functions[ret].ArgName.append(/**/"Center Y");
		Functions[ret].DLL_ExcuteMacro	=MacroRotateItemsWithCenter;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShearXItems";
		Functions[ret].Explain.append(/**/"Shear-X items in Center");
		Functions[ret].ArgName.append(/**/"Angle(Degree)");
		Functions[ret].DLL_ExcuteMacro	=MacroShearXItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShearYItems";
		Functions[ret].Explain.append(/**/"Shear-Y items in Center");
		Functions[ret].ArgName.append(/**/"Angle(Degree)");
		Functions[ret].DLL_ExcuteMacro	=MacroShearYItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ZoomItems";
		Functions[ret].Explain.append(/**/"Zoom items in Center");
		Functions[ret].ArgName.append(/**/"ZoomRate X");
		Functions[ret].ArgName.append(/**/"ZoomRate Y");
		Functions[ret].DLL_ExcuteMacro	=MacroZoomItems;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ZoomItemsWithCenter";
		Functions[ret].Explain.append(/**/"Zoom items in any position");
		Functions[ret].ArgName.append(/**/"ZoomRate X");
		Functions[ret].ArgName.append(/**/"ZoomRate Y");
		Functions[ret].ArgName.append(/**/"Center X");
		Functions[ret].ArgName.append(/**/"Center Y");
		Functions[ret].DLL_ExcuteMacro	=MacroZoomItemsWithCenter;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RoughMatch";
		Functions[ret].Explain.append(/**/"Match roughly");
		Functions[ret].ArgName.append(/**/"Matching layer file name");
		Functions[ret].DLL_ExcuteMacro	=MacroRoughMatch;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearGerber";
		Functions[ret].Explain.append(/**/"ClearGerber");
		Functions[ret].DLL_ExcuteMacro	=MacroGerberClear;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetGerberFileName";
		Functions[ret].Explain.append(/**/"Set Gerber file in line");
		Functions[ret].ArgName.append(/**/"Gerber file name");
		Functions[ret].ArgName.append(/**/"Line number");
		Functions[ret].DLL_ExcuteMacro	=MacroSetGerberFileName;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MoveByMouse";
		Functions[ret].Explain.append(/**/"Move by mouse");
		Functions[ret].DLL_ExcuteMacro	=MacroMoveByMouse;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"RotateByMouse";
		Functions[ret].Explain.append(/**/"Rotate  by mouse in Center");
		Functions[ret].DLL_ExcuteMacro	=MacroRotateByMouse;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ZoomByMouse";
		Functions[ret].Explain.append(/**/"Zoom  by mouse in Center");
		Functions[ret].DLL_ExcuteMacro	=MacroZoomByMouse;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MirrorX";
		Functions[ret].Explain.append(/**/"MirrorX in center");
		Functions[ret].DLL_ExcuteMacro	=MacroMirrorX;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MirrorY";
		Functions[ret].Explain.append(/**/"MirrorY in center");
		Functions[ret].DLL_ExcuteMacro	=MacroMirrorY;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MakeImageToMaster";
		Functions[ret].Explain.append(/**/"Make Image to Master buffer");
		Functions[ret].ArgName.append(/**/"Layer Line number , example, 0,1,2");
		Functions[ret].ArgName.append(/**/"Composite Line number , example, 0,1,2");
		Functions[ret].DLL_ExcuteMacro	=MacroMakeImageToMaster;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"MakeBitImageToMaster";
		Functions[ret].Explain.append(/**/"Make BitImage to Master buffer");
		Functions[ret].ArgName.append(/**/"Layer Line number , example, 0,1,2");
		Functions[ret].ArgName.append(/**/"Composite Line number , example, 0,1,2");
		Functions[ret].DLL_ExcuteMacro	=MacroMakeBitImageToMaster;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateCluster";
		Functions[ret].Explain.append(/**/"Create item cluster");
		Functions[ret].ArgName.append(/**/"Line number");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateClusterItem;
		ret++;
	}
	return ret;
}

static	bool	MacroLoadGerber(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandLoadGerber();

	return true;
}
static	bool	MacroGerberClear(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandGerberClear();

	return true;
}
static	bool	MacroCreateAutoMatchArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<7){
		return false;
	}
	int	DotForRoughSearch	=Args[0].toInt();
	int	DotForMoveSearch	=Args[1].toInt();
	int	DotForRotationSearch=Args[2].toInt();
	int	DotForZoomSearch	=Args[3].toInt();
	int	DotForDetailSearch	=Args[4].toInt();
	bool	BrighterInPattern=(Args[5].toUpper()==/**/"TRUE")?true:false;
	QString	LayerFileName=Args[6];
	V->CommandCreateAutoMatchArea(DotForRoughSearch,DotForMoveSearch,DotForRotationSearch,DotForZoomSearch,DotForDetailSearch,BrighterInPattern
								, LayerFileName);

	return true;
}
static	bool	MacroStartAutoMatch(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandStartAutoMatch();

	return true;
}
static	bool	MacroStartAutoMatchWithParam(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<6){
		return false;
	}
	int	DotForRoughSearch	=Args[0].toInt();
	int	DotForMoveSearch	=Args[1].toInt();
	int	DotForRotationSearch=Args[2].toInt();
	int	DotForZoomSearch	=Args[3].toInt();
	int	DotForDetailSearch	=Args[4].toInt();
	bool	BrighterInPattern=(Args[5].toUpper()==/**/"TRUE")?true:false;

	V->CommandStartAutoMatch(DotForRoughSearch,DotForMoveSearch,DotForRotationSearch,DotForZoomSearch,DotForDetailSearch,BrighterInPattern);

	return true;
}
static	bool	MacroMoveOtherAlgorithm(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandMoveOtherAlgorithm();

	return true;
}
static	bool	MacroBuildAlgorithm(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandBuildAlgorithm();

	return true;
}
static	bool	MacroMoveItems(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	double	Dx=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	Dy=Args[1].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->CommandMoveItems(Dx,Dy);

	return true;
}
static	bool	MacroRotateItems(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	bool	ok;
	double	Angle=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->CommandRotateItems(Angle);

	return true;
}
static	bool	MacroRotateItemsWithCenter(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	bool	ok;
	double	Angle=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	Cx=Args[1].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	Cy=Args[2].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->CommandRotateItems(Angle,Cx,Cy);

	return true;
}
static	bool	MacroShearXItems(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	bool	ok;
	double	Angle=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->CommandShearXItems(Angle);

	return true;
}
static	bool	MacroShearYItems(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	bool	ok;
	double	Angle=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->CommandShearYItems(Angle);

	return true;
}
static	bool	MacroZoomItems(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	bool	ok;
	double	ZoomX=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	ZoomY=Args[1].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->CommandZoomItems(ZoomX,ZoomY);

	return true;
}
static	bool	MacroZoomItemsWithCenter(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	bool	ok;
	double	ZoomX=Args[0].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	ZoomY=Args[1].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	Cx=Args[2].toDouble(&ok);
	if(ok==false){
		return false;
	}
	double	Cy=Args[3].toDouble(&ok);
	if(ok==false){
		return false;
	}
	V->CommandZoomItems(ZoomX,ZoomY,Cx,Cy);

	return true;
}
static	bool	MacroRoughMatch(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString	LayerFileName=Args[0];
	V->CommandRoughMatch(LayerFileName);

	return true;
}

static	bool	MacroSetGerberFileName(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	QString	GerberFileName=Args[0];
	bool	ok=false;
	int	LineNo=Args[1].toInt(&ok);
	if(ok==false)
		return false;
	V->CommandSetGerberFile(GerberFileName,LineNo);

	return true;
}
static	bool	MacroMoveByMouse(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandMoveByMouse();

	return true;
}
static	bool	MacroRotateByMouse(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandRotateByMouse();

	return true;
}
static	bool	MacroZoomByMouse(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandZoomByMouse();

	return true;
}
static	bool	MacroMirrorX(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandMirrorX();

	return true;
}
static	bool	MacroMirrorY(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandMirrorY();

	return true;
}
static	bool	MacroMakeImageToMaster(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	QStringList	LayerNumberList=Args[0].split(',');
	QStringList	CompNumberList =Args[1].split(',');
	IntList	LayerLineNo;
	IntList	CompoLineNo;

	for(int i=0;i<LayerNumberList.count();i++){
		bool	ok;
		int	n=LayerNumberList[i].toInt(&ok);
		if(ok==true){
			LayerLineNo.Add(n);
		}
	}
	for(int i=0;i<CompNumberList.count();i++){
		bool	ok;
		int	n=CompNumberList[i].toInt(&ok);
		if(ok==true){
			CompoLineNo.Add(n);
		}
	}
	V->CommandMakeImageToMaster(LayerLineNo,CompoLineNo);

	return true;
}

static	bool	MacroMakeBitImageToMaster(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	QStringList	LayerNumberList=Args[0].split(',');
	QStringList	CompNumberList =Args[1].split(',');
	IntList	LayerLineNo;
	IntList	CompoLineNo;

	for(int i=0;i<LayerNumberList.count();i++){
		bool	ok;
		int	n=LayerNumberList[i].toInt(&ok);
		if(ok==true){
			LayerLineNo.Add(n);
		}
	}
	for(int i=0;i<CompNumberList.count();i++){
		bool	ok;
		int	n=CompNumberList[i].toInt(&ok);
		if(ok==true){
			CompoLineNo.Add(n);
		}
	}
	V->CommandMakeBitImageToMaster(LayerLineNo,CompoLineNo);

	return true;
}
static	bool	MacroSetLayerType(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok=false;
	int	GerberLineNumber=Args[0].toInt(&ok);
	if(ok==false)
		return false;	
	int	LayerType=Args[1].toInt(&ok);
	if(ok==false)
		return false;
	V->CommandSetLayerType(GerberLineNumber,LayerType);

	return true;
}

static	bool	MacroInitialAlgorithm(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->CommandInitialAlgorithm();

	return true;
}

static	bool	MacroClearLibraryInMakeAlgorithmLine(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok=false;
	int	GerberLineNumber=Args[0].toInt(&ok);
	if(ok==false)
		return false;	
	int	GenerationType=Args[1].toInt(&ok);
	if(ok==false)
		return false;	

	V->CommandClearLibraryInMakeAlgorithmLine(GerberLineNumber,GenerationType);

	return true;
}

static	bool	MacroAppendLibraryInMakeAlgorithmLine(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok=false;
	int	GerberLineNumber=Args[0].toInt(&ok);
	if(ok==false)
		return false;	
	int	GenerationType=Args[1].toInt(&ok);
	if(ok==false)
		return false;	
	QString	DLLRoot	=Args[2];
	QString	DLLName	=Args[3];
	int	LibID=Args[4].toInt(&ok);
	if(ok==false)
		return false;

	V->CommandAppendLibraryInMakeAlgorithmLine(GerberLineNumber,GenerationType ,DLLRoot,DLLName,LibID);

	return true;
}

static	bool	MacroCreateClusterItem(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyGerberFastForm	*V=dynamic_cast<PropertyGerberFastForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok=false;
	int	GerberLineNumber=Args[0].toInt(&ok);
	if(ok==false)
		return false;	

	V->CommandCreateCluster(GerberLineNumber);

	return true;
}

