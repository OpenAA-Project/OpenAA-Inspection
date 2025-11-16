/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\mtVRSCommand\mtVRSCommand\mtvrscommand.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "XSeqDLLGlobal.h"
#include <string.h>
#include <qextserialport.h>


class	mtVRSCommand
{
public:
	QextSerialPort *port;
	enum	__RetType{
			 _Other	=-1
			,_None	=0
			,_ACK	=1
			,_NAK	=2
	}RetType;
	int		iRetry;
	char	ACK;
	char	NAK;

	mtVRSCommand(void)
	{
		port=NULL;
		iRetry=3;
		ACK=0x06;
		NAK=0x15;
	}

	void	HexBCC		(char *BCCData,char *RetBCC);
	char	HexBCCData	(char BCCData);
	bool	ResultCmd	(char *Cmd,int Len);
	bool	ResultCmdTry(char *Cmd);
	int	ResCommand	();
	bool	ReturnCmd	(char *Cmd,int Len,char *RetCmd);
	bool	ReturnCmdTry(char *wData);
	bool	RetCommand	(char *Buff,int &iBytes);
	bool	EvaluateBCC	(char *Buff,int Len);
};


WORD	DLL_GetDLLType(void)
//	return	DLL type for LightDLL
{
	return	DLLSeqDLLVarMode;
}

bool		_cdecl	DLL_GetName(QString &str)
//	return DLL-Name. 
{
	str="mtVRSCommand";
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
	return "Serial Command DLL for MEGATRADE VRS";
}
void	DLLSeq_GetDLLVersion(char *buff)
/*
    バージョンを返す
    buffは２５６バイト以内
*/
{
	strcpy(buff,"Serial Command DLL for MEGATRADE VRS");
}

