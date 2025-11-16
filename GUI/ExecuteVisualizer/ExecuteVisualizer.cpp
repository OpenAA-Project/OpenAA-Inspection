#include "ExecuteVisualizerResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ExecuteVisualizer\ExecuteVisualizer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ExecuteVisualizer.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "XDataInLayer.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ExecuteVisualizer";




DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel to show visual execution");
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
	return(new ExecuteVisualizer(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<1)
		return(-1);

	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"RunnerFileName";
	Data[0].Pointer				 =&((ExecuteVisualizer *)Instance)->RunnerFileName;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ExecuteVisualizer.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ExecuteVisualizer::ExecuteVisualizer(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	RMap=NULL;
	RunnerFileName	=/**/"ExecuteRunner.dat";
}

ExecuteVisualizer::~ExecuteVisualizer(void)
{
	if(RMap!=NULL){
		RMap->deleteLater();
	}
}

void	ExecuteVisualizer::Prepare(void)
{
	RMap=new RunnerMap(GetLayersBase(),false,NULL);

	QFile	File(GetLayersBase()->GetUserPath()+GetSeparator()+RunnerFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		RMap->Load(&File);
	}
	RMap->show();
}

void	ExecuteVisualizer::TransmitDirectly(GUIDirectMessage *packet)
{
	
}
