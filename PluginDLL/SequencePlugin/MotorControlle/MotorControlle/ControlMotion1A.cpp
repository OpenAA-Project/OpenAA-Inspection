/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\PluginDLL\SequencePlugin\MotorControlle\MotorControlle\ControlMotion1A.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


#include "ControlMotion1A.h"
#include <memory.h>
#define NULL    0

const   int     WaitingMilisec  =5000;

ControlMotion1A::ControlMotion1A(void)
{
	RxData=new unsigned char[1024];
	RxByte	=0;
	RxWPoint=0;
	RxNumb	=0;
	RxCmd	=0;

    //原点→撮像完了位置まで移動
//    MotionStage1Data.TargetCount=70;	//等速区間の速度になるカウンター数
    MotionStage1Data.TargetCount=110;	//等速区間の速度になるカウンター数
	MotionStage1Data.Direction  =0;		//回転方向　0 or 1
	MotionStage1Data.StartPulse =100;  	//加速区間のパルス数
	MotionStage1Data.MiddlePulse=2600;	//等速区間のパルス数
	MotionStage1Data.EndPulse   =200;  	//減速区間のパルス数

    //原点→プラスリミットまで移動
    MotionStage2Data.TargetCount=70;	//等速区間の速度になるカウンター数
	MotionStage2Data.Direction  =0;		//回転方向　0 or 1
	MotionStage2Data.StartPulse =100;  	//加速区間のパルス数
	MotionStage2Data.MiddlePulse=3000;	//等速区間のパルス数
	MotionStage2Data.EndPulse   =20;  	//減速区間のパルス数

    //撮像完了位置→プラスリミットまで移動
    MotionStage3Data.TargetCount=100;	//等速区間の速度になるカウンター数
	MotionStage3Data.Direction  =0;		//回転方向　0 or 1
	MotionStage3Data.StartPulse =50;  	//加速区間のパルス数
	MotionStage3Data.MiddlePulse=150;	//等速区間のパルス数
	MotionStage3Data.EndPulse   =10;  	//減速区間のパルス数

    //マイナスリミットまで移動
    MotionStage4Data.TargetCount=70;	//等速区間の速度になるカウンター数
	MotionStage4Data.Direction  =1;		//回転方向　0 or 1
	MotionStage4Data.StartPulse =200;  	//加速区間のパルス数
	MotionStage4Data.MiddlePulse=3000;	//等速区間のパルス数
	MotionStage4Data.EndPulse   =100;  	//減速区間のパルス数

    //原点復帰移動２(プラス方向)
    MotionStage5Data.TargetCount=500;	//等速区間の速度になるカウンター数
	MotionStage5Data.Direction  =0;		//回転方向　0 or 1
	MotionStage5Data.StartPulse =20;  	//加速区間のパルス数
	MotionStage5Data.MiddlePulse=50;	//等速区間のパルス数
	MotionStage5Data.EndPulse   =20;  	//減速区間のパルス数

    //原点復帰移動　電源ＯＮ後の動作
    MotionStage6Data.TargetCount=500;	//等速区間の速度になるカウンター数
	MotionStage6Data.Direction  =0;		//回転方向　0 or 1
	MotionStage6Data.StartPulse =10;  	//加速区間のパルス数
	MotionStage6Data.MiddlePulse=200;	//等速区間のパルス数
	MotionStage6Data.EndPulse   =10;  	//減速区間のパルス数
}
ControlMotion1A::~ControlMotion1A(void)
{
	delete	[]RxData;
	RxData=NULL;
}

bool	ControlMotion1A::GetRx(int &Cmd ,unsigned char *data ,int buffsize)
{
	int d=GetChar();
	if(d<0)
		return false;
	if(RxNumb==0){
		if(d!='\x1b')
			return false;
		RxNumb++;
	}
	else if(RxNumb==1){
		RxByte=d;
		RxNumb++;
	}
	else if(RxNumb==2){
		RxByte|=d<<8;
		RxNumb++;
	}
	else if(RxNumb==3){
		RxCmd=d;
		RxNumb++;
		RxWPoint=0;
	}
	else{
		RxData[RxWPoint]=d;
		RxWPoint++;
		if(RxWPoint>=1024)
			RxWPoint=1023;
	}
	if(RxNumb==4){
		if(RxWPoint>=RxByte){
			Cmd=RxCmd;
            if(RxByte<buffsize)
			    memcpy(data,RxData,RxByte);
            else
                memcpy(data,RxData,buffsize);
			RxByte	=0;
			RxWPoint=0;
			RxNumb	=0;
			RxCmd	=0;
			return true;
		}
	}
	return false;
}

