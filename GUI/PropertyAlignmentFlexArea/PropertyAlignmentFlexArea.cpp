#include "EditLibraryDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentFlexArea\PropertyAlignmentFlexArea.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyAlignmentFlexArea.h"
#include "PropertyAlignmentFlexAreaForm.h"
#include "PropertyAlignmentFlexAreaPacket.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAlignmentFlexAreaForm";


static	bool	MacroCreateArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSelectArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreatePoint(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateAreaFromMask(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSelectModeType(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreateAreaInMaskingArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateAlignmentFlexArea(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for AlignmentFlexArea");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqAreaHistgramInMaster			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentFlexAreaAreaList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentFlexAreaAreaList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentFlexAreaPutArea		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqModifyAlignmentFlexAreaAreaInfo(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentFlexAreaPointList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentFlexAreaPointList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentFlexAreaSetMode		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentFlexAreaItemPack		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentFlexAreaItemPack		(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdSendAddManualAlignmentFlexArea	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdPickupTestList					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateAlignmentFlexAreas		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdTestClear							(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdDeleteArea						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqWholeMatchList					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendWholeMatchList				(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdGenerateBaseMatch					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdExecBaseMatch						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqBaseMatchList					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckBaseMatchList					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdCreateAreaInMaskingArea			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentPointList				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentPointList				(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAlignmentFlexAreaForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAlignmentFlexArea.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentFlexArea"));
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
		Functions[ret].FuncName	=/**/"GenerateArea";
		Functions[ret].ArgName.append(/**/"Priority");
		Functions[ret].ArgName.append(/**/"ItemLib");
		Functions[ret].Explain.append(/**/"Generate Area from Mask");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateAreaFromMask;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreatePoint";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"XSize");
		Functions[ret].ArgName.append(/**/"YSize");
		Functions[ret].ArgName.append(/**/"MoveDot");
		Functions[ret].ArgName.append(/**/"Threshold");
		Functions[ret].ArgName.append(/**/"OutlineAlignmentFlexArea");
		Functions[ret].Explain.append(/**/"Create rectangle alignemnt point");
		Functions[ret].DLL_ExcuteMacro	=MacroCreatePoint;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectModeType";
		Functions[ret].ArgName.append(/**/"Type  0:Area ,1:Item ,2:WholeMatch");
		Functions[ret].Explain.append(/**/"SelectModeType");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectModeType;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateAreaInMaskingArea";
		Functions[ret].ArgName.append(/**/"Priority(1:High,2:Middle,3:Low,4:Global");
		Functions[ret].Explain.append(/**/"Creare rectangle area");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateAreaInMaskingArea;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ClearLibList";
		Functions[ret].Explain.append(/**/"Clear all LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroClearLibList;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetLib";
		Functions[ret].ArgName.append(/**/"LibID");
		Functions[ret].Explain.append(/**/"Set LibID in current list");
		Functions[ret].DLL_ExcuteMacro	=MacroSetLib;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate DotColorMatchings");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateAlignmentFlexArea;
		ret++;
	}

	return ret;
}
static	bool	MacroCreateAreaInMaskingArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	Priority=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->CreateAreaInMaskingArea(Priority);

	return true;
}

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearLibList();

	return true;
}

static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	LibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SetLib(LibID);

	return true;
}

static	bool	MacroGenerateAlignmentFlexArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateAlignmentFlexArea();

	return true;
}
static	bool	MacroCreateArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
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
	//V->CreateAlignmentArea(Area);

	return true;
}

static	bool	MacroSelectArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
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
	//V->SelectAlignmentFlexAreaArea(CenterX,CenterY);

	return true;
}

static	bool	MacroSelectModeType(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	ModeType=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SelectModeType(ModeType);

	return true;
}
static	bool	MacroGenerateAreaFromMask(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
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
	int	ItemLibID=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}

	V->GenerateAreaFromMask(Priority,ItemLibID);

	return true;
}
static	bool	MacroCreatePoint(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentFlexAreaForm	*V=dynamic_cast<PropertyAlignmentFlexAreaForm *>(Instance);
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
	int	MoveDot=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	FlexArea	Point;
	Point.SetRectangle(Left,Top,Left+XSize,Top+YSize);
	//V->CreateAlignmentPoint(Point,MoveDot);

	return true;
}
