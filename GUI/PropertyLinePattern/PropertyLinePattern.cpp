/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyLinePattern\PropertyLinePattern.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyLinePatternFormResource.h"
#include "XGUIDLL.h"
#include "PropertyLinePattern.h"
#include "PropertyLinePatternForm.h"
#include "XLinePatternPacket.h"
#include "XMacroFunction.h"
#include "XGUIPacketGeneral.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyLinePattern";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for LinePattern");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSendAddManualBlock				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualLinePattern		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqLinePatternListForPacketPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIAckLinePatternListForPacketPack	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUIReqGenerateLinePatternItems		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqSetButtonMode				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqBlockInfoList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendBlockInfoList				(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAddManualLinePattern		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReleaseSelectImagePanel		(Base, QString(sRoot), QString(sName));

	(*Base)=new GUICmdReqRemoveAllOriginal			(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdChangeLinePatternThreshold		(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyLinePatternForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyLinePattern.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"LinePattern"));
}


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){

		ret++;
	}
	return ret;
}
