#include "ContecNC4D.h"
#include <QFile>
#include "Windows.h"
#include "math.h"
#include "CSmc.h"
#include "CSmcdef.h"
#include "XGeneralFunc.h"
#include "SettingDialog.h"
#include "XCriticalFunc.h"
#include "CDio.h"

QString	FileName="ContecNC4D.dat";


PIOAccess::PIOAccess(char *_DeviceName)
{
	Id=-1;
	strcpy(DeviceName,_DeviceName);
}
PIOAccess::~PIOAccess(void)
{
	if(Id>=0){
		DioExit(Id);
	}
}

bool	PIOAccess::Initial(void)
{
	long Ret;

	char tDeviceName[256];
	char tDevice[256];
	Id=-1;
	for(int i=0;i<256;i++){
		Ret = DioQueryDeviceName ( i , tDeviceName , tDevice );
		if(Ret!=DIO_ERR_SUCCESS)
			return false;
		if(strcmp(DeviceName,tDeviceName)==0){
			Ret = DioInit ( DeviceName , &Id );
			if(Ret != 0)
				return false;
			break;
		}
	}
	if(Id<0)
		return false;
	return true;
}

bool	PIOAccess::SetBit(int bitNo ,int n)
{
	BYTE	Data=n;
	long	Ret = DioOutBit(Id, bitNo, Data);
	return true;
}
bool	PIOAccess::SetBit(int bitNo ,bool n)
{
	BYTE	Data=(n==true)?1:0;
	long	Ret = DioOutBit(Id, bitNo, Data);
	return true;
}
bool		PIOAccess::GetBit(int bitNo)
{
	BYTE	InData;
	long	Ret = DioInpBit ( Id , bitNo , &InData );
	return (InData==0)?false:true;
}

#define		BitNo_IAI_OUT_SVON		0		
#define		BitNo_IAI_OUT_Reset		1
#define		BitNo_IAI_OUT_Home		2
#define		BitNo_IAI_OUT_TL		3
#define		BitNo_IAI_OUT_CSTP		4
#define		BitNo_IAI_OUT_DCLR		5
#define		BitNo_IAI_OUT_BKRL		6
#define		BitNo_IAI_OUT_RMOD		7

#define		BitNo_IAI_IN_ALM		-1
#define		BitNo_IAI_IN_PWR		3
#define		BitNo_IAI_IN_SV			2
#define		BitNo_IAI_IN_INP		4
#define		BitNo_IAI_IN_HEND		5
#define		BitNo_IAI_IN_EMGS		6
#define		BitNo_IAI_IN_RMOD		7
#define		BitNo_IAI_IN_ZONE1		-1
#define		BitNo_IAI_IN_ZONE2		-1

//=============================================================================

ContecNC4D::ContecNC4D(char *SMCDeviceName ,char *PIODeviceName ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),PipeServer(this),PIO(PIODeviceName)
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

	long	Ret = SmcWInit( SMCDeviceName , &Id );
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

			Ret=SmcWSetPulseType(Id,4,1,0);
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
	PIO.Initial();

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

	ui.toolButtonSVONW->setChecked(true);
	on_toolButtonSVONW_clicked();
}

ContecNC4D::~ContecNC4D()
{

}

void ContecNC4D::on_pushButtonGoOriginXY_clicked()
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
	Ret1=SmcWSetReady(Id,AxisXNum,3,1);	// ・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E峻・鐃・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・ 3:・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・0:・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・
	Ret2=SmcWSetReady(Id,AxisYNum,3,1);	// ・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E峻・鐃・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・ 3:・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・0:・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・・E・
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

void ContecNC4D::on_pushButtonStartScanXY_clicked()
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

void ContecNC4D::on_pushButtonStopXY_clicked()
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

void ContecNC4D::on_pushButtonGoStartPosXY_clicked()
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

void ContecNC4D::on_toolButtonJogYP_clicked()
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

void ContecNC4D::on_toolButtonJogXP_clicked()
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

void ContecNC4D::on_toolButtonJogXM_clicked()
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

void ContecNC4D::on_toolButtonJogYM_clicked()
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

void ContecNC4D::on_pushButtonGoOriginZ_clicked()
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

void ContecNC4D::on_pushButtonStartScanZ_clicked()
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

