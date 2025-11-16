/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\ArrangementDLL\CSVFormat\CSVFormat.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


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
