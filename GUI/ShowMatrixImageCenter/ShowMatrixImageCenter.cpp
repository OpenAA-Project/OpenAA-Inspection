#include "ShowMatrixImageCenterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowMatrixImageCenter\ShowMatrixImageCenter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowMatrixImageCenter.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ShowMatrixImageCenterForm.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"ETC";
static	const	char	*sName=/**/"ShowMatrixImageCenter";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel to show matrix of image center");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowMatrixImageCenterForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowMatrixImageCenter.png")));
}

static	bool	MacroSetCenter(GUIFormBase *Instance ,QStringList &Args);


DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"SetCenter";
		Functions[ret].Explain.append(/**/"Set center of image");
		Functions[ret].ArgName.append(/**/"Center X pos in GlobalImage");
		Functions[ret].ArgName.append(/**/"Center Y pos in GlobalImage");
		Functions[ret].DLL_ExcuteMacro	=MacroSetCenter;
		ret++;
	}


	return ret;
}


static	bool	MacroSetCenter(GUIFormBase *Instance ,QStringList &Args)
{
	ShowMatrixImageCenterForm	*V=dynamic_cast<ShowMatrixImageCenterForm *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<2){
		return false;
	}
	bool	ok;
	int	x=Args[0].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	y=Args[1].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->SetCenter(x,y);

	return true;
}
