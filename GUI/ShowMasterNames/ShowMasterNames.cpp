/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowMasterNames\ShowMasterNames.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowMasterNames.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "ShowMasterNamesForm.h"
#include "ShowMasterNamesFormResource.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ShowMasterNames";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Names and IDs(Master,Lot,Worker)");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowMasterNamesForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	;
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<14)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ShowMasterID";
	Data[0].Pointer				 =&((ShowMasterNamesForm *)Instance)->ShowMasterID;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowMasterName";
	Data[1].Pointer				 =&((ShowMasterNamesForm *)Instance)->ShowMasterName;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowLotID";
	Data[2].Pointer				 =&((ShowMasterNamesForm *)Instance)->ShowLotID;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowLotName";
	Data[3].Pointer				 =&((ShowMasterNamesForm *)Instance)->ShowLotName;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowWorkerID";
	Data[4].Pointer				 =&((ShowMasterNamesForm *)Instance)->ShowWorkerID;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowWorkerName";
	Data[5].Pointer				 =&((ShowMasterNamesForm *)Instance)->ShowWorkerName;

	Data[6].Type				 =/**/"QString";
	Data[6].VariableNameWithRoute=/**/"TitleMasterID";
	Data[6].Pointer				 =&((ShowMasterNamesForm *)Instance)->TitleMasterID;
	Data[7].Type				 =/**/"QString";
	Data[7].VariableNameWithRoute=/**/"TitleMasterName";
	Data[7].Pointer				 =&((ShowMasterNamesForm *)Instance)->TitleMasterName;
	Data[8].Type				 =/**/"QString";
	Data[8].VariableNameWithRoute=/**/"TitleLotID";
	Data[8].Pointer				 =&((ShowMasterNamesForm *)Instance)->TitleLotID;
	Data[9].Type				 =/**/"QString";
	Data[9].VariableNameWithRoute=/**/"TitleLotName";
	Data[9].Pointer				 =&((ShowMasterNamesForm *)Instance)->TitleLotName;
	Data[10].Type				 =/**/"QString";
	Data[10].VariableNameWithRoute=/**/"TitleWorkerID";
	Data[10].Pointer			 =&((ShowMasterNamesForm *)Instance)->TitleWorkerID;
	Data[11].Type				 =/**/"QString";
	Data[11].VariableNameWithRoute=/**/"TitleWorkerName";
	Data[11].Pointer			 =&((ShowMasterNamesForm *)Instance)->TitleWorkerName;

	Data[12].Type				 =/**/"QFont";
	Data[12].VariableNameWithRoute=/**/"TitleFont";
	Data[12].Pointer			 =&((ShowMasterNamesForm *)Instance)->TitleFont;
	Data[13].Type				 =/**/"QFont";
	Data[13].VariableNameWithRoute=/**/"DataFont";
	Data[13].Pointer			 =&((ShowMasterNamesForm *)Instance)->DataFont;
	return(14);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowMasterNames.png")));
}

