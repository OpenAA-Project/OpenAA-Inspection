/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralTabWizard\GeneralTabWizard.h
** Author : YYYYYYYYYY
****************************************************************************-**/

#ifndef GENERALTABWIZARD_H
#define GENERALTABWIZARD_H

#include "generaltabwizard_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include <QStackedWidget>
#include <QTranslator>

class	GTWToolButtonColoredForTab;
class	SignalOperandInt;
class	GeneralTabWizard;

class	GeneralTabWizardPage : public GUIFormBase
{
	GeneralTabWizard	*Parent;
public:
	bool3	ShowingOn;
	int	ID;
	GeneralTabWizardPage(LayersBase *Base ,GeneralTabWizard *p ,QWidget *parent);
	~GeneralTabWizardPage(void);

	virtual void	Prepare(void)		override;
	void	ResizeAction(void);
	virtual	bool	IsShown(void)		override;
};
class	GeneralTabWizardCommon : public GUIFormBase
{
public:
	GeneralTabWizardCommon(LayersBase *Base ,QWidget *parent);
	~GeneralTabWizardCommon(void);
	virtual void	Prepare(void)		override;
	virtual void	ResizeAction(void);
};

class	GTWToolButtonColoredForTab : public mtToolButtonColored
{
	Q_OBJECT
public:
	int		ID;
	GTWToolButtonColoredForTab(QWidget *parent = 0);

signals:
	void	IDClicked(int id);

protected slots:
	virtual	void	SlotClicked();
	void SlotToggled ( bool checked );
};

class	GTWToolButtonStyledTab : public QToolButton
{
	Q_OBJECT
public:
	int		ID;
	GTWToolButtonStyledTab(QWidget *parent = 0);

signals:
	void	IDClicked(int id);

protected slots:
	virtual	void	SlotClicked();
	void SlotToggled ( bool checked );
};

class	GeneralTabWizard : public GUIFormBase
{
	Q_OBJECT

	QStackedWidget						MainTab;
	QList<GTWToolButtonColoredForTab *>	Buttons;
	QList<GTWToolButtonStyledTab *>		ButtonsStyle;
	QStackedWidget						Common;
	int									LastID;
	SignalOperandInt	*oPageNumber;
public:
	QStringList	Msgs;
	QString		TabPosition;
	QFont		ButtonFont;
	QColor		UncheckedColor;
	QColor		ActiveColor;
	QColor		CheckedColor;
	QColor		ArrowColor;
	int32		CommonWidth;
	bool		FromSync;
	QString		ButtonStyle;
	int32		RegNo;

	GeneralTabWizard(LayersBase *Base ,QWidget *parent);
	~GeneralTabWizard(void);
	
	virtual void	Prepare(void)	override;
	virtual GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;
	virtual GUIFormBase	*GetTopTabWizardPage(void)	;
	virtual	int	GetChildCount()								override;
	virtual	GUIFormBase	*GetChild(int index)	const		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	UncheckAll(GTWToolButtonColoredForTab *excludedItem);
	void	UncheckAll(GTWToolButtonStyledTab *excludedItem);
	virtual	void	SwapTab(QWidget *TabStack ,int index1 ,int index2)	override;

	void	ClickTab(int id);
	virtual	void	showEvent ( QShowEvent * event )	override;
	virtual	QWidgetList	GetTabChildren(void)			override;
	int		GetCountOfButtonDown(void);
	void	CommandShowPage(const QString &PageName);

	virtual	void	RxSync(QByteArray &f)	override;

protected:
	virtual	void	RemovedTabSheet(QWidget *TabRoot ,QWidget *RemovedPage)	override;
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)				override;
private slots:
	void	ResizeAction();
	void	SlotIDClicked(int id);
	void	OperandChanged();
private:
	void	DrawDownArrow(QPainter &pnt ,float size ,int PosX, int PosY);
	virtual	void paintEvent ( QPaintEvent * event )	override;
};

class	CmdNextForWizard : public GUIDirectMessage
{
public:
	CmdNextForWizard(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdChangeTab : public GUICmdPacketBase
{
public:
	int		ID;
	QString	TabName;

	GUICmdChangeTab(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // GENERALTABWIZARD_H
