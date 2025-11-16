/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XLogo.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XLOGO_H)
#define	XLOGO_H

#include "NList.h"
#include <QString>
#include "XTypeDef.h"

class	LayersBase;
class	QWidget;
class	GUIFormBase;

class	LogoLeaf : public NPList<LogoLeaf>
{
public:
	QString	DLLRoot;
	QString	DLLName;
	QString	Name;
	QString	ClassName;
	int		XPos;
	int		YPos;
	QString	FileName;

	LogoLeaf(void){}

	bool	Analyze(QString &LineData);
	void	Execute(QWidget *W);
};

class	LogoStocker : public NPListPack<LogoLeaf>
{
public:
	LogoStocker(void){}

	bool	LoadFromLogoListFile(LayersBase *base);

	void	ExecuteInGUIForm(GUIFormBase *W ,const QString &dllroot ,const QString &dllname);
	void	ExecuteInQWidget(QWidget *W ,const char *_typename ,const QString &dllroot ,const QString &dllname);
};


#endif