/*
 * Copyright (C) 2026
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

#ifndef SETTHRESHOLDFORM_H
#define SETTHRESHOLDFORM_H

#include <QWidget>
#include <QComboBox>
#include <QCheckBox>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"

namespace Ui {
class SetThresholdForm;
}

class   BCRGradeListContainer;
class   BCRInspectionThreshold;

class SetThresholdForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

    bool	    OnChanging;

public:
    explicit SetThresholdForm(LayersBase *Base,QWidget *parent = 0);
    ~SetThresholdForm();
 	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;   
private slots:
    void on_pushButtonSet_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();
    void on_comboBoxCheckType_currentIndexChanged(int index);
    void on_doubleSpinBoxQuilityGrade_valueChanged(double arg1);
    void on_checkBoxBarcodeIsOnlyDigit_clicked(bool checked);
    void on_tableWidgetBarcodeType_cellChanged(int row, int column);
    void on_tableWidgetBarcodeOrientation_cellChanged(int row, int column);
    void on_tableWidgetGradeList_cellChanged(int row, int column);

private:
    Ui::SetThresholdForm *ui;

    void	SetDataToWindow(const BCRInspectionThreshold *R);
    void    ShowGradeList(BCRGradeListContainer &List);
    void    LoadGradeListFromWindow(BCRGradeListContainer &List);

    void    CalcResult(void);
};

#endif // SETTHRESHOLDFORM_H