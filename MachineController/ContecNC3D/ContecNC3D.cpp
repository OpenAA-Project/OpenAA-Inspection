#include "ContecNC3D.h"
#include <QFile>
#include "Windows.h"
#include "math.h"
#include "CSmc.h"
#include "CSmcdef.h"
#include "XGeneralFunc.h"
#include "SettingDialog.h"
#include "XCriticalFunc.h"

QString	FileName="ContecNC3D.dat";


ContecNC3D::ContecNC3D(char *DeviceName ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),PipeServer(this)
{
	ui.setupUi(this);

	CurrentScan	=0;
	

	RButtonON	=false;
	LButtonON	=false;
	FootSWON	=false;
	AreaSensorON	=false;
	CoverSensorON	=false;
	EmergencyON	=false;
	FootVacuumON=false;
	lastFootSWON=false;
	LastBlink	=0;
	LastVacuumSW=false;
	LastVacuumMode=false;

	long	Ret = SmcWInit( DeviceName , &Id );
	if(Ret==0){
		{
			Ret=SmcWMotionStop(Id,1);

			Ret=SmcWSetPulseType(Id,1,5,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetCtrlTypeIn(Id,1,1);
			if(Ret!=0)
				return ;
			short inoutlog = 0x81;
			Ret=SmcWSetCtrlInOutLog(Id,1,inoutlog);
			if(Ret!=0)
				return ;
			Ret=SmcWSetOrgMode(Id,1,1,0,1,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetInitParam(Id,1);
			if(Ret!=0)
				return ;

			Ret=SmcWSetResolveSpeed( Id , 1 , 10);
			if(Ret!=0)
				return ;
		}
		{
			Ret=SmcWMotionStop(Id,2);

			Ret=SmcWSetPulseType(Id,2,5,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetCtrlTypeIn(Id,2,1);
			if(Ret!=0)
				return ;
			short inoutlog = 0x81;
			Ret=SmcWSetCtrlInOutLog(Id,2,inoutlog);
			if(Ret!=0)
				return ;
			Ret=SmcWSetOrgMode(Id,2,1,0,1,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetInitParam(Id,2);
			if(Ret!=0)
				return ;
			Ret=SmcWSetResolveSpeed( Id , 2 , 10);
			if(Ret!=0)
				return ;
		}
		{
			Ret=SmcWMotionStop(Id,3);

			Ret=SmcWSetPulseType(Id,3,5,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetCtrlTypeIn(Id,3,1);
			if(Ret!=0)
				return ;
			short inoutlog = 0x81;
			Ret=SmcWSetCtrlInOutLog(Id,3,inoutlog);
			if(Ret!=0)
				return ;
			Ret=SmcWSetOrgMode(Id,3,1,0,2,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetInitParam(Id,3);
			if(Ret!=0)
				return ;
			Ret=SmcWSetResolveSpeed( Id , 3 , 10);
			if(Ret!=0)
				return ;
		}
		{
			Ret=SmcWMotionStop(Id,4);

			Ret=SmcWSetPulseType(Id,4,5,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetCtrlTypeIn(Id,4,1);
			if(Ret!=0)
				return ;
			short inoutlog = 0x81;
			Ret=SmcWSetCtrlInOutLog(Id,4,inoutlog);
			if(Ret!=0)
				return ;
			Ret=SmcWSetOrgMode(Id,4,1,0,2,0);
			if(Ret!=0)
				return ;
			Ret=SmcWSetInitParam(Id,4);
			if(Ret!=0)
				return ;
			Ret=SmcWSetResolveSpeed( Id , 4 , 10);
			if(Ret!=0)
				return ;
		}
	}

	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		Data.Load(&File);
	}

	ShowDataToWindow();

	SetLimitation();

	TM.setInterval(100);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

	CommandTimer.setInterval(100);
	CommandTimer.setSingleShot(false);
	connect(&CommandTimer,SIGNAL(timeout()),this,SLOT(SlotCommandTimeOut()));
	CommandTimer.start();

	PipeServer.Start();
}

ContecNC3D::~ContecNC3D()
{
	SmcWExit(Id);
}

void ContecNC3D::on_toolButtonVacuum_clicked()
{
	if(ui.toolButtonVacuum->isChecked()==true)
		SmcWSetDigitalOut(Id,2,1,1);
	else
		SmcWSetDigitalOut(Id,2,0,1);
}

void ContecNC3D::on_toolButtonPatlightR_clicked()
{
	if(ui.toolButtonPatlightR->isChecked()==true)
		SmcWSetDigitalOut(Id,4,4,4);
	else
		SmcWSetDigitalOut(Id,4,0,4);
}

void ContecNC3D::on_toolButtonPatlightY_clicked()
{
	if(ui.toolButtonPatlightY->isChecked()==true)
		SmcWSetDigitalOut(Id,4,2,2);
	else
		SmcWSetDigitalOut(Id,4,0,2);
}

void ContecNC3D::on_toolButtonPatlightG_clicked()
{
	if(ui.toolButtonPatlightG->isChecked()==true)
		SmcWSetDigitalOut(Id,4,1,1);
	else
		SmcWSetDigitalOut(Id,4,0,1);
}

bool	ContecNC3D::CheckOnMoving(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	SlotTimeOut();

	if(EmergencyON==true){
		on_pushButtonStopXY_clicked();
		on_pushButtonStopZ_clicked();
		ReEntrant=false;
		return false;
	}
	if(Data.EnableAreaSensor==true){
		if(AreaSensorON==true){
			on_pushButtonStopXY_clicked();
			ReEntrant=false;
			return false;
		}
	}
	if(Data.EnableDoorSensor==true){
		if(CoverSensorON==true){
			on_pushButtonStopXY_clicked();
			ReEntrant=false;
			return false;
		}
	}

	ReEntrant=false;
	return true;
}

void ContecNC3D::SetLimitation(void)
{
	long	Ret;
	//Ret=SmcWSetSoftLimit( Id, AxisXNum, 1, 1, Data.AxisX.GetPulseFromMM(Data.AxisX.MaxLength), 0 );
	//Ret=SmcWSetSoftLimit( Id, AxisYNum, 1, 1, Data.AxisY.GetPulseFromMM(Data.AxisY.MaxLength), 0 );
	//Ret=SmcWSetSoftLimit( Id, AxisZNum, 1, 1, Data.AxisZ.GetPulseFromMM(Data.AxisZ.MaxLength), 0 );
}

void ContecNC3D::on_pushButtonGoOriginXY_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	long	Ret;
	try{
		Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AxisY.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AxisY.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.AxisX.OriginVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.OriginVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}


		Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.AxisX.OriginVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.OriginVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
	}
	catch(...){}
	long Ret1,Ret2;
	Ret1=SmcWSetReady(Id,AxisXNum,3,1);	// ・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E峻・鐃・E・・E・・E・・E・・E・・E・・E・・E・ 3:・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・0:・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・
	Ret2=SmcWSetReady(Id,AxisYNum,3,1);	// ・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E峻・鐃・E・・E・・E・・E・・E・・E・・E・・E・ 3:・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・0:・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・
	if(Ret1!=0 && Ret2!=0){
		ReEntrant=false;
		return;
	}

	if(Ret1==0){
		Ret1=SmcWMotionStart(Id,AxisXNum);
	}
	if(Ret2==0){
		Ret2=SmcWMotionStart(Id,AxisYNum);
	}

	GSleep(200);
	for(;;){
		short valX;
		long	RetX=SmcWGetMoveStatus(Id,AxisXNum, &valX);
		short valY;
		long	RetY=SmcWGetMoveStatus(Id,AxisYNum, &valY);
		if(RetX==0 && RetY==0 && valX==0 && valY==0){
			break;
		}
		if(CheckOnMoving()==false){
			break;
		}
		QCoreApplication::processEvents();
	}
	Ret=SmcWSetOutPulse( Id , AxisXNum , 0 );
	if(Ret!=0){
		ReEntrant=false;
		return;
	}
	Ret=SmcWSetOutPulse( Id , AxisYNum , 0 );
	if(Ret!=0){
		ReEntrant=false;
		return;
	}
		
	CurrentScan=0;
	ui.spinBoxCurrentScan->setValue(CurrentScan);

	ReEntrant=false;
}

void ContecNC3D::on_pushButtonStartScanXY_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	long	Ret;
	long	AbsPos;
	long	CurrentPulseX;
	long	CurrentPulseY;

	Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
	if(Ret!=0){
		ReEntrant=false;
		return;
	}
	int		AbsPosX=Data.AxisX.GetPulseFromMM(Data.StepLength)*CurrentScan+Data.AxisX.GetPulseFromMM(Data.StartPosX);
	if(CurrentPulseX!=AbsPosX){
		Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.StepVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.StepVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}

		Ret=SmcWSetStopPosition(Id,AxisXNum,0,AbsPosX);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetReady(Id,AxisXNum,1,0);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}

		Ret=SmcWMotionStart(Id,AxisXNum);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		for(;;){
			short val;
			Ret=SmcWGetMoveStatus(Id,AxisXNum, &val);
			if(Ret==0 && val==0){
				break;
			}
			if(CheckOnMoving()==false){
				ReEntrant=false;
				return ;
			}
			QCoreApplication::processEvents();
		}
	}

	try{
		Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
		Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);

		Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AxisY.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AxisY.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.ScanVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.ScanVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		bool	AttrToMoveY=false;
		if((CurrentScan&1)==0){
			AbsPos=Data.AxisY.GetPulseFromMM(Data.ScanLength+Data.StartPosY);
			if(CurrentPulseY!=AbsPos){
				Ret=SmcWSetStopPosition(Id,AxisYNum,0,AbsPos);	
				if(Ret!=0){
					ReEntrant=false;
					return;
				}
				AttrToMoveY=true;
			}
		}
		else{
			AbsPos=Data.AxisY.GetPulseFromMM(Data.StartPosY);
			if(CurrentPulseY!=AbsPos){
				Ret=SmcWSetStopPosition(Id,AxisYNum,0,AbsPos);
				if(Ret!=0){
					ReEntrant=false;
					return;
				}
				AttrToMoveY=true;
			}
		}

		if((CurrentScan&1)==0)	//Trigger direction
			SmcWSetDigitalOut(Id,3,1,1);
		else
			SmcWSetDigitalOut(Id,3,0,1);

		if(AttrToMoveY==true){
			Ret=SmcWSetReady(Id,AxisYNum,1,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisYNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
	}
	catch(...){
	}
	GSleep(200);
	for(;;){

		short val;
		Ret=SmcWGetMoveStatus(Id,AxisYNum, &val);
		if(Ret==0 && val==0){
			break;
		}
		if(CheckOnMoving()==false){
			ReEntrant=false;
			return ;
			break;
		}
		QCoreApplication::processEvents();
	}
	CurrentScan++;
	ui.spinBoxCurrentScan->setValue(CurrentScan);

	Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);
	if(Ret==0 && CurrentPulseY==AbsPos && CurrentScan<Data.ScanCount){
	
		Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.StepVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.StepVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}

		int		AbsPosX=Data.AxisX.GetPulseFromMM(Data.StepLength)*CurrentScan+Data.AxisX.GetPulseFromMM(Data.StartPosX);
		if(CurrentPulseX!=AbsPosX){
			Ret=SmcWSetStopPosition(Id,AxisXNum,0,AbsPosX);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}

			Ret=SmcWSetReady(Id,AxisXNum,1,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisXNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
			for(;;){
				short val;
				Ret=SmcWGetMoveStatus(Id,AxisXNum, &val);
				if(Ret==0 && val==0){
					break;
				}
				if(CheckOnMoving()==false){
					break;
				}
				QCoreApplication::processEvents();
			}
		}
	}
	else if(Ret==0 && CurrentScan>=Data.ScanCount){
		on_pushButtonGoStartPosXY_clicked();
		for(;;){
			short valX;
			short valY;
			long	RetX=SmcWGetMoveStatus(Id,AxisXNum, &valX);
			long	RetY=SmcWGetMoveStatus(Id,AxisYNum, &valY);
			if(RetX==0 && valX==0 && RetY==0 && valY==0){
				break;
			}
			if(CheckOnMoving()==false){
				break;
			}
			QCoreApplication::processEvents();
		}
	}
	ReEntrant=false;
}

