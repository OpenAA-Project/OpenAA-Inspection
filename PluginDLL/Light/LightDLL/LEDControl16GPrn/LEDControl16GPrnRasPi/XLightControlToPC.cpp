#include "XLightControlToPC.h"
#include "ShowLEDControl16GForm.h"
#include "LEDControl16GPrnRasPi.h"

LightControlToPCClient::LightControlToPCClient(LightControlToPCServer *p ,QTcpSocket *s)
:Sock(s),Parent(p)
{
    connect(Sock,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
    connect(Sock,SIGNAL(disconnected()),this,SLOT(SlotDisconnected()));
}

void	LightControlToPCClient::SlotReadyRead()
{
    char	DipSW;
    char	Cmd;
    if(Sock->read(&DipSW,1)!=1)
        return;
    if(Sock->read(&Cmd,1)!=1)
        return;

    if(Cmd==0x20){
        char    *fp=Parent->Parent->BoardName[0];
        int Len=strlen(fp);
        if(Sock->write((const char *)fp,Len)!=Len)
            return;
    }
    if(Cmd==0x21){
        BYTE	TxData[33];
        TxData[0]=Parent->Parent->BoardCount;
        for(int k=0;k<Parent->Parent->BoardCount;k++){
            TxData[k+1]=Parent->Parent->BoardData[k].DipSW;
        }
        if(Sock->write((const char *)TxData,sizeof(TxData))!=sizeof(TxData))
            return;
    }
    if(Cmd==0x1A){
        struct	TriggerInfo	Data;
        if(Sock->read((char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Parent->SetData(Data);
    }
    else if(Cmd==0x1B){
        struct	TriggerInfo	Data;
        Parent->ReqData(Data);
        char	Ack=0x1E;

        if(Sock->write(&Ack,1)!=1)
            return;
        if(Sock->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Sock->flush();
    }
    else if(Cmd==0x1C){
        struct	DropPassInfo	Data;
        if(Sock->read((char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Parent->SetData(Data);
    }
    else if(Cmd==0x1D){
        struct	DropPassInfo	Data;
        Parent->ReqData(Data);
        char	Ack=0x1F;

        if(Sock->write(&Ack,1)!=1)
            return;
        if(Sock->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Sock->flush();
    }
    else if(Cmd==0x30){
        struct	ResultCounterInfo	Data;
        Parent->ReqData(Data);
        char	Ack=0x30;

        if(Sock->write(&Ack,1)!=1)
            return;
        if(Sock->write((const char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Sock->flush();
    }
    else if(Cmd==0x31){
        Parent->ResetCounter();
    }
    else if(Cmd==0xF0){
        BYTE	Data;
        if(Sock->read((char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Parent->Parent->SetTestLED(DipSW,(Data==0)?false:true);
    }
    else if(Cmd==0xF1){
        BYTE	Data;
        if(Sock->read((char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Parent->Parent->SetAllOn(DipSW,(Data==0)?false:true);
    }
    else if(Cmd==0xF2){
        BYTE	Data;
        if(Sock->read((char *)&Data,sizeof(Data))!=sizeof(Data))
            return;
        Parent->Parent->SetAllCurrentPattern(DipSW,Data);
    }
    else if(Cmd==0xF3){
        BYTE	PatternNo;
        if(Sock->read((char *)&PatternNo,sizeof(PatternNo))!=sizeof(PatternNo))
            return;
        BYTE	TxData[10+4*MaxCountLines];
        int	Brd=-1;
        for(int k=0;k<Parent->Parent->BoardCount;k++){
            if(Parent->Parent->BoardData[k].DipSW==DipSW){
                Brd=k;
                break;
            }
        }
        if(Brd>=0){
            Parent->Parent->BoardData[Brd].GetLightData(PatternNo);
            int	Len=0;
            TxData[Len]=0xF3;
            Len++;
            for(int i=0;i<MaxCountLines;i++){
                uint32	d=Parent->Parent->BoardData[Brd].LineInfo[i].TargetValue[PatternNo];
                TxData[1+Len+0]=d&0xFF;
                TxData[1+Len+1]=(d>>8)&0xFF;
                TxData[1+Len+2]=(d>>16)&0xFF;
                TxData[1+Len+3]=(d>>24)&0xFF;
                Len+=4;
            }
            if(Sock->write((const char *)TxData,Len)!=Len){
                return;
            }
        }
        else{
            TxData[0]=0xFF;
            if(Sock->write((const char *)TxData,1)!=1){
                return;
            }
        }
    }
    else if(Cmd==0xF4){
        BYTE	PatternNo;
        if(Sock->read((char *)&PatternNo,sizeof(PatternNo))!=sizeof(PatternNo))
            return;
        BYTE	RxData[10+4*MaxCountLines];
        int	Brd=-1;
        for(int k=0;k<Parent->Parent->BoardCount;k++){
            if(Parent->Parent->BoardData[k].DipSW==DipSW){
                Brd=k;
                break;
            }
        }
        if(Brd>=0){
            int	Len=MaxCountLines*4;
            if(Sock->read((char *)RxData,Len)!=Len)
                return;
            for(int i=0;i<MaxCountLines;i++){
                uint32	d=
                     (RxData[1+Len+0]&0xFF)
                    +(RxData[1+Len+1]<<8)
                    +(RxData[1+Len+2]<<16)
                    +(RxData[1+Len+3]<<24);
                Parent->Parent->BoardData[Brd].LineInfo[i].TargetValue[PatternNo]=d;
            }
            Parent->Parent->BoardData[Brd].SetLightData(PatternNo);
        }
    }
    else if(Cmd==0xF5){
        BYTE	TxData[10+4*MaxCountLines];
        int	Brd=-1;
        for(int k=0;k<Parent->Parent->BoardCount;k++){
            if(Parent->Parent->BoardData[k].DipSW==DipSW){
                Brd=k;
                break;
            }
        }
        if(Brd>=0){
            Parent->Parent->BoardData[Brd].GetCurrentValue();
            int	Len=0;
            TxData[Len]=0xF3;
            Len++;
            for(int i=0;i<MaxCountLines;i++){
                uint32	d=Parent->Parent->BoardData[Brd].LineInfo[i].CurrentValue;
                TxData[1+Len+0]=d&0xFF;
                TxData[1+Len+1]=(d>>8)&0xFF;
                TxData[1+Len+2]=(d>>16)&0xFF;
                TxData[1+Len+3]=(d>>24)&0xFF;
                Len+=4;
            }
            if(Sock->write((const char *)TxData,Len)!=Len){
                return;
            }
        }
        else{
            TxData[0]=0xFF;
            if(Sock->write((const char *)TxData,1)!=1){
                return;
            }
        }
    }

    qint64	N=Sock->bytesAvailable();
    if(N>0){
        QByteArray	Dummy=Sock->readAll();
    }
}

void	LightControlToPCClient::SlotDisconnected()
{
    deleteLater();
}


LightControlToPCServer::LightControlToPCServer(ShowLEDControl16GForm *p)
:Parent(p)
{
    connect(this,SIGNAL(newConnection()),this,SLOT(SlotNewConnection()));
}
void	LightControlToPCServer::StartListen(void)
{
    listen(QHostAddress::Any,LightControlToPCPort);
}

void	LightControlToPCServer::SlotNewConnection()
{
    QTcpSocket	*s=nextPendingConnection ();
    new LightControlToPCClient(this,s);
}

void	LightControlToPCServer::SetData(struct	TriggerInfo &Data)
{
    Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerA	=Data.TriggerTiming1;
    Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerB	=Data.TriggerTiming2;
    Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerC	=Data.TriggerTiming3;
    Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerD	=Data.TriggerTiming4;
    //Parent->Parent->GIOData.DropLength			=Data.DropTiming;
    Parent->Parent->SetGIODataToWindow();
    Parent->Parent->WriteGIO();
    //Parent->WriteEIO();
}
void	LightControlToPCServer::ReqData(struct	TriggerInfo &Data)
{
    Data.TriggerTiming1	=Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerA;
    Data.TriggerTiming2	=Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerB;
    Data.TriggerTiming3	=Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerC;
    Data.TriggerTiming4	=Parent->Parent->GIOData.GioFixedData.DelayFrameTriggerD;
    //Data.DropTiming		=Parent->EIOData.DropLength;
}

void	LightControlToPCServer::SetData(struct	DropPassInfo &Data)
{
    Parent->Parent->GIOData.GioFixedData.ConveyerLength	=Data.ConveyerLength;
    Parent->Parent->GIOData.GioFixedData.GateOpenTerm	=Data.GateOpenTerm;
    Parent->Parent->GIOData.GioFixedData.DefDelayedCount=Data.DefDelayedCount;
    //Parent->Parent->GIOData.DropLength			=Data.DropTiming;
    Parent->Parent->SetGIODataToWindow();
    Parent->Parent->WriteGIO();
    //Parent->WriteEIO();
}
void	LightControlToPCServer::ReqData(struct	DropPassInfo &Data)
{
    Data.ConveyerLength	=Parent->Parent->GIOData.GioFixedData.ConveyerLength;
    Data.GateOpenTerm	=Parent->Parent->GIOData.GioFixedData.GateOpenTerm;
    Data.DefDelayedCount=Parent->Parent->GIOData.GioFixedData.DefDelayedCount;
    //Data.DropTiming		=Parent->EIOData.DropLength;
}
void	LightControlToPCServer::ReqData(struct	ResultCounterInfo &Data)
{
    Data.TotalCount	=Parent->Parent->GIOData.TotalCount;
    Data.OKCount	=Parent->Parent->GIOData.OKCount;
    Data.NGCount	=Parent->Parent->GIOData.NGCount;
    Data.TMCount	=Parent->Parent->GIOData.TMCount;
}
void    LightControlToPCServer::ResetCounter(void)
{
    Parent->Parent->GIOData.ResetCounter=true;
    Parent->Parent->WriteGIO();
    Parent->Parent->GIOData.ResetCounter=false;
    Parent->Parent->WriteGIO();
}
