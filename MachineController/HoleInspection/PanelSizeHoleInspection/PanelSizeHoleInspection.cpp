//#include "PanelSizeHoleInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelSizeHoleInspection\PanelSizeHoleInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelSizeHoleInspection.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "PanelSizeHoleInspectionForm.h"
#include "XGUI.h"



static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"SizeHoleInspection";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for setting X-Y size and calc");
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
	return(new PanelSizeHoleInspectionForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);

	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"LimitMaxX";
	Data[0].Pointer				 =&((PanelSizeHoleInspectionForm *)Instance)->LimitMaxX;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"LimitMaxY";
	Data[1].Pointer				 =&((PanelSizeHoleInspectionForm *)Instance)->LimitMaxY;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ModeIncrementStrategy";
	Data[2].Pointer				 =&((PanelSizeHoleInspectionForm *)Instance)->ModeIncrementStrategy;
	Data[3].Type				 =/**/"True,False,FlipTrue,FlipFalse";
	Data[3].VariableNameWithRoute=/**/"ModeXDirection";
	Data[3].Pointer				 =&((PanelSizeHoleInspectionForm *)Instance)->ModeXDirection;
	Data[4].Type				 =/**/"True,False,FlipTrue,FlipFalse";
	Data[4].VariableNameWithRoute=/**/"ModeYDirection";
	Data[4].Pointer				 =&((PanelSizeHoleInspectionForm *)Instance)->ModeYDirection;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"SwitchLabel";
	Data[5].Pointer				 =&((PanelSizeHoleInspectionForm *)Instance)->SwitchLabel;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ReflectOnlyWindow";
	Data[6].Pointer				 =&((PanelSizeHoleInspectionForm *)Instance)->ReflectOnlyWindow;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelSizeHoleInspection.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase();
	A->TableName=/**/"MASTERDATA";
	A->FieldName=/**/"XSIZE";
	A->DefaultData.setValue((int)1000);
	Data.AppendList(A);

	GuiAdditionalDatabase	*B=new GuiAdditionalDatabase();
	B->TableName=/**/"MASTERDATA";
	B->FieldName=/**/"YSIZE";
	B->DefaultData.setValue((int)1000);
	Data.AppendList(B);
}
