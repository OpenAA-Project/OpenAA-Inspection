#include "GeneralLabelResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralLabel\GeneralLabel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralLabel.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"Label";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"General Label");
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
	return(new GeneralLabel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((GeneralLabel *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((GeneralLabel *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((GeneralLabel *)Instance)->BackColor;
	Data[3].Type				 =/**/"AlignLeft,AlignCenter";
	Data[3].VariableNameWithRoute=/**/"AlignAttr";
	Data[3].Pointer				 =&((GeneralLabel *)Instance)->AlignAttr;
	Data[4].Type				 =/**/"QFont";
	Data[4].VariableNameWithRoute=/**/"CFont";
	Data[4].Pointer				 =&((GeneralLabel *)Instance)->CFont;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GeneralLabel.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
GeneralLabel::GeneralLabel(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	AlignAttr=/**/"AlignLeft";
	Label.setParent(this);
	Label.move(0,0);
	Label.setWordWrap(true);
	Msg=/**/"Label";
	resize(600,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

GeneralLabel::~GeneralLabel(void)
{
}

void	GeneralLabel::Prepare(void)
{
	Label.setText(Msg);
	Label.setFont (CFont);
	if(AlignAttr==/**/"AlignLeft")
		Label.setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	else
		Label.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	ResizeAction();
}

void	GeneralLabel::ResizeAction(void)
{
	Label.resize(width(),height());
}