bool	ControlMotion1A::SendAck(void)
{
	SendTx('A',NULL, 0);

	Wait100ms();

	int	Cmd;
	unsigned char data[1024];
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,data,sizeof(data))==true){
			if(Cmd=='A')
				return true;
			return false;
		}
	}
	return false;
}

void ControlMotion1A::SendTx(char Cmd ,char *Buff, unsigned short datalen)
{
	short	i;
    Wait1ms();
	SendChar('\x1b') ;
    Wait1ms();

	int	idatalen=datalen+1;
	char	Sum=(char)(idatalen);
	SendChar((char)(idatalen)) 	;
    Wait1ms();
	Sum+=(char)(idatalen>>8);
	SendChar((char)(idatalen>>8));
    Wait1ms();
	SendChar(Cmd) ;
	Sum+=Cmd;
    Wait1ms();
	for(i=0;i<datalen;i++){
		SendChar(Buff[i]) ;
		Sum+=Buff[i];
        Wait1ms();
	}
	SendChar(Sum);
}

void    ControlMotion1A::Wait1ms(void)
{
    for(unsigned int t=GetCPUMilisec();GetCPUMilisec()-t<=1;);
}

void    ControlMotion1A::Wait100ms(void)
{
    for(unsigned int t=GetCPUMilisec();GetCPUMilisec()-t<=100;);
}

void    ChangeEndian(int src, unsigned char dest[])
{
    unsigned char *p=(unsigned char *)&src;

    dest[0]=*(p+3);
    dest[1]=*(p+2);
    dest[2]=*(p+1);
    dest[3]=*(p+0);
}
void    ChangeEndian(unsigned int src, unsigned char dest[])
{
    ChangeEndian((int)src, dest);
}
void    ChangeEndian(short src, unsigned char dest[])
{
    unsigned char *p=(unsigned char *)&src;

    dest[0]=*(p+1);
    dest[1]=*(p+0);
}
void    ChangeEndian(unsigned short src, unsigned char dest[])
{
    ChangeEndian((short)src, dest);
}

void    ChangeEndian(unsigned char src[],int &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+3)=src[0];
    *(p+2)=src[1];
    *(p+1)=src[2];
    *(p+0)=src[3];
}
void    ChangeEndian(unsigned char src[],short &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+1)=src[0];
    *(p+0)=src[1];
}

void    ChangeEndian(unsigned char src[],unsigned int &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+3)=src[0];
    *(p+2)=src[1];
    *(p+1)=src[2];
    *(p+0)=src[3];
}
void    ChangeEndian(unsigned char src[],unsigned short &dest)
{
    unsigned char *p=(unsigned char *)&dest;

    *(p+1)=src[0];
    *(p+0)=src[1];
}
bool	ControlMotion1A::SetMotionNumb(int N)
{
    if(IsInitialed()==false)
        Initial();

	unsigned char data[1024];
	int	Cmd;
    ChangeEndian(N,data);
	SendTx('B' ,(char *)data, sizeof(N));

	Wait100ms();

	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,data,sizeof(data))==true){
			if(Cmd=='A')
				return true;
			return false;
		}
	}
	return false;
}
bool	ControlMotion1A::ReqMotionNumb(int &N)
{
    if(IsInitialed()==false)
        Initial();

	SendTx('b' ,NULL, 0);

	Wait100ms();

	int	Cmd;
    unsigned char    Data[4];
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)Data,sizeof(N))==true){
			if(Cmd=='b'){
                ChangeEndian(Data,N);
				return true;
                }
			return false;
		}
	}
	return false;
}

