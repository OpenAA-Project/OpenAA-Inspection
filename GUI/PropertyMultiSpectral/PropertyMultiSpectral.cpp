/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyMultiSpectral\PropertyMultiSpectral.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "AlignmentProjectionFormResource.h"
#include "PropertyMultiSpectral.h"
#include "PropertyMultiSpectralForm.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"
#include "XGUIDLL.h"
#include "XPropertyMultiSpectralPacket.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyMultiSpectral";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for MultiSpectral");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdSendAddMultiSpectralUsageAreaItem(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyMultiSpectralForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyMultiSpectral.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"MultiSpectral"));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

//	if(MaxBuffer>ret){
//		Functions[ret].FuncName	=/**/"SelectArea";
//		Functions[ret].ArgName.append(/**/"AreaCenterX");
//		Functions[ret].ArgName.append(/**/"AreaCenterY");
//		Functions[ret].Explain.append(/**/"Select area in position");
//		Functions[ret].DLL_ExcuteMacro	=MacroSelectArea;
//		ret++;
//	}

	return ret;
}


