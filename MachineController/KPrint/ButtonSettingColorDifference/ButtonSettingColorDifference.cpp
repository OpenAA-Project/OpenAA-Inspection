#include "ButtonSettingColorDifferenceResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSettingColorDifference\ButtonSettingColorDifference.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSettingColorDifference.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "ButtonSettingColorDifferenceForm.h"
#include "SettingColorDifferenceDialog.h"
#include <QPixmap>
#include <QIcon>

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"SettingColorDifference";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for SettingColorDifference");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationCmdReqItemInfos		(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationCmdAckItemInfos		(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationCmdReqItemData		(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationCmdAckItemData		(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationCmdReqTryItem		(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationCmdAckTryItem		(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationCmdReqSetItemOnly	(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationCmdReqSetItemAll	(Base ,sRoot,sName ,-1);

	(*Base)	=new IntegrationReqImageColorDifference	(Base ,sRoot,sName ,-1);
	(*Base)	=new IntegrationAckImageColorDifference	(Base ,sRoot,sName ,-1);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSettingColorDifferenceForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				  =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"SlaveNo";
	Data[0].Pointer			  =&((ButtonSettingColorDifferenceForm *)Instance)->SlaveNo;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"Msg";
	Data[1].Pointer				 =&((ButtonSettingColorDifferenceForm *)Instance)->Msg;
	Data[1].Translatable		 =true;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((ButtonSettingColorDifferenceForm *)Instance)->CharColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"BackColor";
	Data[3].Pointer				 =&((ButtonSettingColorDifferenceForm *)Instance)->BackColor;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((ButtonSettingColorDifferenceForm *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSettingColorDifference.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"ColorDifference"));
}
