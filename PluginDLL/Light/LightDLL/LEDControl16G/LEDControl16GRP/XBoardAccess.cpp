/*
 * Copyright (C) 2021
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


#include <wiringPi.h>
#include "LightDeviceStruct.h"

void WriteRegister(int Data);


void WriteRegister(int DipSW ,int Data[] ,int DataLen)
{
    digitalWrite(13 , ((DipSW&0x01)!=0)?1:0);
    digitalWrite(14 , ((DipSW&0x02)!=0)?1:0);
    digitalWrite(16 , ((DipSW&0x04)!=0)?1:0);
    digitalWrite(17 , ((DipSW&0x08)!=0)?1:0);

    digitalWrite(11 , 1);	//iRPiCmdW
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();

    digitalWrite(15 , 1);	//iRPiStrobe
    delay(1);
    for(int i=0;i<DataLen;i++){
        WriteRegister(Data[i]);
    }
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
}

void WriteRegisterData(int Data)
{
    digitalWrite(2 , ((Data&0x01)!=0)?1:0);
    digitalWrite(3 , ((Data&0x02)!=0)?1:0);
    digitalWrite(4 , ((Data&0x04)!=0)?1:0);
    digitalWrite(5 , ((Data&0x08)!=0)?1:0);
    digitalWrite(6 , ((Data&0x10)!=0)?1:0);
    digitalWrite(7 , ((Data&0x20)!=0)?1:0);
    digitalWrite(8 , ((Data&0x40)!=0)?1:0);
    digitalWrite(9 , ((Data&0x80)!=0)?1:0);
}

void WriteRegister(int Data)
{
    WriteRegisterData(Data);

    delay(1);
    digitalWrite(12, 1);
    delay(1);
    digitalWrite(12, 0);
    delay(1);
}

void ReadRegister4Bit(int DipSW ,int Data[] ,int DataLen)
{
    digitalWrite(13 , ((DipSW&0x01)!=0)?1:0);
    digitalWrite(14 , ((DipSW&0x02)!=0)?1:0);
    digitalWrite(16 , ((DipSW&0x04)!=0)?1:0);
    digitalWrite(17 , ((DipSW&0x08)!=0)?1:0);

    digitalWrite(11 , 0);	//iRPiCmdW
    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    digitalWrite(15 , 1);	//iRPiStrobe
    delay(1);

    for(int i=0;i<DataLen;i++){
        ReadRegister4Bit(Data[i]);
    }

    digitalWrite(15 , 0);	//iRPiStrobe
    DummyClock();
    delay(1);
}

void ReadRegister4Bit(int &Data)
{
    delay(1);
    digitalWrite(12, 1);
    delay(1);
    int b1=digitalRead(23);
    int b2=digitalRead(24);
    int b4=digitalRead(25);
    int b8=digitalRead(26);
    Data=(b1&0x01) + ((b2&0x1)<<1) + ((b4&0x1)<<2) + ((b8&0x1)<<3);

    digitalWrite(12, 0);
    delay(1);
}

void DummyClock(void)
{
    delay(1);
    digitalWrite(12, 1);
    delay(1);
    digitalWrite(12, 0);
    delay(1);
}