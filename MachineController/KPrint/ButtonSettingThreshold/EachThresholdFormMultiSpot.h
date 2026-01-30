/*
 * Copyright (C) 2022
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

#ifndef EACHTHRESHOLDFORMMULTISPOT_H
#define EACHTHRESHOLDFORMMULTISPOT_H

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
class EachThresholdFormMultiSpot;
}

class ButtonSettingThresholdForm;


class EachThresholdFormMultiSpot:public EachThresholdCommon
                                ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	bool	OnChanging;
public:
    explicit EachThresholdFormMultiSpot(LayersBase *base ,ButtonSettingThresholdForm *p
										,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
										,QWidget *parent = 0);
    ~EachThresholdFormMultiSpot();

private slots:
    void on_horizontalSliderSIze_valueChanged(int value);
    void on_doubleSpinBoxSizeMM_valueChanged(double arg1);
    void on_spinBoxSize_valueChanged(int arg1);
    void on_horizontalSliderNGCount_valueChanged(int value);
    void on_spinBoxNGCount_valueChanged(int arg1);
    void on_PushButtonMarker_clicked();
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();

    void on_PushButtonShowWhole_clicked();

private:
    Ui::EachThresholdFormMultiSpot *ui;

	virtual	void	MouseLDoubleClick(int gx,int gy,int LevelID) override;
	void	ShowDataAfterMarker(void);
};

#endif // EACHTHRESHOLDFORMMULTISPOT_H