#include "EditRemainTimeFormResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowSumTimer\ShowSumTimer.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowSumTimer.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ShowSumTimerForm.h"
#include "XGUI.h"

static	const	char	*sRoot=/**/"Panel";
static	const	char	*sName=/**/"ShowSumTimer";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Sum time operation and view");
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
	return(new ShowSumTimerForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<18)return -1;

	int n = 0;

	Data[n].Type = /**/"QString";
	Data[n].VariableNameWithRoute=/**/"TitleName";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->TitleName;

	n++;
	
	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"ioCtrlRegNo";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->TimerControlIONumber;

	n++;
	
	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"ioProgressRegNo";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->TimerProgressIONumber;

	n++;
	
	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"ioFuncEndIORegNo";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->TimerFuncEndIONumber;

	n++;

	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"Hour";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->MaxTime_Hour;

	n++;

	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"Minuite";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->MaxTime_Minuite;

	n++;

	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"Second";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->MaxTime_Second;

	n++;

	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"MiliSecond";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->MaxTime_MiliSec;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"isIncreaseProgress";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isIncreaseProgress;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"isIncreaseTime";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isIncreaseTime;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"ViewTitleLabel";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isViewTitleLabel;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"ViewResetButton";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isViewResetButton;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"ViewTimeLabel";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isViewTimeLabel;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"ViewProgressBar";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isViewProgressBar;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"SaveFileEnable";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isSaveToFile;

	n++;

	Data[n].Type = /**/"QString";
	Data[n].VariableNameWithRoute=/**/"ViewTimeFormat";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->ViewStringFormat;

	n++;

	Data[n].Type = /**/"int32";
	Data[n].VariableNameWithRoute=/**/"UpdateDuration";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->UpdateDuration;

	n++;

	Data[n].Type = /**/"QFont";
	Data[n].VariableNameWithRoute=/**/"TitleFont";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->TitleFont;

	n++;

	Data[n].Type = /**/"QFont";
	Data[n].VariableNameWithRoute=/**/"TimeFont";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->TimeFont;

	n++;

	Data[n].Type = /**/"bool";
	Data[n].VariableNameWithRoute=/**/"TimeEditEnable";
	Data[n].Pointer				 =&((ShowSumTimerForm *)Instance)->isTimeEditEnable;

	n++;

	return(n);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowSumTimer.png")));
}

//DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
//{
//	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase();
//	A->TableName="MASTERDATA";
//	A->FieldName="MACOFFSET";
//	A->DefaultData.setValue((int)0);
//	Data.AppendList(A);
//}
