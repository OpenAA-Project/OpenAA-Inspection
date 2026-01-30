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



#ifndef CAMERASETTINGMONO_H
#define CAMERASETTINGMONO_H

#include <QDialog>
#include "ui_CameraSettingMono.h"

class	CameraXtiumFx8Mono;
class	featureCtrl;

class CameraSettingMono : public QDialog
{
    Q_OBJECT

	CameraXtiumFx8Mono	*Cam;
	featureCtrl		*Feature;

public:
    CameraSettingMono(CameraXtiumFx8Mono *s ,featureCtrl *f ,QWidget *parent = 0);
    ~CameraSettingMono();

	void moveData(void);

private:
    Ui::CameraSettingMonoClass ui;
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


	void GraphDraw(ColorType,int);
	//Proof
	QString wProofDataFile;

	void setUiBuff(void);

private slots:
	void on_pbProofCancel_clicked();
	void on_pbProof_clicked();
	void on_cbRedGraphType_currentIndexChanged(int);
	void on_pbRedUpdate_clicked();
	void on_pbRedApply_clicked();
	void on_pbOK_clicked();
	void on_pbCancel_clicked();
};

#endif // CAMERASETTINGMONO_H