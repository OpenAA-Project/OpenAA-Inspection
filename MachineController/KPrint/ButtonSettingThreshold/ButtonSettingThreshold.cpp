#include "ButtonSettingThresholdResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSettingThreshold\ButtonSettingThreshold.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonSettingThreshold.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "ButtonSettingThresholdForm.h"
#include "XEachThresholdCommon.h"
#include "EachThresholdWholeForm.h"

//extern	LangSolverNew	LangCGSolver;

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"SettingThreshold";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for SettingThreshold");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)	=new IntegrationReqRepresentative		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckRepresentative		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqTryInspection		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckTryInspection		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqItemID				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckItemID				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqItemData				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckItemData				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqReflectThreshold		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqReflectOnlySize		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqReflectOnlyAreaSearch(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqReflectEnable		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqRepresentativeByLib	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckRepresentativeByLib	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqColor				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckColor				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqAreaType				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckAreaType				(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationSetBrightnessShift		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqThresholdPanelImage	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckThresholdPanelImage	(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqThresholdLibID		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckThresholdLibID		(Base,sRoot,sName,-1);

	//(*Base)	=new GUICmdReqThresholdPanelImage		(Base,sRoot,sName,-1);
	//(*Base)	=new GUICmdAckThresholdPanelImage		(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdReqThresholdLibID			(Base,sRoot,sName,-1);
	(*Base)	=new GUICmdAckThresholdLibID			(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationReqItemByAreaLib		(Base,sRoot,sName,-1);
	(*Base)	=new IntegrationAckItemByAreaLib		(Base,sRoot,sName,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSettingThresholdForm(Base,parent));
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
	Data[0].Pointer			  =&((ButtonSettingThresholdForm *)Instance)->SlaveNo;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"Msg";
	Data[1].Pointer				 =&((ButtonSettingThresholdForm *)Instance)->Msg;
	Data[1].Translatable		=true;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CharColor";
	Data[2].Pointer				 =&((ButtonSettingThresholdForm *)Instance)->CharColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"BackColor";
	Data[3].Pointer				 =&((ButtonSettingThresholdForm *)Instance)->BackColor;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((ButtonSettingThresholdForm *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSettingThreshold.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
}


DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QByteArray	Array;
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA"
														,/**/"BSThreshold"
														,Array);
	Data.AppendList(A);


}