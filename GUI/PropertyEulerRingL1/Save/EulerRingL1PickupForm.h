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

#ifndef EULERRINGL1PICKUPFORM_H
#define EULERRINGL1PICKUPFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
class EulerRingL1PickupForm;
}
class	EulerRingL1ImagePanel;

class EulerRingL1PickupForm : public QWidget
{
    Q_OBJECT

public:
    explicit EulerRingL1PickupForm(FlexArea &area ,EulerRingL1ImagePanel *parentPanel ,int pickupL,int pickupH,QWidget *parent = 0);
    ~EulerRingL1PickupForm();

	mtLineGraph						LGraph;
	mtGStick						GraphColMaster[100];
	mtGStick						GraphThresh;
	FlexArea						GlobalArea;
	EulerRingL1ImagePanel			*ParentPanel;
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
    Ui::EulerRingL1PickupForm *ui;

	int	MaxY;
};

#endif // EULERRINGL1PICKUPFORM_H