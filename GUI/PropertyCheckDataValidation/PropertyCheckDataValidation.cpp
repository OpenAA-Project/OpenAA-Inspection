/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyCheckDataValidation\PropertyCheckDataValidation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "CheckDataValidationResource.h"
#include "PropertyCheckDataValidation.h"
#include "PropertyCheckDataValidationForm.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "XMacroFunction.h"
#include <QStringList>
#include <QIcon>
#include <QPixmap>
#include "XPropertyCheckDataValidationPacket.h"
#include "XDisplaySimPanel.h"
#include "XGUIPacketGeneral.h"


const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyCheckDataValidation";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for CheckDataValidation");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddManualCheckDataValidation	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqGridList						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckGridList						(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqCheckDataValidationItemData	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckCheckDataValidationItemData	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSetCheckDataValidationItemData	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdDeleteCheckDataValidationItem		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqThresholdMemberString			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckThresholdMemberString			(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyCheckDataValidationForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyCheckDataValidation.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"CheckDataValidation"));
}
