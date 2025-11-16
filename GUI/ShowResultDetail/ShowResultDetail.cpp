/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowResultDetail\ShowResultDetail.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowResultDetailForm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"Inspection";
const	char	*sName=/**/"ShowResultDetail";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Execute PIX file list");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqResultDetailList(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdAckResultDetailList(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowResultDetailForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"AutoWrite";
	Data[0].Pointer				 =&((ShowResultDetailForm *)Instance)->AutoWrite;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"FileName";
	Data[1].Pointer				 =&((ShowResultDetailForm *)Instance)->FileName;
	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowResultDetail.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
