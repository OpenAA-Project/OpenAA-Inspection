/*
 * Copyright (C) 2023
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

#ifndef CONFIRMPROPALIGNMENTFORM_H
#define CONFIRMPROPALIGNMENTFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XConfirmAlgorithm.h"

namespace Ui {
class ConfirmPropAlignmentForm;
}

class ConfirmForm;
class  ButtonShowConfirm;
class  AlignmentAreaListContainer;
class  AlignmentMarkListContainer;
class  AlignmentLargeThreshold;

class ConfirmPropAlignmentForm : public ConfirmAlgorithm,public ServiceForLayers
{
    Q_OBJECT
		
    AlignmentAreaListContainer      *AreaListInPage;
    AlignmentMarkListContainer      *MarkListInArea;

public:
    explicit ConfirmPropAlignmentForm(ConfirmForm *p ,QWidget *parent = 0);
    ~ConfirmPropAlignmentForm();
    
    virtual	int		GetLibType(void)            override;
    virtual	QString	GetButtonName(void)         override;
    virtual	QWidget	*GetPropertyWidget(void)    override    {   return this;    }
    virtual	void	InitialShow(void)           override;
    virtual	void	SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)   override;
    virtual	void    AlgoMouseMove(int ux ,int uy)   override;
    virtual	void	SetProperty(void)               override;
    virtual	void	ForceDraw(void)                 override;
    virtual	void	ShowConfirmItem(ConfirmItemList *Item)  override;
private slots:
    void on_toolButtonAlignmentLargeArea_clicked();
    void on_toolButtonAlignmentLargeMark_clicked();
    void on_listWidgetAlignmentLargeArea_itemSelectionChanged();
    void on_tableWidgetAlignmentLargeMark_itemSelectionChanged();
    void on_radioButtonAlignmentLargePriorityLGlobal_clicked();
    void on_radioButtonAlignmentLargePriorityHigh_clicked();
    void on_radioButtonAlignmentLargePriorityMiddle_clicked();
    void on_radioButtonAlignmentLargePriorityLow_clicked();
    void on_spinBoxAlignmentLargeSearchDot_valueChanged(int arg1);
    void on_doubleSpinBoxAlignmentLargeSearchDotUnit_valueChanged(double arg1);
    void on_spinBoxAlignmentLargeSearchDotY_valueChanged(int arg1);
    void on_doubleSpinBoxAlignmentLargeSearchDotUnitY_valueChanged(double arg1);
    void on_spinBoxAlignmentLargeSearchDot2_valueChanged(int arg1);
    void on_doubleSpinBoxAlignmentLargeSearchDot2Unit_valueChanged(double arg1);
    void on_spinBoxAlignmentLargeSearchDot2Y_valueChanged(int arg1);
    void on_doubleSpinBoxAlignmentLargeSearchDot2UnitY_valueChanged(double arg1);
    void on_spinBoxAlignmentLargeMaxCountHLine_valueChanged(int arg1);
    void on_spinBoxAlignmentLargeMaxCountVLine_valueChanged(int arg1);
	void on_checkBoxAlignmentLargeJudgeWithBrDif_clicked();
    void on_tableWidgetAlignmentLargeMark_doubleClicked(const QModelIndex &index);
    void on_listWidgetAlignmentLargeArea_clicked(const QModelIndex &index);
    void on_tableWidgetAlignmentLargeMark_clicked(const QModelIndex &index);

private:
    Ui::ConfirmPropAlignmentForm *ui;

    void    GetThresholdFromWindow(AlignmentLargeThreshold *s);
    void    ShowMarkList(int AreaRow);
};

#endif // CONFIRMPROPALIGNMENTFORM_H