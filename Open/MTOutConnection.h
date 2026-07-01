/*
 * Copyright (C) 2023
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



#ifndef MTOUTCONNECTION_H
#define MTOUTCONNECTION_H


typedef	void *	MTOCHandle;

enum	MTOC_Operation
{
	_MTOC_Ope_None		=0
};

enum	MTOC_Command
{
	_MTOC_Cmd_None		=0
};

enum	MTOC_ImageAttr
{
	 _MTOC_Img_Master	=1
	,_MTOC_Img_Target	-2
};
enum	MTOC_BinaryAttr
{
	 _MTOC_Bin_MasterOutline		=1
	,_MTOC_Bin_TargetOutline		=2
};

extern "C"{

DEFFUNCEX	MTOCHandle	DLL_OC_Connect(char *IPAddress ,int Port);
DEFFUNCEX	MTOCHandle	DLL_OC_Close(MTOCHandle handle );

DEFFUNCEX	int			DLL_OC_EnumParam(MTOCHandle handle ,char **Keywords ,int MaxParams);
DEFFUNCEX	bool		DLL_OC_GetParam(MTOCHandle handle,char *Keyword ,void *);

DEFFUNCEX	bool		DLL_OC_GetImage(MTOCHandle handle ,MTOC_ImageAttr attr
										,BYTE **Image[]
										,int areaX1 ,int areay1,int areaX2 ,int areay2
										,int *DotPerLine, int *MaxLines, int *LayerCount);
DEFFUNCEX	bool		DLL_OC_SetImage(MTOCHandle handle ,MTOC_ImageAttr attr
										,int areaX1 ,int areay1,int areaX2 ,int areay2
										,int *DotPerLine, int *MaxLines, int *LayerCount);

DEFFUNCEX	bool		DLL_OC_GetBinarized(MTOCHandle handle,MTOC_BinaryAttr Attr 
											,BYTE **Image[]
											,int areaX1 ,int areay1,int areaX2 ,int areay2
											,int *DotPerLine, int *MaxLines, int *LayerCount);

DEFFUNCEX	bool		DLL_OC_RegistCallback(MTOCHandle handle,bool (*Func)(MTOCHandle handle ,MTOC_Operation ope));

DEFFUNCEX	bool		DLL_OC_SendCommand(MTOCHandle handle,MTOC_Command cmd ,void *data);

};

#endif
