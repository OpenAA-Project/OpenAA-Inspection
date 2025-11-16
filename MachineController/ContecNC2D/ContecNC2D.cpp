#include "ContecNC2D.h"
#include <QFile>
#include "Windows.h"
#include "math.h"
#include "CSmc.h"
#include "CSmcdef.h"
#include "XGeneralFunc.h"

QString	FileName="ContecNC2D.dat";

int		AxisXNum	=1;
int		AxisYNum	=2;


ContecNC2D::ContecNC2D(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),PipeServer(this)
{
	ui.setupUi(this);

	CurrentScan	=0;
	char *DeviceName ="SMC001" ;

	RButtonON	=false;
	LButtonON	=false;
	FootSWON	=false;
	AreaSewnsorON	=false;
	EmergencyON	=false;
	FootVacuumON=false;
	lastFootSWON=false;

	long	Ret = SmcWInit( DeviceName , &Id );
	if(Ret==0){
		for(int Cnt=1;Cnt<=4;Cnt++){
			//・E・・E・E・E・・E・・E粛・E申・E・・E・・E縮・・鐃・5 ・E・CW/CCW:High)2・E・・E・E・E・・E・E・E・E・・E・・E・E・E・・E・E・
			Ret=SmcWSetPulseType(Id,Cnt,5,0);
			if(Ret!=0)
				return ;

			//・E・E・E・E・E・E・E粛・M・E・E・E・・E・E・E・・E縦・p・E・E・E・E・ALM,INP,SD,LTC,PCS,CLR・E・・E縮・・鐃・IN1/ALM)
			Ret=SmcWSetCtrlTypeIn(Id,Cnt,1);
			if(Ret!=0)
				return ;

			//・E・E・E・E・E・E・E・・E粛・M・E・E・E・・E・E・E縮・・鐃・LIM,IN1)[0|0|0|0|0|OUT3|OUT2|OUT1|LIM|IN7|IN6|IN5|IN4|IN3|IN2|IN1]・E・・E楯・鐃・E粛・・F0・E・7FF(Hex)
			short inoutlog = 0x81;
			Ret=SmcWSetCtrlInOutLog(Id,Cnt,inoutlog);
			if(Ret!=0)
				return ;

			//・E・E・E・・E・E・E・・E・E・E・E・E・・E・・E・・E・E・E縮・・鐃・
			Ret=SmcWSetOrgMode(Id,Cnt,1,0,2,0);
			if(Ret!=0)
				return ;

			//・E・E・E・E・E楯・鐃・E瞬・鐃・E縮・鐃・E・・E・E・E・・E・・E・・E・・E・・E・・E宿・鐃・E・
			Ret=SmcWSetInitParam(Id,Cnt);
			if(Ret!=0)
				return ;
		}
	}

	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly)==true){
		Data.Load(&File);
	}

	ShowDataToWindow();

	TM.setInterval(100);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));
	TM.start();

	PipeServer.Start();
}

ContecNC2D::~ContecNC2D()
{

}

void	ContecNC2D::ShowDataToWindow(void)
{
	ui.spinBoxMaxPulseX		->setValue(Data.MaxPulseX);
	ui.spinBoxMaxPulseY		->setValue(Data.MaxPulseY);
	ui.spinBoxStartPosX		->setValue(Data.StartPosX);
	ui.spinBoxStartPosY		->setValue(Data.StartPosY);
	ui.spinBoxStartVelocity	->setValue(Data.StartVelocity);
	ui.spinBoxAccel			->setValue(Data.AccelRate);

	ui.spinBoxScanPulse		->setValue(Data.ScanPulse);
	ui.spinBoxScanVelocity	->setValue(Data.ScanVelocity);
	ui.spinBoxStepPulse		->setValue(Data.StepPulse);
	ui.spinBoxStepVelocity	->setValue(Data.StepVelocity);
	ui.spinBoxScanCount		->setValue(Data.ScanCount);
	ui.spinBoxOriginVelocity->setValue(Data.OriginVelocity);
}

