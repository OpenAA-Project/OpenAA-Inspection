#include "EasyPropertyMeasureResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyPropertyMeasure\EasyPropertyMeasure.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <QIcon>
#include <QPixmap>

#include "EasyPropertyMeasure.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "EasyPropertyMeasureForm.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyPropertyMeasure";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Easy property for Measure inspection");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new IntegrationCmdReqListData			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckListData			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetCorrectValue		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAddDistance			(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetMeasureDistanceEndPoint(Base,sRoot,sName);
	(*Base)=new IntegrationCmdDeleteDistance		(Base,sRoot,sName);
	(*Base)=new IntegrationCmdReqMeasureLineInfo	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdAckMeasureLineInfo	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetMeasureLineInfo	(Base,sRoot,sName);
	(*Base)=new IntegrationCmdSetMeasureLineInfoAll	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new EasyPropertyMeasureForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return -1;
	Data[0].Type				  =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer			  =&((EasyPropertyMeasureForm *)Instance)->SlaveNo;

	return(1);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyPropertyMeasure.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

