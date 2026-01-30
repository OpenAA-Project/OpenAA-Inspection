/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */


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