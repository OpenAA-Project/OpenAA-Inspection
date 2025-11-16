/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyAlignmentProjection\PropertyAlignmentProjection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "AlignmentProjectionFormResource.h"
#include "PropertyAlignmentProjection.h"
#include "PropertyAlignmentProjectionForm.h"
#include "PropertyAlignmentProjectionPacket.h"
#include "XDisplayImage.h"
#include "XMacroFunction.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"PropertyAlignmentProjectionForm";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Property for AlignmentProjection");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqAlignmentProjectionPoint			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentProjectionPoint			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentProjectionPointListPack	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdSendAlignmentProjectionPointListPack	(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentProjectionPutPoint		(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAlignmentProjectionModifyPoint		(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new PropertyAlignmentProjectionForm(Base,parent));
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
	return(new QIcon(QPixmap(/**/":Resources/PropertyAlignmentProjection.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"AlignmentProjection"));
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


