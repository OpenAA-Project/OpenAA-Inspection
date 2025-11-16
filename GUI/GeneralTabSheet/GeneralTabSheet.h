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

class	GeneralTabSheet;

class	GeneralTabPage : public GUIFormBase
{
	GeneralTabSheet	*Parent;
public:
	GeneralTabPage(LayersBase *Base ,GeneralTabSheet *p,QWidget *parent);
	~GeneralTabPage(void);
	QTranslator Translator;
	virtual void	Prepare(void)		override;
	virtual void	ResizeAction(void);
	virtual	bool	IsShown(void)		override;
};

class	GeneralTabSheet : public GUIFormBase
{
	Q_OBJECT

	QTabWidget	MainTab;

public:
	QStringList	Msgs;
	QString		TabPosition;
	int32		StartTop;
	QFont		Font;

	GeneralTabSheet(LayersBase *Base ,QWidget *parent);
	~GeneralTabSheet(void);
	virtual void	Prepare(void)		override;
	virtual GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;
	virtual GUIFormBase	*GetTopTabWizardPage(void);
	virtual	int	GetChildCount()								override;
	virtual	GUIFormBase	*GetChild(int index)		const	override;
	virtual	void	SwapTab(QWidget *TabStack ,int index1 ,int index2)	override;

	virtual	void	showEvent ( QShowEvent * event )	override;
	void	CommandShowPage(const QString &PageName);
	virtual	QWidgetList	GetTabChildren(void)	override;
protected:
	virtual	void	RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
private slots:
	void	ResizeAction();
	void	TabCurrentChanged( int index );
};

#endif // GENERALTABSHEET_H
