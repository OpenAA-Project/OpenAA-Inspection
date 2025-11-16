#include "CreateMatrixCellListResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MatrixCellList\MatrixCellList.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "MatrixCellList.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "MatrixCellListForm.h"

static	const	char	*sRoot=/**/"Review";
static	const	char	*sName=/**/"MatrixCellList";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Listbox of cell matrix zones");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new MatrixCellListForm(Base,parent));
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
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"DisplayImageRoot";
	Data[0].Pointer				 =&((MatrixCellListForm *)Instance)->DisplayImageRoot;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"DisplayImageName";
	Data[1].Pointer				 =&((MatrixCellListForm *)Instance)->DisplayImageName;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"DisplayImageInst";
	Data[2].Pointer				 =&((MatrixCellListForm *)Instance)->DisplayImageInst;
	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"WholeImageInstName";
	Data[3].Pointer				 =&((MatrixCellListForm *)Instance)->WholeImageInstName;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MatrixCellList.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Naming"));
}