void ContecNC3D::on_pushButtonStopXY_clicked()
{
	long	Ret;
	Ret=SmcWSetDecelTime(Id,AxisXNum,50);
	Ret=SmcWSetDecelTime(Id,AxisYNum,50);

	long Ret1,Ret2;
	Ret1=SmcWMotionDecStop(Id,AxisXNum);
	Ret2=SmcWMotionDecStop(Id,AxisYNum);
	if(Ret1!=0)
		return;
	if(Ret2!=0)
		return;
}

void ContecNC3D::on_pushButtonGoStartPosXY_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	long	Ret;
	try{
		long	CurrentPulseX;
		Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
		long	CurrentPulseY;
		Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);

		Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AxisX.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AxisY.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AxisY.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.StartVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.AxisX.GetPulseFromMM(Data.StartVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}


		Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.StartVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.StartVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		bool	AttrToMoveX=false;
		int		AbsPosX=Data.AxisX.GetPulseFromMM(Data.StartPosX);
		int		AbsPosY=Data.AxisY.GetPulseFromMM(Data.StartPosY);
		if(CurrentPulseX!=AbsPosX){
			Ret=SmcWSetStopPosition(Id,AxisXNum,0,AbsPosX);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			AttrToMoveX=true;
		}
		bool	AttrToMoveY=false;
		if(CurrentPulseY!=AbsPosY){
			Ret=SmcWSetStopPosition(Id,AxisYNum,0,AbsPosY);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			AttrToMoveY=true;
		}

		if(AttrToMoveX==true){
			Ret=SmcWSetReady(Id,AxisXNum,1,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		if(AttrToMoveY==true){
			Ret=SmcWSetReady(Id,AxisYNum,1,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}

		if(AttrToMoveX==true){
			Ret=SmcWMotionStart(Id,AxisXNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		if(AttrToMoveY==true){
			Ret=SmcWMotionStart(Id,AxisYNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		CurrentScan=0;
		ui.spinBoxCurrentScan->setValue(CurrentScan);
	}
	catch(...){
	}
	GSleep(200);
	for(;;){
		short valX;
		long	RetX=SmcWGetMoveStatus(Id,AxisXNum, &valX);
		short valY;
		long	RetY=SmcWGetMoveStatus(Id,AxisYNum, &valY);
		if(RetX==0 && RetY==0 && valX==0 && valY==0){
			break;
		}
		if(CheckOnMoving()==false){
			break;
		}
		QCoreApplication::processEvents();
	}
	long	CurrentPulseX;
	Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
	long	CurrentPulseY;
	Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);
	ReEntrant=false;
}

void ContecNC3D::on_toolButtonJogYP_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogYP->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseY;
			Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);

			Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AxisY.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AxisY.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			/*
			Ret=SmcWSetStopPosition(Id,AxisYNum,0,-Data.AxisY.GetPulseFromMM(Data.AxisY.JogLength));
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			*/

			Ret=SmcWSetReady(Id,AxisYNum,2,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisYNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		catch(...){
		}
	}
	else{
		long	Ret;
		Ret=SmcWMotionDecStop(Id,AxisYNum);
	}
	ReEntrant=false;
}

void ContecNC3D::on_toolButtonJogYM_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogYM->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseY;
			Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);

			Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AxisY.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AxisY.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			/*
			Ret=SmcWSetStopPosition(Id,AxisYNum,0,Data.AxisY.GetPulseFromMM(Data.AxisY.JogLength));
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			*/

			Ret=SmcWSetReady(Id,AxisYNum,2,1);	
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisYNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		catch(...){
		}
	}
	else{
		long	Ret;
		Ret=SmcWMotionDecStop(Id,AxisYNum);
	}
	ReEntrant=false;
}

