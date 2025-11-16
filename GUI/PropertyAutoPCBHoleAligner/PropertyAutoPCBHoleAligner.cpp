/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAutoPCBHoleAligner\PropertyAutoPCBHoleAligner.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "PropertyAutoPCBHoleAlignerFormResource.h"
#include "PropertyAutoPCBHoleAligner.h"
#include "PropertyAutoPCBHoleAlignerForm.h"
#include "XGUIDLL.h"
#include "XAutoPCBHoleAlignerPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAutoPCBHoleAligner";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for AutoPCBHoleAligner");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdCreateAutoPCBHoleAligner	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdReqAutoPCBHoleAlignerInfo	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendAutoPCBHoleAlignerInfo	(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAutoPCBHoleAlignerForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAutoPCBHoleAligner.png")));
}
DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoPCBHoleAligner"));
}

