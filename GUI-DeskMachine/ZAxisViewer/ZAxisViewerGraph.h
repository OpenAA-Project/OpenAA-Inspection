/*
 * Copyright (C) 2022
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

#ifndef ZAXISVIEWERGRAPH_H
#define ZAXISVIEWERGRAPH_H

#include "ui_ZAxisViewerGraph.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

class ZAxisViewerGraph : public GUIFormBase
{
	Q_OBJECT

	mtLineGraph			LGraph;
	mtGStick			GraphPower;
	mtGStick			GraphLine;
public:
	int		ID;
	int		Page;
	QColor	PowerColor;
	QColor	LineColor;

	ZAxisViewerGraph(LayersBase *Base ,QWidget *parent = 0);
	~ZAxisViewerGraph();

	virtual void	ShowInPlayer(int64 shownInspectionID)		override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::ZAxisViewerGraphClass ui;
};

//===========================================================================

class	GUICmdReqItemResult: public GUICmdPacketBase
{
public:
	int		AxisID;
	int		Layer;

	GUICmdReqItemResult(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemResult: public GUICmdPacketBase
{
public:
	double	*ResultTable;
	int		ResultCount;

	GUICmdAckItemResult(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUICmdAckItemResult(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // ZAXISVIEWERGRAPH_H