void ContecNC3D::on_toolButtonJogXP_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogXP->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseX;
			Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);

			Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AxisX.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AxisX.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.AxisX.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.AxisX.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWSetReady(Id,AxisXNum,2,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisXNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		catch(...){
		}
	}
	else{
		long	Ret;
		Ret=SmcWMotionDecStop(Id,AxisXNum);
	}
	ReEntrant=false;
}

void ContecNC3D::on_toolButtonJogXM_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogXM->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseX;
			Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);

			Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AxisX.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AxisX.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.AxisX.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.AxisX.GetPulseFromMM(Data.AxisX.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWSetReady(Id,AxisXNum,2,1);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisXNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		catch(...){
		}
	}
	else{
		long	Ret;
		Ret=SmcWMotionDecStop(Id,AxisXNum);
	}
	ReEntrant=false;
}

void ContecNC3D::on_pushButtonGoOriginZ_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	long	Ret;
	try{
		Ret=SmcWSetAccelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.AxisZ.OriginVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}


		Ret=SmcWSetTargetSpeed(Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.AxisZ.OriginVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
	}
	catch(...){}

	Ret=SmcWSetReady(Id,AxisZNum,3,0);
	if(Ret!=0){
		ReEntrant=false;
		return;
	}

	if(Ret==0){
		Ret=SmcWMotionStart(Id,AxisZNum);
	}

	GSleep(200);
	for(;;){
		short valZ;
		long	RetZ=SmcWGetMoveStatus(Id,AxisZNum, &valZ);
		if(RetZ==0 && valZ==0){
			break;
		}
		if(CheckOnMoving()==false){
			break;
		}
		QCoreApplication::processEvents();
	}

	Ret=SmcWSetOutPulse( Id , AxisZNum , 0 );
	if(Ret!=0){
		ReEntrant=false;
		return;
	}
	ReEntrant=false;
}

