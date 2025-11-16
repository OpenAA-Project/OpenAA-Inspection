#include "PropertyBuslineFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyBusline\PropertyBusline.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PropertyBuslineResource.h"
#include "XGUIDLL.h"
#include "PropertyBusline.h"
#include "PropertyBuslineForm.h"
#include "XBuslinePacket.h"
#include "XMacroFunction.h"
#include "XDisplaySimPanel.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyBusline";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Busline");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendAddManualBlock		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqBuslineListForPacketPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIAckBuslineListForPacketPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqGenerateBuslineItems		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqTestMap					(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIClearMap						(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqDSimPanelImage			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckDSimPanelImage			(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyBuslineForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyBusline.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Busline"));
}

static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroGenerateBlocksByLib(GUIFormBase *Instance,QStringList &Args);

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Generate";
		Functions[ret].Explain.append(/**/"Generate blocks");
		Functions[ret].ArgName.append(/**/"Minimum X");
		Functions[ret].ArgName.append(/**/"Minimum Y");
		Functions[ret].ArgName.append(/**/"Maximum X");
		Functions[ret].ArgName.append(/**/"Maximum Y");
		Functions[ret].ArgName.append(/**/"Lib ID");
		Functions[ret].DLL_ExcuteMacro	=MacroGenerateBlocks;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName=/**/"GenerateByLibFromMask";
		Functions[ret].Explain.append(/**/"Generate blocks from mask");
		Functions[ret].ArgName.append(/**/"Lib ID");
		Functions[ret].DLL_ExcuteMacro=MacroGenerateBlocksByLib;
		ret++;
	}
	return ret;
}
static	bool	MacroGenerateBlocks(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyBuslineForm	*V=dynamic_cast<PropertyBuslineForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<5){
		return false;
	}
	bool	ok;
	int	X1=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Y1=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	X2=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	LibID=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->CommandGenerateBlocks(LibID,X1,Y1,X2,Y2);

	return true;
}

static	bool	MacroGenerateBlocksByLib(GUIFormBase *Instance,QStringList &Args)
{
	PropertyBuslineForm *V=dynamic_cast<PropertyBuslineForm *>(Instance);
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
	V->CommandGenerateBlocksByLib(LibID);

	return true;
}