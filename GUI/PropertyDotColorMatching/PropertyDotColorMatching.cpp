//#include "CreateManualDotColorMatchingFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyDotColorMatching\PropertyDotColorMatching.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyDotColorMatchingResource.h"
#include "PropertyDotColorMatching.h"
#include "PropertyDotColorMatchingForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include "XPropertyDotColorMatchingPacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateDotColorMatchings(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroShowEditLibrary(GUIFormBase *Instance ,QStringList &Args);

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyDotColorMatching";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for DotColorMatching Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualDotColorMatching			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendModifySelectedDotColorMatching		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSelectedDotColorMatchingItemAttr		(Base, QString(sRoot), QString(sName));
	(*Base)=new	GUICmdSendSelectedDotColorMatchingItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqDotColorMatchingInfoList				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendDotColorMatchingInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqDotColorMatchingFromList				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckDotColorMatchingFromList				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdPickupTestList							(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateDotColorMatchings				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdTestClear								(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel					(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqSetButtonMode						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqItemListForPageContainer				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckItemListForPageContainer				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqDSimPanelImage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckDSimPanelImage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqBlockListInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckBlockListInfo	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetItemsByLibID	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqItemsByLibID	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckItemsByLibID	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetSpecialData	(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdAddDotColorMatching			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdDeleteDotColorMatchingByName	(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"DotColorMatching");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}

	return(new PropertyDotColorMatchingForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyDotColorMatching.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

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
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateDotColorMatchings;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShowEditLibrary";
		Functions[ret].Explain.append(/**/"open edit-library dialog");
		Functions[ret].DLL_ExcuteMacro	=MacroShowEditLibrary;
		ret++;
	}
	return ret;
}


static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyDotColorMatchingForm	*V=dynamic_cast<PropertyDotColorMatchingForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearLibList();

	return true;
}

static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyDotColorMatchingForm	*V=dynamic_cast<PropertyDotColorMatchingForm *>(Instance);
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

static	bool	MacroGenerateDotColorMatchings(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyDotColorMatchingForm	*V=dynamic_cast<PropertyDotColorMatchingForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateDotColorMatchings();

	return true;
}

static	bool	MacroShowEditLibrary(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyDotColorMatchingForm	*V=dynamic_cast<PropertyDotColorMatchingForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ShowEditLibrary();

	return true;
}