void ContecNC4D::on_pushButtonStopZ_clicked()
{
	long	Ret;
	Ret=SmcWSetDecelTime(Id,AxisZNum,50);
	Ret=SmcWMotionDecStop(Id,AxisZNum);
	if(Ret!=0)
		return;
}

void ContecNC4D::on_toolButtonJogZM_clicked()
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

void ContecNC4D::on_toolButtonJogZP_clicked()
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

void ContecNC4D::on_toolButtonVacuum_clicked()
{
	if(ui.toolButtonVacuum->isChecked()==true)
		SmcWSetDigitalOut(Id,2,1,1);
	else
		SmcWSetDigitalOut(Id,2,0,1);
}

void ContecNC4D::on_toolButtonPatlightR_clicked()
{
	if(ui.toolButtonPatlightR->isChecked()==true)
		SmcWSetDigitalOut(Id,4,4,4);
	else
		SmcWSetDigitalOut(Id,4,0,4);
}

void ContecNC4D::on_toolButtonPatlightY_clicked()
{
	if(ui.toolButtonPatlightY->isChecked()==true)
		SmcWSetDigitalOut(Id,4,2,2);
	else
		SmcWSetDigitalOut(Id,4,0,2);
}

void ContecNC4D::on_toolButtonPatlightG_clicked()
{
	if(ui.toolButtonPatlightG->isChecked()==true)
		SmcWSetDigitalOut(Id,4,1,1);
	else
		SmcWSetDigitalOut(Id,4,0,1);
}

bool	ContecNC4D::CheckOnMoving(void)
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
void ContecNC4D::on_toolButtonSwitchLampL_clicked()
{
	if(ui.toolButtonSwitchLampL->isChecked()==true)
		SmcWSetDigitalOut(Id,2,2,2);
	else
		SmcWSetDigitalOut(Id,2,0,2);
}

void ContecNC4D::on_toolButtonSwitchLampR_clicked()
{
	if(ui.toolButtonSwitchLampR->isChecked()==true)
		SmcWSetDigitalOut(Id,2,4,4);
	else
		SmcWSetDigitalOut(Id,2,0,4);
}

void ContecNC4D::on_toolButtonDirectionDignal_clicked()
{
	if(ui.toolButtonDirectionDignal->isChecked()==true)
		SmcWSetDigitalOut(Id,3,1,1);
	else
		SmcWSetDigitalOut(Id,3,0,1);
}

void ContecNC4D::on_toolButtonBlinkMode_clicked()
{

}

void ContecNC4D::on_pushButtonGoOriginW_clicked()
{
	ui.toolButtonHomeW->setChecked(false);
	on_toolButtonHomeW_clicked();

	ui.toolButtonSVONW	->setChecked(false);
	on_toolButtonSVONW_clicked();
	GSleep(1000);
	ui.toolButtonSVONW	->setChecked(true);
	on_toolButtonSVONW_clicked();
	GSleep(1000);

	ui.toolButtonResetW->setChecked(true);
	on_toolButtonResetW_clicked();
	GSleep(1000);
	ui.toolButtonResetW->setChecked(false);
	on_toolButtonResetW_clicked();
	GSleep(1000);

	ui.toolButtonHomeW->setChecked(true);
	on_toolButtonHomeW_clicked();
	GSleep(300);

	short	LimitSts4;
	do{
		SmcWGetLimitStatus( Id , AxisWNum , &LimitSts4 );
	}while((LimitSts4&0x02)!=0);

	SmcWSetCountPulse( Id , AxisWNum , 0 );
	SmcWSetOutPulse( Id , AxisWNum , 0 );
	ui.toolButtonHomeW->setChecked(false);
	on_toolButtonHomeW_clicked();
}

