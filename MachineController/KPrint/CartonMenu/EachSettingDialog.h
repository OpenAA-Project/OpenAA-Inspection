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

#ifndef EACHSETTINGDIALOG_H
#define EACHSETTINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

namespace Ui {
class EachSettingDialog;
}
class	CartonMenuForm;

class EachSettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	friend	class CartonMenuForm;

    CartonMenuForm	*Parent;
	QTimer		TM;

public:
    explicit EachSettingDialog(LayersBase *Base ,CartonMenuForm *p,QWidget *parent = 0);
    ~EachSettingDialog();
    
private slots:
    void on_PushButtonSwitchPhase_clicked();
    void on_PushButtonMask_clicked();
    void on_PushButtonAlignment_clicked();
    void on_PushButtonInspection_clicked();
    void on_PushButtonBlade_clicked();
    void on_PushButtonAutoGenerate_clicked();
    void on_PushButtonSettingThresholdTop_clicked();
    void on_PushButtonBladeSettingThresholdBottom_clicked();
    void on_PushButtonClose_clicked();
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
	void	SlotTimeOut();
    void on_PushButtonColorDifference_clicked();
    void on_PushButtonMakeAverageImage_clicked();
    void on_PushButtonSettingExpose_clicked();
    void on_PushButtonBCode_clicked();
    void on_PushButtonMeasure_clicked();
    void on_PushButtonSettingThresholdMono_clicked();
    void on_PushButtonCalcFinalize_clicked();

    void on_PushButtonResetSlaves_clicked();

private:
    Ui::EachSettingDialog *ui;

	void	SetRunningGray(void);
};

#endif // EACHSETTINGDIALOG_H