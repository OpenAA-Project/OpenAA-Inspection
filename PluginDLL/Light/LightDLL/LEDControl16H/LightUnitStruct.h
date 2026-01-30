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

#if        !defined(LightUnitStruct_h)
#define        LightUnitStruct_h


struct        LightLineUnit
{
	int		ColorType;        //1:Reg        2:Green       3:Blue       4:IR        5:UV        6:White        7:Other
	int		BoardID;
	int		LineNo;
	int		MaxValue;
	wchar_t	Comment[64];

	LightLineUnit(void){
		ColorType	=0;
		BoardID		=-1;
		LineNo		=-1;
		MaxValue	=0;
		Comment[0]	=0;
	}
};

#define DimCountOfLineData    128


#endif