#pragma once

#define	_CmdRetryCount		5
#define _NoLicenseKey		1

short	MotoOpenCom(const char *IPAddress,int &ErrorCode,HWND hWnd);
bool	MotoCloseCom(short Cid);
bool    MotoServoOn(short Cid);
bool    MotoServoOff(short Cid);
bool    MotoHoldOn(short Cid);
bool    MotoHoldOff(short Cid);
bool    MotoGetStatus(short Cid ,unsigned short Status[2]);
bool    MotoGetPulsePos(short Cid ,double Pos[16]);
bool    MotoGetTorque(short Cid ,double Torque[16]);
bool    MotoGetRobotPos(short Cid ,double RobotPos[16]);
bool    MotoMovRelRobotPos(short Cid ,double Speed ,double RobotPos[16]);
bool    MotoMovAbdRobotPos(short Cid ,double Speed ,double RobotPos[16]);
bool    MotoMovPulsePos(short Cid ,double SpeedPercent ,double PulsePos[16]);
bool    MotoStop(short Cid);
bool    MotoIsServoON(short Cid);
bool	MotoIsHoldOn(short Cid);

bool    MotoWriteIO(short Cid ,int Addr ,unsigned char value[32]);	//value=0.01mm ’PˆÊ
bool    MotoReadIO (short Cid ,int Addr ,unsigned char value[32]);	//value=0.01mm ’PˆÊ

