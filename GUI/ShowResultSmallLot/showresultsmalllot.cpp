/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Anessys\SpecifiedCellCover\BCR_Oracle\BCR_Oracle.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ShowResultSmallLotFormResource.h"
#include "showresultsmalllot.h"
#include "ShowResultSmallLotForm.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

const	char	*sRoot=/**/"Result";
const	char	*sName=/**/"ShowResultSmallLot";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show small lot");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdChangeLot(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowResultSmallLotForm(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"ChangeToClear";
	Data[0].Pointer				 =&((ShowResultSmallLotForm *)Instance)->ChangeToClear;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"TransmitLotInfo";
	Data[1].Pointer				 =&((ShowResultSmallLotForm *)Instance)->TransmitLotInfo;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowResultSmallLot.png")));
}


DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*ASubNumber=new GuiAdditionalDatabase(/**/"INSPECTIONLOT",/**/"SUBNUMBER",(int)0);
	Data.AppendList(ASubNumber);

	GuiAdditionalDatabase	*AIDNumber=new GuiAdditionalDatabase(/**/"INSPECTIONLOT",/**/"IDNumber",(int)0);
	Data.AppendList(AIDNumber);
}