void ContecNC3D::on_pushButtonStartScanZ_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	long	Ret;
	long	AbsPos;
	long	CurrentPulseZ;
	try{
		Ret=SmcWGetOutPulse(Id,AxisZNum, &CurrentPulseZ);

		Ret=SmcWSetAccelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.VelocityZ)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetTargetSpeed(Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.VelocityZ));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		bool	AttrToMoveY=false;
		AbsPos=Data.AxisZ.GetPulseFromMM(Data.PosZ);
		if(CurrentPulseZ!=AbsPos){
			Ret=SmcWSetStopPosition(Id,AxisZNum,0,AbsPos);	
			if(Ret!=0){
				ReEntrant=false;
				return;
			}

			Ret=SmcWSetReady(Id,AxisZNum,1,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisZNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
	}
	catch(...){
	}

	GSleep(200);
	for(;;){
		short val;
		Ret=SmcWGetMoveStatus(Id,AxisZNum, &val);
		if(Ret==0 && val==0){
			break;
		}
		if(CheckOnMoving()==false){
			break;
		}
		QCoreApplication::processEvents();
	}


	ReEntrant=false;
}

void ContecNC3D::on_toolButtonJogZP_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogZP->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseZ;
			Ret=SmcWGetOutPulse(Id,AxisZNum, &CurrentPulseZ);
				
			Ret=SmcWSetAccelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.AxisZ.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.AxisZ.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWSetReady(Id,AxisZNum,2,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisZNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		catch(...){
		}
	}
	else{
		long	Ret;
		Ret=SmcWMotionDecStop(Id,AxisZNum);
	}
	ReEntrant=false;
}

