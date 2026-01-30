/*
 * Copyright (C) 2025
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

#ifndef CONFIRMPROPDOTCOLORMATCHINGFORM_H
#define CONFIRMPROPDOTCOLORMATCHINGFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XConfirmAlgorithm.h"
#include "XFlexArea.h"

namespace Ui {
class ConfirmPropDotColorMatchingForm;
}
class ConfirmForm;
class  ButtonShowConfirm;
class  DotColorMatchingThreshold;

class ConfirmPropDotColorMatchingForm : public ConfirmAlgorithm,public ServiceForLayers
{
    Q_OBJECT

    FlexArea	        NGShape;

public:
    explicit ConfirmPropDotColorMatchingForm(ConfirmForm *p ,QWidget *parent = 0);
    ~ConfirmPropDotColorMatchingForm();
    
    virtual	int		GetLibType(void)            override;
    virtual	QString	GetButtonName(void)         override;
    virtual	QWidget	*GetPropertyWidget(void)    override    {   return this;    }
    virtual	void	InitialShow(void)           override;
    virtual	void	SetDrawAttr(AlgorithmLibTypeWithAttrDataContainer &s)   override;
    virtual	void	AlgoMouseMove(int ux ,int uy)		    override;
    virtual	void	AlgoMouseLDownWithShift(int ux ,int uy) override;
    virtual	void	AlgoMouseRDown(int ux ,int uy)          override;
    virtual	void	CanvasSlotDrawEnd(FlexArea &Area)       override;
    virtual	void	CanvasSlotOnPaint(mtGraphicUnit	&ImagePanel,int page,QImage &Pnt)  override;
    virtual	void	SetProperty(void)           override;
    virtual	void	ForceDraw(void)             override;
    virtual	void	ShowConfirmItem(ConfirmItemList *Item)  override;

private slots:
    void on_EditBrightWidthBRL_valueChanged(int arg1);
    void on_EditBrightWidthBGL_valueChanged(int arg1);
    void on_EditBrightWidthBBL_valueChanged(int arg1);
    void on_EditBrightWidthBRH_valueChanged(int arg1);
    void on_EditBrightWidthBGH_valueChanged(int arg1);
    void on_EditBrightWidthBBH_valueChanged(int arg1);
    void on_EditRThrOffsetBL_valueChanged(int arg1);
    void on_EditGThrOffsetBL_valueChanged(int arg1);
    void on_EditBThrOffsetBL_valueChanged(int arg1);
    void on_EditRThrOffsetBH_valueChanged(int arg1);
    void on_EditGThrOffsetBH_valueChanged(int arg1);
    void on_EditBThrOffsetBH_valueChanged(int arg1);
    void on_EditOKDotB_valueChanged(int arg1);
    void on_doubleSpinBoxOKDotBMM_valueChanged(double arg1);
    void on_EditOKLengthB_valueChanged(int arg1);
    void on_doubleSpinBoxOKLengthBMM_valueChanged(double arg1);

    void on_EditBrightWidthNRL_valueChanged(int arg1);
    void on_EditBrightWidthNGL_valueChanged(int arg1);
    void on_EditBrightWidthNBL_valueChanged(int arg1);
    void on_EditBrightWidthNRH_valueChanged(int arg1);
    void on_EditBrightWidthNGH_valueChanged(int arg1);
    void on_EditBrightWidthNBH_valueChanged(int arg1);
    void on_EditRThrOffsetNL_valueChanged(int arg1);
    void on_EditGThrOffsetNL_valueChanged(int arg1);
    void on_EditBThrOffsetNL_valueChanged(int arg1);
    void on_EditRThrOffsetNH_valueChanged(int arg1);
    void on_EditGThrOffsetNH_valueChanged(int arg1);
    void on_EditBThrOffsetNH_valueChanged(int arg1);
    void on_EditOKDotN_valueChanged(int arg1);
    void on_doubleSpinBoxOKDotNMM_valueChanged(double arg1);
    void on_EditOKLengthN_valueChanged(int arg1);
    void on_doubleSpinBoxOKLengthNMM_valueChanged(double arg1);

    void on_checkBoxUseBackGround_clicked();
    void on_EditBackGroundOKDot_valueChanged(int arg1);
    void on_doubleSpinBoxBackGroundOKDotMM_valueChanged(double arg1);
    void on_EditBackGroundOKLength_valueChanged(int arg1);
    void on_doubleSpinBoxBackGroundOKLengthMM_valueChanged(double arg1);
    void on_EditAreaSearchX_valueChanged(int arg1);
    void on_doubleSpinBoxAreaSearchXMM_valueChanged(double arg1);
    void on_EditSelfSearch_valueChanged(int arg1);
    void on_doubleSpinBoxSelfSearchMM_valueChanged(double arg1);
    void on_EditAdjustBlack_valueChanged(int arg1);
    void on_EditAdjustWhite_valueChanged(int arg1);
    void on_EditMultiSpotDot_valueChanged(int arg1);
    void on_EditMultiSpotCount_valueChanged(int arg1);
    void on_checkBoxRedCheckMode_clicked();
    void on_EditRedHighRate_valueChanged(int arg1);
    void on_EditRedMinBrightness_valueChanged(int arg1);
    void on_EditRedGBMerginRate_valueChanged(int arg1);
    void on_EditRedGBMerginOffset_valueChanged(int arg1);
    void on_EditRedShrink_valueChanged(int arg1);
    void on_EditRedOKDot_valueChanged(int arg1);
    void on_doubleSpinBoxMultiSpotDotMM_valueChanged(double arg1);
    void on_doubleSpinBoxRedOKDotMM_valueChanged(double arg1);

private:
    Ui::ConfirmPropDotColorMatchingForm *ui;

    void    ShowThreshold(int LibID,DotColorMatchingThreshold *s);
    void    ShowItemData(void)  override;
    void    ShowResult(void)    override;
    void    GetThresholdFromWindow(DotColorMatchingThreshold *s);
};

#endif // CONFIRMPROPDOTCOLORMATCHINGFORM_H