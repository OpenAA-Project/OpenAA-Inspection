/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ListHistory\ListHistory.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ListHistory.h"
#include "ListHistoryForm.h"
#include "ListHistoryFormResource.h"

const	char	*sRoot=/**/"List";
const	char	*sName=/**/"History";


/*
const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}
*/
DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show list of history");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUIReqRemoveHistry(Base ,sRoot,sName ,-1);

	return true;
}

DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ListHistoryForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<11)
		return -1;
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"OutputFileName";
	Data[0].Pointer				 =&((ListHistoryForm *)Instance)->OutputFileName;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"EditMode";
	Data[1].Pointer				 =&((ListHistoryForm *)Instance)->EditMode;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ColorOK";
	Data[2].Pointer				 =&((ListHistoryForm *)Instance)->ColorOK;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"ColorNG";
	Data[3].Pointer				 =&((ListHistoryForm *)Instance)->ColorNG;
	Data[4].Type				 =/**/"QColor";
	Data[4].VariableNameWithRoute=/**/"ColorNot";
	Data[4].Pointer				 =&((ListHistoryForm *)Instance)->ColorNot;
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"ColorIrregular";
	Data[5].Pointer				 =&((ListHistoryForm *)Instance)->ColorIrregular;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ShowColumnID";
	Data[6].Pointer				 =&((ListHistoryForm *)Instance)->ShowColumnID;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ShowColumnTime";
	Data[7].Pointer				 =&((ListHistoryForm *)Instance)->ShowColumnTime;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"ShowColumnOKNG";
	Data[8].Pointer				 =&((ListHistoryForm *)Instance)->ShowColumnOKNG;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"ShowColumnSV";
	Data[9].Pointer				 =&((ListHistoryForm *)Instance)->ShowColumnSV;
	Data[10].Type				 =/**/"bool";
	Data[10].VariableNameWithRoute=/**/"ShowColumnMS";
	Data[10].Pointer				 =&((ListHistoryForm *)Instance)->ShowColumnMS;

	return(11);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ListHistory.png")));
}