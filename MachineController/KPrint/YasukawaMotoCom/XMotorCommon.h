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

bool    MotoWriteIO(short Cid ,int Addr ,unsigned char value[32]);	//value=0.01mm �P��
bool    MotoReadIO (short Cid ,int Addr ,unsigned char value[32]);	//value=0.01mm �P��
