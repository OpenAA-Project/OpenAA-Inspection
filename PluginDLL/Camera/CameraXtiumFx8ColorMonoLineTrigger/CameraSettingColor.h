/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\Camera\CameraGraphinXCM8040\CameraGraphin\CameraSettingColor.h
** Author : YYYYYYYYYY
****************************************************************************-**/


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
