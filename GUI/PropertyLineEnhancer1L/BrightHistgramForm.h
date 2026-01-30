/*
 * Copyright (C) 2017
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

#ifndef BRIGHTHISTGRAMFORM_H
#define BRIGHTHISTGRAMFORM_H

#include <QDialog>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
    class BrightHistgramForm;
}

class	LineEnhancer1LImagePanel;

class BrightHistgramForm : public QDialog
{
    Q_OBJECT

public:
    explicit BrightHistgramForm(FlexArea &area ,LineEnhancer1LImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent = 0);
    ~BrightHistgramForm();

	mtLineGraph						LGraph;
//	mtGLine							GraphColMaster[100];
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	LineEnhancer1LImagePanel		*ParentPanel;
	int								PickupL;
	int								PickupH;

	void	GetDataFromWindow(void);
	void	GetHistogramData(void);
	void	ShowThreshold(void);

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	Reflect(int PickupL ,int PickupH);

private slots:
    void on_ButtonReflect_clicked();
    void on_ButtonClose_clicked();
	void	SlotLineGraphDClick(int ,int );
	void on_EditPickupL_valueChanged(int arg1);
	void on_EditPickupH_valueChanged(int arg1);

private:
    Ui::BrightHistgramForm *ui;

	int	MaxY;
};

#endif // BRIGHTHISTGRAMFORM_H