void	ContecNC2D::DataFromWindow(void)
{
	Data.MaxPulseX		=ui.spinBoxMaxPulseX		->value();
	Data.MaxPulseY		=ui.spinBoxMaxPulseY		->value();
	Data.StartPosX		=ui.spinBoxStartPosX		->value();
	Data.StartPosY		=ui.spinBoxStartPosY		->value();
	Data.StartVelocity	=ui.spinBoxStartVelocity	->value();
	Data.AccelRate		=ui.spinBoxAccel			->value();

	Data.ScanPulse		=ui.spinBoxScanPulse		->value();
	Data.ScanVelocity	=ui.spinBoxScanVelocity		->value();
	Data.StepPulse		=ui.spinBoxStepPulse		->value();
	Data.StepVelocity	=ui.spinBoxStepVelocity		->value();
	Data.ScanCount		=ui.spinBoxScanCount		->value();
	Data.OriginVelocity	=ui.spinBoxOriginVelocity	->value();
}

void ContecNC2D::SlotTimeOut()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	short	Val1;
	long	Ret=SmcWGetDigitalIn(Id,1,&Val1);
	if((Val1&0x20)!=0){
		ui.checkBoxAreaSensor->setChecked(true);
		AreaSewnsorON=false;
	}
	else{
		ui.checkBoxAreaSensor->setChecked(false);
		AreaSewnsorON=true;
	}

	if((Val1&0x10)!=0){
		ui.checkBoxFootSW->setChecked(true);
		FootSWON=true;
	}
	else{
		ui.checkBoxFootSW->setChecked(false);
		FootSWON=false;
	}
	if((Val1&0x40)!=0){
		ui.checkBoxEmergency->setChecked(true);
		EmergencyON	=false;
	}
	else{
		ui.checkBoxEmergency->setChecked(false);
		EmergencyON=true;
	}

	short	Val2;
	Ret=SmcWGetDigitalIn(Id,2,&Val2);
	if((Val2&0x20)!=0){
		ui.checkBoxStartButtonL->setChecked(true);
		LButtonON=true;
	}
	else{
		ui.checkBoxStartButtonL->setChecked(false);
		LButtonON=false;
	}
	if((Val2&0x40)!=0){
		ui.checkBoxStartButtonR->setChecked(true);
		RButtonON=true;
	}
	else{
		ui.checkBoxStartButtonR->setChecked(false);
		RButtonON=false;
	}

	if(lastFootSWON==false && FootSWON==true){
		if(FootVacuumON==false){
			FootVacuumON=true;
			ui.toolButtonVacuum->setChecked(true);
			on_toolButtonVacuum_clicked();
		}
		else{
			FootVacuumON=false;
			ui.toolButtonVacuum->setChecked(false);
			on_toolButtonVacuum_clicked();
		}
	}
	lastFootSWON=FootSWON;

	long	CurrentPulseX;
	Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
	long	CurrentPulseY;
	Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);
	ui.spinBoxCurrentPulseX	->setValue(CurrentPulseX);
	ui.spinBoxCurrentPulseY	->setValue(CurrentPulseY);

	ReEntrant=false;
}