DEFFUNCEX		void	*DLLSeq_Initial(LayersBase *Base ,const QString &Param)
{
	mtVRSCommand	*LSeq=new mtVRSCommand();
	return LSeq;
}
bool	DLLSeq_Cmd(void *handle ,QApplication &App ,const QString &cmdstr)
/*
    命令を送る
    DLLCmd   dllVar,CommandString
    でこの関数が呼ばれる
    この関数の戻り値が、DLLCmdの結果フラグに反映される
*/
{
	mtVRSCommand	*LSeq=(mtVRSCommand	*)handle;

	int i=0;
	char Data[16];
	char BCC[2];
	if(cmdstr=="Stop"){
		Data[i++]=0x02;
        Data[i++]=0x30;
        Data[i++]=0x24;
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
	else
		return false;

	Data[i++]=0x03;
	LSeq->HexBCC(Data,BCC);
	for(int Cnt=0;Cnt<2;Cnt++)
		Data[i++]=BCC[Cnt];
	Data[i]=0;
	if(LSeq->ResultCmd(Data,i))
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
	mtVRSCommand	*LSeq=(mtVRSCommand	*)handle;

	int i=0;
	char Data[32];
	char BCC[2];
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
		char Buff[5];
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
	Data[i++]=0x03;
	LSeq->HexBCC(Data,BCC);
	for(int Cnt=0;Cnt<2;Cnt++)
		Data[i++]=BCC[Cnt];
	Data[i]=0;
	if(LSeq->ResultCmd(Data,i))
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
	mtVRSCommand	*LSeq=(mtVRSCommand	*)handle;

	int i=0;
	char Data[32];
	char BCC[2];
	if(cmdstr=="GetState"){
		Data[i++]=0x02;
        Data[i++]=0x40;
        Data[i++]=0x21;
		Data[i++]=0x03;
		LSeq->HexBCC(Data,BCC);
		for(int Cnt=0;Cnt<2;Cnt++)
			Data[i++]=BCC[Cnt];
		Data[i]=0;
		if(!LSeq->ResultCmd(Data,i))
			return false;
		char RetData[32];
		if(!LSeq->ReturnCmd(Data,i,RetData))
			return false;

		//Statusを分類分け
//        if(RetData[6]=='1' || RetData[11]=='1' || RetData[15]=='1')
		if(RetData[6]=='1' || RetData[6]=='3' || RetData[11]=='1' || RetData[11]=='3' || RetData[16]=='1' || RetData[16]=='3')
            *data=1;    //移動中
        else if((RetData[4]=='1' || RetData[4]=='2' || RetData[9]=='1' || RetData[9]=='2' || RetData[14]=='1' || RetData[14]=='2') || (RetData[3]=='8' || RetData[8]=='8' || RetData[13]=='8'))
            *data=-1;	//エラー発生
        else if(RetData[5]=='1' || RetData[10]=='1' || RetData[15]=='1')
            *data=2;    //原点復帰未完了
        else
            *data=0;    //待機中
		return true;
	}
	else if(cmdstr=="Open"){
		QString COM="COM";
		COM.append(QString::number(*data));
		LSeq->port = new QextSerialPort(COM);
		LSeq->port->setBaudRate(BAUD38400);
		LSeq->port->setFlowControl(FLOW_OFF);
		LSeq->port->setParity(PAR_NONE);
		LSeq->port->setDataBits(DATA_8);
		LSeq->port->setStopBits(STOP_1_5);
		if(LSeq->port->open(QIODevice::ReadWrite))
			return true;
		return false;
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
	Data[i++]=0x03;
	LSeq->HexBCC(Data,BCC);
	for(int Cnt=0;Cnt<2;Cnt++)
		Data[i++]=BCC[Cnt];
	Data[i]=0;
	if(LSeq->ResultCmd(Data,i))
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
	mtVRSCommand	*LSeq=(mtVRSCommand	*)handle;

	int i=0;
	char Data[32];
	char BCC[2];
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
	Data[i++]=0x03;
	LSeq->HexBCC(Data,BCC);
	for(int Cnt=0;Cnt<2;Cnt++)
		Data[i++]=BCC[Cnt];
	Data[i]=0;
	if(LSeq->ResultCmd(Data,i))
		return true;
	return false;
}

void	DLLSeq_Close(void *handle)
/*
    終了処理
*/
{
	mtVRSCommand	*LSeq=(mtVRSCommand	*)handle;

	if(LSeq->port!=NULL){
		LSeq->port->close();
	}
	delete	LSeq;
}

void	DLLSeq_DebugShow(void *handle ,QApplication &App)
{}

void mtVRSCommand::HexBCC(char *BCCData,char *RetBCC)
{
	unsigned char BCC=BCCData[1];
	for(int i=2;BCCData[i]!=0x03;i++)
		BCC=BCC^BCCData[i];
	char BCC1=0;
	if((BCC&0x10)!=0)
		BCC1|=0x01;
	if((BCC&0x20)!=0)
		BCC1|=0x02;
	if((BCC&0x40)!=0)
		BCC1|=0x04;
	if((BCC&0x80)!=0)
		BCC1|=0x08;
	RetBCC[0]=HexBCCData(BCC1);
	char BCC2=0;
	if((BCC&0x01)!=0)
		BCC2|=0x01;
	if((BCC&0x02)!=0)
		BCC2|=0x02;
	if((BCC&0x04)!=0)
		BCC2|=0x04;
	if((BCC&0x08)!=0)
		BCC2|=0x08;
	RetBCC[1]=HexBCCData(BCC2);
}

char mtVRSCommand::HexBCCData(char BCCData)
{
	if(BCCData==0)
		return '0';
	else if(BCCData==0x01)
		return '1';
	else if(BCCData==0x02)
		return '2';
	else if(BCCData==0x03)
		return '3';
	else if(BCCData==0x04)
		return '4';
	else if(BCCData==0x05)
		return '5';
	else if(BCCData==0x06)
		return '6';
	else if(BCCData==0x07)
		return '7';
	else if(BCCData==0x08)
		return '8';
	else if(BCCData==0x09)
		return '9';
	else if(BCCData==0x0a)
		return 'A';
	else if(BCCData==0x0b)
		return 'B';
	else if(BCCData==0x0c)
		return 'C';
	else if(BCCData==0x0d)
		return 'D';
	else if(BCCData==0x0e)
		return 'E';
	else if(BCCData==0x0f)
		return 'F';
	else
		return 0;
}

bool mtVRSCommand::ResultCmd(char *Cmd,int Len)
{
	for(int Cnt=0;Cnt<iRetry;Cnt++){
		if(port->write(Cmd,Len)!=Len)
			return false;
		if(ResultCmdTry(Cmd))
			return true;
	}
	return false;
}

bool mtVRSCommand::ResultCmdTry(char *Cmd)
{
	DWORD t=::GetTickCount();

	while(::GetTickCount()-t<500){
		int Res;
		if((Res=ResCommand())==_ACK)
			return true;
		else if(Res==_NAK)
			return false;
		else if(Res==_Other)
			return false;
		else if(Res==_None)
			continue;
	}
	return false;
}

int mtVRSCommand::ResCommand()
{
	char Buff[1];
	int RetSize=1;
	if(RetCommand(Buff,RetSize)){
		if(Buff[0]==0x06)
			return _ACK;
		else if(Buff[0]==0x15)
			return _NAK;
		else
			return _Other;
	}
	return _None;
}

bool mtVRSCommand::ReturnCmd(char *Cmd,int Len,char *RetCmd)
{
	for(int Cnt=0;Cnt<iRetry;Cnt++){
		if(ReturnCmdTry(RetCmd))
			return true;
		if(Cnt+1==iRetry)
			break;
		ResultCmd(Cmd,Len);
	}
	return false;
}

bool mtVRSCommand::ReturnCmdTry(char *wData)
{
	DWORD t=::GetTickCount();

	wData[0]=0;
	int RetSize=0;

	while(::GetTickCount()-t<500){
		if(RetCommand(wData,RetSize)){
			//BCC計算、評価
			if(EvaluateBCC(wData,RetSize))
				//ACKの送信
				port->write(&ACK,1);
			else
				//NAKの送信
				port->write(&NAK,1);
			return true;
		}
	}
	return false;
}

bool mtVRSCommand::RetCommand(char *Buff,int &iBytes)
{
	int numBytes;
	numBytes = port->bytesAvailable();
	if(numBytes > 0){
		if(iBytes==0)
			iBytes=numBytes;
		if(port->read(Buff, iBytes)!=iBytes)
			return false;
		return true;
	}
	return false;
}

bool mtVRSCommand::EvaluateBCC(char *Buff,int Len)
{
	char BCCData[2];
	HexBCC(Buff,BCCData);
	if(BCCData[0]!=Buff[Len-2])
		return false;
	if(BCCData[1]!=Buff[Len-1])
		return false;
	return true;
}