bool	ControlMotion1A::SetMotionData(short N,struct MotionStruct &Data)
{
    if(IsInitialed()==false)
        Initial();

	for(int i=0;i<5;i++){
SendAgain:;
		unsigned char data[1024];
		ChangeEndian(N                  ,&data[0]);
	    ChangeEndian(Data.TargetCount   ,&data[2]);
		ChangeEndian(Data.Direction     ,&data[4]);
	    ChangeEndian(Data.StartPulse    ,&data[6]);
		ChangeEndian(Data.MiddlePulse   ,&data[10]);
	    ChangeEndian(Data.EndPulse      ,&data[14]);
		SendTx('C' ,(char *)data, 18);

		Wait100ms();

		int	Cmd;
		for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
			if(GetRx(Cmd ,data,sizeof(data))==true){
				if(Cmd=='A')
					return true;
				if(Cmd=='N')
					goto	SendAgain;
				return false;
			}
		}
	}
	return false;
}
bool	ControlMotion1A::ReqMotionData(short N,struct MotionStruct &Data)
{
    if(IsInitialed()==false)
        Initial();

    unsigned char data[1024];
    ChangeEndian(N                  ,&data[0]);
	SendTx('c' ,(char *)data, sizeof(N));

	Wait100ms();

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)&data,sizeof(data))==true){
			if(Cmd=='c'){
                ChangeEndian(&data[0] ,Data.TargetCount );
                ChangeEndian(&data[2] ,Data.Direction   );
                ChangeEndian(&data[4] ,Data.StartPulse  );
                ChangeEndian(&data[8] ,Data.MiddlePulse );
                ChangeEndian(&data[12],Data.EndPulse    );
				return true;
                }
			return false;
		}
	}
	return false;
}


bool    ControlMotion1A::SetTriggerSetting(struct TriggerSetting &Data)
{
    if(IsInitialed()==false)
        Initial();

	for(int i=0;i<5;i++){
SendAgain:;
		unsigned char data[1024];
		ChangeEndian(Data.OutTriggerStartPulse  ,&data[0]);
	    ChangeEndian(Data.OutTriggerKeepOnTime  ,&data[4]);
		ChangeEndian(Data.OutTriggerPort        ,&data[8]);
		SendTx('T' ,(char *)data, 12);

		Wait100ms();

		int	Cmd;
		for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
			if(GetRx(Cmd ,data,sizeof(data))==true){
				if(Cmd=='A')
					return true;
				if(Cmd=='N')
					goto	SendAgain;
				return false;
			}
		}
	}
	return false;
}

bool    ControlMotion1A::ReqTriggerSetting(struct TriggerSetting &Data)
{
    if(IsInitialed()==false)
        Initial();

    unsigned char data[1024];
	SendTx('t' ,NULL, 0);

	Wait100ms();

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)&data,sizeof(data))==true){
			if(Cmd=='t'){
                ChangeEndian(&data[0] ,Data.OutTriggerStartPulse );
                ChangeEndian(&data[4] ,Data.OutTriggerKeepOnTime   );
                ChangeEndian(&data[8] ,Data.OutTriggerPort  );
				return true;
                }
			return false;
		}
	}
	return false;
}


bool	ControlMotion1A::SetMotionAttr(struct MotionAttrStruct &Data)
{
    if(IsInitialed()==false)
        Initial();

	for(int i=0;i<5;i++){
SendAgain:;
		unsigned char data[1024];

	    ChangeEndian(Data.MotionStopPercentage ,&data[0]);
		ChangeEndian(Data.DropTime      ,&data[4]);
		SendTx('D' ,(char *)&data, 8);

		Wait100ms();

		int	Cmd;
		for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
			if(GetRx(Cmd ,data,sizeof(data))==true){
				if(Cmd=='A')
					return true;
				if(Cmd=='M')
					goto	SendAgain;
				return false;
			}
		}
	}
	return false;
}
bool	ControlMotion1A::ReqMotionAttr(struct MotionAttrStruct &Data)
{
    if(IsInitialed()==false)
        Initial();

	unsigned char data[1024];
	SendTx('d' ,NULL, 0);

	Wait100ms();

	int	Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)&data,sizeof(data))==true){
			if(Cmd=='d'){
                ChangeEndian(&data[0],Data.MotionStopPercentage);
                ChangeEndian(&data[4],Data.DropTime);
				return true;
                }
			return false;
		}
	}
	return false;
}

bool	ControlMotion1A::SetCurrentMotion(MotionState c)
{
    if(IsInitialed()==false)
        Initial();

	for(int i=0;i<5;i++){
SendAgain:;
		char	Data=(char)c;
		SendTx('G' ,&Data, sizeof(Data));

		Wait100ms();

		unsigned char data[1024];
		int	Cmd;
		for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
			if(GetRx(Cmd ,data,sizeof(data))==true){
				if(Cmd=='A')
					return true;
				if(Cmd=='N')
					goto	SendAgain;
				return false;
			}
		}
	}
	return false;
}

