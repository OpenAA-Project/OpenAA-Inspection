#ifndef CONTECNC4D_H
#define CONTECNC4D_H

#include <QMainWindow>
#include "ui_ContecNC4D.h"
#include "XContecNC4DInfo.h"
#include<QTimer>
#include "XContecNC4DPipe.h"
#include "NList.h"

#define	AxisXNum	2
#define	AxisYNum	1
#define	AxisZNum	3
#define	AxisWNum	4

class	ContecNC4D;
class	CommandLeaf : public NPList<CommandLeaf>
{
protected:
	ContecNC4D	*Parent;
public:
	CommandLeaf(ContecNC4D *p):Parent(p){}

	virtual	void	Execute(void)	=0;
};

class	PIOAccess
{
	short	Id;
	char	DeviceName[256];
public:
	PIOAccess(char *_DeviceName);
	~PIOAccess(void);

	bool	Initial(void);

	bool	SetBit(int bitNo ,int n);
	bool	SetBit(int bitNo ,bool n);
	bool	GetBit(int bitNo);
};

class ContecNC4D : public QMainWindow
{
	Q_OBJECT

	short Id ;
	ContecNC4DInfo	Data;
	int				CurrentScan;
	QTimer			TM;
	ContecNC4DPipe	PipeServer;
	unsigned long	LastBlink;

	NPListPack<CommandLeaf>	CommandQueue;
	QTimer			CommandTimer;
	bool			LastVacuumSW;
	bool			LastVacuumMode;

	PIOAccess		PIO;

public:
	ContecNC4D(char *SMCDeviceName ,char *PIODeviceName ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ContecNC4D();

	void	ExeOrigin(void);
	void	ExeStartXY();
	void	ExeStepXY();
	bool	IsEndXY();
	void	ExeStartZ(int ZMicron);
	bool	IsEndZ();
	bool	IsStartButton();
	bool	IsAreaSensorON();
	void	ExeMoveVRS(int VRSX ,int VRSY);

	void	SetLightGreen(bool b);
	void	SetBlink(bool b);
	void	GoMoveZ(int ZMicron);
	void	SetVacuum(bool b);
	void	SetLaserPointer(bool b);
	void	GoMoveVRS(double X,double Y);
	void	GoMoveVRS(int X,int Y);

public slots:
    void on_pushButtonGoOriginXY_clicked();
    void on_pushButtonStartScanXY_clicked();
    void on_pushButtonStopXY_clicked();
    void on_pushButtonGoStartPosXY_clicked();
    void on_toolButtonJogYP_clicked();
    void on_toolButtonJogXP_clicked();
    void on_toolButtonJogXM_clicked();
    void on_toolButtonJogYM_clicked();
    void on_pushButtonGoOriginZ_clicked();
    void on_pushButtonStartScanZ_clicked();
    void on_pushButtonStopZ_clicked();
    void on_toolButtonJogZM_clicked();
    void on_toolButtonJogZP_clicked();
    void on_toolButtonVacuum_clicked();
    void on_toolButtonPatlightR_clicked();
    void on_toolButtonPatlightY_clicked();
    void on_toolButtonPatlightG_clicked();
	void on_toolButtonSwitchLampL_clicked();
    void on_toolButtonSwitchLampR_clicked();
    void on_toolButtonDirectionDignal_clicked();
    void on_toolButtonBlinkMode_clicked();
    void on_pushButtonGoOriginW_clicked();
    void on_pushButtonStartScanW_clicked();
    void on_pushButtonStopW_clicked();
    void on_toolButtonJogWM_clicked();
    void on_toolButtonJogWP_clicked();
    void on_pushButtonConvertToScan_clicked();
    void on_toolButtonEnableAreaSensor_clicked();
    void on_toolButtonEnableDoorSensor_clicked();
    void on_toolButtonAW0X_clicked();
    void on_toolButtonFreeX_clicked();
    void on_toolButtonAlmRstX_clicked();
	void on_toolButtonAW0Y_clicked();
    void on_toolButtonFreeY_clicked();
    void on_toolButtonAlmRstY_clicked();
    void on_toolButtonAW0Z_clicked();
    void on_toolButtonFreeZ_clicked();
    void on_toolButtonAlmRstZ_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonSetting_clicked();

    void on_toolButtonSVONW_clicked();
    void on_toolButtonResetW_clicked();
    void on_toolButtonHomeW_clicked();
    void on_toolButtonTLW_clicked();
    void on_toolButtonCSTPW_clicked();
    void on_toolButtoDCLRW_clicked();
    void on_toolButtonBKRLW_clicked();
    void on_toolButtonRModW_clicked();

	void	SlotTimeOut();
	void	SlotCommandTimeOut();

    void on_pushButtonGoVRS_clicked();
    void on_toolButtonLaserPointer_clicked();

private:
	Ui::ContecNC4DClass ui;

	void	ShowDataToWindow(void);
	void	DataFromWindow(void);

	bool	RButtonON;
	bool	LButtonON;
	bool	FootSWON;
	bool	AreaSensorON;
	bool	CoverSensorON;
	bool	EmergencyON;

	bool	FootVacuumON;
	bool	lastFootSWON;

	bool	CheckOnMoving(void);
	void	SetLimitation(void);
};

//------------------------------------------------------



class	CommandOrigin :public CommandLeaf
{
public:
	CommandOrigin(ContecNC4D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};

class	CommandGotoXY :public CommandLeaf
{
public:
	CommandGotoXY(ContecNC4D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};
class	CommandStepXY :public CommandLeaf
{
public:
	CommandStepXY(ContecNC4D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};
class	CommandMoveZ :public CommandLeaf
{
public:
	int ZMicron;

	CommandMoveZ(ContecNC4D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};

class	CommandGotoVRS :public CommandLeaf
{
public:
	int	X,Y;
	CommandGotoVRS(ContecNC4D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};

#endif // CONTECNC4D_H
