#include "GraphTrendKidaResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GraphTrendKida\GraphTrendKida.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GraphTrendKida.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "GraphTrendKidaForm.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"GraphTrendKida";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for set shift on filter");
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
	return(new GraphTrendKidaForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<11)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"ColorData0";
	Data[0].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[0];
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"ColorData1";
	Data[1].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[1];
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"ColorData2";
	Data[2].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[2];
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"ColorData3";
	Data[3].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[3];
	Data[4].Type				 =/**/"QColor";
	Data[4].VariableNameWithRoute=/**/"ColorData4";
	Data[4].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[4];
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"ColorData5";
	Data[5].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[5];
	Data[6].Type				 =/**/"QColor";
	Data[6].VariableNameWithRoute=/**/"ColorData6";
	Data[6].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[6];
	Data[7].Type				 =/**/"QColor";
	Data[7].VariableNameWithRoute=/**/"ColorData7";
	Data[7].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[7];
	Data[8].Type				 =/**/"QColor";
	Data[8].VariableNameWithRoute=/**/"ColorData8";
	Data[8].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[8];
	Data[9].Type				 =/**/"QColor";
	Data[9].VariableNameWithRoute=/**/"ColorData9";
	Data[9].Pointer				 =&((GraphTrendKidaForm *)Instance)->ColorData[9];
	Data[10].Type				 =/**/"int32";
	Data[10].VariableNameWithRoute=/**/"SlaveNo";
	Data[10].Pointer				 =&((GraphTrendKidaForm *)Instance)->SlaveNo;

	return(11);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GraphTrendKida.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_AssociateGUI(RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"KidaPrint",/**/"ShowPrintTotalBlade"));
}