/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowAlignmentResult\ShowAlignmentResult.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowAlignmentResult.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ShowAlignmentResultForm.h"
#include "XGUI.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"ShowAlignmentResult";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Panel for alignment result");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqAlignmentResult			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAlignmentResult			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdReqAllAlignmentArea			(Base, QString(sRoot), QString(sName));
	(*Base)=new GUICmdAckAllAlignmentArea			(Base, QString(sRoot), QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowAlignmentResultForm(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"RegDxNo";
	Data[0].Pointer				 =&((ShowAlignmentResultForm *)Instance)->RegDxNo;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"RegDyNo";
	Data[1].Pointer				 =&((ShowAlignmentResultForm *)Instance)->RegDyNo;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"RegThetaNo";
	Data[2].Pointer				 =&((ShowAlignmentResultForm *)Instance)->RegThetaNo;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowAlignmentResult.png")));
}
