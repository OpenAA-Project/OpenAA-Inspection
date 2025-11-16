/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\LogWriter\ThreadLogWriter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ThreadLogWriter.h"
#include "XGeneralFunc.h"
#include <stdio.h>

ThreadLogWriter::ThreadLogWriter()
{
	OnWriteMode		=false;
	OnInspectionID	=0;
	OnSignalOn		=false;

	OffWriteMode	=false;
	OffInspectionID	=0;
	OffSignalOn		=false;
}

void ThreadLogWriter::run()
{
	char	buff[100];
	for(;;){
		setTerminationEnabled(false);
		if(OnWriteMode==true){
			FILE	*f=fopen(FileName,"a+t");
			if(f!=NULL){
				QString	A=OnWrittenTime.toString("yy/MM/dd hh:mm:ss.z");
				::QString2Char(A,buff ,sizeof(buff));
				if(OnSignalOn==true)
					fprintf(f,"%s,%d,ON\n",buff,(int)OnInspectionID);
				else if(OnSignalOn==false)
					fprintf(f,"%s,%d,OFF\n",buff,(int)OnInspectionID);
				fclose(f);
			}
			OnWriteMode=false;
		}
		if(OffWriteMode==true){
			FILE	*f=fopen(FileName,"a+t");
			if(f!=NULL){
				QString	A=OffWrittenTime.toString("yy/MM/dd hh:mm:ss.z");
				::QString2Char(A,buff ,sizeof(buff));
				if(OffSignalOn==true)
					fprintf(f,"%s,%d,ON\n",buff,(int)OffInspectionID);
				else if(OffSignalOn==false)
					fprintf(f,"%s,%d,OFF\n",buff,(int)OffInspectionID);
				fclose(f);
			}
			OffWriteMode=false;
		}
		if(PrintWriteMode==true){
			FILE	*f=fopen(FileName,"a+t");
			if(f!=NULL){
				char	buff2[100];
				QString	A=PrintWrittenTime.toString("yy/MM/dd hh:mm:ss.z");
				::QString2Char(A,buff ,sizeof(buff));
				::QString2Char(PrintString,buff2 ,sizeof(buff2));
				fprintf(f,"%s,%s:%d\n",buff,buff2,(int)PrintNumber);
				fclose(f);
			}
			PrintWriteMode=false;
		}
		setTerminationEnabled(true);
		msleep(20);
	}
}
