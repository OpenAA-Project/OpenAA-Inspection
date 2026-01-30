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