void ContecNC4D::on_pushButtonStartScanW_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	long	Ret;
	long	AbsPos;
	long	CurrentPulseW;
	try{
		Ret=SmcWGetOutPulse(Id,AxisWNum, &CurrentPulseW);

		Ret=SmcWSetAccelTime(Id,AxisWNum,Data.AxisW.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisWNum,Data.AxisW.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.VelocityW)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetTargetSpeed(Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.VelocityW));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		bool	AttrToMoveY=false;
		AbsPos=Data.AxisW.GetPulseFromMM(Data.PosW);
		if(CurrentPulseW!=AbsPos){
			Ret=SmcWSetStopPosition(Id,AxisWNum,0,AbsPos);	
			if(Ret!=0){
				ReEntrant=false;
				return;
			}

			Ret=SmcWSetReady(Id,AxisWNum,1,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisWNum);
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
		Ret=SmcWGetMoveStatus(Id,AxisWNum, &val);
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

void ContecNC4D::on_pushButtonStopW_clicked()
{
	long	Ret;
	Ret=SmcWSetDecelTime(Id,AxisWNum,50);
	Ret=SmcWMotionDecStop(Id,AxisWNum);
	if(Ret!=0)
		return;
}

void ContecNC4D::on_toolButtonJogWM_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogWM->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseW;
			Ret=SmcWGetOutPulse(Id,AxisWNum, &CurrentPulseW);

			Ret=SmcWSetAccelTime(Id,AxisWNum,Data.AxisW.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisWNum,Data.AxisW.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.AxisW.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.AxisW.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWSetReady(Id,AxisWNum,2,1);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisWNum);
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
		Ret=SmcWMotionDecStop(Id,AxisWNum);
	}
	ReEntrant=false;
}

void ContecNC4D::on_toolButtonJogWP_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();
	if(ui.toolButtonJogWP->isChecked()==true){
		long	Ret;
		try{
			long	CurrentPulseW;
			Ret=SmcWGetOutPulse(Id,AxisWNum, &CurrentPulseW);
				
			Ret=SmcWSetAccelTime(Id,AxisWNum,Data.AxisW.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetDecelTime(Id,AxisWNum,Data.AxisW.AccelRate);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			Ret=SmcWSetStartSpeed( Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.AxisW.JogVelocity)/20);
			if(Ret!=0){
				ReEntrant=false;
				return;
			}


			Ret=SmcWSetTargetSpeed(Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.AxisW.JogVelocity));
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWSetReady(Id,AxisWNum,2,0);
			if(Ret!=0){
				ReEntrant=false;
				return ;
			}

			Ret=SmcWMotionStart(Id,AxisWNum);
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
		Ret=SmcWMotionDecStop(Id,AxisWNum);
	}
	ReEntrant=false;
}

void ContecNC4D::on_pushButtonGoVRS_clicked()
{
	double	VRSX=ui.doubleSpinBoxVRSX	->value();
	double	VRSY=ui.doubleSpinBoxVRSY	->value();
	GoMoveVRS(VRSX,VRSY);
}
void ContecNC4D::GoMoveVRS(double VRSX,double VRSY)
{
	GoMoveVRS(Data.AxisW.GetPulseFromMM(VRSX),Data.AxisY.GetPulseFromMM(VRSY));
}

void ContecNC4D::GoMoveVRS(int VRSX,int VRSY)
{
	static	bool	ReEntrant=false;
	if(ReEntrant==true)
		return;
	ReEntrant=true;

	DataFromWindow();

	long	Ret;
	long	AbsPos;
	long	CurrentPulseW;
	long	CurrentPulseY;
	bool	AttrToMoveY=false;
	bool	AttrToMoveX=false;
	try{
		Ret=SmcWGetOutPulse(Id,AxisWNum, &CurrentPulseW);
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

		Ret=SmcWSetStartSpeed( Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.MaxVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetTargetSpeed(Id,AxisYNum,Data.AxisY.GetPulseFromMM(Data.AxisY.MaxVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}

		if(CurrentPulseY!=VRSY){
			Ret=SmcWSetStopPosition(Id,AxisYNum,0,VRSY);	
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			AttrToMoveY=true;
		}

		SmcWSetDigitalOut(Id,3,0,1);	//Set trigger to backside 


		Ret=SmcWSetAccelTime(Id,AxisWNum,Data.AxisW.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}
		Ret=SmcWSetDecelTime(Id,AxisWNum,Data.AxisW.AccelRate);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetStartSpeed( Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.AxisW.MaxVelocity)/20);
		if(Ret!=0){
			ReEntrant=false;
			return;
		}

		Ret=SmcWSetTargetSpeed(Id,AxisWNum,Data.AxisW.GetPulseFromMM(Data.AxisW.MaxVelocity));
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
		if(CurrentPulseW!=VRSX){
			Ret=SmcWSetStopPosition(Id,AxisWNum,0,VRSX);	
			if(Ret!=0){
				ReEntrant=false;
				return;
			}
			AttrToMoveX=true;
		}
	}
	catch(...){
	}
	if(AttrToMoveX==true){
		Ret=SmcWSetReady(Id,AxisWNum,1,0);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}		
		Ret=SmcWMotionStart(Id,AxisWNum);
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
		Ret=SmcWMotionStart(Id,AxisYNum);
		if(Ret!=0){
			ReEntrant=false;
			return ;
		}
	}
	GSleep(200);
	for(;;){
		short valY;
		short valW;
		long	RetY=SmcWGetMoveStatus(Id,AxisYNum, &valY);
		long	RetW=SmcWGetMoveStatus(Id,AxisWNum, &valW);
		if(RetY==0 && valY==0 && RetW==0 && valW==0){
			break;
		}
		if(CheckOnMoving()==false){
			ReEntrant=false;
			return ;
			break;
		}
		QCoreApplication::processEvents();
	}

	ReEntrant=false;
}

