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

#ifndef EACHTHRESHOLDFORMBLADE_H
#define EACHTHRESHOLDFORMBLADE_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XPanelShowResultImage.h"
#include "XEachThresholdCommon.h"
#include "XPasswordQWidget.h"

namespace Ui {
class EachThresholdFormBlade;
}
class ButtonSettingThresholdForm;

class EachThresholdFormBlade:public EachThresholdCommon
                            ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	bool	OnChanging;
public:
    explicit EachThresholdFormBlade(LayersBase *base ,ButtonSettingThresholdForm *p,QWidget *parent = 0);
    ~EachThresholdFormBlade();

    void	ShowDataAfterMarker(void);
private slots:
    void on_horizontalSliderBRL_valueChanged(int value);
    void on_horizontalSliderBRH_valueChanged(int value);
    void on_spinBoxBRL_valueChanged(int arg1);
    void on_spinBoxBRH_valueChanged(int arg1);
    void on_horizontalSliderSizeB_valueChanged(int value);
    void on_doubleSpinBoxSizeBMM_valueChanged(double arg1);

    void on_horizontalSliderNRL_valueChanged(int value);
    void on_horizontalSliderNRH_valueChanged(int value);
    void on_spinBoxNRL_valueChanged(int arg1);
    void on_spinBoxNRH_valueChanged(int arg1);
    void on_horizontalSliderSizeN_valueChanged(int value);
    void on_doubleSpinBoxSizeNMM_valueChanged(double arg1);

    void on_spinBoxSizeB_valueChanged(int arg1);
    void on_horizontalSliderLengthB_valueChanged(int value);
    void on_doubleSpinBoxLengthBMM_valueChanged(double arg1);
    void on_spinBoxLengthB_valueChanged(int arg1);

    void on_spinBoxSizeN_valueChanged(int arg1);
    void on_horizontalSliderLengthN_valueChanged(int value);
    void on_doubleSpinBoxLengthNMM_valueChanged(double arg1);
    void on_spinBoxLengthN_valueChanged(int arg1);

    void on_toolButtonSet_clicked();
    void on_toolButtonOKSize_clicked();
    void on_toolButtonCancel_clicked();
    void on_PushButtonMarker_clicked();
    void on_PushButtonShowWhole_clicked();

    void on_toolButtonBroad_clicked();
    void on_toolButtonNarrow_clicked();

private:
    Ui::EachThresholdFormBlade *ui;
};

#endif // EACHTHRESHOLDFORMBLADE_H