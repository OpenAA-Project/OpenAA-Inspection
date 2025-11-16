/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\CameraSettingMono.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef CAMERASETTINGMONO_H
#define CAMERASETTINGMONO_H

#include <QDialog>
#include "ui_CameraSettingMono.h"

class	CameraXtiumLinearHSMono;
class	featureCtrl;

class CameraSettingMono : public QDialog
{
    Q_OBJECT

	CameraXtiumLinearHSMono	*Cam;
	featureCtrl		*Feature;

public:
    CameraSettingMono(CameraXtiumLinearHSMono *s ,featureCtrl *f ,QWidget *parent = 0);
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
    void on_checkBoxCameraControl_clicked();
};

#endif // CAMERASETTINGMONO_H
