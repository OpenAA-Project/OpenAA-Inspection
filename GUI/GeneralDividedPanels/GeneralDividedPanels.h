/*
 * Copyright (C) 2024
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

#ifndef GENERALDIVIDEDPANELS_H
#define GENERALDIVIDEDPANELS_H

#include "generaldividedpanels_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QThread>
#include <QSplitter>
#include "XServiceForLayers.h"

class	GeneralDividedPanels;

class	GDividedPanel : public GUIFormBase
{
	GeneralDividedPanels	*Parent;
	int	ID;
public:
	GDividedPanel(LayersBase *Base ,GeneralDividedPanels *p,int id ,QWidget *parent);
	~GDividedPanel(void);

	virtual	bool	IsShown(void);
};


class	GeneralDividedPanels : public GUIFormBase
{
	Q_OBJECT

	GDividedPanel	**Children;
	int			CountChildren;
	QSplitter	SplitterWidget;
public:
	int32	DividedCount;
	QString	Direction;
	int		CurrentMarkPanel;
	int		Mergin;
	bool	Movable;

	GeneralDividedPanels(LayersBase *Base ,QWidget *parent);
	~GeneralDividedPanels(void);

	virtual	void	Prepare(void)	override;

	virtual	int		GetChildCount()							override;
	virtual	GUIFormBase	*GetChild(int index)	const		override;
	virtual	GUIFormBase	*GetTopSurfaceWidget(int x ,int y)	override;

private slots:
	void	ResizeAction();

private:
	virtual	void	paintEvent ( QPaintEvent * event )	override;
};

#endif // GENERALDIVIDEDPANELS_H