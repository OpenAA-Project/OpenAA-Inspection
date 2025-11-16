/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowThresholdSlideBar\ShowThresholdSlideBar.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowThresholdSlideBarForm.h"
#include <QFile>
#include <QFileDialog>
#include "XGeneralFunc.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"ShowThresholdSlideBar";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show threshold slide bar");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqThresholdSlider(Base,sRoot,sName);
	(*Base)=new GUICmdAckThresholdSlider(Base,sRoot,sName);
	(*Base)=new GUICmdSetThresholdSlider(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowThresholdSlideBarForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<9)
		return(-1);

	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Title";
	Data[0].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->Title;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"AlgoDLLRoot";
	Data[1].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->AlgoDLLRoot;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"AlgoDLLName";
	Data[2].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->AlgoDLLName;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"Layer";
	Data[3].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->Layer;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"LibID";
	Data[4].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->LibID;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"MemberID";
	Data[5].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->MemberID;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"MinimumValue";
	Data[6].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->MinimumValue;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"MaximumValue";
	Data[7].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->MaximumValue;
	Data[8].Type				 =/**/"None,D1,D2,D3";
	Data[8].VariableNameWithRoute=/**/"DisplayUnitStr";
	Data[8].Pointer				 =&((ShowThresholdSlideBarForm *)Instance)->DisplayUnitStr;
	
	return(9);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowThresholdSlideBar.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