bool	ContecNC2D::CheckOnMoving(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return true;
	ReEntrant=true;

	bool	ShouldStop=false;
	short	Val1;
	long	Ret=SmcWGetDigitalIn(Id,1,&Val1);
	if((Val1&0x20)!=0){
		ui.checkBoxAreaSensor->setChecked(true);
		AreaSewnsorON=false;
	}
	else{
		ui.checkBoxAreaSensor->setChecked(false);
		AreaSewnsorON=true;
		ShouldStop=true;
	}

	if((Val1&0x10)!=0){
		ui.checkBoxFootSW->setChecked(true);
		FootSWON=true;
	}
	else{
		ui.checkBoxFootSW->setChecked(false);
		FootSWON=false;
	}
	if((Val1&0x40)!=0){
		ui.checkBoxEmergency->setChecked(true);
		EmergencyON	=false;
	}
	else{
		ui.checkBoxEmergency->setChecked(false);
		EmergencyON=true;
		ShouldStop=true;
	}


	if(lastFootSWON==false && FootSWON==true){
		if(FootVacuumON==false){
			FootVacuumON=true;
			ui.toolButtonVacuum->setChecked(true);
			on_toolButtonVacuum_clicked();
		}
		else{
			FootVacuumON=false;
			ui.toolButtonVacuum->setChecked(false);
			on_toolButtonVacuum_clicked();
		}
	}
	lastFootSWON=FootSWON;

	if(ShouldStop==true){
		on_pushButtonStop_clicked();
		QMessageBox::warning(NULL,"Stop message","Stop",QMessageBox::Ok);
		ReEntrant=false;
		return false;
	}

	long	CurrentPulseX;
	Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
	long	CurrentPulseY;
	Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);
	ui.spinBoxCurrentPulseX	->setValue(CurrentPulseX);
	ui.spinBoxCurrentPulseY	->setValue(CurrentPulseY);

	ReEntrant=false;
	return true;
}

