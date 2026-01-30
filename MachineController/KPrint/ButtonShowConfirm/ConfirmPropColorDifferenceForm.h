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

#ifndef CONFIRMPROPCOLORDIFFERENCEFORM_H
#define CONFIRMPROPCOLORDIFFERENCEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XConfirmAlgorithm.h"
#include "XFlexArea.h"

namespace Ui {
class ConfirmPropColorDifferenceForm;
}
class ConfirmForm;
class  ButtonShowConfirm;
class  ColorDifferenceThreshold;

class ConfirmPropColorDifferenceForm : public ConfirmAlgorithm,public ServiceForLayers
{
    Q_OBJECT

    bool                OutputConstantlyInItem;
public:
    explicit ConfirmPropColorDifferenceForm(ConfirmForm *p ,QWidget *parent = 0);
    ~ConfirmPropColorDifferenceForm();
    
    virtual	int		GetLibType(void)            override;
    virtual	QString	GetButtonName(void)         override;
    virtual	QWidget	*GetPropertyWidget(void)    override    {   return this;    }
    virtual	void	InitialShow(void)           override;
    virtual	void	AlgoMouseLDownWithShift(int ux ,int uy) override;
    virtual	void	CanvasSlotDrawEnd(FlexArea &Area)       override;
    virtual	void	SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)   override;
    virtual	void	SetProperty(void)           override;
    virtual	void	ForceDraw(void)             override;
    virtual	void	ShowConfirmItem(ConfirmItemList *Item)  override;
private slots:
    void on_doubleSpinBoxColorDifferenceAdoptedRate_valueChanged(double arg1);
    void on_checkBoxColorDifferenceOutputConstantly_clicked();
    void on_comboBoxColorDifferenceJudgeMethod_currentIndexChanged(int index);
    void on_doubleSpinBoxColorDifferenceTHDeltaE_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedH_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedSL_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedSH_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedVL_valueChanged(double arg1);
    void on_doubleSpinBoxColorDifferencedVH_valueChanged(double arg1);

private:
    Ui::ConfirmPropColorDifferenceForm *ui;

    void    ShowThreshold(int LibID,ColorDifferenceThreshold *s);
    void    ShowItemData(void)  override;
    void    ShowResult(void)    override;
    void    GetThresholdFromWindow(ColorDifferenceThreshold *s);
};

#endif // CONFIRMPROPCOLORDIFFERENCEFORM_H