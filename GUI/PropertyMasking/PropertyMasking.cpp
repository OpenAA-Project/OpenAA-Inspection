/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMasking\PropertyMasking.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyMaskingForm.h"
#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XPropertyMaskingPacket.h"
#include "PropertyMaskingFormResource.h"
#include "XMacroFunction.h"

static	bool	MacroCreateMask(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroExpandMask(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroReplaceInclusiveMask(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyMaskingForm";

//const	char	*LayersBase::GetLanguageSolutionFileName(void)
//{
//	return NULL;
//}
DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Masking");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdAddMaskingArea			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGenerateMaskInSameColor	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeMaskingAttr			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqMaskList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendMaskList				(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqSetButtonMode			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdPourOnMouseLDown			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdPickupArea				(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdExpandMask				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReplaceInclusiveMask		(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqLimitedLibMask			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckLimitedLibMask			(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdMaskingMakeBackGround		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdClearMakeBackGround		(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqBindedLimitedLibMask	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckBindedLimitedLibMask	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSetBindedLimitedLibMask	(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdReqMaskCount				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckMaskCount				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGenerateMaskOnSelectedItemsEdge	(Base,QString(sRoot),QString(sName));(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdGeneratePatternEdgeOnSelected		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReflectSelection			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqRemoveMask				(Base,QString(sRoot),QString(sName));

	(*Base)=new GUICmdSetItemSelection			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSelectBindedLimitedLibMask(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyMaskingForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyMasking.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Masking"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"CreateMask";
		Functions[ret].ArgName.append(/**/"X");
		Functions[ret].ArgName.append(/**/"Y");
		Functions[ret].ArgName.append(/**/"XSize");
		Functions[ret].ArgName.append(/**/"YSize");
		Functions[ret].Explain.append(/**/"Create rectangle mask");
		Functions[ret].DLL_ExcuteMacro	=MacroCreateMask;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ExpandMask";
		Functions[ret].ArgName.append(/**/"Expanded Pixel");
		Functions[ret].Explain.append(/**/"Expand pix size");
		Functions[ret].DLL_ExcuteMacro	=MacroExpandMask;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ReplaceInclusiveMask";
		Functions[ret].Explain.append(/**/"Replace Inclusive Mask");
		Functions[ret].DLL_ExcuteMacro	=MacroReplaceInclusiveMask;
		ret++;
	}
	return ret;
}

static	bool	MacroCreateMask(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyMaskingForm	*V=dynamic_cast<PropertyMaskingForm *>(Instance);
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
	V->CreateMask(Area);

	return true;
}

static	bool	MacroExpandMask(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyMaskingForm	*V=dynamic_cast<PropertyMaskingForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	ExpandPix=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}

	V->ExpandMask(ExpandPix);

	return true;
}

static	bool	MacroReplaceInclusiveMask(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyMaskingForm	*V=dynamic_cast<PropertyMaskingForm *>(Instance);
	if(V==NULL){
		return false;
	}

	V->ReplaceInclusiveMask();

	return true;
}