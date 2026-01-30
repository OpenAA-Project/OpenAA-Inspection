/*
 * Copyright (C) 2020
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

#if	!defined(DeviceStruct_h)
#define	DeviceStruct_h

#include <QIODevice>

struct	EOIStruct
{
	unsigned long	CamResolution;
	unsigned long	Conveyer1Pulse;
	unsigned char	OutExt;
    unsigned char   InExt;
	bool	RESET;
	bool	TestLEDReg;
	bool	CamOut;
	bool	LEDOutToPanel[2];
    unsigned long   MulInput;
    unsigned int	ResultMulL;
    unsigned long	ResultMulH;
    unsigned int    ClockInMotorPulse;
    unsigned long   DelayFrameTriggerA;
    unsigned long   DelayFrameTriggerB;
    unsigned long   FrameCycle;
    unsigned long   DropLength;
    unsigned long   DropFlapONLength;
    
    unsigned long	TimeUpLatchA;
    unsigned long	TimeUpLatchB;
    unsigned long	ResultTimeLatchA;
    unsigned long	ResultTimeLatchB;

    EOIStruct(void){
        CamResolution=10;
        Conveyer1Pulse=5000;
        OutExt=0;
        InExt=0;
        RESET=false;
        TestLEDReg=false;
        CamOut=false;
        LEDOutToPanel[0]=false;
        LEDOutToPanel[1]=false;
        MulInput=0;
        ResultMulL=0;
        ResultMulH=0;
        ClockInMotorPulse=0;
        DelayFrameTriggerA=0;
        DelayFrameTriggerB=0;
    }
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};



#endif