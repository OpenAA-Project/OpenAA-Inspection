/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelMaxStock\PanelMaxStock.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelMaxStock.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "PanelMaxStockForm.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"MaxStock";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for max stock");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new PanelMaxStockForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"TopRegNumber";
	Data[0].Pointer				 =&((PanelMaxStockForm *)Instance)->TopRegNumber;
	Data[1].Type				 =/**/"QStringList";
	Data[1].VariableNameWithRoute=/**/"StockStringList";
	Data[1].Pointer				 =&((PanelMaxStockForm *)Instance)->StockStringList;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelMaxStock.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QByteArray	StockCount;
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"MAXSTOCK",StockCount);
	Data.AppendList(A);
}
