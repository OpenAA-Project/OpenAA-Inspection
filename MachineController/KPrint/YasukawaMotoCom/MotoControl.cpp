#include <direct.h>
#include <windef.h>
#include "MotoCom.h"
#include "XMotorCommon.h"
#include "XGeneralFunc.h"

short	MotoOpenCom(const char *IPAddress,int &ErrorCode,HWND hWnd)
{
	short	Cid=BscOpen((char *)"c:\\Data",16);
	short	Ret;
	if(Cid>=0){
		Ret=BscSetEther(Cid, (char *)IPAddress,0,hWnd);
		if(Ret!=0){
			Ret=BscConnect(Cid);
			if(Ret!=0){
				ErrorCode=0;
				return Cid;
			}
			Ret=BscReConnect(Cid);
			if(Ret==1){
				ErrorCode=0;
				return Cid;
			}
		}
	}
	if(Cid==-8){
		ErrorCode=_NoLicenseKey;
		return -1;
	}
	ErrorCode=Cid;
	return -1;
}

bool	MotoCloseCom(short Cid)
{
	short	Ret;
	Ret=BscDisConnect(Cid);
	if(Ret!=0){
		Ret=BscClose(Cid);
		if(Ret==0){
			return true;
		}
	}
	return false;
}

bool    MotoServoOn(short Cid)
{
	if(Cid>=0){
		short	ErrorCode=BscOPUnLock(Cid);
		if(ErrorCode!=0){
			return false;
		}
		short	SvOn=BscIsServo(Cid);
		if(SvOn==0){
			ErrorCode=BscServoOn(Cid);
			if(ErrorCode==0){
				return true;
			}
		}
		else if(SvOn==1){
			return true;
		}
	}
	return false;
}
bool    MotoServoOff(short Cid)
{
	if(Cid>=0){
		short	SvOn=BscIsServo(Cid);
		if(SvOn==0){
			return true;
		}
		else if(SvOn==1){
			short	ErrorCode=BscServoOff(Cid);
			if(ErrorCode==0){
				return true;
			}
		}
	}
	return false;
}
bool    MotoHoldOn(short Cid)
{
	if(Cid>=0){
		short	ErrorCode=BscHoldOn(Cid);
		if(ErrorCode==0){
			return true;
		}
	}
	return false;
}
bool    MotoHoldOff(short Cid)
{
	if(Cid>=0){
		short	ErrorCode=BscHoldOff(Cid);
		if(ErrorCode==0){
			return true;
		}
	}
	return false;
}
bool    MotoGetStatus(short Cid ,unsigned short Status[2])
{
	short	Ret=BscGetStatus(Cid,&Status[0],&Status[1]);
	if(Ret!=-1){
		return true;
	}
	return false;
}


bool    MotoGetPulsePos(short Cid ,double Pos[16])
{
	if(Cid>=0){
		for(int i=0;i<_CmdRetryCount;i++){
			short	Ret=BscGetPulsePos(Cid,Pos);
			if(Ret==0){
				return true;
			}
			GSleep(100);
		}
	}
	return false;
}

bool    MotoGetTorque(short Cid ,double Torque[16])
{
	if(Cid>=0){
		short	Ret=BscGetTorque(Cid,Torque);
		if(Ret==0){
			return true;
		}
	}
	return false;
}


bool    MotoGetRobotPos(short Cid ,double Pos[16])
{
	if(Cid>=0){
		unsigned short	rconf[16];
		for(int i=0;i<_CmdRetryCount;i++){
			short	Ret=BscIsLoc(Cid,0,rconf,Pos);
			if(Ret==0){
				return true;
			}
			GSleep(100);
		}
	}
	return false;
}
bool    MotoMovRelRobotPos(short Cid  ,double Speed ,double RobotPos[16])
{
	if(Cid>=0){
		for(int i=0;i<_CmdRetryCount;i++){
			short	Ret=BscImov(Cid,(char *)"V",Speed,(char *)"BASE",0,RobotPos);
			if(Ret==0){
				return true;
			}
			GSleep(100);
		}
	}
	return false;
}
bool    MotoMovAbdRobotPos(short Cid ,double Speed ,double RobotPos[16])
{
	if(Cid>=0){
		for(int i=0;i<_CmdRetryCount;i++){
			short	Ret=BscMov(Cid,(char *)"MOVL",(char *)"V",Speed,(char *)"BASE",0,0,RobotPos);
			if(Ret==0){
				return true;
			}
			GSleep(100);
		}
	}
	return false;
}
bool    MotoMovPulsePos(short Cid ,double SpeedPercent ,double PulsePos[16])
{
	if(Cid>=0){
		short	Ret=BscPMovj(Cid,SpeedPercent,0,PulsePos);
		if(Ret==0){
			return true;
		}
	}
	return false;
}

bool    MotoStop(short Cid)
{
	if(Cid>=0){
		for(int i=0;i<_CmdRetryCount;i++){
			short	ErrorCode=BscHoldOn(Cid);
			if(ErrorCode==0){
				return true;
			}
			GSleep(100);
		}
		//double RobotPos[16];
		//for(int i=0;i<16;i++){
		//	RobotPos[i]=0;
		//}
		//short	Ret=BscImov(Cid,(char *)"V",0.1,(char *)"ROBOT",0,RobotPos);
		//if(Ret==0){
		//	return true;
		//}
	}
	return false;
}
bool    MotoIsServoON(short Cid)
{
	if(Cid>=0){
		short	Ret=BscIsServo(Cid);
		if(Ret==1)
			return true;
	}
	return false;
}

bool	MotoIsHoldOn(short Cid)
{
	if(Cid>=0){
		short	Ret=BscIsHold(Cid);
		if(Ret==0)
			return false;
	}
	return true;
}

bool    MotoWriteIO(short Cid ,int Addr ,unsigned char value[32])
//value=0.01mm ’PˆÊ
{
	if(Cid>=0){
		unsigned short stat[256];
		for(int n=0;n<32;n++){
			stat[n]=value[n];
		}
		short	Ret=BscWriteIO2(Cid,27010+Addr,256,stat);
		if(Ret==0)
			return true;
	}
	return false;
}
bool    MotoReadIO (short Cid ,int Addr ,unsigned char value[32])
//value=0.01mm ’PˆÊ
{
	if(Cid>=0){
		unsigned short stat[256];

		short	Ret=BscReadIO2(Cid,27010+Addr,256,stat);
		if(Ret==0){
			for(int n=0;n<32;n++){
				value[n]=stat[n];
			}
			return true;
		}
	}
	return false;
}
