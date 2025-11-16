#include "ShowResultMultiDeliveryResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowResultMultiDelivery\ShowResultMultiDeliveryForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "ShowResultSmallLotFormResource.h"
#include "ShowResultMultiDeliveryForm.h"

#include "XDLLOnly.h"
#include "XTypeDef.h"
#include "XGUIDLL.h"
#include "XDataInLayer.h"
#include "XGUI.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

const	char	*sRoot=/**/"Result";
const	char	*sName=/**/"ShowResultMultiDelivery";

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
	return(new ShowResultMultiDeliveryForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ChangeToClear";
	Data[0].Pointer				 =&((ShowResultMultiDeliveryForm *)Instance)->ChangeToClear;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"SysNoNGStockedCounter";
	Data[1].Pointer				 =&((ShowResultMultiDeliveryForm *)Instance)->SysNoNGStockedCounter;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"SysNoReqChangeLot";
	Data[2].Pointer				 =&((ShowResultMultiDeliveryForm *)Instance)->SysNoReqChangeLot;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowResultMultiDelivery.png")));
}


DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*ASubNumber=new GuiAdditionalDatabase(/**/"INSPECTIONLOT",/**/"SUBNUMBER",(int)0);
	Data.AppendList(ASubNumber);

	GuiAdditionalDatabase	*AIDNumber=new GuiAdditionalDatabase(/**/"INSPECTIONLOT",/**/"DeliveryNo",(int)0);
	Data.AppendList(AIDNumber);
}
