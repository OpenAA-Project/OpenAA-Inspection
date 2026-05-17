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

static	char	*sRoot="Panel";
static	char	*sName="ShowMasterNames";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Show Names and IDs(Master,Lot,Worker)");
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
	if(maxDataDim<35){
		return(-1);
	}
	Data[0].Type					="bool";
	Data[0].VariableNameWithRoute	="ShowMasterID";
	Data[0].Pointer					=&((ShowMasterNamesForm *)Instance)->ShowMasterID;
	Data[1].Type					="bool";
	Data[1].VariableNameWithRoute	="ShowMasterName";
	Data[1].Pointer					=&((ShowMasterNamesForm *)Instance)->ShowMasterName;
	Data[2].Type					="bool";
	Data[2].VariableNameWithRoute	="ShowLotID";
	Data[2].Pointer					=&((ShowMasterNamesForm *)Instance)->ShowLotID;
	Data[3].Type					="bool";
	Data[3].VariableNameWithRoute	="ShowLotName";
	Data[3].Pointer					=&((ShowMasterNamesForm *)Instance)->ShowLotName;
	Data[4].Type					="bool";
	Data[4].VariableNameWithRoute	="ShowWorkerID";
	Data[4].Pointer					=&((ShowMasterNamesForm *)Instance)->ShowWorkerID;
	Data[5].Type					="bool";
	Data[5].VariableNameWithRoute	="ShowWorkerName";
	Data[5].Pointer					=&((ShowMasterNamesForm *)Instance)->ShowWorkerName;

	Data[6].Type					="QString";
	Data[6].VariableNameWithRoute	="TitleMasterID";
	Data[6].Pointer					=&((ShowMasterNamesForm *)Instance)->TitleMasterID;
	Data[7].Type					="QString";
	Data[7].VariableNameWithRoute	="TitleMasterName";
	Data[7].Pointer					=&((ShowMasterNamesForm *)Instance)->TitleMasterName;
	Data[8].Type					="QString";
	Data[8].VariableNameWithRoute	="TitleLotID";
	Data[8].Pointer					=&((ShowMasterNamesForm *)Instance)->TitleLotID;
	Data[9].Type					="QString";
	Data[9].VariableNameWithRoute	="TitleLotName";
	Data[9].Pointer					=&((ShowMasterNamesForm *)Instance)->TitleLotName;
	Data[10].Type					="QString";
	Data[10].VariableNameWithRoute	="TitleWorkerID";
	Data[10].Pointer				=&((ShowMasterNamesForm *)Instance)->TitleWorkerID;
	Data[11].Type					="QString";
	Data[11].VariableNameWithRoute	="TitleWorkerName";
	Data[11].Pointer				=&((ShowMasterNamesForm *)Instance)->TitleWorkerName;

	Data[12].Type					="bool";
	Data[12].VariableNameWithRoute	="ShowHeadMasterID";
	Data[12].Pointer				=&((ShowMasterNamesForm *)Instance)->ShowHeadMasterID;
	Data[13].Type					="bool";
	Data[13].VariableNameWithRoute	="ShowHeadMasterName";
	Data[13].Pointer				=&((ShowMasterNamesForm *)Instance)->ShowHeadMasterName;
	Data[14].Type					="bool";
	Data[14].VariableNameWithRoute	="ShowHeadLotID";
	Data[14].Pointer				=&((ShowMasterNamesForm *)Instance)->ShowHeadLotID;
	Data[15].Type					="bool";
	Data[15].VariableNameWithRoute	="ShowHeadLotName";
	Data[15].Pointer				=&((ShowMasterNamesForm *)Instance)->ShowHeadLotName;
	Data[16].Type					="bool";
	Data[16].VariableNameWithRoute	="ShowHeadWorkerID";
	Data[16].Pointer				=&((ShowMasterNamesForm *)Instance)->ShowHeadWorkerID;
	Data[17].Type					="bool";
	Data[17].VariableNameWithRoute	="ShowHeadWorkerName";
	Data[17].Pointer				=&((ShowMasterNamesForm *)Instance)->ShowHeadWorkerName;

	Data[18].Type					="AlignLeft,AlignCenter,AlignRight";
	Data[18].VariableNameWithRoute	="AlignAttr";
	Data[18].Pointer				=&((ShowMasterNamesForm *)Instance)->AlignAttr;
	Data[19].Type					="QColor";
	Data[19].VariableNameWithRoute	="CharColor";
	Data[19].Pointer				=&((ShowMasterNamesForm *)Instance)->CharColor;
	Data[20].Type					="QColor";
	Data[20].VariableNameWithRoute	="BackColor";
	Data[20].Pointer				=&((ShowMasterNamesForm *)Instance)->BackColor;
	Data[21].Type					="bool";
	Data[21].VariableNameWithRoute	="TransparentBackColor";
	Data[21].Pointer				=&((ShowMasterNamesForm *)Instance)->TransparentBackColor;
	Data[22].Type					="QColor";
	Data[22].VariableNameWithRoute	="BorderColor";
	Data[22].Pointer				=&((ShowMasterNamesForm *)Instance)->BorderColor;
	Data[23].Type					="int32";
	Data[23].VariableNameWithRoute	="BorderWidth";
	Data[23].Pointer				=&((ShowMasterNamesForm *)Instance)->BorderWidth;
	Data[24].Type					="dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none";
	Data[24].VariableNameWithRoute	="BorderStyle";
	Data[24].Pointer				=&((ShowMasterNamesForm *)Instance)->BorderStyle;
	Data[25].Type					="QFont";
	Data[25].VariableNameWithRoute	="CFont";
	Data[25].Pointer				=&((ShowMasterNamesForm *)Instance)->CFont;

	Data[26].Type					="AlignLeft,AlignCenter,AlignRight";
	Data[26].VariableNameWithRoute	="HeadAlignAttr";
	Data[26].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadAlignAttr;
	Data[27].Type					="QColor";
	Data[27].VariableNameWithRoute	="HeadCharColor";
	Data[27].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadCharColor;
	Data[28].Type					="QColor";
	Data[28].VariableNameWithRoute	="HeadBackColor";
	Data[28].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadBackColor;
	Data[29].Type					="bool";
	Data[29].VariableNameWithRoute	="HeadTransparentBackColor";
	Data[29].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadTransparentBackColor;
	Data[30].Type					="QColor";
	Data[30].VariableNameWithRoute	="HeadBorderColor";
	Data[30].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadBorderColor;
	Data[31].Type					="int32";
	Data[31].VariableNameWithRoute	="HeadBorderWidth";
	Data[31].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadBorderWidth;
	Data[32].Type					="dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none";
	Data[32].VariableNameWithRoute	="HeadBorderStyle";
	Data[32].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadBorderStyle;
	Data[33].Type					="QFont";
	Data[33].VariableNameWithRoute	="HeadCFont";
	Data[33].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadCFont;

	Data[34].Type					="int32";
	Data[34].VariableNameWithRoute	="HeadWidth";
	Data[34].Pointer				=&((ShowMasterNamesForm *)Instance)->HeadWidth;

	return(35);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ShowMasterNames.png")));
}

