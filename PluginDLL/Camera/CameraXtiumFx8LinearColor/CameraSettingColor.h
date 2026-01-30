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



#ifndef CAMERASETTINGCOLOR_H
#define CAMERASETTINGCOLOR_H

#include <QDialog>
#include "ui_CameraSettingColor.h"
#include "XCameraCommon.h"

class	CameraXtiumFx8Color;
class	featureCtrl;

class CameraSettingColor : public QDialog
{
    Q_OBJECT

	CameraXtiumFx8Color	*Cam;
	featureCtrl		*Feature;

public:
    CameraSettingColor(CameraXtiumFx8Color *s ,featureCtrl *f ,QWidget *parent = 0);
    ~CameraSettingColor();

	void moveData(void);

private:
    Ui::CameraSettingColorClass ui;
	enum GraphType{
			Default,
			StraightLine,
			HightPass,
			LowPass,
			UpDownPass,
			DownUpPass,
			ShigmoidCurve,
			Logarithm
	};
//	GraphType GraphMode;
	enum ColorType{
			Red,
			Green,
			Blue
	};
	//Red
	int RedFirstPoint;
	int RedSecondPoint;
	int RedFirstX;
	int RedFirstY;
	int RedSecondX;
	int RedSecondY;
	//Green
	int GreenFirstPoint;
	int GreenSecondPoint;
	int GreenFirstX;
	int GreenFirstY;
	int GreenSecondX;
	int GreenSecondY;
	//Blue
	int BlueFirstPoint;
	int BlueSecondPoint;
	int BlueFirstX;
	int BlueFirstY;
	int BlueSecondX;
	int BlueSecondY;

	void GraphDraw(ColorType,int);
	//Proof
	QString wProofDataFile;

	void setUiBuff(void);
	bool	SetQuickProperty(CameraQuickProperty Attr, double RelativeValue);
private slots:
	void on_pbProofCancel_clicked();
	void on_pbProof_clicked();
	void on_cbBlueGraphType_currentIndexChanged(int);
	void on_cbGreenGraphType_currentIndexChanged(int);
	void on_cbRedGraphType_currentIndexChanged(int);
	void on_pbBlueUpdate_clicked();
	void on_pbGreenUpdate_clicked();
	void on_pbRedUpdate_clicked();
	void on_pbBlueApply_clicked();
	void on_pbGreenApply_clicked();
	void on_pbRedApply_clicked();
	void on_pbOK_clicked();
	void on_pbCancel_clicked();
    void on_checkBoxCameraControl_clicked();
};

#endif // CAMERASETTINGCOLOR_H