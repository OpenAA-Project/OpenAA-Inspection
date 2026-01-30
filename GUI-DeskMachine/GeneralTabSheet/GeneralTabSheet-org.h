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