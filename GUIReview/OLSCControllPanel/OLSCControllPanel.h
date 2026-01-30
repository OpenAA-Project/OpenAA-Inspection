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

#ifndef OLSCCONTROLLPANEL_H
#define OLSCCONTROLLPANEL_H

#include "OLSCControllPanel_global.h"

#include "ui_OLSCControllPanelForm.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"
#include "qextserialport.h"


class SignalOperandInt;
class SignalOperandBit;

// �e���v���[�gGUIReview
class OLSCCONTROLLPANEL_EXPORT OLSCControllPanel : public GUIFormBase
{
	Q_OBJECT

public:
	OLSCControllPanel(LayersBase *Base,QWidget *parent);
	~OLSCControllPanel();

public:
	// �X�V�v�����󂯎����Am_map���X�V����
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructure�����f�[�^���擾����m_map�̏������X�V����
	virtual	void Prepare()	override;

public slots:
	void ResizeAction(void);

public slots:
	void on_pbCOMOpen_clicked();
	void on_pbSensorStatus_clicked();
	void on_pbMotorStatus_clicked();
	void on_pbHome_clicked();
	void on_pbMotorStop_clicked();
	void on_pbMoveToPulse_clicked();
	void on_pbJog_clicked();
	void on_pbMoveToPort1_clicked();
	void on_pbMoveToPort2_clicked();
	void on_pbMoveToPort3_clicked();
	void on_pbMoveToPort4_clicked();

	void updatePortShowByButton();

	bool waitForStop(QString &stopInfo=QString());

	void OperandChangedHome();
	void OperandChangedMovePort();
	void OperandChangedStop();

public:
	bool readParameter(int number, int &value);
	void updatePortPosition();
	int portPosition(int i) const;// zero start:0..3

private:
	bool m_initializedPortValue;
	int m_port1;
	int m_port2;
	int m_port3;
	int m_port4;

	int32	ZoomRate1;
	int32	ZoomRate2;
	int32	ZoomRate3;
	int32	ZoomRate4;
	double	ZoomRate;

public slots:
	int searchCurrentPortPosition();	// -1:unknown or not state in posision of port
										//0:port 1
										//1:port 2
										//2:port 3
										//3:port 4

private:
	Ui::OLSCControllPanelClass ui;
	QextSerialPort *sio;
	const QString derimita;

public:
	QString COMMName;
	QString Port1Name;
	QString Port2Name;
	QString Port3Name;
	QString Port4Name;

	bool ShowCOMInfo;
	bool ShowGetState;
	bool ShowStopAndPulseMove;
	bool ShowJogMove;
	bool ShowHomeAndPortMove;

	int SysSHomeNo;
	int SysSMovePortNo;
	int SysPStopNo;

	SignalOperandInt *ioHome;
	SignalOperandInt *ioMovePort;
	SignalOperandBit *ioStopNo;

protected:
	virtual	void paintEvent ( QPaintEvent * event )	override;

private:
	bool waitForDerimita(QString &recieve);
	bool writeCommand(const QString &sendStr, QString &recieve=QString());
};


#endif // OLSCCONTROLLPANEL_H