void ContecNC4D::on_pushButtonConvertToScan_clicked()
{

}

void ContecNC4D::on_toolButtonEnableAreaSensor_clicked()
{

}

void ContecNC4D::on_toolButtonEnableDoorSensor_clicked()
{

}

void ContecNC4D::on_toolButtonAW0X_clicked()
{
	if(ui.toolButtonAW0X->isChecked()==true)
		SmcWSetDigitalOut(Id,1,2,2);
	else
		SmcWSetDigitalOut(Id,1,0,2);
}

void ContecNC4D::on_toolButtonFreeX_clicked()
{
	if(ui.toolButtonFreeX->isChecked()==true)
		SmcWSetDigitalOut(Id,1,4,4);
	else
		SmcWSetDigitalOut(Id,1,0,4);
}

void ContecNC4D::on_toolButtonAlmRstX_clicked()
{
	if(ui.toolButtonAlmRstX->isChecked()==true)
		SmcWSetDigitalOut(Id,1,1,1);
	else
		SmcWSetDigitalOut(Id,1,0,1);
}

void ContecNC4D::on_toolButtonAW0Y_clicked()
{
	if(ui.toolButtonAW0Y->isChecked()==true)
		SmcWSetDigitalOut(Id,1,2,2);
	else
		SmcWSetDigitalOut(Id,1,0,2);
}

void ContecNC4D::on_toolButtonFreeY_clicked()
{
	if(ui.toolButtonFreeY->isChecked()==true)
		SmcWSetDigitalOut(Id,1,4,4);
	else
		SmcWSetDigitalOut(Id,1,0,4);
}

void ContecNC4D::on_toolButtonAlmRstY_clicked()
{
	if(ui.toolButtonAlmRstY->isChecked()==true)
		SmcWSetDigitalOut(Id,1,1,1);
	else
		SmcWSetDigitalOut(Id,1,0,1);
}

void ContecNC4D::on_toolButtonAW0Z_clicked()
{
	if(ui.toolButtonAW0Z->isChecked()==true)
		SmcWSetDigitalOut(Id,AxisZNum,2,2);
	else
		SmcWSetDigitalOut(Id,AxisZNum,0,2);
}

void ContecNC4D::on_toolButtonFreeZ_clicked()
{
	if(ui.toolButtonFreeZ->isChecked()==true)
		SmcWSetDigitalOut(Id,AxisZNum,4,4);
	else
		SmcWSetDigitalOut(Id,AxisZNum,0,4);
}

void ContecNC4D::on_toolButtonAlmRstZ_clicked()
{
	if(ui.toolButtonAlmRstZ->isChecked()==true)
		SmcWSetDigitalOut(Id,1,1,1);
	else
		SmcWSetDigitalOut(Id,1,0,1);
}


void ContecNC4D::on_toolButtonSVONW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_SVON,ui.toolButtonSVONW->isChecked());
}

void ContecNC4D::on_toolButtonResetW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_Reset,ui.toolButtonResetW->isChecked());
}

void ContecNC4D::on_toolButtonHomeW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_Home,ui.toolButtonHomeW->isChecked());
}

void ContecNC4D::on_toolButtonTLW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_TL,ui.toolButtonTLW->isChecked());
}

void ContecNC4D::on_toolButtonCSTPW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_CSTP,ui.toolButtonCSTPW->isChecked());
}