void ContecNC2D::on_pushButtonGoStartPos_clicked()
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

		//・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		//・E・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		//・E・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.StartVelocity/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.StartVelocity/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}


		//・E准・W・E・E・E・・E縮・・鐃・
		Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.StartVelocity);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.StartVelocity);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		bool	AttrToMoveX=false;
		if(CurrentPulseX!=-Data.StartPosX){
			Ret=SmcWSetStopPosition(Id,AxisXNum,0,-Data.StartPosX);	//0:・E・E・E塾・鐃・
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			AttrToMoveX=true;
		}
		bool	AttrToMoveY=false;
		if(CurrentPulseY!=-(Data.MaxPulseY-Data.StartPosY)){
			Ret=SmcWSetStopPosition(Id,AxisYNum,0,-(Data.MaxPulseY-Data.StartPosY));	//0:・E・E・E塾・鐃・
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			AttrToMoveY=true;
		}

		//・E・・E・・E・E・E・E・E・・E・E・E・E・E・・E・・E縮・・鐃・
		if(AttrToMoveX==true){
			Ret=SmcWSetReady(Id,AxisXNum,1,0);	//・E・E・E峻・鐃・E・ 1:PTP・E・E・E・E・0:・E・E・E・E・E・E・
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		if(AttrToMoveY==true){
			Ret=SmcWSetReady(Id,AxisYNum,1,0);	//・E・E・E峻・鐃・E・ 1:PTP・E・E・E・E・0:・E・E・E・E・E・E・
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}

		//・E・・E・E・E・E・E塾・・u・E准・鐃・
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
		//・E・E・E・・E・・E縮・鐃・E・・E・・E・E・E縮・・・
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

void ContecNC2D::on_pushButtonStartScan_clicked()
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
	try{
		Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
		Ret=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);

		//・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		//・E・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.StartVelocity/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		//・E准・W・E・E・E・・E縮・・鐃・
		Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.StartVelocity);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		bool	AttrToMoveX=false;
		if((CurrentScan&1)==0){
			AbsPos=-(Data.StartPosX+Data.ScanPulse);
			if(CurrentPulseX!=AbsPos){
				Ret=SmcWSetStopPosition(Id,AxisXNum,0,AbsPos);	//0:・E・E・E塾・鐃・
				if(Ret!=0){
					ReEntrant=false;
					return;
				}
				AttrToMoveX=true;
			}
		}
		else{
			AbsPos=-(Data.StartPosX);
			if(CurrentPulseX!=AbsPos){
				Ret=SmcWSetStopPosition(Id,AxisXNum,0,AbsPos);	//0:・E・E・E塾・鐃・
				if(Ret!=0){
					ReEntrant=false;
					return;
				}
				AttrToMoveX=true;
			}
		}
		if(AttrToMoveX==true){

			//・E・・E・・E・E・E・E・E・・E・E・E・E・E・・E・・E縮・・鐃・
			Ret=SmcWSetReady(Id,AxisXNum,1,0);	//・E・E・E峻・鐃・E・ 1:PTP・E・E・E・E・0:・E・E・E・E・E・E・
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			//・E・・E・E・E・E・E塾・・u・E准・鐃・
			Ret=SmcWMotionStart(Id,AxisXNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
	}
	catch(...){
	}
	CurrentScan++;
	ui.spinBoxCurrentScan->setValue(CurrentScan);
	GSleep(200);
	for(;;){
		//・E・E・E・・E・・E縮・鐃・E・・E・・E・E・E縮・・・
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

	Ret=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
	if(Ret==0 && CurrentPulseX==AbsPos && CurrentScan<Data.ScanCount){
		//・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		//・E・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.StartVelocity/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		//・E准・W・E・E・E・・E縮・・鐃・
		Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.StartVelocity);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}

		bool	AttrToMoveY=false;
		if(CurrentPulseY!=-(Data.MaxPulseY-(Data.StartPosY+Data.StepPulse*CurrentScan))){
			Ret=SmcWSetStopPosition(Id,AxisYNum,0,-(Data.MaxPulseY-(Data.StartPosY+Data.StepPulse*CurrentScan)));	//0:・E・E・E塾・鐃・
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			AttrToMoveY=true;
		}

		if(AttrToMoveY==true){
		//・E・・E・・E・E・E・E・E・・E・E・E・E・E・・E・・E縮・・鐃・
			Ret=SmcWSetReady(Id,AxisYNum,1,0);	//・E・E・E峻・鐃・E・ 1:PTP・E・E・E・E・0:・E・E・E・E・E・E・
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			//・E・・E・E・E・E・E塾・・u・E准・鐃・
			Ret=SmcWMotionStart(Id,AxisYNum);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}
		}
		for(;;){
			//・E・E・E・・E・・E縮・鐃・E・・E・・E・E・E縮・・・
			short val;
			Ret=SmcWGetMoveStatus(Id,AxisYNum, &val);
			if(Ret==0 && val==0){
				break;
			}
			if(CheckOnMoving()==false){
				break;
			}
			QCoreApplication::processEvents();
		}
	}
	else if(Ret==0 && CurrentPulseX==AbsPos && CurrentScan>=Data.ScanCount){
		on_pushButtonGoStartPos_clicked();
		for(;;){
			//・E・E・E・・E・・E縮・鐃・E・・E・・E・E・E縮・・・
			short val;
			Ret=SmcWGetMoveStatus(Id,AxisYNum, &val);
			if(Ret==0 && val==0){
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

void ContecNC2D::on_pushButtonJogYP_clicked()
{

}

void ContecNC2D::on_pushButtonJogYM_clicked()
{

}

void ContecNC2D::on_pushButtonJogXP_clicked()
{

}

void ContecNC2D::on_pushButtonJogXM_clicked()
{

}

void ContecNC2D::on_pushButtonGoOrigin_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	long	Ret;
	try{
		//・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetAccelTime(Id,AxisXNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		//・E・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetDecelTime(Id,AxisXNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetAccelTime(Id,AxisYNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		//・E・E・E・E・E・E・E峻・・・鐃・
		Ret=SmcWSetDecelTime(Id,AxisYNum,Data.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisXNum,Data.OriginVelocity/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.OriginVelocity/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}


		//・E准・W・E・E・E・・E縮・・鐃・
		Ret=SmcWSetTargetSpeed(Id,AxisXNum,Data.OriginVelocity);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.OriginVelocity);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
	}
	catch(...){}
	long Ret1,Ret2,Ret3=0,Ret4;
	Ret1=SmcWSetReady(Id,1,3,0);	// ・E・E・E峻・鐃・E・ 3:・E・E・E・・E・E・E・・E・E・E・E・0:・E・E・E・E・E・E・
	Ret2=SmcWSetReady(Id,2,3,0);	// ・E・E・E峻・鐃・E・ 3:・E・E・E・・E・E・E・・E・E・E・E・0:・E・E・E・E・E・E・
	Ret3=SmcWSetReady(Id,3,3,0);	// ・E・E・E峻・鐃・E・ 3:・E・E・E・・E・E・E・・E・E・E・E・0:・E・E・E・E・E・E・
	Ret4=SmcWSetReady(Id,4,3,0);	// ・E・E・E峻・鐃・E・ 3:・E・E・E・・E・E・E・・E・E・E・E・0:・E・E・E・E・E・E・
	if(Ret1!=0 && Ret2!=0 && Ret3!=0 && Ret4!=0){
		ReEntrant=false;
		return;
	}

	if(Ret1==0){
		Ret1=SmcWMotionStart(Id,1);
	}
	if(Ret2==0){
		Ret2=SmcWMotionStart(Id,2);
	}
	if(Ret3==0){
		Ret3=SmcWMotionStart(Id,3);
	}
	if(Ret4==0){
		Ret4=SmcWMotionStart(Id,4);
	}
	GSleep(200);
	for(;;){
		//・E・E・E・・E・・E縮・鐃・E・・E・・E・E・E縮・・・
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
	ReEntrant=false;
}

void ContecNC2D::on_pushButtonConvertToScan_clicked()
{
	int	BoardSizeX=ui.spinBoxBoardSizeX->value();
	int	BoardSizeY=ui.spinBoxBoardSizeY->value();
	int	SpaceY		=ui.spinBoxSpaceY->value();
}

void ContecNC2D::on_pushButtonSave_clicked()
{
	DataFromWindow();
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		Data.Save(&File);
	}
}

void ContecNC2D::on_toolButtonVacuum_clicked()
{
	if(ui.toolButtonVacuum->isChecked()==true)
		SmcWSetDigitalOut(Id,1,1,1);
	else
		SmcWSetDigitalOut(Id,1,0,1);
}

void ContecNC2D::on_pushButtonStop_clicked()
{
		//・E・E・E・E・E・
	long	Ret;
	Ret=SmcWSetDecelTime(Id,1,50);
	Ret=SmcWSetDecelTime(Id,2,50);
	Ret=SmcWSetDecelTime(Id,3,50);
	Ret=SmcWSetDecelTime(Id,4,50);

	long Ret1,Ret2,Ret3,Ret4;
	Ret1=SmcWMotionDecStop(Id,1);
	Ret2=SmcWMotionDecStop(Id,2);
	Ret3=SmcWMotionDecStop(Id,3);
	Ret4=SmcWMotionDecStop(Id,4);
	if(Ret1!=0)
		return;
	if(Ret2!=0)
		return;
	if(Ret3!=0)
		return;
	if(Ret4!=0)
		return;
}

void ContecNC2D::on_toolButtonPatlightR_clicked()
{
	if(ui.toolButtonPatlightR->isChecked()==true)
		SmcWSetDigitalOut(Id,3,1,1);
	else
		SmcWSetDigitalOut(Id,3,0,1);
}

void ContecNC2D::on_toolButtonPatlightY_clicked()
{
	if(ui.toolButtonPatlightY->isChecked()==true)
		SmcWSetDigitalOut(Id,3,2,2);
	else
		SmcWSetDigitalOut(Id,3,0,2);
}

void ContecNC2D::on_toolButtonPatlightG_clicked()
{
	if(ui.toolButtonPatlightG->isChecked()==true)
		SmcWSetDigitalOut(Id,3,4,4);
	else
		SmcWSetDigitalOut(Id,3,0,4);
}

void	ContecNC2D::ExeStart()
{
	on_pushButtonGoStartPos_clicked();

}
void	ContecNC2D::ExeStep()
{
	on_pushButtonStartScan_clicked();
}
bool	ContecNC2D::IsEnd()
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
bool	ContecNC2D::IsStartButton()
{
	if(FootVacuumON==true
	&& RButtonON==true
	&& LButtonON==true
	&& AreaSewnsorON==false
	&& EmergencyON==false){
		return true;
	}
	return false;
}