void ContecNC3D::on_toolButtonJogZM_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogZM->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseZ;
			Ret=SmcWGetOutPulse(Id,AxisZNum, &CurrentPulseZ);

			Ret=SmcWSetAccelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisZNum,Data.AxisZ.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.AxisZ.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisZNum,Data.AxisZ.GetPulseFromMM(Data.AxisZ.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWSetReady(Id,AxisZNum,2,1);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisZNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		catch(...){
		}
	}
	else{
		long	Ret;
		Ret=SmcWMotionDecStop(Id,AxisZNum);
	}
	ReEntrant=false;
}

void ContecNC3D::on_pushButtonStopZ_clicked()
{
	long	Ret;
	Ret=SmcWSetDecelTime(Id,AxisZNum,50);
	Ret=SmcWMotionDecStop(Id,AxisZNum);
	if(Ret!=0)
		return;
}

void ContecNC3D::on_pushButtonSave_clicked()
{
	DataFromWindow();
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		Data.Save(&File);
	}
}

void ContecNC3D::on_pushButtonConvertToScan_clicked()
{

}

void ContecNC3D::on_pushButtonSetting_clicked()
{
	SettingDialog	D(&Data,this);
	if(D.exec()==(int)true){
		on_pushButtonSave_clicked();
		SetLimitation();
	}
}

void	ContecNC3D::ShowDataToWindow(void)
{
	ui.spinBoxStartPosX		->setValue(Data.StartPosX);
	ui.spinBoxStartPosY		->setValue(Data.StartPosY);
	ui.spinBoxStartVelocity	->setValue(Data.StartVelocity);
	ui.spinBoxScanPulse		->setValue(Data.ScanLength);
	ui.spinBoxScanVelocity	->setValue(Data.ScanVelocity);
	ui.spinBoxStepPulse		->setValue(Data.StepLength);
	ui.spinBoxStepVelocity	->setValue(Data.StepVelocity);
	ui.doubleSpinBoxPosZ	->setValue(Data.PosZ);
	ui.spinBoxVelocityZ		->setValue(Data.VelocityZ);
	ui.spinBoxScanCount		->setValue(Data.ScanCount);
	ui.toolButtonEnableAreaSensor	->setChecked(Data.EnableAreaSensor);
	ui.toolButtonEnableDoorSensor	->setChecked(Data.EnableDoorSensor);
}
void	ContecNC3D::DataFromWindow(void)
{
	Data.StartPosX		=ui.spinBoxStartPosX	->value();
	Data.StartPosY		=ui.spinBoxStartPosY	->value();
	Data.StartVelocity	=ui.spinBoxStartVelocity->value();
	Data.ScanLength		=ui.spinBoxScanPulse	->value();
	Data.ScanVelocity	=ui.spinBoxScanVelocity	->value();
	Data.StepLength		=ui.spinBoxStepPulse	->value();
	Data.StepVelocity	=ui.spinBoxStepVelocity	->value();
	Data.PosZ			=ui.doubleSpinBoxPosZ	->value();
	Data.VelocityZ		=ui.spinBoxVelocityZ	->value();
	Data.ScanCount		=ui.spinBoxScanCount	->value();
	Data.EnableAreaSensor	=ui.toolButtonEnableAreaSensor	->isChecked();
	Data.EnableDoorSensor	=ui.toolButtonEnableDoorSensor	->isChecked();
}


