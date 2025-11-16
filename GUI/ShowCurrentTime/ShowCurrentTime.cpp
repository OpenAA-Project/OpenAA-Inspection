/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ShowCurrentTime\ShowCurrentTime.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ShowCurrentTime.h"
#include <QFile>
#include <QFileDialog>
#include <QColor>
#include <QPalette>
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"

const	char	*sRoot=/**/"General";
const	char	*sName=/**/"ShowCurrentTime";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show current time");
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
	return(new ShowCurrentTime(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"CharColor";
	Data[0].Pointer				 =&((ShowCurrentTime *)Instance)->CharColor;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"BackColor";
	Data[1].Pointer				 =&((ShowCurrentTime *)Instance)->BackColor;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"CFont";
	Data[2].Pointer				 =&((ShowCurrentTime *)Instance)->CFont;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowCurrentTime.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//=======================================================================================

ShowCurrentTime::ShowCurrentTime(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	CharColor	=Qt::black;
	BackColor	=Qt::lightGray;

	MessageTime.setParent(this);
	IdleCount=0;
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()),Qt::QueuedConnection);
}

void	ShowCurrentTime::Prepare(void)
{
	MessageTime.setFont(CFont);
	QPalette	P=MessageTime.palette();
	P.setColor(QPalette::Text,CharColor);
	P.setColor(QPalette::Window,BackColor);
	MessageTime.setPalette(P);
	MessageTime.setWordWrap(true);
	MessageTime.setAutoFillBackground(false);
}

void	ShowCurrentTime::ShowMessage(void)
{
	QString	s=QDateTime::currentDateTime().toString(/**/"yyyy/MM/dd hh:mm:ss");
	MessageTime.setText(s);
}

void	ShowCurrentTime::ResizeAction()
{
	MessageTime.setGeometry(0,0,width(),height());
}

bool ShowCurrentTime::OnIdle(void)
{
	IdleCount++;
	if(IdleCount>100){
		IdleCount=0;
		ShowMessage();
	}
	return true;
}
