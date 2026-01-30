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



#include "XArrangementDLL.h"
#include "XArrangementFromFile.h"
#include "XGeneralFunc.h"
#include <stdio.h>


bool		DLL_GetOrganization(QString &str)
{
	str="MEGATRADE";
	return true;
}
WORD		DLL_GetDLLType(void)
{
	return DLLArrangement;
}
bool		DLL_GetName(QString &Root ,QString &Name)
{
	Root="Basic";
	Name="CSVFormat";
	return true;
}
WORD		DLL_GetVersion(void)
{
	return 1;
}
const char	*DLL_GetExplain(void)
{
	return "Arrangement from CSV file";
}

bool		DLL_Initial(LayersBase *Base)
{
	return true;
}
bool		DLL_GetFileExtType(QString &ExtTypeStr)
{
	ExtTypeStr="CSV(*.csv)";
	return true;
}
bool		DLL_LoadFile(QString &FileName ,NPListPack<ArrangementItem> &RetList)
{
	char	Buff[1024];

	QString2Char(FileName,Buff ,sizeof(Buff));
	FILE	*f=fopen(Buff,"rt");
	if(f!=NULL){
		while(fgets(Buff,sizeof(Buff)-1,f)!=NULL){
			double	PosX,PosY,W,H;
			if(matchscanf(Buff,"\t%lf\t,\t%lf\t,\t%lf\t,\t%lf",&PosX,&PosY,&W,&H)==4){
				ArrangementItem	*a=new ArrangementItem();
				a->CenterX		=PosX;
				a->CenterY		=PosY;
				a->ItemWidth	=W;
				a->ItemHeight	=H;
				RetList.AppendList(a);
			}
		}
		fclose(f);
		return true;
	}
	return false;
}