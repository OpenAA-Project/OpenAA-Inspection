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

#ifndef ADJUSTALIGNMENTLARGEFORM_H
#define ADJUSTALIGNMENTLARGEFORM_H

#include <QDialog>
#include <QWidget>
#include <QToolBar>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XAlignmentLarge.h"

namespace Ui {
class AdjustAlignmentLargeForm;
}

class AdjustAlignmentLargeForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    
    int HistgramPage;

public:
    explicit AdjustAlignmentLargeForm(LayersBase *Base,QWidget *parent = 0);
    ~AdjustAlignmentLargeForm();
    
	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonHistogramX_clicked();
    void on_pushButtonHistogramY_clicked();
    void on_spinBoxSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDotUnit_valueChanged(double arg1);
    void on_spinBoxSearchDotY_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDotUnitY_valueChanged(double arg1);
    void on_spinBoxSearchDot2_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDot2Unit_valueChanged(double arg1);
    void on_spinBoxSearchDot2Y_valueChanged(int arg1);
    void on_doubleSpinBoxSearchDot2UnitY_valueChanged(double arg1);

    void on_listWidgetHistList_doubleClicked(const QModelIndex &index);

private:
    Ui::AdjustAlignmentLargeForm *ui;
	bool	OnChanging;
};

#endif // ADJUSTALIGNMENTLARGEFORM_H