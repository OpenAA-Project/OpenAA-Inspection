/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentLarge\PropertyAlignmentLarge.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "AlignmentLargeFormResource.h"
#include "PropertyAlignmentLarge.h"
#include "PropertyAlignmentLargeForm.h"
#include "PropertyAlignmentLargePacket.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAlignmentLargeForm";


static	bool	MacroCreateArea				(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSelectArea				(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreatePoint			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroClearAllAreas			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroClearAllPoints			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroClearAllPointsByPriority(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreateAreaInMask		(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAutoCreatePoint		(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroAutoCreatePointWithLib	(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetAreaMode			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetPointMode			(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroDeleteAreaExceptGlobal	(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroDeleteItemsExceptGlobal(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for AlignmentLarge");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAlignmentLargeAreaList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargeAreaList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargePointList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentLargePointList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargePutArea		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargePutPoint		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargeModifyPoint	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargeRemovePoint	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargeMakeGroup	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargeRemoveGroup	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentLargeAreaInfo		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentLargeAreaInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqModifyAlignmentLargeAreaInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetActiveAreas			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClickAreaButton			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClickPointButton			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClickGroupButton			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdClearAllAreas				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClearAllPoints			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdCreateAreaInMask			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAutoCreatePoint			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqHeadAlignment			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckHeadAlignment			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetHeadAlignment			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetAlignmentData			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdDeleteAreaExceptGlobal	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdDeleteItemsExceptGlobal	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqDelAlignmentArea		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAlignmentLargeForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAlignmentLarge.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentLarge"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateArea";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"XSize");
		Functions[ret].ArgName.append(/**/"YSize");
		Functions[ret].Explain.append(/**/"Creare rectangle area");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateArea;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearAllAreas";
		Functions[ret].Explain.append(/**/"Clear all areas");
		Functions[ret].DLL_ExcuteMacro	=MacroClearAllAreas;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearAllPoints";
		Functions[ret].Explain.append(/**/"Clear all points");
		Functions[ret].DLL_ExcuteMacro	=MacroClearAllPoints;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearAllPointsByPriority";
		Functions[ret].ArgName.append(/**/"Priority");
		Functions[ret].Explain.append(/**/"Clear all points");
		Functions[ret].DLL_ExcuteMacro	=MacroClearAllPointsByPriority;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateAreaInMask";
		Functions[ret].ArgName.append(/**/"Priority");
		Functions[ret].ArgName.append(/**/"Erosion");
		Functions[ret].Explain.append(/**/"Creare area in mask");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateAreaInMask;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AutoCreatePoint";
		Functions[ret].ArgName.append(/**/"Size");
		Functions[ret].ArgName.append(/**/"SearchAreaDot");
		Functions[ret].ArgName.append(/**/"SearchAreaDotY");
		Functions[ret].ArgName.append(/**/"SearchAreaDot2");
		Functions[ret].ArgName.append(/**/"SearchAreaDot2Y");
		Functions[ret].ArgName.append(/**/"GeneratedLayerNo");
		Functions[ret].ArgName.append(/**/"Area Priority");
		Functions[ret].ArgName.append(/**/"GeneratePartialAlignment(true/false)");
		Functions[ret].Explain.append(/**/"Automatic create points");
		Functions[ret].DLL_ExcuteMacro	=MacroAutoCreatePoint;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AutoCreatePointWithLib";
		Functions[ret].ArgName.append(/**/"Size");
		Functions[ret].ArgName.append(/**/"SearchAreaDot");
		Functions[ret].ArgName.append(/**/"SearchAreaDotY");
		Functions[ret].ArgName.append(/**/"GeneratedLayerNo");
		Functions[ret].ArgName.append(/**/"Area Priority");
		Functions[ret].ArgName.append(/**/"GeneratePartialAlignment(true/false)");
		Functions[ret].ArgName.append(/**/"limited-LibType");
		Functions[ret].ArgName.append(/**/"limited-LibID");
		Functions[ret].ArgName.append(/**/"GeneratePartialAlignment(true/false)");
		Functions[ret].Explain.append(/**/"Automatic create points with limited-lib");
		Functions[ret].DLL_ExcuteMacro	=MacroAutoCreatePointWithLib;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreatePoint";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"XSize");
		Functions[ret].ArgName.append(/**/"YSize");
		Functions[ret].ArgName.append(/**/"MoveDot");
		Functions[ret].ArgName.append(/**/"MoveDot2");
		Functions[ret].ArgName.append(/**/"Threshold");
		Functions[ret].ArgName.append(/**/"OutlineAlignmentLarge");
		Functions[ret].Explain.append(/**/"Create rectangle alignemnt point");
		Functions[ret].DLL_ExcuteMacro	=MacroCreatePoint;
		ret++;
	}

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetAreaMode";
		Functions[ret].Explain.append(/**/"Set area mode to draw");
		Functions[ret].DLL_ExcuteMacro	=MacroSetAreaMode;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetPointMode";
		Functions[ret].Explain.append(/**/"Set point mode to draw");
		Functions[ret].DLL_ExcuteMacro	=MacroSetPointMode;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DeleteAreaExceptGlobal";
		Functions[ret].Explain.append(/**/"Delete all areas except for global");
		Functions[ret].DLL_ExcuteMacro	=MacroDeleteAreaExceptGlobal;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"DeleteItemsExceptGlobal";
		Functions[ret].Explain.append(/**/"Delete all areas except for global");
		Functions[ret].DLL_ExcuteMacro	=MacroDeleteItemsExceptGlobal;
		ret++;
	}	
	return ret;
}


static	bool	MacroClearAllAreas(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ClearAllAreas();

	return true;
}

static	bool	MacroClearAllPoints(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ClearAllPoints();

	return true;
}

static	bool	MacroClearAllPointsByPriority(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	Priority=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ClearAllPoints(Priority);

	return true;
}

static	bool	MacroCreateAreaInMask(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	Priority=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Erosion=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}

	V->CreateAreaInMask(Priority,Erosion);

	return true;
}

static	bool	MacroAutoCreatePoint(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<9){
		return false;
	}
	bool	ok;
	int	PointSize=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	SearchAreaDotX=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	SearchAreaDotY=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	SearchAreaDot2X=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	SearchAreaDot2Y=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Layer=Args[5].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	AreaPriority=Args[6].toInt(&ok);
	if(ok==false){
		return false;
	}
	bool	GeneratePartialAlignment=false;
	if(Args[7].toLower()==QString(/**/"true")){
		GeneratePartialAlignment=true;
	}
	else
	if(Args[7].toLower()==QString(/**/"false")){
		GeneratePartialAlignment=false;
	}
	else{
		return false;
	}
	bool	AlignmntJudgeWithBrDif=false;
	if(Args[8].toLower()==QString(/**/"true")){
		AlignmntJudgeWithBrDif=true;
	}
	else
	if(Args[8].toLower()==QString(/**/"false")){
		AlignmntJudgeWithBrDif=false;
	}
	else{
		return false;
	}

	V->AutoCreatePoint(Layer,PointSize
						,SearchAreaDotX	,SearchAreaDotY
						,SearchAreaDot2X,SearchAreaDot2Y
						,AreaPriority
						,GeneratePartialAlignment
						,AlignmntJudgeWithBrDif);

	return true;
}

static	bool	MacroAutoCreatePointWithLib	(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<9){
		return false;
	}
	bool	ok;
	int	PointSize=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	SearchAreaDotX=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	SearchAreaDotY=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Layer=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	AreaPriority=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	bool	GeneratePartialAlignment=false;
	if(Args[5].toLower()==QString(/**/"true")){
		GeneratePartialAlignment=true;
	}
	else
	if(Args[5].toLower()==QString(/**/"false")){
		GeneratePartialAlignment=false;
	}
	else{
		return false;
	}

	int	LimitedLibType=Args[6].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	LimitedLibID=Args[7].toInt(&ok);
	if(ok==false){
		return false;
	}
	bool	AlignmntJudgeWithBrDif=false;
	if(Args[8].toLower()==QString(/**/"true")){
		AlignmntJudgeWithBrDif=true;
	}
	else
	if(Args[8].toLower()==QString(/**/"false")){
		AlignmntJudgeWithBrDif=false;
	}
	else{
		return false;
	}
	V->AutoCreatePoint(Layer,PointSize
						,SearchAreaDotX,SearchAreaDotY
						,SearchAreaDotX,SearchAreaDotY
						,AreaPriority
						,GeneratePartialAlignment
						,AlignmntJudgeWithBrDif
						,LimitedLibType,LimitedLibID);

	return true;
}



static	bool	MacroCreateArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<4){
		return false;
	}
	bool	ok;
	int	Left=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Top	=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	XSize=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	YSize=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Area;
	Area.SetRectangle(Left,Top,Left+XSize,Top+YSize);
	V->CreateAlignmentArea(Area);

	return true;
}

static	bool	MacroSelectArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	CenterX=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	CenterY=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	//V->SelectAlignmentLargeArea(CenterX,CenterY);

	return true;
}

static	bool	MacroCreatePoint(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<5){
		return false;
	}
	bool	ok;
	int	Left=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Top	=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	XSize=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	YSize=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	MoveDot=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	MoveDot2=Args[5].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Point;
	Point.SetRectangle(Left,Top,Left+XSize,Top+YSize);
	V->CreateAlignmentPoint(Point,MoveDot,MoveDot,MoveDot2,MoveDot2,0);

	return true;
}
static	bool	MacroSetAreaMode	(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SetAreaMode();

	return true;
}
static	bool	MacroSetPointMode	(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->SetPointMode();

	return true;
}

static	bool	MacroDeleteAreaExceptGlobal	(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->DeleteAreaExceptGlobal();

	return true;
}

static	bool	MacroDeleteItemsExceptGlobal	(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentLargeForm	*V=dynamic_cast<PropertyAlignmentLargeForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->DeleteItemsExceptGlobal();

	return true;
}