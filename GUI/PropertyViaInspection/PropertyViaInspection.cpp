/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyVIA\PropertyVIA.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyViaInspection.h"
#include "PropertyVIAInspectionForm.h"
#include "XDisplayImage.h"
//#include "PropertyVIAFormResource.h"
#include "PropertyVIAInspectionFormResource.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include "XDisplaySimPanel.h"
#include "XPropertyVIAPacket.h"
#include "XGUIPacketGeneral.h"

static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateVIAs(GUIFormBase *Instance ,QStringList &Args);


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyVIAInspection";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for VIA Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualVIA			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendModifySelectedVIA		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSelectedVIAItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendSelectedVIAItemAttr	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqVIAInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendVIAInfoList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqVIAFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckVIAFromList			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdPickupTestList				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdGenerateVIAs				(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAreaHistgramInMaster		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAreaHistgramInMaster	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdTestClear					(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqSetButtonMode			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqDSimPanelImage	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckDSimPanelImage	(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	AlgorithmBase	*BBase=Base->GetAlgorithmBase(/**/"Basic",/**/"VIAInspection");
	if(BBase!=NULL){
		new GUICmdSelectByLibs	(BBase, QString(sRoot), QString(sName));
	}

	return(new PropertyVIAInspectionForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyViaInspection.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"VIAInspection"));
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
		Functions[ret].Explain.append(/**/"Generate VIAs");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateVIAs;
		ret++;
	}
	return ret;
}


static	bool	MacroClearLibList(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyVIAInspectionForm	*V=dynamic_cast<PropertyVIAInspectionForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->ClearLibList();

	return true;
}

static	bool	MacroSetLib(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyVIAInspectionForm	*V=dynamic_cast<PropertyVIAInspectionForm *>(Instance);
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

static	bool	MacroGenerateVIAs(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyVIAInspectionForm	*V=dynamic_cast<PropertyVIAInspectionForm *>(Instance);
	if(V==NULL){
		return false;
	}
	V->GenerateVIAs();

	return true;
}
