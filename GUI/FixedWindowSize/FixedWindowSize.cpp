#include "FixedWindowSizeResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\FixedWindowSize\FixedWindowSize.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "FixedWindowSize.h"
#include "XDLLOnly.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XDisplayImage.h"

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"FixedWindowSize";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Fix Window Size");
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
	return(new FixedWindowSize(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"PosLeft";
	Data[0].Pointer				 =&((FixedWindowSize *)Instance)->PosLeft;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"PosTop";
	Data[1].Pointer				 =&((FixedWindowSize *)Instance)->PosTop;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"PosRight";
	Data[2].Pointer				 =&((FixedWindowSize *)Instance)->PosRight;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"PosBottom";
	Data[3].Pointer				 =&((FixedWindowSize *)Instance)->PosBottom;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/FixedWindowSize.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
FixedWindowSize::FixedWindowSize(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	PosLeft		=0;
	PosTop		=0;
	PosRight	=1000;
	PosBottom	=1000;
}

FixedWindowSize::~FixedWindowSize(void)
{
}

void	FixedWindowSize::Prepare(void)
{
	if(GetEditMode()==false){
		GUIFormBase	*r=GetTopParent();
		if(r==NULL)
			return;
		int	W=PosRight-PosLeft;
		int	H=PosBottom-PosTop;
		r->setGeometry(PosLeft,PosTop,W,H);
		r->setMaximumSize(W,H);
		r->setMinimumSize(W,H);
		//r->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | r->windowFlags());
	}
}
