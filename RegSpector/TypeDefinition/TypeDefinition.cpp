/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\RegSpector\TypeDefinition\TypeDefinition.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "TypeDefinition.h"
#include <QFile>
#include <QBuffer>
#include <QIcon>
#include <QPixmap>
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "XGUIPacketForDLL.h"

static	const	char	*sRoot=/**/"RegSpector";
static	const	char	*sName=/**/"TypeDefinition";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Define AppType");
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
	return(new TypeDefinition(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<8)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"ApplicationHashTag";
	Data[0].Pointer				 =&((TypeDefinition *)Instance)->ApplicationHashTag;
	Data[1].Type				 =/**/"QString";
	Data[1].VariableNameWithRoute=/**/"ApplicationName";
	Data[1].Pointer				 =&((TypeDefinition *)Instance)->ApplicationName;
	Data[2].Type				 =/**/"QString";
	Data[2].VariableNameWithRoute=/**/"ServerAddress";
	Data[2].Pointer				 =&((TypeDefinition *)Instance)->ServerAddress;

	Data[3].Type				 =/**/"QString";
	Data[3].VariableNameWithRoute=/**/"Msg";
	Data[3].Pointer				 =&((TypeDefinition *)Instance)->Msg;
	Data[3].Translatable		 =true;
	Data[4].Type				 =/**/"QColor";
	Data[4].VariableNameWithRoute=/**/"CharColor";
	Data[4].Pointer				 =&((TypeDefinition *)Instance)->CharColor;
	Data[5].Type				 =/**/"QColor";
	Data[5].VariableNameWithRoute=/**/"NormalColor";
	Data[5].Pointer				 =&((TypeDefinition *)Instance)->NormalColor;
	Data[6].Type				 =/**/"QColor";
	Data[6].VariableNameWithRoute=/**/"PushedColor";
	Data[6].Pointer				 =&((TypeDefinition *)Instance)->PushedColor;	
	Data[7].Type				 =/**/"QFont";
	Data[7].VariableNameWithRoute=/**/"CFont";
	Data[7].Pointer				 =&((TypeDefinition *)Instance)->CFont;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/TypeDefinition.png")));
}

