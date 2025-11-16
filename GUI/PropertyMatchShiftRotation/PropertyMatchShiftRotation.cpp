//#include "EditLibraryDialogResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMatchShiftRotation\PropertyMatchShiftRotation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyMatchShiftRotation.h"
#include "PropertyMatchShiftRotationForm.h"
#include "XPropertyMatchShiftRotationPacket.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyMatchShiftRotationForm";


static	bool	MacroCreateArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSelectArea(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroCreatePoint(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateAreaFromMask(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSelectModeType(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for MatchShiftRotation");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqMatchShiftRotationAreaList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendMatchShiftRotationAreaList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqMatchShiftRotationPutArea		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqModifyMatchShiftRotationAreaInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqMatchShiftRotationPointList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendMatchShiftRotationPointList		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqMatchShiftRotationSetMode		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqMatchShiftRotationItemPack		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckMatchShiftRotationItemPack		(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdSendAddManualMatchShiftRotation		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdUpdateManualMatchShiftRotation		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdDeleteManualMatchShiftRotation		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateMatchShiftRotations			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdDeleteArea							(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqMatchShiftItemImages				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendMatchShiftItemImages			(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyMatchShiftRotationForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyMatchShiftRotation.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MatchShiftRotation"));
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
		Functions[ret].ArgName.append(/**/"OutlineMatchShiftRotation");
		Functions[ret].Explain.append(/**/"Create rectangle alignemnt point");
		Functions[ret].DLL_ExcuteMacro	=MacroCreatePoint;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SelectModeType";
		Functions[ret].ArgName.append(/**/"Type  0:Area ,1:Item");
		Functions[ret].Explain.append(/**/"SelectModeType");
		Functions[ret].DLL_ExcuteMacro	=MacroSelectModeType;
		ret++;
	}
	return ret;
}

static	bool	MacroCreateArea(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyMatchShiftRotationForm	*V=dynamic_cast<PropertyMatchShiftRotationForm *>(Instance);
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
	PropertyMatchShiftRotationForm	*V=dynamic_cast<PropertyMatchShiftRotationForm *>(Instance);
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
	//V->SelectMatchShiftRotationArea(CenterX,CenterY);

	return true;
}

static	bool	MacroSelectModeType(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyMatchShiftRotationForm	*V=dynamic_cast<PropertyMatchShiftRotationForm *>(Instance);
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
	PropertyMatchShiftRotationForm	*V=dynamic_cast<PropertyMatchShiftRotationForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	ItemLibID=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}

	V->GenerateAreaFromMask(ItemLibID);

	return true;
}
static	bool	MacroCreatePoint(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyMatchShiftRotationForm	*V=dynamic_cast<PropertyMatchShiftRotationForm *>(Instance);
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
