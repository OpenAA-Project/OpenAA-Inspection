/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\mtVRSCommand2\mtVRSCommand2\mtvrscommand2.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include <windows.h>
#include <QString>
#include "XSeqDLLGlobal.h"
#include "SPcom2.h"

WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="mtVRSCommand2";
	return true;
}

WORD		_cdecl	DLL_GetVersion(void)
//	return Light DLL version
{
	return 1;
}

bool	DLL_CheckCopyright(QString &CopyrightString)
//	return Copyright string
{
	CopyrightString="Copyright(c) MEGATRADE 2007.9";
	return true;
}


DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return "USB Command DLL for MEGATRADE VRS";
}

void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"USB Command DLL for MEGATRADE VRS");
}

bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	int i=0;
	BYTE Data[16];
	if(cmdstr=="Stop"){
		Data[i++]=0x02;
		Data[i++]=0x30;
		Data[i++]=0x24;
	}
	else if(cmdstr=="Status"){
		Data[i++]=0x02;
		Data[i++]=0x40;
		Data[i++]=0x21;
	}
	else if(cmdstr=="ErrClear"){
		Data[i++]=0x02;
		Data[i++]=0x50;
		Data[i++]=0x2c;
	}
	else if(cmdstr=="Org"){
		Data[i++]=0x02;
		Data[i++]=0x30;
		Data[i++]=0x20;
		Data[i++]='1';
		Data[i++]=',';
		Data[i++]='1';
		Data[i++]=',';
		Data[i++]='1';
		Data[i++]=',';
	}
	else if(cmdstr=="Open"){
		SPcomSetPackLen(128);
		if(!SPcomOpen(19,"192.168.1.230",1,1))
			return false;
		if(!SPcomConectCheck(1,0))
			return false;
	}
	else if(cmdstr=="LevelSP"){
		Data[i++]=0x02;
		Data[i++]=0x30;
		Data[i++]=0x26;
		Data[i++]='1';
		Data[i++]='0';
		Data[i++]='0';
		Data[i++]=',';
		Data[i++]='1';
		Data[i++]='0';
		Data[i++]='0';
		Data[i++]=',';
		Data[i++]='1';
		Data[i++]='0';
		Data[i++]='0';
		Data[i++]=',';
		Data[i++]='1';
		Data[i++]='0';
		Data[i++]='0';
	}
	else
		return false;

	Data[i++]=0x0d;
	int Ret=0;
	if((Ret=SPcomWriteTxData(Data,0,1))==1)
		return true;
	return false;
}

