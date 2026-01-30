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

#ifndef GRAPHTRENDKIDAFORM_H
#define GRAPHTRENDKIDAFORM_H

#include "XGUIFormBase.h"
#include "mtGraph.h"
#include "mtLineGraph.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XServiceForLayers.h"

namespace Ui {
class GraphTrendKidaForm;
}

class	ShowPrintTotalBladeForm;
class	EasyPropertyDentMeasureForm;
class	EasyPropertyMeasureForm;
class	GraphTrendKidaForm;
class	BladeLogForm;

#define	MaxCountGraphLine	10


class	TrendGraphList: public mtLineGraph , public ServiceForLayers
{
	friend class GraphTrendKidaForm;

	GraphTrendKidaForm	*Parent;
	mtGLine			GraphData;
	mtGLine			ThresholdL;
	mtGLine			ThresholdH;
public:
	EachMaster	*Machine;
	int		Phase;
	int		Page;
	int		MeasureNo;
	int		ItemID;

	int			LibID;
	int			UniqueID;
	int			IndexInMachine;
	int			Index;
	int			StartIndex;
	QColor		ColorData;
	QColor		ColorThreshold;

	TrendGraphList(int index,GraphTrendKidaForm *p);
	
	void	Draw(void);
private slots:
private:
};


class GraphTrendKidaForm : public GUIFormBase
{
    Q_OBJECT
    
	friend class	TrendGraphList;

public:
	ShowPrintTotalBladeForm		*ShowPrintTotalBladePointer;
	EasyPropertyDentMeasureForm	*EasyPropertyDentMeasurePointer[10];
	EasyPropertyMeasureForm		*EasyPropertyMeasurePointer[10];

public:
	QColor		ColorData[10];
	int32		MaxCount;
	TrendGraphList	*TrendGraphDim[MaxCountGraphLine];
	int			CountGraphLine;
	BladeLogForm	*BladeLog;
	int32		SlaveNo;

    explicit GraphTrendKidaForm(LayersBase *Base ,QWidget *parent = 0);
    ~GraphTrendKidaForm();
    
	virtual	void	Prepare(void) override;
	virtual void	ReadyParam(void) override;
	virtual void	StartLot(void)override;
private:
    Ui::GraphTrendKidaForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	void	ShowGraph(void);
	void	ClearGraph(void);
	void	SetBladeList(EachMaster *M);
private slots:
	void	ResizeAction();
    void on_listWidget_clicked(const QModelIndex &index);
	void on_pushButtonShowLog_clicked();
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
};

#endif // GRAPHTRENDKIDAFORM_H