#include "DisplayMasterImageResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\DisplayMasterImage\DisplayMasterImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "DisplayMasterImage.h"
#include "XCrossObj.h"
#include "XGUIDLL.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"DisplayMasterImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Master Image for Inspeaction");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);

	DisplayImage::InitialDisplayImageInDLL(Base->GetGUICmdContainer(),Base ,sRoot ,sName ,DisplayImage::__Master);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayMasterImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((DisplayMasterImage *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	Data[N].Type				 =/**/"QStringList";
	Data[N].VariableNameWithRoute=/**/"RelatedItems";
	Data[N].Pointer				 =&((DisplayMasterImage *)Instance)->RelatedItems;
	Data[N+1].Type				  =/**/"QString";
	Data[N+1].VariableNameWithRoute=/**/"ImageControlToolsName";
	Data[N+1].Pointer			  =&((DisplayMasterImage *)Instance)->ImageControlToolsName;
	Data[N+2].Type				  =/**/"int32";
	Data[N+2].VariableNameWithRoute=/**/"ShowFixedPhase";
	Data[N+2].Pointer			  =&((DisplayMasterImage *)Instance)->ShowFixedPhase;

	return(N+3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayMasterImage.png")));
}

DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImage::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
DisplayMasterImage::DisplayMasterImage(LayersBase *Base ,QWidget *parent)
:DisplayImage(Base,QString(sRoot),QString(sName),__Master,parent)
{}
