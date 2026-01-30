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

#ifndef SHOWFLOWGRAPHDIALOG_H
#define SHOWFLOWGRAPHDIALOG_H

#include <QDialog>
#include "XColorDifference.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XServiceForLayers.h"

namespace Ui {
class SHowFlowGraphDialog;
}



class SHowFlowGraphDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
	ColorDifferenceItem	*Item;

	mtLineGraph		HLGraph;
	mtGStick		HGraphColMaster;
	mtGStick		HGraphColTarget;
	mtGStick		HGraphThresh;

	mtLineGraph		SLGraph;
	mtGStick		SGraphColMaster;
	mtGStick		SGraphColTarget;
	mtGStick		SGraphThresh;

	mtLineGraph		VLGraph;
	mtGStick		VGraphColMaster;
	mtGStick		VGraphColTarget;
	mtGStick		VGraphThresh;

	mtLineGraph		ELGraph;
	mtGStick		EGraphColMaster;
	mtGStick		EGraphColTarget;
	mtGStick		EGraphThresh;

public:
    explicit SHowFlowGraphDialog(LayersBase *base,ColorDifferenceItem *Item ,QWidget *parent = 0);
    ~SHowFlowGraphDialog();
    
private:
    Ui::SHowFlowGraphDialog *ui;

	virtual	void resizeEvent ( QResizeEvent * event )	override;
	void ShowGraph(void);
};

#endif // SHOWFLOWGRAPHDIALOG_H