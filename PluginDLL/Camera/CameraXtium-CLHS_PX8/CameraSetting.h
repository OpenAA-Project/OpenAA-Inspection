/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\CameraSetting.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
};

#endif // CAMERASETTING_H
