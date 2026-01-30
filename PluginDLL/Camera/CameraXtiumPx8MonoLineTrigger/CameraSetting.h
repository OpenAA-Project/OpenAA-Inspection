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



#ifndef CAMERASETTING_H
#define CAMERASETTING_H

#include <QDialog>
#include "ui_CameraSetting.h"

extern QString ProofDataFile;
extern bool pbProofFlag;
extern bool pbProofCancelFlag;

class	CLHS_PX8Setting;
class	featureCtrl;

class CameraSetting : public QDialog
{
    Q_OBJECT

	CLHS_PX8Setting	*Setting;
	featureCtrl		*Feature;

public:
    CameraSetting(CLHS_PX8Setting *s ,featureCtrl *f ,QWidget *parent = 0);
    ~CameraSetting();

	void moveData(void);

private:
    Ui::CameraSettingClass ui;
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

#endif // CAMERASETTING_H