void ContecNC3D::SlotTimeOut()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	short	Val1;
	short	Val2;
	short	Val3;
	long	Ret1=SmcWGetDigitalIn(Id,1,&Val1);
	long	Ret2=SmcWGetDigitalIn(Id,2,&Val2);
	long	Ret3=SmcWGetDigitalIn(Id,2,&Val3);

	if((Val1&0x08)!=0){
		ui.checkBoxEmergency->setChecked(true);
		EmergencyON	=false;
	}
	else{
		ui.checkBoxEmergency->setChecked(false);
		EmergencyON=true;
	}
	if((Val1&0x10)!=0){
		ui.checkBoxVacuumSwitch->setChecked(true);
		if(LastVacuumSW==false){
			if(LastVacuumMode==false){
				LastVacuumMode=true;
				ui.toolButtonVacuum->setChecked(true);
				on_toolButtonVacuum_clicked();
			}
			else{
				LastVacuumMode=false;
				ui.toolButtonVacuum->setChecked(false);
				on_toolButtonVacuum_clicked();
			}
		}
		LastVacuumSW=true;
	}
	else{
		ui.checkBoxVacuumSwitch->setChecked(false);
		LastVacuumSW=false;
	}

	if((Val1&0x20)!=0){
		ui.checkBoxButtonLeft->setChecked(true);
		LButtonON=true;
	}
	else{
		ui.checkBoxButtonLeft->setChecked(false);
		LButtonON=false;
	}
	if((Val1&0x40)!=0){
		ui.checkBoxButtonRight->setChecked(true);
		RButtonON=true;
	}
	else{
		ui.checkBoxButtonRight->setChecked(false);
		RButtonON=false;
	}

	if((Val2&0x08)!=0){
		ui.checkBoxAreaSensor->setChecked(true);
		AreaSensorON=false;
	}
	else{
		ui.checkBoxAreaSensor->setChecked(false);
		AreaSensorON=true;
	}
	if((Val2&0x10)!=0){
		ui.checkBoxCoverSensor->setChecked(true);
		CoverSensorON=true;
	}
	else{
		ui.checkBoxCoverSensor->setChecked(false);
		CoverSensorON=false;
	}
	/*
	if((Val1&0x10)!=0){
		ui.checkBoxFootSW->setChecked(true);
		FootSWON=true;
	}
	else{
		ui.checkBoxFootSW->setChecked(false);
		FootSWON=false;
	}
	*/
	short	LimitSts1;
	Ret1 = SmcWGetLimitStatus( Id , AxisXNum , &LimitSts1 );
	short	LimitSts2;
	Ret2 = SmcWGetLimitStatus( Id , AxisYNum , &LimitSts2 );
	short	LimitSts3;
	Ret3 = SmcWGetLimitStatus( Id , AxisZNum , &LimitSts3 );



	ui.checkBoxReadyX	->setChecked(((Val1&0x02)!=0)?true:false);
	ui.checkBoxALMX		->setChecked(((LimitSts1&0x01)!=0)?true:false);
	ui.checkBoxTIMX		->setChecked(((Val1&0x08)!=0)?true:false);
	ui.checkBoxLimitPX	->setChecked(((LimitSts1&0x02)!=0)?true:false);
	ui.checkBoxLimitMX	->setChecked(((LimitSts1&0x04)!=0)?true:false);
	ui.checkBoxORGX		->setChecked(((LimitSts1&0x08)!=0)?true:false);

	ui.checkBoxReadyY	->setChecked(((Val2&0x02)!=0)?true:false);
	ui.checkBoxALMY		->setChecked(((LimitSts2&0x01)!=0)?true:false);
	ui.checkBoxTIMY		->setChecked(((Val2&0x08)!=0)?true:false);
	ui.checkBoxLimitPY	->setChecked(((LimitSts2&0x02)!=0)?true:false);
	ui.checkBoxLimitMY	->setChecked(((LimitSts2&0x04)!=0)?true:false);
	ui.checkBoxORGY		->setChecked(((LimitSts2&0x08)!=0)?true:false);

	ui.checkBoxReadyZ	->setChecked(((Val3&0x02)!=0)?true:false);
	ui.checkBoxALMZ		->setChecked(((LimitSts3&0x01)!=0)?true:false);
	ui.checkBoxTIMZ		->setChecked(((Val3&0x08)!=0)?true:false);
	ui.checkBoxLimitPZ	->setChecked(((LimitSts3&0x02)!=0)?true:false);
	ui.checkBoxLimitMZ	->setChecked(((LimitSts3&0x04)!=0)?true:false);
	ui.checkBoxORGZ		->setChecked(((LimitSts3&0x08)!=0)?true:false);

	long	CurrentPulseX;
	long	RetX=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
	long	CurrentPulseY;
	long	RetY=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);
	long	CurrentPulseZ;
	long	RetZ=SmcWGetOutPulse(Id,AxisZNum, &CurrentPulseZ);
	if(RetX==0){
		ui.spinBoxCurrentPulseX		->setValue(CurrentPulseX);
		ui.lineEditCurrentPosMMX	->setText(QString::number(Data.AxisX.GetMMFromPulse(CurrentPulseX),'f',2));
	}
	if(RetY==0){
		ui.spinBoxCurrentPulseY		->setValue(CurrentPulseY);
		ui.lineEditCurrentPosMMY	->setText(QString::number(Data.AxisY.GetMMFromPulse(CurrentPulseY),'f',2));
	}
	if(RetZ==0){
		ui.spinBoxCurrentPulseZ		->setValue(CurrentPulseZ);
		ui.lineEditCurrentPosMMZ	->setText(QString::number(Data.AxisZ.GetMMFromPulse(CurrentPulseZ),'f',2));
	}

	if(ui.toolButtonBlinkMode->isChecked()==true){
		if(GetComputerMiliSec()-LastBlink>300){
			if(ui.toolButtonSwitchLampL->isChecked()==true){
				ui.toolButtonSwitchLampL->setChecked(false);
				ui.toolButtonSwitchLampR->setChecked(false);
			}
			else{
				ui.toolButtonSwitchLampL->setChecked(true);
				ui.toolButtonSwitchLampR->setChecked(true);
			}
			on_toolButtonSwitchLampL_clicked();
			on_toolButtonSwitchLampR_clicked();
			LastBlink=GetComputerMiliSec();
		}
	}
		
	ReEntrant=false;
}
void ContecNC3D::on_toolButtonSwitchLampL_clicked()
{
	if(ui.toolButtonSwitchLampL->isChecked()==true)
		SmcWSetDigitalOut(Id,2,2,2);
	else
		SmcWSetDigitalOut(Id,2,0,2);
}