void ContecNC4D::on_toolButtoDCLRW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_DCLR,ui.toolButtoDCLRW->isChecked());
}

void ContecNC4D::on_toolButtonBKRLW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_BKRL,ui.toolButtonBKRLW->isChecked());
}

void ContecNC4D::on_toolButtonRModW_clicked()
{
	PIO.SetBit(BitNo_IAI_OUT_RMOD,ui.toolButtonRModW->isChecked());
}

void ContecNC4D::on_pushButtonSave_clicked()
{
	DataFromWindow();
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		Data.Save(&File);
	}
}

void ContecNC4D::on_pushButtonSetting_clicked()
{
	SettingDialog	D(&Data,this);
	if(D.exec()==(int)true){
		on_pushButtonSave_clicked();
		SetLimitation();
	}
}

void	ContecNC4D::ShowDataToWindow(void)
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
	ui.doubleSpinBoxPosW	->setValue(Data.PosW);
	ui.spinBoxVelocityW		->setValue(Data.VelocityW);
	ui.spinBoxScanCount		->setValue(Data.ScanCount);
	ui.toolButtonEnableAreaSensor	->setChecked(Data.EnableAreaSensor);
	ui.toolButtonEnableDoorSensor	->setChecked(Data.EnableDoorSensor);
}
void	ContecNC4D::DataFromWindow(void)
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
	Data.PosW			=ui.doubleSpinBoxPosW	->value();
	Data.VelocityW		=ui.spinBoxVelocityW	->value();
	Data.ScanCount		=ui.spinBoxScanCount	->value();
	Data.EnableAreaSensor	=ui.toolButtonEnableAreaSensor	->isChecked();
	Data.EnableDoorSensor	=ui.toolButtonEnableDoorSensor	->isChecked();
}


void ContecNC4D::SlotTimeOut()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	short	Val1;
	short	Val2;
	short	Val3;
	short	Val4;
	long	Ret1=SmcWGetDigitalIn(Id,1,&Val1);
	long	Ret2=SmcWGetDigitalIn(Id,2,&Val2);
	long	Ret3=SmcWGetDigitalIn(Id,2,&Val3);
	long	Ret4=SmcWGetDigitalIn(Id,2,&Val4);

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
	short	LimitSts4;
	Ret3 = SmcWGetLimitStatus( Id , AxisWNum , &LimitSts4 );



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

	ui.checkBoxALMW		->setChecked(((LimitSts4&0x01)!=0)?true:false);	
	ui.checkBoxPWRW		->setChecked(((Val4&(0x01<<(BitNo_IAI_IN_PWR-1 )))!=0)?true:false);
	ui.checkBoxSVW		->setChecked(((Val4&(0x01<<(BitNo_IAI_IN_SV-1  )))!=0)?true:false);
	ui.checkBoxINPW		->setChecked(((Val4&(0x01<<(BitNo_IAI_IN_INP-1 )))!=0)?true:false);
	ui.checkBoxHENDW	->setChecked(((Val4&(0x01<<(BitNo_IAI_IN_HEND-1)))!=0)?true:false);
	ui.checkBoxEMGSW	->setChecked(((Val4&(0x01<<(BitNo_IAI_IN_EMGS-1)))!=0)?true:false);
	ui.checkBoxRMODSW	->setChecked(((Val4&(0x01<<(BitNo_IAI_IN_RMOD-1)))!=0)?true:false);
	ui.checkBoxZone1W	->setChecked(((LimitSts4&0x02)!=0)?true:false);
	ui.checkBoxZone2W	->setChecked(((LimitSts4&0x04)!=0)?true:false);

	long	CurrentPulseX;
	long	RetX=SmcWGetOutPulse(Id,AxisXNum, &CurrentPulseX);
	long	CurrentPulseY;
	long	RetY=SmcWGetOutPulse(Id,AxisYNum, &CurrentPulseY);
	long	CurrentPulseZ;
	long	RetZ=SmcWGetOutPulse(Id,AxisZNum, &CurrentPulseZ);
	long	CurrentPulseW;
	long	RetW=SmcWGetOutPulse(Id,AxisWNum, &CurrentPulseW);

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
	if(RetW==0){
		ui.spinBoxCurrentPulseW		->setValue(CurrentPulseW);
		ui.lineEditCurrentPosMMW	->setText(QString::number(Data.AxisW.GetMMFromPulse(CurrentPulseW),'f',2));
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
	int	AlarmCode	=	((PIO.GetBit(0)==true)?1:0)
					   +((PIO.GetBit(1)==true)?2:0)
					   +((PIO.GetBit(2)==true)?4:0)
					   +((PIO.GetBit(3)==true)?8:0);

	ui.lineEdiAlarmCodeW	->setText(QString::number(AlarmCode));
		
	ReEntrant=false;
}
void	ContecNC4D::ExeOrigin(void)
{
	CommandLeaf	*a=new CommandOrigin(this);
	CommandQueue.AppendList(a);
}
void	ContecNC4D::ExeStartXY()
{
	CommandLeaf	*a=new CommandGotoXY(this);
	CommandQueue.AppendList(a);
}
void	ContecNC4D::ExeStepXY()
{
	CommandLeaf	*a=new CommandStepXY(this);
	CommandQueue.AppendList(a);
}
void	ContecNC4D::ExeMoveVRS(int VRSX ,int VRSY)
{
	CommandGotoVRS	*a=new CommandGotoVRS(this);
	a->X=VRSX;
	a->Y=VRSY;
	CommandQueue.AppendList(a);
}
bool	ContecNC4D::IsEndXY()
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
void	ContecNC4D::ExeStartZ(int ZMicron)
{
	CommandMoveZ	*a=new CommandMoveZ(this);
	a->ZMicron=ZMicron;
	CommandQueue.AppendList(a);
}
bool	ContecNC4D::IsEndZ()
{
	short valZ;
	long	RetZ=SmcWGetMoveStatus(Id,AxisZNum, &valZ);
	if(RetZ==0 && valZ==0){
		return true;
	}
	return false;
}
bool	ContecNC4D::IsStartButton()
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

