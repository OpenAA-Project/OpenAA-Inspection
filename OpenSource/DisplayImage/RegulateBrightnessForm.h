/*
 * Copyright (C) 2021
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

#ifndef REGULATEBRIGHTNESSFORM_H
#define REGULATEBRIGHTNESSFORM_H

#include <QDialog>
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XDisplayImagePacket.h"
#include "XServiceForLayers.h"
#include "mtToolButtonColored.h"

class	HistgramListContainer;
class	AvrVarListByLayerContainer;

namespace Ui {
class RegulateBrightnessForm;
}

class RegulateBrightnessForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    QToolBar		LayerBar;
    int				LNumb;
    mtToolButtonColored		**LButtonList;

    mtLineGraph		LGraph;
    mtGStick		GraphCol;
    int				YMax;

public:
    explicit RegulateBrightnessForm(	IntList &EffectiveLayerList
                                        ,HistgramListContainer		&_HistDatas
                                        ,AvrVarListByLayerContainer	&_AvrDatas
                                        ,LayersBase *base
                                        ,QWidget *parent = 0);
    ~RegulateBrightnessForm();

    HistgramListContainer		HistDatas;
    AvrVarListByLayerContainer	AvrDatas;
    int		BlockSize;

private:
    Ui::RegulateBrightnessForm *ui;

    int	GetCurrentNo(void);

    void ShowData(void);
    void GetData(int No);
    int	LastLayer;

private slots:
    void	SlotLayerClicked();
    void on_pushButtonOk_clicked();
    void on_pushButtonCancel_clicked();
};

#endif // REGULATEBRIGHTNESSFORM_H