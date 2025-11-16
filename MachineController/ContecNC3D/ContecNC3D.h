#ifndef CONTECNC3D_H
#define CONTECNC3D_H

#include <QMainWindow>
#include "ui_ContecNC3D.h"
#include "XContecNC3DInfo.h"
#include<QTimer>
#include "XContecNC3DPipe.h"
#include "NList.h"

#define	AxisXNum	2
#define	AxisYNum	1
#define	AxisZNum	3

class	ContecNC3D;

class	CommandLeaf : public NPList<CommandLeaf>
{
protected:
	ContecNC3D	*Parent;
public:
	CommandLeaf(ContecNC3D *p):Parent(p){}

	virtual	void	Execute(void)	=0;
};


class ContecNC3D : public QMainWindow
{
	Q_OBJECT

	short Id ;
	ContecNC3DInfo	Data;
	int				CurrentScan;
	QTimer			TM;
	ContecNC3DPipe	PipeServer;
	unsigned long	LastBlink;

	NPListPack<CommandLeaf>	CommandQueue;
	QTimer			CommandTimer;
	bool			LastVacuumSW;
	bool			LastVacuumMode;

public:
	ContecNC3D(char *DeviceName ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~ContecNC3D();

	void	ExeOrigin(void);
	void	ExeStartXY();
	void	ExeStepXY();
	bool	IsEndXY();
	void	ExeStartZ(int ZMicron);
	bool	IsEndZ();
	bool	IsStartButton();

	void	SetLightGreen(bool b);
	void	SetBlink(bool b);
	void	GoMoveZ(int ZMicron);
	void	SetVacuum(bool b);

public slots:
    void on_toolButtonVacuum_clicked();
    void on_toolButtonPatlightR_clicked();
    void on_toolButtonPatlightY_clicked();
    void on_toolButtonPatlightG_clicked();
    void on_pushButtonGoOriginXY_clicked();
    void on_pushButtonStartScanXY_clicked();
    void on_pushButtonStopXY_clicked();
    void on_pushButtonGoStartPosXY_clicked();
    void on_pushButtonGoOriginZ_clicked();
    void on_pushButtonStartScanZ_clicked();
    void on_pushButtonStopZ_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonConvertToScan_clicked();
    void on_pushButtonSetting_clicked();
    void on_toolButtonSwitchLampL_clicked();
    void on_toolButtonSwitchLampR_clicked();
    void on_toolButtonAW0X_clicked();
    void on_toolButtonFreeX_clicked();
    void on_toolButtonAlmRstX_clicked();
    void on_toolButtonAW0Y_clicked();
    void on_toolButtonFreeY_clicked();
    void on_toolButtonAlmRstY_clicked();
    void on_toolButtonAW0Z_clicked();
    void on_toolButtonFreeZ_clicked();
    void on_toolButtonAlmRstZ_clicked();
    void on_toolButtonJogYP_clicked();
    void on_toolButtonJogYM_clicked();
    void on_toolButtonJogXP_clicked();
    void on_toolButtonJogXM_clicked();
    void on_toolButtonJogZM_clicked();
    void on_toolButtonJogZP_clicked();

    void on_toolButtonDirectionDignal_clicked();
	void	SlotTimeOut();
	void	SlotCommandTimeOut();

private:
	Ui::ContecNC3DClass ui;

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
	CommandOrigin(ContecNC3D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};

class	CommandGotoXY :public CommandLeaf
{
public:
	CommandGotoXY(ContecNC3D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};
class	CommandStepXY :public CommandLeaf
{
public:
	CommandStepXY(ContecNC3D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};
class	CommandMoveZ :public CommandLeaf
{
public:
	int ZMicron;

	CommandMoveZ(ContecNC3D *p):CommandLeaf(p){}
	virtual	void	Execute(void);
};



#endif // CONTECNC3D_H
