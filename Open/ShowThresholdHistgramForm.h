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

#ifndef SHOWTHRESHOLDHISTGRAMFORM_H
#define SHOWTHRESHOLDHISTGRAMFORM_H

#include <QWidget>
#include <QString>
#include "XServiceForLayers.h"
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "XHistgramByParam.h"

namespace Ui {
class ShowThresholdHistgramForm;
}

class ShowThresholdHistgramForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    HistStepClass	GraphData;
    double	ThresholdA,ThresholdB;

    mtLineGraph			LGraph;
    mtGStick			GraphHistgram;
    mtGStick			GraphThresh;

    double				Average;
    double				Dispersion;
    double				HistDiv;

    int		Phase;
    int		GlobalPage;
    int		Layer;
    int		ItemID;
    int		LibID;
    int		HistID;
    QString AlgoRoot;
    QString AlgoName;

public:
    explicit ShowThresholdHistgramForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowThresholdHistgramForm();

    bool	Initial(int Phase ,int GlobalPage ,int Layer ,int ItemID ,int HistID
                   ,const QString &AlgoRoot ,const QString &AlgoName);
    bool	Initial(int Phase ,int GlobalPage ,int Layer ,int HistID
                   ,const QString &AlgoRoot ,const QString &AlgoName);
    void	ShowCalculated(void);
    void	ShowGrah(void);
    void	SaveText(void);

signals:
    void	SignalClose();
private slots:
    void on_pushButtonCalc_clicked();
    void on_pushButtonCalcD_clicked();
    void on_pushButtonCalc2_clicked();
    void on_pushButtonCalcU_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonSetThreshold_clicked();
    void on_pushButtonClose_clicked();
    void	SlotLineGraphDClick(int X,int Y);
private:
    Ui::ShowThresholdHistgramForm *ui;
};

#endif // SHOWTHRESHOLDHISTGRAMFORM_H