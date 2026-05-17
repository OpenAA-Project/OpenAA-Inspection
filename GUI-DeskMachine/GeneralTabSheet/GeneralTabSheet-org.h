/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralTabSheet\GeneralTabSheet.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALTABSHEET_H
#define GENERALTABSHEET_H

#include "generaltabsheet_global.h"
#include <QTabWidget>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	GeneralTabPage : public GUIFormBase
{
public:
	GeneralTabPage(LayersBase *Base ,QWidget *parent);
	~GeneralTabPage(void);
	
	QTranslator Translator;
	
	virtual void	Prepare(void)	override;
	virtual void	ResizeAction(void);
};

class	GeneralTabSheet : public GUIFormBase
{
	Q_OBJECT

	QTabWidget	MainTab;
	QColor		NGSizeColor;

public:
	QStringList	Msgs;
	QString	TabPosition;
	QColor	CharColor;
	QColor	BackColor;
	bool	TransparentBackColor;
	QColor	UnSelectTabColor;
	bool	TransparentUnSelectTabColor;
	QFont	CFont;
	QStringList	Passwords;

	GeneralTabSheet(LayersBase *Base ,QWidget *parent);
	~GeneralTabSheet(void);
	
	virtual void	Prepare(void)	override;
	virtual GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;
	virtual	int	GetChildCount()		override;
	virtual	GUIFormBase	*GetChild(int index)	override;
	virtual	void	SwapTab(QWidget *TabStack ,int index1 ,int index2)	override;

	void	SetNGSizeColor(QColor c)	{	NGSizeColor=c;	}
	void	ExecNormalColor();
	void	ExecNGSizeColor();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
	void	ResizeAction();
	void	TabCurrentChanged( int index );
};

#endif // GENERALTABSHEET_H
