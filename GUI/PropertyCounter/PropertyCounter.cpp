/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyCounter\PropertyCounter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PropertyCounter.h"
#include "PropertyCounterForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include "XPropertyCounterPacket.h"
#include "XGUIPacketGeneral.h"
#include "XDataInLayer.h"
#include <QIcon>
#include <QPixmap>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyCounter";

static	bool	MacroAddCount(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for Counter Inspection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	//new GUICmdAddLimitedMask(QString(sRoot),QString(sName));
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdAddAreaManual			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqItemImage			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckItemImage			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqResultCounter		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckResultCounter		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAdoptedRate		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAdoptedRate		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAdoptedRate		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAdoptPixelsRate	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAdoptPixelsRate	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAdoptPixelsRate	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqFocusLevel			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckFocusLevel			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendFocusLevel		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendOutsideCalc		(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqItemArea			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckItemArea			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetFilterMode			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdAddMaskForCounter		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdRemoveMask			(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqMaskCount			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckMaskCount			(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyCounterForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyCounter.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Counter"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"Masking"));
}


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"AddCount";
		Functions[ret].ArgName.append(/**/"Addional count");
		Functions[ret].Explain.append(/**/"Add count");
		Functions[ret].DLL_ExcuteMacro	=MacroAddCount;
		ret++;
	}
	return ret;
}
static	bool	MacroAddCount(GUIFormBase *Instance ,QStringList &Args)
{
	PropertyCounterForm	*V=dynamic_cast<PropertyCounterForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	bool	ok;
	int	Count=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}

	V->AddCount(Count);

	return true;
}