void ContecNC3D::on_toolButtonSwitchLampR_clicked()
{
	if(ui.toolButtonSwitchLampR->isChecked()==true)
		SmcWSetDigitalOut(Id,2,4,4);
	else
		SmcWSetDigitalOut(Id,2,0,4);

}

void ContecNC3D::on_toolButtonAW0X_clicked()
{
	if(ui.toolButtonAW0X->isChecked()==true)
		SmcWSetDigitalOut(Id,1,2,2);
	else
		SmcWSetDigitalOut(Id,1,0,2);
}

void ContecNC3D::on_toolButtonFreeX_clicked()
{
	if(ui.toolButtonFreeX->isChecked()==true)
		SmcWSetDigitalOut(Id,1,4,4);
	else
		SmcWSetDigitalOut(Id,1,0,4);
}

void ContecNC3D::on_toolButtonAlmRstX_clicked()
{
	if(ui.toolButtonAlmRstX->isChecked()==true)
		SmcWSetDigitalOut(Id,1,1,1);
	else
		SmcWSetDigitalOut(Id,1,0,1);
}

void ContecNC3D::on_toolButtonAW0Y_clicked()
{
	if(ui.toolButtonAW0Y->isChecked()==true)
		SmcWSetDigitalOut(Id,1,2,2);
	else
		SmcWSetDigitalOut(Id,1,0,2);

}

void ContecNC3D::on_toolButtonFreeY_clicked()
{
	if(ui.toolButtonFreeY->isChecked()==true)
		SmcWSetDigitalOut(Id,1,4,4);
	else
		SmcWSetDigitalOut(Id,1,0,4);

}

