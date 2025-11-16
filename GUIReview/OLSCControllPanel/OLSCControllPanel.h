#ifndef OLSCCONTROLLPANEL_H
#define OLSCCONTROLLPANEL_H

#include "OLSCControllPanel_global.h"

#include "ui_OLSCControllPanelForm.h"

#include "XDLLOnly.h"

#include "ReviewStructureItems.h"
#include "qextserialport.h"


class SignalOperandInt;
class SignalOperandBit;

// テンプレートGUIReview
class OLSCCONTROLLPANEL_EXPORT OLSCControllPanel : public GUIFormBase
{
	Q_OBJECT

public:
	OLSCControllPanel(LayersBase *Base,QWidget *parent);
	~OLSCControllPanel();

public:
	// 更新要求を受け取り、m_mapを更新する
	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;

public:
	void updateGUI();// ReviewStructureからデータを取得してm_mapの情報を更新する
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
