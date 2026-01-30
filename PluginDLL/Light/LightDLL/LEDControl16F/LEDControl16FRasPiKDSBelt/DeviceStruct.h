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

#if	!defined(DeviceStruct_h)
#define	DeviceStruct_h
#include "XTypeDef.h"

class   QIODevice;

#pragma pack(push, 1)
struct  KDSBeltPIORealStruct
{
    bool     GIN0     :1;
    bool     GIN1     :1;
    bool     GIN2     :1;
    bool     GIN3     :1;
    bool     GIN4     :1;
    bool     GIN5     :1;
    bool     GIN6     :1;
    bool     GIN7     :1;
    bool     GIN8     :1;
    bool     GIN9     :1;
    bool     GIN10    :1;
    bool     GIN11    :1;
    bool     GIN12    :1;
    bool     GIN13    :1;
    bool     GIN14    :1;
    bool     GIN15    :1;
    bool     GOUT0    :1;
    bool     GOUT1    :1;
    bool     GOUT2    :1;
    bool     GOUT3    :1;
    bool     GOUT4    :1;
    bool     GOUT5    :1;
    bool     GOUT6    :1;
    bool     GOUT7    :1;
    bool     GOUT8    :1;
    bool     GOUT9    :1;
    bool     GOUT10   :1;
    bool     GOUT11   :1;
    bool     GOUT12   :1;
    bool     GOUT13   :1;
    bool     GOUT14   :1;
    bool     GOUT15   :1;
    bool     FASTIN0  :1;
    bool     FASTIN1  :1;
    bool     FASTIN2  :1;
    bool     FASTIN3  :1;
    bool     FASTIN4  :1;
    bool     FASTIN5  :1;
    bool     FASTIN6  :1;
    bool     FASTIN7  :1;
    bool    OuterSW   :1;
    bool    ExtDirect :1;
    bool    CamFrameTrigger:1;
    bool    CamLineTrigger:1;
    bool    CamOut0:1;
    bool    CamOut1:1;
};
#pragma pack(pop)

struct  KDSBeltPIOFixedStruct
{
    unsigned long   MulInput;
    unsigned long   TriggerFilterMinOFF;
    unsigned long   TriggerFilterMinON;

	KDSBeltPIOFixedStruct(void){
		MulInput			=700;
		TriggerFilterMinOFF	=10;
		TriggerFilterMinON	=10;
	}
	
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

#pragma pack(push, 1)
struct  TimingData
{
    DWORD   CurrentMiliSec;
    struct  KDSBeltPIORealStruct  RealData;
};
#pragma pack(pop)

struct	KDSBeltPIOStruct
{
    struct  KDSBeltPIOFixedStruct  KDSBeltPIOFixedData;

    //Not saved
	unsigned char	RMode;
	bool			TestMode;
	bool			TestLEDReg;
	bool			RegLEDOut[2];
    struct  KDSBeltPIORealStruct  RealData;

    bool	AD_CS           :1;
    bool	AD_DIN          :1;
    bool	AD_CLK          :1;
    bool	AD_DOUT         :1;
    bool    OutSW           :1;
	unsigned long   MotorPulseCounter;
	

    KDSBeltPIOStruct(void){
        TestLEDReg	=false;
    }
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};


#endif