bool	ControlMotion1A::ReqCurrentMotion(MotionState &c)
{
    if(IsInitialed()==false)
        Initial();

	SendTx('g' ,NULL, 0);

	Wait100ms();

	int		Cmd;
	char	Data;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)&Data,sizeof(Data))==true){
			if(Cmd=='g'){
				c=(MotionState)Data;
				return true;
			}
			return false;
		}
	}
	return false;
}

bool	ControlMotion1A::ReqInport(int port ,unsigned char &portbit)
{
    if(IsInitialed()==false)
        Initial();

	unsigned char	N=(unsigned char)port;
	SendTx('I' ,(char *)&N, sizeof(N));

	Wait100ms();

	int		Cmd;
	char	k;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)&k,sizeof(k))==true){
			if(Cmd=='I'){
				portbit=k;
				return true;
			}
			return false;
		}
	}
	return false;
}

bool	ControlMotion1A::ReqInport(unsigned char &portallbit)
{
    if(IsInitialed()==false)
        Initial();

	SendTx('i' ,NULL, 0);

	Wait100ms();

	int		Cmd;
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,&portallbit,sizeof(portallbit))==true){
			if(Cmd=='i'){
				return true;
			}
			return false;
		}
	}
	return false;
}

bool	ControlMotion1A::SendOutport(int port ,unsigned char portbit)
{
    if(IsInitialed()==false)
        Initial();

	unsigned char	N[2];
	N[0]=(unsigned char)port;
	N[1]=portbit;
	SendTx('O' ,(char *)N, sizeof(N));

	Wait100ms();

	int		Cmd;
	unsigned char data[1024];
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)&data,sizeof(data))==true){
			if(Cmd=='A'){
				return true;
			}
			return false;
		}
	}
	return false;
}
bool	ControlMotion1A::SendOutport(unsigned char portbit)
{
    if(IsInitialed()==false)
        Initial();

	SendTx('I' ,(char *)&portbit, sizeof(portbit));

	Wait100ms();

	int		Cmd;
	unsigned char data[1024];
	for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
		if(GetRx(Cmd ,(unsigned char *)&data,sizeof(data))==true){
			if(Cmd=='A'){
				return true;
			}
			return false;
		}
	}
	return false;
}

bool	ControlMotion1A::SendMotionCommand(unsigned char CommandNo)
{
    if(IsInitialed()==false)
        Initial();

	for(int i=0;i<5;i++){
SendAgain:;
		SendTx('H' ,(char *)&CommandNo, sizeof(CommandNo));

		Wait100ms();

		int	Cmd;
		unsigned char data[1024];
		for(unsigned int d=GetCPUMilisec();GetCPUMilisec()-d<WaitingMilisec;){
			if(GetRx(Cmd ,data,sizeof(data))==true){
				if(Cmd=='A')
					return true;
				if(Cmd=='N')
					goto	SendAgain;
				return false;
			}
		}
	}
	return false;
}

bool	ControlMotion1A::SetMotionData1(void)
{
    if(IsInitialed()==false)
        Initial();
//	Wait100ms();
    return SetMotionData(MotionStage1Code,MotionStage1Data);
}

bool	ControlMotion1A::SetMotionData2(void)
{
    if(IsInitialed()==false)
        Initial();
//	Wait100ms();
    return SetMotionData(MotionStage2Code,MotionStage2Data);
}

bool	ControlMotion1A::SetMotionData3(void)
{
    if(IsInitialed()==false)
        Initial();
//	Wait100ms();
    return SetMotionData(MotionStage3Code,MotionStage3Data);
}

bool	ControlMotion1A::SetMotionData4(void)
{
    if(IsInitialed()==false)
        Initial();
//	Wait100ms();
    return SetMotionData(MotionStage4Code,MotionStage4Data);
}

bool	ControlMotion1A::SetMotionData5(void)
{
    if(IsInitialed()==false)
        Initial();
//	Wait100ms();
    return SetMotionData(MotionStage5Code,MotionStage5Data);
}

bool	ControlMotion1A::SetMotionData6(void)
{
    if(IsInitialed()==false)
        Initial();
//	Wait100ms();
    return SetMotionData(MotionStage6Code,MotionStage6Data);
}
