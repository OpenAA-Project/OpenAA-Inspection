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

#ifndef REGISTCOLORLIBFORM_H
#define REGISTCOLORLIBFORM_H

#include <QWidget>
#include "ShowRGBSamples.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XServiceForLayers.h"

namespace Ui {
class RegistColorLibForm;
}
class	RGBStock;

class RegistColorLibForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    ShowRGBSamples		RGBPanel;
    SelectColorSample	RegistPanel;
    ShowRGBSpace		ColorPanel;
public:
    explicit RegistColorLibForm(RGBStock *data ,LayersBase *Base,QWidget *parent = 0);
    ~RegistColorLibForm();
    
signals:
    void	SignalClose(void);

private slots:
    void on_pushButtonClose_clicked();
    void	SlotSelectCData();
    void	SlotBeforeSave();

private:
    Ui::RegistColorLibForm *ui;
};

#endif // REGISTCOLORLIBFORM_H