void ContecNC3D::on_toolButtonAlmRstY_clicked()
{
	if(ui.toolButtonAlmRstY->isChecked()==true)
		SmcWSetDigitalOut(Id,1,1,1);
	else
		SmcWSetDigitalOut(Id,1,0,1);

}

void ContecNC3D::on_toolButtonAW0Z_clicked()
{
	if(ui.toolButtonAW0Z->isChecked()==true)
		SmcWSetDigitalOut(Id,AxisZNum,2,2);
	else
		SmcWSetDigitalOut(Id,AxisZNum,0,2);
}

void ContecNC3D::on_toolButtonFreeZ_clicked()
{
	if(ui.toolButtonFreeZ->isChecked()==true)
		SmcWSetDigitalOut(Id,AxisZNum,4,4);
	else
		SmcWSetDigitalOut(Id,AxisZNum,0,4);
}

void ContecNC3D::on_toolButtonAlmRstZ_clicked()
{
	if(ui.toolButtonAlmRstZ->isChecked()==true)
		SmcWSetDigitalOut(Id,1,1,1);
	else
		SmcWSetDigitalOut(Id,1,0,1);
}
void	ContecNC3D::ExeOrigin(void)
{
	CommandLeaf	*a=new CommandOrigin(this);
	CommandQueue.AppendList(a);
}
void	ContecNC3D::ExeStartXY()
{
	CommandLeaf	*a=new CommandGotoXY(this);
	CommandQueue.AppendList(a);
}
void	ContecNC3D::ExeStepXY()
{
	CommandLeaf	*a=new CommandStepXY(this);
	CommandQueue.AppendList(a);
}
bool	ContecNC3D::IsEndXY()
{
	short valX;
	long	RetX=SmcWGetMoveStatus(Id,AxisXNum, &valX);
	short valY;
	long	RetY=SmcWGetMoveStatus(Id,AxisYNum, &valY);
	if(RetX==0 && RetY==0 && valX==0 && valY==0){
		return true;
	}
	return false;
}
void	ContecNC3D::ExeStartZ(int ZMicron)
{
	CommandMoveZ	*a=new CommandMoveZ(this);
	a->ZMicron=ZMicron;
	CommandQueue.AppendList(a);
}
bool	ContecNC3D::IsEndZ()
{
	short valZ;
	long	RetZ=SmcWGetMoveStatus(Id,AxisZNum, &valZ);
	if(RetZ==0 && valZ==0){
		return true;
	}
	return false;
}
bool	ContecNC3D::IsStartButton()
{
	if((CoverSensorON==false || Data.EnableDoorSensor==false)
	&& RButtonON==true
	&& LButtonON==true
	&& (AreaSensorON==false || Data.EnableAreaSensor==false)
	&& EmergencyON==false){
		return true;
	}
	return false;
}


void ContecNC3D::on_toolButtonDirectionDignal_clicked()
{
	if(ui.toolButtonDirectionDignal->isChecked()==true)
		SmcWSetDigitalOut(Id,3,1,1);
	else
		SmcWSetDigitalOut(Id,3,0,1);

}

void	ContecNC3D::SetLightGreen(bool b)
{
	ui.toolButtonPatlightG->setChecked(b);
	on_toolButtonPatlightG_clicked();
}
void	ContecNC3D::SetBlink(bool b)
{
	ui.toolButtonBlinkMode->setChecked(b);
}

void	ContecNC3D::GoMoveZ(int ZMicron)
{
	Data.PosZ=ZMicron/1000.0;
	ShowDataToWindow();
	on_pushButtonStartScanZ_clicked();
}

void	ContecNC3D::SlotCommandTimeOut()
{
	CommandLeaf	*a=CommandQueue.GetFirst();
	if(a!=NULL){
		CommandQueue.RemoveList(a);
		a->Execute();
		delete	a;
	}
}
void	ContecNC3D::SetVacuum(bool b)
{
	ui.toolButtonVacuum->setChecked(b);
	on_toolButtonVacuum_clicked();
	LastVacuumMode=b;
}

//-----------------------------------------------------------

void	CommandOrigin::Execute(void)
{
	Parent->on_pushButtonGoOriginXY_clicked();
	Parent->on_pushButtonGoOriginZ_clicked();
}
void	CommandGotoXY::Execute(void)
{
	Parent->on_pushButtonGoStartPosXY_clicked();
}

void	CommandStepXY::Execute(void)
{
	Parent->on_pushButtonStartScanXY_clicked();
}
void	CommandMoveZ::Execute(void)
{
	Parent->GoMoveZ(ZMicron);
}