bool	ContecNC4D::IsAreaSensorON()
{
	if((CoverSensorON==false || Data.EnableDoorSensor==false)
	&& (AreaSensorON==true && Data.EnableAreaSensor==true)
	&& EmergencyON==false){
		return true;
	}
	return false;
}

void	ContecNC4D::SetLightGreen(bool b)
{
	ui.toolButtonPatlightG->setChecked(b);
	on_toolButtonPatlightG_clicked();
}
void	ContecNC4D::SetBlink(bool b)
{
	ui.toolButtonBlinkMode->setChecked(b);
}

void	ContecNC4D::GoMoveZ(int ZMicron)
{
	Data.PosZ=ZMicron/1000.0;
	ShowDataToWindow();
	on_pushButtonStartScanZ_clicked();
}

void	ContecNC4D::SlotCommandTimeOut()
{
	CommandLeaf	*a=CommandQueue.GetFirst();
	if(a!=NULL){
		CommandQueue.RemoveList(a);
		a->Execute();
		delete	a;
	}
}
void	ContecNC4D::SetVacuum(bool b)
{
	ui.toolButtonVacuum->setChecked(b);
	on_toolButtonVacuum_clicked();
	LastVacuumMode=b;
}
void	ContecNC4D::SetLaserPointer(bool b)
{
	ui.toolButtonLaserPointer->setChecked(b);
	on_toolButtonLaserPointer_clicked();
}
void ContecNC4D::SetLimitation(void)
{
	long	Ret;
	//Ret=SmcWSetSoftLimit( Id, AxisXNum, 1, 1, Data.AxisX.GetPulseFromMM(Data.AxisX.MaxLength), 0 );
	//Ret=SmcWSetSoftLimit( Id, AxisYNum, 1, 1, Data.AxisY.GetPulseFromMM(Data.AxisY.MaxLength), 0 );
	//Ret=SmcWSetSoftLimit( Id, AxisZNum, 1, 1, Data.AxisZ.GetPulseFromMM(Data.AxisZ.MaxLength), 0 );
}
void ContecNC4D::on_toolButtonLaserPointer_clicked()
{

}

//-----------------------------------------------------------

void	CommandOrigin::Execute(void)
{
	Parent->on_pushButtonGoOriginXY_clicked();
	Parent->on_pushButtonGoOriginZ_clicked();
	Parent->on_pushButtonGoOriginW_clicked();
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

void	CommandGotoVRS::Execute(void)
{
	Parent->GoMoveVRS(X,Y);
}