bool	DLLSeq_CmdStrInt(void *handle ,QApplication &App ,const QString &cmdstr , const QByteArray &datastr ,int *data)
/*
    命令を送る
    データなしの記述のときもこの関数がコールされる
    DLLCmd   dllVar,CommandString
    DLLCmd   dllVar,CommandString,Cxx
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	int i=0;
	BYTE Data[32];
	if(cmdstr=="TargetSP"){
		char Buff[8];
        int n=sprintf(Buff,"%.3lf",((double)*data)/1000.0);
		Data[i++]=0x02;
        Data[i++]=0x20;
        Data[i++]=0x23;
        Data[i++]='9';
        Data[i++]=',';
		if(datastr=="X"){
			for(int Cnt=0;Cnt<n;Cnt++)
				Data[i++]=Buff[Cnt];
	        Data[i++]=',';
	        Data[i++]=',';
		}
		else if(datastr=="Y"){
	        Data[i++]=',';
			for(int Cnt=0;Cnt<n;Cnt++)
				Data[i++]=Buff[Cnt];
	        Data[i++]=',';
		}
		else if(datastr=="Z"){
	        Data[i++]=',';
	        Data[i++]=',';
			for(int Cnt=0;Cnt<n;Cnt++)
				Data[i++]=Buff[Cnt];
		}
		else
			return false;
	}
	else if(cmdstr=="ADTime"){
		char Buff[8];
        int n=sprintf(Buff,"%.3lf",((double)*data)/1000.0);
		Data[i++]=0x02;
        Data[i++]=0x20;
        Data[i++]=0x24;
        Data[i++]='9';
        Data[i++]=',';
		if(datastr=="X"){
			for(int Cnt=0;Cnt<n;Cnt++)
				Data[i++]=Buff[Cnt];
	        Data[i++]=',';
	        Data[i++]=',';
		}
		else if(datastr=="Y"){
	        Data[i++]=',';
			for(int Cnt=0;Cnt<n;Cnt++)
				Data[i++]=Buff[Cnt];
	        Data[i++]=',';
		}
		else if(datastr=="Z"){
	        Data[i++]=',';
	        Data[i++]=',';
			for(int Cnt=0;Cnt<n;Cnt++)
				Data[i++]=Buff[Cnt];
		}
		else
			return false;
	}
	else
		return false;

	Data[i++]=',';
	Data[i++]=0x0d;
	int Ret=0;
	if((Ret=SPcomWriteTxData(Data,0,1))==1)
		return true;
	return false;
}

bool	DLLSeq_CmdInt(void *handle ,QApplication &App ,const QString &cmdstr , int *data)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	int i=0;
	BYTE Data[32];
	BYTE RetData[128];
	if(cmdstr=="GetState"){
		//Read
		SPcomReadRxData(RetData);
		if(RetData[0]==0x06 || RetData[0]==0x02){
			int Cmd1=RetData[1];
			int Cmd2=RetData[2];
			BYTE AA1=RetData[3];
			BYTE AA2=RetData[3];
			BYTE AA3=RetData[5];
			BYTE AA4=RetData[6];
			BYTE BB1=RetData[8];
			BYTE BB2=RetData[9];
			BYTE BB3=RetData[10];
			BYTE BB4=RetData[11];
			BYTE CC1=RetData[13];
			BYTE CC2=RetData[14];
			BYTE CC3=RetData[15];
			BYTE CC4=RetData[16];
		}
		else{
			*data=RetData[0];
			return false;
		}

		//Statusを分類分け
		if(RetData[6]=='1' || RetData[6]=='3' || RetData[11]=='1' || RetData[11]=='3' || RetData[16]=='1' || RetData[16]=='3')
			*data=2;    //移動中
		else if((RetData[4]=='1' || RetData[4]=='2' || RetData[9]=='1' || RetData[9]=='2' || RetData[14]=='1' || RetData[14]=='2') || (RetData[3]=='8' || RetData[8]=='8' || RetData[13]=='8'))
			*data=-1;	//エラー発生
		else if(RetData[5]=='1' || RetData[10]=='1' || RetData[15]=='1')
			*data=3;    //原点復帰未完了
		else
			*data=1;    //待機中
		return true;
	}
	else if(cmdstr=="Read"){
		int Ret=0;
		if((Ret=SPcomReadRxData(RetData))!=1)
			return false;
		*data=RetData[0];
		return true;
	}
	else if(cmdstr=="GetErrCode"){
		Data[i++]=0x02;
		Data[i++]=0x40;
		Data[i++]=0x24;
		Data[i++]=0x0d;
		int Ret=0;
		if((Ret=SPcomWriteTxData(Data,0,1))!=1)
			return false;
		//Read
		SPcomReadRxData(RetData);
		if(RetData[0]==0x06 || RetData[0]==0x02){
			*data=RetData[4];
			return true;
		}
		else{
			*data=-1;
			return false;
		}
	}
	else if(cmdstr=="MovZ"){
		char Buff[8];
        int n=sprintf(Buff,"%.3lf",((double)*data)/1000.0);
		Data[i++]=0x02;
        Data[i++]=0x30;
        Data[i++]=0x22;
        Data[i++]=',';
        Data[i++]=',';
		for(int Cnt=0;Cnt<n;Cnt++)
			Data[i++]=Buff[Cnt];
	}
	else if(cmdstr=="MovX"){
		char Buff[8];
        int n=sprintf(Buff,"%.3lf",((double)*data)/1000.0);
		Data[i++]=0x02;
        Data[i++]=0x30;
        Data[i++]=0x22;
		for(int Cnt=0;Cnt<n;Cnt++)
			Data[i++]=Buff[Cnt];
        Data[i++]=',';
        Data[i++]=',';
	}
	else if(cmdstr=="MovY"){
		char Buff[8];
        int n=sprintf(Buff,"%.3lf",((double)*data)/1000.0);
		Data[i++]=0x02;
        Data[i++]=0x30;
        Data[i++]=0x22;
        Data[i++]=',';
		for(int Cnt=0;Cnt<n;Cnt++)
			Data[i++]=Buff[Cnt];
        Data[i++]=',';
	}
	else
		return false;

	Data[i++]=',';
	Data[i++]=0x0d;
	int Ret=0;
	if((Ret=SPcomWriteTxData(Data,0,1))==1)
		return true;
	return false;
}

bool	DLLSeq_CmdInt2(void *handle ,QApplication &App ,const QString &cmdstr , int *data1 ,int *data2)
/*
    命令を送る
    DLLCmd   dllVar,CommandString,Wxx,Wxx
    でこの関数が呼ばれる
    データを返すとき、*dataに値を格納すれば、「Wxx」に値が入る
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	int i=0;
	BYTE Data[128];
	BYTE RetData[128];
	if(cmdstr=="MovXY"){
		char BuffX[8];
		char BuffY[8];
        int nX=sprintf(BuffX,"%.3lf",((double)*data1)/1000.0);
        int nY=sprintf(BuffY,"%.3lf",((double)*data2)/1000.0);
		Data[i++]=0x02;
        Data[i++]=0x30;
        Data[i++]=0x22;
		for(int Cnt=0;Cnt<nX;Cnt++)
			Data[i++]=BuffX[Cnt];
        Data[i++]=',';
		for(int Cnt=0;Cnt<nY;Cnt++)
			Data[i++]=BuffY[Cnt];
        Data[i++]=',';
	}
	else
		return false;

	Data[i++]=',';
	Data[i++]=0x0d;
	int Ret=0;
	if((Ret=SPcomWriteTxData(Data,0,1))==1)
		return true;
	return false;
}

void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
	SPcomClose();
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{
}
