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

#if	!defined(LightDeviceStruct_H)
#define	LightDeviceStruct_H

#include <QBuffer>
#include <QIODevice>
#include "XTypeDef.h"

#define	MaxCountLEDPattern	16
#define	MaxCountLines   	16
#define MaxBoardCount       10

class	LEDControl16GPanel;

class   LightBoard
{
public:
	LEDControl16GPanel	*Parent;
    class   __LineInfo
    {
    public:
        uint32    TargetValue[MaxCountLEDPattern];    //Micro ampare
        uint32    CurrentValue;                       //Micro ampare

        __LineInfo(void);
        bool    Save(QIODevice *f);
        bool    Load(QIODevice *f);

    }LineInfo[MaxCountLines];
    int		DipSW;
    bool    AllON;

	LightBoard(void);

	void	SetParent(LEDControl16GPanel *p);

    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);

    bool    SetTestLED(bool b);
    bool    SetAllON(bool b);
    bool    SetCurrentPatternNo(int n);

    bool    GetLightData(int PatternNo);
    bool    SetLightData(int PatternNo);
    bool    GetCurrentValue(void);
private:

};

#if	!defined(PCMode)

void DummyClock(void);
void WriteRegister(int DipSW ,int Data[] ,int DataLen);
void WriteRegisterData(int Data);
void ReadRegister4Bit(int DipSW ,int Data[] ,int DataLen);
void ReadRegister4Bit(int &Data);

#endif

#endif