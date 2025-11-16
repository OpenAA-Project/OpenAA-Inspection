/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignment\PropertyAlignment.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyAlignment.h"
#include "PropertyAlignmentForm.h"
#include "XDisplayImage.h"
#include "PropertyAlignmentFormResource.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAlignmentForm";


static	bool	MacroCreateArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSelectArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreatePoint(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Alignment");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAlignmentAreaList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentAreaList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentPointList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentPointList	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentPutArea		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentPutPoint	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentModifyPoint	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentPutGroup	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentAreaInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentAreaInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqModifyAlignmentAreaInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetActiveAreas			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClickAreaButton			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClickPointButton		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdClickGroupButton		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAlignmentForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAlignment.png")));
}


DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Alignment"));
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
//	if(MaxBuffer>ret){
//		Functions[ret].FuncName	=/**/"SelectArea";
//		Functions[ret].ArgName.append(/**/"AreaCenterX");
//		Functions[ret].ArgName.append(/**/"AreaCenterY");
//		Functions[ret].Explain.append(/**/"Select area in position");
//		Functions[ret].DLL_ExcuteMacro	=MacroSelectArea;
//		ret++;
//	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreatePoint";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"XSize");
		Functions[ret].ArgName.append(/**/"YSize");
		Functions[ret].ArgName.append(/**/"MoveDot");
		Functions[ret].ArgName.append(/**/"Threshold");
		Functions[ret].ArgName.append(/**/"OutlineAlignment");
		Functions[ret].Explain.append(/**/"Create rectangle alignemnt point");
		Functions[ret].DLL_ExcuteMacro	=MacroCreatePoint;
		ret++;
	}
	return ret;
}

static	bool	MacroCreateArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentForm	*V=dynamic_cast<PropertyAlignmentForm *>(Instance);
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
	PropertyAlignmentForm	*V=dynamic_cast<PropertyAlignmentForm *>(Instance);
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
	//V->SelectAlignmentArea(CenterX,CenterY);

	return true;
}

static	bool	MacroCreatePoint(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyAlignmentForm	*V=dynamic_cast<PropertyAlignmentForm *>(Instance);
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
	int	Threshold=Args[5].toInt(&ok);
	if(ok==false){
		return false;
	}
	bool	OutlineAlignment=false;
	if(Args[5]==/**/"true" || Args[5]==/**/"TRUE"){
		OutlineAlignment=true;
	}
	FlexArea	Point;
	Point.SetRectangle(Left,Top,Left+XSize,Top+YSize);
	V->CreateAlignmentPoint(Point,MoveDot,Threshold,OutlineAlignment);

	return true;
}
