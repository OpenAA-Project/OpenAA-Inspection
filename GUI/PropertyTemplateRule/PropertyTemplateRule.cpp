/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTemplateRule\PropertyTemplateRule.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "PropertyTemplateRuleResource.h"
#include "PropertyTemplateRule.h"
#include "PropertyTemplateRuleForm.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"
#include "XGUIDLL.h"
#include "XPropertyTemplateRulePacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyTemplateRule";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for TemplateRule");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	//(*Base)=new GUICmdSetAverageToMaster(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdReqAverageCount	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdAckAverageCount	(Base, QString(sRoot), QString(sName));
	//(*Base)=new GUICmdResetAverage		(Base, QString(sRoot), QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyTemplateRuleForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyTemplateRule.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"TemplateRule"));
}

DEFFUNCEX	void	DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List)
{
	List.Add(GUILIB_ID,/**/"Button" ,/**/"TemplateRule");
}

