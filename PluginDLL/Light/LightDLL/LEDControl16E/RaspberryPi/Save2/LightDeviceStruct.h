/*
 * Copyright (C) 2019
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

#if	!defined(CamTriggerStruct_H)
#define	CamTriggerStruct_h

#include <QBuffer>

struct	LightBoard
{
	struct	LightPattern
	{
		struct	LightLine
		{
			unsigned long	MicroAmp;
            bool			ON;

            int GetPGAChannel(void);//1Bit
            int GetDAGainX2(void);  //1Bit
            int GetPGAGain(void);   //3Bit
            int GetDAValue(void);   //12Bit
            int GetDCClock(void);   //8Bit
            
            LightLine(void){
                MicroAmp=100000;
            	ON=false;
            }
            bool    Save(QIODevice *f);
            bool    Load(QIODevice *f);
        }LineData[16];
        bool    DCEnable;

        LightPattern(void){
            DCEnable=true;
        }
        void    SetAllON(bool ONMode=true);

        bool    Save(QIODevice *f);
        bool    Load(QIODevice *f);
    }LightPatternData[128];

	struct	MotorPluseDecoder
	{
		unsigned short	CounterL;
		unsigned short	CounterH;

        bool    Save(QIODevice *f);
        bool    Load(QIODevice *f);
    }MotorPluseDecoderData[16];
	
	bool	CmdSetAnalog;
	bool	CmdLoad;
	bool	CmdSetLineOn;
	bool	TestLEDReg;
	int		CurrentPatternNo;
	
	LightBoard(void){
		CmdSetAnalog	=false;
		CmdLoad			=false;
		CmdSetLineOn	=false;
		TestLEDReg		=false;
		CurrentPatternNo=0;
	}
    bool    Save(QIODevice *f);
    bool    Load(QIODevice *f);
};

#endif