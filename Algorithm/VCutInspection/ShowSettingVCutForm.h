/*
 * Copyright (C) 2019
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

#ifndef SHOWSETTINGVCUTFORM_H
#define SHOWSETTINGVCUTFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class ShowSettingVCutForm;
}

class ShowSettingVCutForm;

class	DisplaySimPanelVCutInspection	: public DisplaySimPanel
{
	ShowSettingVCutForm	*ParentWidget;
public:
	DisplaySimPanelVCutInspection(LayersBase *base ,ShowSettingVCutForm *parentw ,QWidget *parent = 0);

	virtual	void	DrawOther(QPainter &Pnt);
};

class ShowSettingVCutForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit ShowSettingVCutForm(LayersBase *Base,QWidget *parent = 0);
    ~ShowSettingVCutForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;
	bool	ModeShowItem;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();
    void on_toolButtonSimShowItem_clicked();
    void on_toolButtonSimShowNGMark_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_EditThresholdLevel_valueChanged(int arg1);
    void on_EditThresholdShift_valueChanged(int arg1);
    void on_EditThresholdLength_valueChanged(int arg1);
    void on_EditExpandGenMask_valueChanged(int arg1);
    void on_checkBoxGenDynamicMask_clicked();

    void on_EditThresholdLevel_valueChanged(double arg1);

private:
    Ui::ShowSettingVCutForm *ui;

	DisplaySimPanelVCutInspection		SimPanel;
	void Calc(void);
};

#endif // SHOWSETTINGVCUTFORM_H