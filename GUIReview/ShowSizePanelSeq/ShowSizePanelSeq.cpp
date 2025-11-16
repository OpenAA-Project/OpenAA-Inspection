#include "ShowSizePanelSeqResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowSizePanelSeq\ShowSizePanelSeq.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowSizePanelSeq.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ShowSizePanelSeqForm.h"
#include "XGUI.h"



static	char	*sRoot=/**/"Panel";
static	char	*sName=/**/"SizePanelSeq";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for setting X,Y,Z size");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ShowSizePanelSeqForm(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"LimitMaxLength";
	Data[0].Pointer				 =&((ShowSizePanelSeqForm *)Instance)->LimitMaxLength;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"LimitMaxWidth";
	Data[1].Pointer				 =&((ShowSizePanelSeqForm *)Instance)->LimitMaxWidth;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"LimitMaxHeight";
	Data[2].Pointer				 =&((ShowSizePanelSeqForm *)Instance)->LimitMaxHeight;

	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"SysRegisterNoLength";
	Data[3].Pointer				 =&((ShowSizePanelSeqForm *)Instance)->SysRegisterNoLength;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"SysRegisterNoWidth";
	Data[4].Pointer				 =&((ShowSizePanelSeqForm *)Instance)->SysRegisterNoWidth;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"SysRegisterNoHeight";
	Data[5].Pointer				 =&((ShowSizePanelSeqForm *)Instance)->SysRegisterNoHeight;
	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowSizePanelSeq.png")));
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase();
	A->TableName=/**/"MASTERDATA";
	A->FieldName=/**/"SIZELENGTH";
	A->DefaultData.setValue((int)1000);
	Data.AppendList(A);

	GuiAdditionalDatabase	*B=new GuiAdditionalDatabase();
	B->TableName=/**/"MASTERDATA";
	B->FieldName=/**/"SIZEWIDTH";
	B->DefaultData.setValue((int)1000);
	Data.AppendList(B);

	GuiAdditionalDatabase	*C=new GuiAdditionalDatabase();
	C->TableName=/**/"MASTERDATA";
	C->FieldName=/**/"SIZEHEIGHT";
	C->DefaultData.setValue((int)1000);
	Data.AppendList(C);
}
