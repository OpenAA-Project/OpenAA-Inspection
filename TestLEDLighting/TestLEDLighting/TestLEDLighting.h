/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\TestLEDLighting\TestLEDLighting\TestLEDLighting.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef TESTLEDLIGHTING_H
#define TESTLEDLIGHTING_H

#include <QWidget>
#include <QThread>
#include "LightDLLBase.h"
#include "LED64CTRLib.h"
#include "ui_TestLEDLighting.h"

class ContinueThread : public QThread
{
	Q_OBJECT

public:
	ContinueThread();
	void SetSwitchTime(int value)	{	SwitchTime=value;	}

signals:
	void SignalOneOn();
	void SignalNextOn();

protected:
	void run();

private:
	int SwitchTime;
};

class TestLEDLighting : public QWidget
{
	Q_OBJECT

public:
	TestLEDLighting(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~TestLEDLighting();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
	virtual void closeEvent(QCloseEvent *event);

private slots:
	void pbAllOnClicked			();
	void pbAllOffClicked		();
	void pbOneOnClicked			();
	void pbNextOnClicked		();
	void pbStartPosClearClicked	();
	void pbStartClicked			();
	void pbCloseClicked			();
	void pbDetailsClicked		();
	void twBarRowChanged		(const QModelIndex &CIndex);
	void twLEDRowChanged		(const QModelIndex &CIndex);
	void twBrightnessRowChanged	(const QModelIndex &CIndex);

private:
	Ui::TestLEDLightingClass ui;

	WDC_DEVICE_HANDLE	hDev;
	DWORD				dwStatus;
	WDC_ADDR_MODE		mode;
	DWORD				dwAddrSpace;
	short				LEDBright[LEDBARNUMB][LEDsNumb];
	double				Gain[LEDBARNUMB][LEDsNumb];
	bool				ChangeTransferLED[LEDBARNUMB][LEDsNumb];
	LED64ctr			CLED[LEDBARNUMB];

	ContinueThread		tContinue;

	LightDLLBase		*hLighDLLtBase;

	void Init();
};

#endif // TESTLEDLIGHTING_H
