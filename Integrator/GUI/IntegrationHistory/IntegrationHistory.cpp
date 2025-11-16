#include "IntegrationHistoryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationHistory\IntegrationHistory.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationHistoryForm.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"History";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show history list in Integration");
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
	return(new IntegrationHistoryForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QFont";
	Data[0].VariableNameWithRoute=/**/"CharFont";
	Data[0].Pointer				 =&((IntegrationHistoryForm *)Instance)->CharFont;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"AllocatedCount";
	Data[1].Pointer				 =&((IntegrationHistoryForm *)Instance)->AllocatedCount;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowOnlyNG";
	Data[2].Pointer				 =&((IntegrationHistoryForm *)Instance)->ShowOnlyNG;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowTotal";
	Data[3].Pointer				 =&((IntegrationHistoryForm *)Instance)->ShowTotal;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"ScrollerWidth";
	Data[4].Pointer				 =&((IntegrationHistoryForm *)Instance)->ScrollerWidth;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationHistory.png")));
}
