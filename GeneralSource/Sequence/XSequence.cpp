/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\XSequence.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/
#include "XMacro.h"
#include "swap.h"
#include <QApplication>
#include <stdio.h>
#include <ctype.h>
#define	_USE_MATH_DEFINES
#include <math.h>
#include <QMessageBox>
//#include <mbstring.h>

#include "XSeqDLLGlobal.h"	//D-20051026
#include "XSeqDLLVar.h"
#include "XSequence.h"
#include "XPIOButton.h"
#include "ThreadSequence.h"
#include "XIODefine.h"
#include "XWaveEdit.h"
#include "XTimeConvert.h"
#include "XDataInLayer.h"
#include "XCriticalFunc.h"
#include "XGUIFormBase.h"

#include "OutSequenceYesNo.h"
#include "OutSequenceShowYesNo.h"
#include "OutSequenceShow.h"
#include "OutSequenceShowOK.h"
#include "OutSequenceMessage.h"
#include "OutSequenceInput.h"

/*
OutSequenceYesNo		*SeqControl::OutSequenceYesNoForm;
OutSequenceShowYesNo	*SeqControl::OutSequenceShowYesNoForm;
OutSequenceShow			*SeqControl::OutSequenceShowForm;
OutSequenceShowOK		*SeqControl::OutSequenceShowOKForm;
OutSequenceMessage		*SeqControl::OutSequenceMessageForm;
OutSequenceInput		*SeqControl::OutSequenceInputForm;


///static  SeqControl  SeqControlInstance;
NPListPack<SequenceStock>   SeqControl::SeqStock;
NPListPack<Sequence>        SeqControl::Seq;
volatile    int         SeqControl::SeqNumb;
QThread     *SeqControl::Parent;

IOOperandPack               SeqControl::IOOpe;
CommOperandPack             SeqControl::CommOpe;
BitOperandPack              SeqControl::BitOpe;
WordOperandPack             SeqControl::WordOpe;
FloatOperandPack            SeqControl::FloatOpe;
StringOperandPack           SeqControl::StringOpe;
SpecialOperandPack          SeqControl::SpecialOpe;
NumberOperandPack           SeqControl::NumberOpe;
CharOperandPack             SeqControl::CharOpe;
GroupOperandPack            SeqControl::GroupOpe;
SpecialBitOperandPack       SeqControl::SpecialBitOpe;
SpecialStringOperandPack    SeqControl::SpecialStringOpe;
///LanvarOperandPack           SeqControl::LanvarOpe;	//D-20051026
FifoOperandPack             SeqControl::FifoOpe;
DLLVarOperandPack           SeqControl::DLLVarOpe;

volatile    int     SeqControl::ReqHalt=0;
volatile    bool    SeqControl::OnStepping=false;


volatile    bool    SeqControl::DoHalt=false;
volatile    bool    SeqControl::OnHalting=false;
volatile    int     SeqControl::GlanceFreq=0;
volatile    int     SeqControl::NowGlanceTime=0;


///NPListPack<LanVarSocketList>    SeqControl::LanVarSocket;	//D-20051026
///NPListPack<LanVarRCmd>          SeqControl::LanVarRData;	//D-20051026
QMutex                *SeqControl::LanVarCSection;	//D-20051026
volatile    bool                SeqControl::GetLanverReqMode=false;
volatile    QColor  SeqControl::MessageCol=Qt::red;

QString  SeqControl::SeqTitle="";
QString  SeqControl::TimingPath="";
QString  SeqControl::TimingFileName;
QDataStream *SeqControl::WriteTimingFile=NULL;

volatile    bool    SeqControl::ReArrangehistSW=false;
volatile    int     SeqControl::StepTime=20;
volatile    int     SeqControl::LastOperationTime;	// 最後に操作、実行された時
													// 刻
QString  SeqControl::ErrorLine;
bool            SeqControl::Started=false;

//void    (*SeqControl::StateOut)(int code ,char *msg)=NULL;
void    (*SeqControl::StateOut)(int code ,QString &msg)=NULL;
///MTWSocket   *SeqControl::ServerSock=NULL;	//D-20051026
int         SeqControl::LanvarPort=20031;
void        (*SeqControl::XSeqLocalInit)(void)=NULL;

void    (*SeqControl::SetDataSpecialOperand)(int ID, int d)=NULL;
int     (*SeqControl::GetDataSpecialOperand)(int ID);

void    (*SeqControl::SetDataSpecialBitOperand)(int ID, bool d)=NULL;
bool     (*SeqControl::GetDataSpecialBitOperand)(int ID)=NULL;

void    (*SeqControl::SetDataSpecialStringOperand)(int ID, QString d)=NULL;
QString  (*SeqControl::GetDataSpecialStringOperand)(int ID)=NULL;

time_t  SpecialOperand::S20Time;

NPListPack<SeqCommandList>  SeqControl::CmdList;
bool                        SeqControl::DLLDebugMode    =false;
QMutex                      *SeqControl::DLLSync        =NULL;
DWORD                       SeqControl::StartTickCount  =0;
time_t                      SeqControl::StartTime       =0;
*/

//=========================================================================

bool    WriteString(QString data , FILE *os)
{
	int Len=data.length()+1;
    if(fwrite(&Len,sizeof(Len),1,os)!=1)
        return(false);
    if(fwrite(data.data(),Len,1,os)!=1)
        return(false);
    return(true);
}
bool    ReadString(QString &data , FILE *is)
{
    char    Buff[1000];
    int Len;
    if(fread(&Len,sizeof(Len),1,is)!=1)
        return(false);
    if(Len<sizeof(Buff)){
        if(fread(Buff,Len,1,is)!=1)
            return(false);
        data=Buff;
        }
    else{
        char    *buff=new char[Len];
        if(fread(buff,Len,1,is)!=1){
			delete	[]buff;
            return(false);
		}
        data=buff;
        delete  []buff;
        }
    return(true);
}

/*↓D-20051026------------------------------------------------------------------
LanVarSocketList::LanVarSocketList(void)
{
    CliSock=NULL;
    BuiltInListen=false;
    OnConnectingMode=false;
}

LanVarSocketList::~LanVarSocketList(void)
{
    if(IsConnected()==true)
        CliSock->Close();
    //if(CliSock!=NULL)
    //    delete  CliSock;
    CliSock=NULL;
}
bool    LanVarSocketList::Connect(void)
{
    OnConnectingMode=true;

    if(CliSock==NULL){
        static  int CliNumber=0;
        CliSock=new MTWSocket(Application->MainForm);
        CliSock->Name     =AnsiString("SeqCli")+AnsiString(CliNumber);
        CliNumber++;
        }
    CliSock->LineMode =false;
    CliSock->OnDataAvailable=RReceiverDataAvailable;
    CliSock->OnSessionClosed=RReceiverSessionClosed;
    CliSock->Port=SeqControl::LanvarPort;
    CliSock->Addr=IPAddress;
    CliSock->Proto  = "tcp";              // Protocol we wants to use

    try{
        if(CliSock->State != wsConnected
        && CliSock->State != wsConnecting) {
            CliSock->Connect();                   // Let's connect !
            }
        while(((unsigned int)CliSock)!=(0xEFEFEFEFLU)
        && CliSock->State == wsConnecting){
            Application->ProcessMessages();
            }
        OnConnectingMode=false;
        return(true);
        }
    catch(...){
        CliSock->Close();
        delete  CliSock;
        CliSock=NULL;
        OnConnectingMode=false;
        return(false);
        }
}

bool    LanVarSocketList::Close(void)
{
    if(CliSock!=NULL && CliSock->State == wsConnected){
        CliSock->Close();
        return(true);
        }
    return(false);
}

bool    LanVarSocketList::IsConnected(void)
{
    if(Application->Terminated==true)
        return(false);
    if(CliSock!=NULL && CliSock->State == wsConnected)
        return(true);
    return(false);
}
bool    LanVarSocketList::SendStr(char *buff)
{
    if(IsConnected()==true){
        try{
            CliSock->SendStr(AnsiString(buff) + "\r\n");
            return(true);
            }
        catch(...){
            }
        }
    return(false);
}

void  LanVarSocketList::RReceiverDataAvailable(
                          TObject *Sender, WORD Error)
{
    char Buffer[256];

    for(;;){
        int Count       = CliSock->Receive(Buffer, sizeof(Buffer)-1);
        if(Count<=0)
            return;
        Buffer[Count]   = 0;             // Null terminate received data
        if(SeqControl::LanVarCSection!=NULL){
            SeqControl::LanVarCSection->Acquire();
            SeqControl::LanVarRData.AppendList(new LanVarRCmd(Sender , Buffer[0],&Buffer[1]));
            SeqControl::LanVarCSection->Release();
            }
        }
}

LanVarRCmd::LanVarRCmd(TObject *sender ,BYTE cmd ,char *data)
{
    Sender=sender;
    Cmd=cmd;
    Data=data;
}

void    SeqControl::ProcessLanvar(void)
{
    for(;;){
		SeqControl::LanVarCSection->lock();
        LanVarRCmd  *c=LanVarRData.GetFirst();
        if(c==NULL){
            SeqControl::LanVarCSection->Release();
            return;
            }
        LanVarRData.RemoveList(c);
        SeqControl::LanVarCSection->Release();

        char    *fp=c->Data.c_str();
        if(c->Cmd=='A'){
            char    *cp=strchr(fp,'\x1b');
            if(cp!=NULL){
                *cp=0;
                cp++;
                AnsiString  name=fp;
                char    *ep=strstr(cp,"\r\n");
                if(ep!=NULL)
                    *ep=0;
                AnsiString  data=cp;
                for(LanvarOperand *c=SeqControl::LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                    if(name==c->GetName()){
                        c->Data=data;
                        }
                    }
                }
            MTWSocket    *M=dynamic_cast<MTWSocket *>(c->Sender);
            if(M!=NULL){
                LanVarSocketList *B=NULL;
                for(LanVarSocketList *q=SeqControl::LanVarSocket.GetFirst();q!=NULL;q=q->GetNext()){
                    if(q->CliSock==M){
                        q->GotIt=true;
                        B=q;
                        break;
                        }
                    }
                }
            }
        else
        if(c->Cmd=='B'){
            char    *cp=strstr(fp,"\r\n");
            if(cp!=NULL){
                *cp=0;
                AnsiString  name=fp;
                for(LanvarOperand *c=SeqControl::LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                    if(name==c->GetName()){
                        c->SetData(c->Data);
                        for(IPList *p=c->IP.GetFirst();p!=NULL;p=p->GetNext()){
                            p->SendData(name ,c->Data);
                            }
                        }
                    }
                }
            }
        else
        if(c->Cmd=='C'){
            char    *cp=strchr(fp,'\x1b');
            if(cp!=NULL){
                *cp=0;
                cp++;
                AnsiString  name=fp;
                char    *ep=strstr(cp,"\r\n");
                if(ep!=NULL){
                    *ep=0;
                    AnsiString  IPAddr=cp;
                    MTWSocket    *M=dynamic_cast<MTWSocket *>(c->Sender);
                    if(M!=NULL){
                        LanVarSocketList *B=NULL;
                        for(LanVarSocketList *q=SeqControl::LanVarSocket.GetFirst();q!=NULL;q=q->GetNext()){
                            if(q->CliSock==M){
                                B=q;
                                break;
                                }
                            }
                        if(B!=NULL){
                            for(LanvarOperand *c=SeqControl::LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                                if(name==c->GetName()){
                                    for(IPList *p=c->IP.GetFirst();p!=NULL;p=p->GetNext()){
                                        if(p->Sock==NULL){
                                            p->Sock=B;
                                            break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        else
        if(c->Cmd=='D'){
            MTWSocket    *M=dynamic_cast<MTWSocket *>(c->Sender);
            if(M!=NULL){
            LanVarSocketList *B=NULL;
                for(LanVarSocketList *q=SeqControl::LanVarSocket.GetFirst();q!=NULL;q=q->GetNext()){
                    if(q->CliSock==M){
                        B=q;
                        break;
                        }
                    }
                if(B!=NULL){
                    for(LanvarOperand *c=SeqControl::LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                        for(IPList *p=c->IP.GetFirst();p!=NULL;p=p->GetNext()){
                            if(p->Sock==B){
                                p->Sock=NULL;
                                break;
                                }
                            }
                        }
                    B->CliSock->Close();
                    }
                }
            }
        delete  c;
        }
}

void  LanVarSocketList::RReceiverSessionClosed(TObject *Sender,
                          WORD Error)
{
    MTWSocket    *M=dynamic_cast<MTWSocket *>(Sender);
    if(M!=NULL){
        M->Close();
        //LanVarSocketList *B=NULL;
        for(LanVarSocketList *q=SeqControl::LanVarSocket.GetFirst();q!=NULL;q=q->GetNext()){
            if(q->CliSock==M){
                for(LanvarOperand *c=SeqControl::LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                    for(IPList *p=c->IP.GetFirst();p!=NULL;p=p->GetNext()){
                        if(p->Sock==q)
                            p->Sock=NULL;
                        }
                    }
                //SeqControl::LanVarSocket.RemoveList(q);
                //while(q->OnConnectingMode==true)
                //    ThreadSequence::MSleep(10);
                //delete  q;

                break;
                }
            }
        }
}

IPList::IPList(void)
{
    Sock=NULL;
}
IPList::IPList(char *ip)
{
    IPAddress=ip;
    Sock=NULL;
}

void    IPList::Initial(void)
{
    if(Sock!=NULL)
        return;
    for(LanVarSocketList *c=SeqControl::LanVarSocket.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->IPAddress==IPAddress){
            Sock=c;
            return;
            }
        }
    LanVarSocketList *c=new LanVarSocketList();
    c->IPAddress=IPAddress;
    Sock=c;
    SeqControl::LanVarSocket.AppendList(c);
}

bool    IPList::Connect(void)
{
    if(Sock==NULL)
        return(false);
    if(IsConnected()==false){
        if(Sock==NULL)
            return(false);
        return(Sock->Connect());
        }
    return(true);
}
bool    IPList::IsConnected(void)
{
    if(Sock==NULL)
        return(false);
    return(Sock->IsConnected());
}

bool    IPList::SendConnection(AnsiString name)
{
    if(Sock==NULL)
        return(false);
    if(IsConnected()==true){
        if(Sock==NULL)
            return(false);
        char    *buff=new char[name.Length()+IPAddress.Length()+3];
        char    *fp=buff;
        *fp='C';
        fp++;
        strcpy(fp,name.c_str());
        fp+=name.Length();
        *fp=0x1b;
        fp++;
        strcpy(fp,IPAddress.c_str());

        Sock->SendStr(buff);
        delete  []buff;
        return(true);
        }
    return(false);
}

bool    IPList::SendData(AnsiString &name ,AnsiString &data)
{
    if(Sock==NULL)
        return(false);

    if(IsConnected()==false){
        Connect();
        if(IsConnected()==true){
            SendConnection(name);
            }
        }

    if(IsConnected()==true){
        if(Sock==NULL)
            return(false);
        char    *buff=new char[name.Length()+data.Length()+3];
        char    *fp=buff;
        *fp='A';
        fp++;
        strcpy(fp,name.c_str());
        fp+=name.Length();
        *fp=0x1b;
        fp++;
        strcpy(fp,data.c_str());

        Sock->SendStr(buff);
        delete  []buff;
        return(true);
        }
    return(false);
}


bool    IPList::ReqData(AnsiString name)
{
    ReqPrepare(name);
    if(Sock==NULL)
        return(false);

    if(IsConnected()==false){
        Connect();
        if(IsConnected()==true){
            SendConnection(name);
            }
        }

    if(IsConnected()==true){
        if(Sock==NULL)
            return(false);

        Sock->GotIt=false;

        char    *buff=new char[name.Length()+2];
        char    *fp=buff;
        *fp='B';
        fp++;
        strcpy(fp,name.c_str());
        fp+=name.Length();
        *fp=0;

        Sock->SendStr(buff);
        delete  []buff;

        for(DWORD t=ThreadSequence::GetNowMiliSec();Sock->GotIt==false && ::GetComputerMiliSec()-t<200;){
            Application->ProcessMessages();
            SeqControl::ProcessLanvar();
            if(Sock==NULL)
                break;
            }

        return(true);
        }
    return(false);
}

bool    IPList::ReqPrepare(AnsiString name)
{
    if(Sock==NULL)
        return(false);

    if(IsConnected()==false){
        Connect();
        if(IsConnected()==true){
            SendConnection(name);
            }
        }

    if(IsConnected()==true){
        if(Sock==NULL)
            return(false);

        Sock->GotIt=false;

        char    *buff=new char[name.Length()+2];
        char    *fp=buff;
        *fp='B';
        fp++;
        strcpy(fp,name.c_str());
        fp+=name.Length();
        *fp=0;

        Sock->SendStr(buff);
        delete  []buff;
        }
    return(true);
}

bool    IPList::ReqDone(void)
{
    if(IsConnected()==true){
        if(Sock==NULL)
            return(false);

        return(Sock->GotIt);
        }
    return(false);
}

bool    IPList::SaveBinHeader(FILE *file)
{
    if(WriteString(IPAddress,file)==false)
        return(false);
    return(true);
}
bool    IPList::LoadBinHeader(FILE *file)
{
    if(ReadString(IPAddress,file)==false)
        return(false);
    return(true);
}
↑D-20051026------------------------------------------------------------------*/


//==================================================================================

static  const	char    *Dellimiter=",: .{}\t\n";

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    fp
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
static  char    *GetTopString(char *fp)
{
    while(*fp==' ' || *fp=='\t')
        fp++;
    return(fp);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    fp
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
static  char    *GetWordCut(char *fp ,char buff[])
{
    fp=GetTopString(fp);
    int i;
    for(i=0;i<100;i++){
        if(strchr(Dellimiter,*fp)!=0 || *fp==0)
            break;
        buff[i]=*fp;
        fp++;
        }
    buff[i]=0;
    if(i==0)
        return(NULL);
    return(fp);
}

static	void	CutComment(char *Buff)
{
	for(char *fp=Buff;*fp!=0;fp++){
		if(*fp=='/' && *(fp+1)=='/'){
			*fp=0;
			return;
		}
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
Operand::Operand(SeqControl *baseParent)
{
	ID		=-1;
	BaseParent=baseParent;	
    Name=/**/"";
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
Operand::~Operand(void)
{
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    name
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    Operand::SetName(QString &name)
{
    Name=name;
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    id
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    Operand::SetID(int id)
{
    ID=id;
}

void    Operand::SetComment(const QString &comment)
{
    Comment=comment;
}

void      Operand::Copy(Operand *dest)
{
    dest->Name=Name;
    dest->ID=ID;
    dest->Comment=Comment;
}

void      Operand::SetData(const QString &d)
{
    QByteArray  D=d.toLocal8Bit();
    SetData(D);
}


IOOperand::IOOperand(SeqControl *baseParent):Operand(baseParent)
{
    hPIO_DRV=0;
    OutData=-1;
    ID=GetSeqControl()->IOOpe.GetNumber();


    BoardNumber	=0;
    PortNumber	=0;
    BitNumber	=0;
    InMode		=true;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    IOOperand::GetName(void)
{
    return(Name);
}

QString  IOOperand::GetComment(void)
{
    /*
    AnsiString ret;
    if(InMode==true){
        if(IORegData.GetIName(BoardNumber,PortNumber,BitNumber,ret)==true){
            return(ret);
            }
        return("");
        }
    else{
        if(IORegData.GetOName(BoardNumber,PortNumber,BitNumber,ret)==true){
            return(ret);
            }
        return("");
        }
    */
    return(/**/"");
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    IOOperand::Load(char buff[])
{
    char    nbuff[100];

    char    *fp=buff;
    fp+=9;
    fp=GetTopString(fp);
    fp=GetWordCut(fp,nbuff);
    if(fp==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=':'){
        return(false);
    }
    fp++;

    char    n1[20];
    char    n2[20];
    char    n3[20];

    if((fp=GetWordCut(fp,n1))==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=','){
        return(false);
    }
    fp++;

    if((fp=GetWordCut(fp,n2))==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=','){
        return(false);
    }
    fp++;

    if((fp=GetWordCut(fp,n3))==NULL){
        return(false);
    }

	QString	Q(nbuff);
    SetName(Q);
	BoardNumber=QString(n1).toInt();
    PortNumber =QString(n2).toInt();
    BitNumber  =QString(n3).toInt();

    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   IOOperand::GetNumeric(bool SrcReconstruct)
{
    Initial();
    if(GetSeqControl()->PIO!=NULL){
        return(GetSeqControl()->PIO->GetBit(BoardNumber,PortNumber,BitNumber));
    }
    return 0;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   IOOperand::GetStringCount(void)
{
    return(1);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      IOOperand::GetString(bool ThreadMode)
{
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(GetNumeric());
    return(A);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    IOOperand::Initial(void)
{
	//PIOClass::Initialize(ThreadSequence::InstSeq->Param);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void     IOOperand::SetData(int d)
{
    OutData=d&1;
    if(GetSeqControl()->PIO!=NULL){
        GetSeqControl()->PIO->SetBit(BoardNumber,PortNumber,BitNumber ,(BYTE)d);
    }
}
void     IOOperand::SetData(const QByteArray &d)
{
	int nD=d.toInt();
    OutData=nD&1;
    if(GetSeqControl()->PIO!=NULL){
        GetSeqControl()->PIO->SetBit(BoardNumber,PortNumber,BitNumber ,(BYTE)nD);
    }
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::LetSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int d=(BYTE)src->GetNumeric(true);
    SetData(d);

    if(parent!=NULL)
        parent->Add1NowLine();
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::LetBSeq(Sequence *parent,bool,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int d=(BYTE)src->GetNumeric(true);
    SetData(d);

    if(parent!=NULL)
        parent->Add1NowLine();
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=(GetNumeric(true) + src->GetNumeric(true))&1;

    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();

        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }

    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=(GetNumeric(true) - (src->GetNumeric(true)&1))&1;
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=(GetNumeric(true) & (src->GetNumeric(true)&1))&1;

    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();;
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	if(src->IsGetEnabled()==false)
		return(false);
	int r=(GetNumeric(true) | (src->GetNumeric(true)&1))&1;
	SetData(r);

	if(parent!=NULL){
		parent->Add1NowLine();
	    if(r!=0)
	    	parent->SetFlag(FlagConnectedMode,true);
	    else
	    	parent->SetFlag(FlagConnectedMode,false);
    }
	return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    int r=(GetNumeric(true) ^ (src->GetNumeric(true)&1))&1;
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();;
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=(~GetNumeric(true))&1;
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::FlushSeq(Sequence *parent,bool)
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::AllocSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::IndSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::BitloadSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3)
{
    if(src1->IsGetEnabled()==false)
        return(false);
    if(src2->IsGetEnabled()==false)
        return(false);
    if(src3->IsGetEnabled()==false)
        return(false);

    if(src1->GetNumeric(true)==BitNumber){
        int r=(src2->GetNumeric(true)>>src3->GetNumeric(true))&1;
        SetData(r);

        if(parent!=NULL){
            if(r!=0)
                parent->SetFlag(FlagConnectedMode,true);
            else
                parent->SetFlag(FlagConnectedMode,false);
        }
    }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=GetNumeric(true);

    if(parent!=NULL){
        if(r==0){
            parent->SetFlag(FlagConnectedMode,false);
        }
        else{
            parent->SetFlag(FlagConnectedMode,true);
        }
        parent->Add1NowLine();;
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) & (src->GetNumeric(true)&1);
    if(parent!=NULL){
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();;
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) | (src->GetNumeric(true)&1);
    if(parent!=NULL){
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) ^ (src->GetNumeric(true)&1);
    if(parent!=NULL){
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) == (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false)
        return(false);
    if(src2->IsGetEnabled()==false)
        return(false);

    int d1=src1->GetNumeric(true)&1;
    if(parent!=NULL){
        if(GetNumeric(true)<=d1 && d1<=(src2->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) != (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) >= (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) > (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) <= (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) < (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::MultSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=(GetNumeric(true) * (src->GetNumeric(true)&1))&1;
    SetData(r);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::DivSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=src->GetNumeric(true)&1;
    if(r!=0){
        int d=(GetNumeric(true) / r)&1;
        SetData(d);
        }

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::ModSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=src->GetNumeric(true)&1;
    if(r!=0){
        int d=(GetNumeric(true) % r)&1;
        SetData(d);
        }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::StrMoveSeq(Sequence *parent,bool ,Operand * ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::LowerSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::UpperSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::StateSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::TWSetSeq(Sequence *parent,bool)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::FSetSeq(Sequence *parent,bool)
{
    SetData(1);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      IOOperand::FResetSeq(Sequence *parent,bool)
{
    SetData(0);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

bool      IOOperand::RxTimeoutSeq(Sequence *parent,bool ,Operand * ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

bool      IOOperand::StrLenSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
bool      IOOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      IOOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      IOOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      IOOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      IOOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      IOOperand::BPrintSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
bool      IOOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();;
    }
    return(true);
}

bool      IOOperand::InputFromString(Sequence *parent,QString &Src)
{
	if(Src.compare("true")==0
    || Src=="1")
        SetData(1);
    else
        SetData(0);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

bool      IOOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *src)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    CommOperand::GetName(void)
{
    return(Name);
}

CommOperand::CommOperand(SeqControl *baseParent)
    :QObject(baseParent->GetLayersBase()->GetMainWidget()),Operand(baseParent)
{
    sio=NULL;
    RxTop=0;
    TermNumb=0;
    IgnoreNumb=0;
    RxTimeoutMilisec=0;
    IntoTime=0;
    RsCs=false;
    ID=GetSeqControl()->CommOpe.GetNumber();

	for(int i=0;i<sizeof(TermChar)/sizeof(TermChar[0]);i++){
		TermChar[i]=NULL;
	}
	for(int i=0;i<sizeof(IgnoreChar)/sizeof(IgnoreChar[0]);i++){
		IgnoreChar[i]=NULL;
	}

    CommPort	=0;
    BPS			=0;
    Parity		=0;
	Stopbit		=0;
    Character	=0;
    NoTermRxByte	=0;
	memset(RxBuff,0,sizeof(RxBuff));
    RxTimeoutAddress	=0;
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    CommOperand::Load(char buff[])
{
    char    nbuff[100];

	char	*commentstr=strstr(buff,"//");
	if(commentstr!=NULL){
		*commentstr=0;
    }
    char    *fp=buff;
    fp+=11;
    fp=GetTopString(fp);
    fp=GetWordCut(fp,nbuff);
    if(fp==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=':'){
        return(false);
    }
    fp++;

    char    n1[20];
    char    n2[20];
    char    n3[20];
    char    n4[20];
    char    n5[20];
    char    n6[20];

    if((fp=GetWordCut(fp,n1))==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=','){
        return(false);
    }
    fp++;

    if((fp=GetWordCut(fp,n2))==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=','){
        return(false);
    }
    fp++;

    if((fp=GetWordCut(fp,n3))==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=','){
        return(false);
    }
    fp++;

    if((fp=GetWordCut(fp,n4))==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=','){
        return(false);
    }
    fp++;

    if((fp=GetWordCut(fp,n5))==NULL){
        return(false);
    }

	QString	Q(nbuff);
    SetName(Q);
	bool ok;
	CommPort    =QString(n1).toInt();
    BPS         =QString(n2).toInt(&ok);
	if(ok==false) BPS=9600;
    Parity      =QString(n3).toInt(&ok);
	if(ok==false) Parity=1;
    Character   =QString(n4).toInt(&ok);
	if(ok==false) Character=8;
    Stopbit     =QString(n5).toInt(&ok);
	if(ok==false) Stopbit=1;
    RsCs        =false;

    if((fp=GetWordCut(fp,n6))!=NULL){
        if(stricmp(n6,"rscs")==0){
            RsCs=true;
        }
    }

    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
CommOperand::~CommOperand(void)
{
    if(sio!=NULL){
        sio->close();
        delete  sio;
        sio=NULL;
        }
	for(int i=0;i<sizeof(TermChar)/sizeof(TermChar[0]);i++){
		if(TermChar[i]!=NULL)
			delete	[]TermChar[i];
		TermChar[i]=NULL;
	}
	for(int i=0;i<sizeof(IgnoreChar)/sizeof(IgnoreChar[0]);i++){
		if(IgnoreChar[i]!=NULL)
			delete	[]IgnoreChar[i];
		IgnoreChar[i]=NULL;
	}
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    CommOperand::Initial(void)
{
	if(sio!=NULL && sio->isOpen()==false){
		delete	sio;
		sio=NULL;
	}
    if(sio==NULL){
		//char *portName;
        //sio = new QSerialPort();
        //
        //switch(CommPort){
        //    case 0:
        //        portName="COM1";
        //        break;
        //    case 1:
        //        portName="COM1";
        //        break;
        //    case 2:
        //        portName="COM2";
        //        break;
        //    case 3:
        //        portName="COM3";
        //        break;
        //    case 4:
        //        portName="COM4";
        //        break;
        //    case 5:
        //        portName="COM5";
        //        break;
        //    case 6:
        //        portName="COM6";
        //        break;
        //    case 7:
        //        portName="COM7";
        //        break;
        //    case 8:
        //        portName="COM8";
        //        break;
        //    case 9:
        //        portName="COM9";
        //        break;
        //    case 10:
        //        portName="\\\\.\\COM10";
        //        break;
        //    case 11:
        //        portName="\\\\.\\COM11";
        //        break;
        //    case 12:
        //        portName="\\\\.\\COM12";
        //        break;
        //    case 13:
        //        portName="\\\\.\\COM13";
        //        break;
        //    case 14:
        //        portName="\\\\.\\COM14";
        //        break;
        //    case 15:
        //        portName="\\\\.\\COM15";
        //        break;
        //    case 16:
        //        portName="\\\\.\\COM16";
        //        break;
		//}
        //
        //sio->setPortName(QString(portName));
        //
        //switch(Character){
        //    case 5:
		//		sio->setDataBits(QSerialPort::Data5);
        //        break;
        //    case 6:
        //        sio->setDataBits(QSerialPort::Data6);
        //        break;
        //    case 7:
        //        sio->setDataBits(QSerialPort::Data7);
        //        break;
        //    case 8:
        //        sio->setDataBits(QSerialPort::Data8);
        //        break;
		//}
        //switch(Parity){
        //    case 0:
		//		sio->setParity(QSerialPort::NoParity);
        //        break;
        //    case 1:
        //        sio->setParity(QSerialPort::OddParity);
        //        break;
        //    case 2:
        //        sio->setParity(QSerialPort::EvenParity);
        //        break;
		//}
        //switch(Stopbit){
        //    case 1:
		//		sio->setStopBits(QSerialPort::OneStop);
        //        break;
        //    case 2:
        //        sio->setStopBits(QSerialPort::TwoStop);
        //        break;
        //    case 3:
        //        sio->setStopBits(QSerialPort::OneAndHalfStop);
        //        break;
		//}
        //sio->setBaudRate(BPS);
        //
		//sio->setFlowControl(QSerialPort::NoFlowControl);
        //
        //bool    Ret=false;
        //if(sio->open(QIODevice::ReadWrite)==true){
        //    if(GetSeqControl()!=NULL
        //    && GetSeqControl()->GetThread()!=NULL){
        //        GetSeqControl()->GetThread()->OpenComm(CommPort,sio);
        //    }
        //}
        if(GetSeqControl()!=NULL
        && GetSeqControl()->GetThread()!=NULL){
            sio=GetSeqControl()->GetThread()->OpenCommInThread(CommPort,Character,Parity,Stopbit,BPS);
        }

        RxTop=0;
	}
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   CommOperand::GetNumeric(bool SrcReconstruct)
{
    Initial();

    if(sio!=NULL){
        if(GetSeqControl()!=NULL
        && GetSeqControl()->GetThread()!=NULL){
 		   char	buff[1];
           if(GetSeqControl()->GetThread()->CommReadByte(CommPort,buff,1)>0){
		        return buff[0];
           }
        }
    }
    return(-1);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   CommOperand::GetStringCount(void)
{
    if(TermNumb==0){
        return(NoTermRxByte);
        }
    return(RxTop);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      CommOperand::GetString(bool ThreadMode)
{
    Initial();
    if(TermNumb==0){
		int	len;
        if(GetSeqControl()!=NULL
        && GetSeqControl()->GetThread()!=NULL){
            if((len=GetSeqControl()->GetThread()->CommBytesAvailable(CommPort))>0){
		        len=GetSeqControl()->GetThread()->CommReadByte(CommPort,RxBuff,sizeof(RxBuff));
                if(len>0){
	            	NoTermRxByte=len;
		            RxBuff[len]=0;
                    QByteArray  Array(RxBuff,len);
                    emit    SignalRx(Array);
                    return(Array);
                }
            }
        }
        NoTermRxByte=0;
        return(/**/"");
    }

    RxBuff[RxTop]=0;
    QByteArray  Array(RxBuff,RxTop);
    emit    SignalRx(Array);
    return(Array);
}
bool	CommOperand::IsOpened(void)
{
    Initial();
    return sio->isOpen();
}
QByteArray   CommOperand::GetBufferingString(void)
{
   return(QByteArray(RxBuff,strlen(RxBuff)));
}


void     CommOperand::SetData(int d)
{
    Initial();
    if(sio!=NULL){
		sio->write((char *)&d,sizeof(d));
	}
}

void     CommOperand::SetData(const QByteArray &d)
{
    Initial();
    if(sio!=NULL){
		SendStr(d);
	}
    emit    SignalTx(d);
}

void     CommOperand::SendStr(char Buff[] ,int Len)
{
	//for(int i=0;i<Len;i++){
	//	sio->write(&Buff[i],1);
	//	sio->flush();
	//}
    sio->write(Buff,Len);
    sio->flush();
    //sio->waitForBytesWritten(1000);
    QByteArray  Array(Buff,Len);
    emit    SignalTx(Array);
}
void     CommOperand::SendStr(const QByteArray &s)
{
    sio->write(s);

    emit    SignalTx(s);
    sio->waitForBytesWritten(1000);
}
void	CommOperand::SendStr(const QString &s)
{
    sio->write(s.toLocal8Bit());

    emit    SignalTx(s.toLocal8Bit());
    sio->waitForBytesWritten(1000);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::LetSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    Initial();
    if(sio!=NULL){
        QByteArray  A=src->GetString();
		int	len=A.size();
		SendStr(A.data(),len);
        ThreadSequence::MSleep(10);
        src->FlushSource();
        }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::LetBSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    Initial();
    if(sio!=NULL){
        BYTE    k=src->GetNumeric(true);
		sio->write((char *)&k,1);
        }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::AddSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::SubSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::AndSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::OrSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::XorSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::NotSeq(Sequence *parent,bool)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::FlushSeq(Sequence *parent,bool)
{
    if(sio!=NULL){
		sio->flush();
        }
    RxTop=0;
    RxBuff[0]=0;

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::AllocSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::IndSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::BitloadSeq(Sequence *parent,bool ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::FlagSeq(Sequence *parent,bool)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::CAndSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::COrSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::CXorSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    Initial();
    if(parent!=NULL){
        QByteArray  A=src->GetString();
        int         len=A.size();
        if(RxTop>=len && memcmp(RxBuff,A.data(),len)==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    src->FlushSource();

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false)
        return(false);
    if(src2->IsGetEnabled()==false)
        return(false);

    Initial();

    src1->FlushSource();
    src2->FlushSource();
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    Initial();
    if(parent!=NULL){
        QByteArray  A=src->GetString();
        int         len=A.size();
        if(RxTop>=len && memcmp(RxBuff,A.data(),len)==0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    src->FlushSource();
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    Initial();
    if(parent!=NULL){
        QByteArray  A=src->GetString();
        int         len=A.size();
        if(RxTop>=len && memcmp(RxBuff,A.data(),len)==0)
            parent->SetFlag(FlagConnectedMode,false);
        else
            parent->SetFlag(FlagConnectedMode,true);
    }
    src->FlushSource();
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::GreaterSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::LargeSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::LessSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::SmallSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::MultSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::DivSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::ModSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::StrMoveSeq(Sequence *parent,bool ,Operand * ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::LowerSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    Initial();
    if(sio!=NULL){
        QByteArray  A=src->GetString();
        int         len=A.size();
		char    Buff[1000];
		for(int i=0;i<len;i++){
			Buff[i]=tolower(A[i]);
		}
		//sio->write(Buff,len);
		SendStr(Buff ,len);
        src->FlushSource();
        }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::UpperSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Initial();
    if(sio!=NULL){
		char	Buff[1000];
        QByteArray  A=src->GetString();
        int         len=A.size();
		for(int i=0;i<len;i++){
			Buff[i]=toupper(A[i]);
		}
		SendStr(Buff ,len);
        src->FlushSource();
    }
    if(parent!=NULL){
        parent->Add1NowLine();;
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::StateSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::TWSetSeq(Sequence *parent,bool)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::FSetSeq(Sequence *parent,bool)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::FResetSeq(Sequence *parent,bool)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CommOperand::RxTimeoutSeq(Sequence *parent,bool ,Operand *src1 ,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }
    RxTimeoutMilisec=src1->GetNumeric(true);
    RxTimeoutAddress=src2->GetNumeric(true);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::StrLenSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Initial();
    if(sio!=NULL){
        QByteArray  A=src->GetString();
		SendStr(A);
        src->FlushSource();
    }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CommOperand::ReceiveLoop(void)
{
    bool    ret=false;

    //Initial();
    //if(TermNumb!=0){
    //    if(sio!=NULL){
	//		if(sio->bytesAvailable()>0){
	//			char	d;
	//			sio->read(&d,1);
    //            for(int i=0;i<IgnoreNumb;i++){
    //                int len=strlen(IgnoreChar[i]);
    //                if(len==1 && *(IgnoreChar[i])==d){
    //                    return(true);
	//				}
	//			}
    //
    //            for(int i=0;i<TermNumb;i++){
    //                int len=strlen(TermChar[i]);
    //                if(RxTop>=len && memcmp(&RxBuff[RxTop-len],TermChar[i],len)==0){
    //                    RxTop=0;
    //                    break;
	//				}
	//			}
    //            for(int i=0;i<TermNumb;i++){
    //                int len=strlen(TermChar[i]);
    //                if(RxTop>len && memcmp(&RxBuff[0],TermChar[i],len)==0){
    //                    memmove(&RxBuff[0],&RxBuff[len],RxTop-len);
    //                    RxTop-=len;
    //                    break;
	//				}
	//			}
    //
    //            RxBuff[RxTop]=(char)d;
    //            RxTop++;
    //            RxBuff[RxTop]=0;
    //
    //            for(int i=0;i<IgnoreNumb;i++){
    //                int len=strlen(IgnoreChar[i]);
    //                if(memcmp(&RxBuff[RxTop-len],IgnoreChar[i],len)==0){
    //                    RxBuff[RxTop-len]=0;
    //                    RxTop-=len;
    //                    break;
	//				}
	//			}
    //            ret=true;
	//		}
	//	}
	//}
    return(ret);
}

int      CommOperand::ReceiveWaitTillTimeout(void)
/*
    戻り値：０　ターミネーションで終了
            １  継続で終了
            ２  タイムアウトで終了
*/
{
    Initial();
    if(TermNumb!=0){
        if(sio!=NULL){
            if(IntoTime==0)
                IntoTime=ThreadSequence::GetNowMiliSec();
			if(sio->bytesAvailable()>0){
				char	d;
				sio->read(&d,1);
                IntoTime=::GetComputerMiliSec();
                for(int i=0;i<IgnoreNumb;i++){
                    int len=strlen(IgnoreChar[i]);
                    if(len==1 && *(IgnoreChar[i])==d){
                        goto    HNext;
					}
				}

                RxBuff[RxTop]=(char)d;
                RxTop++;
                RxBuff[RxTop]=0;

                for(int i=0;i<TermNumb;i++){
                    int len=strlen(TermChar[i]);
                    if(RxTop>=len && memcmp(&RxBuff[RxTop-len],TermChar[i],len)==0){
                        RxTop=0;
                        return(0);
					}
				}
                for(int i=0;i<TermNumb;i++){
                    int len=strlen(TermChar[i]);
                    if(RxTop>len && memcmp(&RxBuff[0],TermChar[i],len)==0){
                        memmove(&RxBuff[0],&RxBuff[len],RxTop-len);
                        RxTop-=len;
                        return(0);
					}
				}

                for(int i=0;i<IgnoreNumb;i++){
                    int len=strlen(IgnoreChar[i]);
                    if(memcmp(&RxBuff[RxTop-len],IgnoreChar[i],len)==0){
                        RxBuff[RxTop-len]=0;
                        RxTop-=len;
                        break;
					}
				}
			}
            HNext:;
            if(RxTimeoutMilisec!=0
            && ::GetComputerMiliSec()-IntoTime>RxTimeoutMilisec){
                return(2);
			}
            if(RxTimeoutMilisec==0){
                return(0);
			}

            for(int i=0;i<TermNumb;i++){
                int len=strlen(TermChar[i]);
                if(RxTop>=len && memcmp(&RxBuff[RxTop-len],TermChar[i],len)==0){
                    RxTop=0;
                    return(0);
				}
			}
            for(int i=0;i<TermNumb;i++){
                int len=strlen(TermChar[i]);
                if(RxTop>len && memcmp(&RxBuff[0],TermChar[i],len)==0){
                    memmove(&RxBuff[0],&RxBuff[len],RxTop-len);
                    RxTop-=len;
                    return(0);
				}
			}
		}
	}
    return(1);
}

bool      CommOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      CommOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      CommOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      CommOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      CommOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}

bool      CommOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Initial();

    QString  s=GetString();
    QString  formatStr=src->GetString();
    bool flag=GetSeqControl()->BPrintExecute(parent ,s, formatStr);
    if(parent!=NULL)
        parent->SetFlag(FlagConnectedMode,flag);

    if(sio!=NULL && flag==true){
		SendStr(s);
    }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
bool      CommOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Initial();

    QString  s=GetString();
    QString  formatStr=src->GetString();
    bool flag=GetSeqControl()->BScanExecute(parent,s,formatStr);
    if(parent!=NULL)
        parent->SetFlag(FlagConnectedMode,flag);
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CommOperand::InputFromString(Sequence *parent,QString &Src)
{
    Initial();
    if(sio!=NULL){
		char	Buff[200];
        int len=QString2Char(Src,Buff,sizeof(Buff));
		//sio->write(Buff,len);
		SendStr(Buff ,len);
	}
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CommOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *src)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    BitOperand::GetName(void)
{
    return(QString("B")+QString::number(ID));
}

QString    LocalBitOperand::GetName(void)
{
    return(QString("LB")+QString::number(ID));
}

Operand     *LocalBitOperand::MakeDup(LocalReg *DestLReg)
{
    int id=GetID();
    LocalBitOperand *b=(LocalBitOperand *)DestLReg->LocalBitOpe.GetItemFromID(id);
    b->Data=0;
    return(b);
}

BitBaseOperand::BitBaseOperand(SeqControl *baseParent):Operand(baseParent)
{
    Data=0;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    BitBaseOperand::Load(char buff[])
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   BitBaseOperand::GetNumeric(bool SrcReconstruct)
{
    return(Data&1);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   BitBaseOperand::GetStringCount(void)
{
    return(1);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      BitBaseOperand::GetString(bool ThreadMode)
{
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(Data&1);
    return(A);
}

void     BitBaseOperand::SetData(const QByteArray &d)
{
	int nD=d.toInt();
    Data=nD&1;
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::LetSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Data=(BYTE)(src->GetNumeric(true)&1);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::LetBSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Data=(BYTE)(src->GetNumeric(true)&1);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=(BYTE)((Data+src->GetNumeric(true))&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=(BYTE)((Data-(src->GetNumeric(true)&1))&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=(BYTE)((Data&src->GetNumeric(true))&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=(BYTE)((Data|src->GetNumeric(true))&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=(BYTE)((Data|src->GetNumeric(true))&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        if((Data=(BYTE)((~Data)&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
bool      BitBaseOperand::FlushSeq(Sequence *parent,bool)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::AllocSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::IndSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::BitloadSeq(Sequence *parent,bool
                                    ,Operand *src1 ,Operand *src2 ,Operand *src3)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }
    if(src3->IsGetEnabled()==false){
        return(false);
    }

    if(src1->GetNumeric(true)==0){
        Data=(BYTE)((src2->GetNumeric(true)>>src3->GetNumeric(true))&1);
    }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        if(Data!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data & (src->GetNumeric(true)&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data | (src->GetNumeric(true)&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data ^ (src->GetNumeric(true)&1))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data == (src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    int d1=(src1->GetNumeric(true)&1);
    if(parent!=NULL){
        if(Data<=d1 && d1<=(src2->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data != (src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(Data >= (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();;
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(Data > (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();;
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(Data <= (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();;
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(Data < (src->GetNumeric(true)&1))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();;
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::MultSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    Data=(BYTE)((GetNumeric(true) * (src->GetNumeric(true)&1))&1);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::DivSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    int r=src->GetNumeric(true);
    if(r!=0){
        Data=(BYTE)((GetNumeric(true) / r)&1);
        }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::ModSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    int r=src->GetNumeric(true);
    if(r!=0){
        Data=(BYTE)((GetNumeric(true) % r)&1);
        }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::StrMoveSeq(Sequence *parent,bool ,Operand * ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::LowerSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::UpperSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::StateSeq(Sequence *parent,bool ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::FSetSeq(Sequence *parent,bool )
{
    Data=1;

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::FResetSeq(Sequence *parent,bool )
{
    Data=0;

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      BitBaseOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      BitBaseOperand::StrLenSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      BitBaseOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      BitBaseOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      BitBaseOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      BitBaseOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      BitBaseOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      BitBaseOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      BitBaseOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

bool      BitBaseOperand::InputFromString(Sequence *parent,QString &Src)
{
    if(Src.compare("true")==0
    || Src=="1"){
        Data=1;
    }
    else{
        Data=0;
    }

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      BitBaseOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *src)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    WordOperand::GetName(void)
{
	return(QString("W")+QString::number(ID));
}

QString    LocalWordOperand::GetName(void)
{
    return(QString("LW")+QString::number(ID));
}

Operand     *LocalWordOperand::MakeDup(LocalReg *DestLReg)
{
    int id=GetID();
    LocalWordOperand *b=(LocalWordOperand *)DestLReg->LocalWordOpe.GetItemFromID(id);
    b->Data=0;
    return(b);
}


WordBaseOperand::WordBaseOperand(SeqControl *baseParent):Operand(baseParent)
{
    Data=0;
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    WordBaseOperand::Load(char buff[])
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   WordBaseOperand::GetNumeric(bool SrcReconstruct)
{
    return(Data);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int    WordBaseOperand::GetStringCount(void)
{
    QByteArray  A=QByteArray().setNum(Data);
    return(A.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      WordBaseOperand::GetString(bool ThreadMode)
{
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(Data);
    return(A);
}

void     WordBaseOperand::SetData(const QByteArray &d)
{
	Data=d.toInt();
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::LetSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Data=src->GetNumeric(true);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::LetBSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    Data=src->GetNumeric(true);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=Data+src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=Data-src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=Data&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=Data|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if((Data=Data^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        if((Data=~Data)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
bool      WordBaseOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::BitloadSeq(Sequence *parent,bool  ,Operand *src1 ,Operand *src2 ,Operand *src3)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }
    if(src3->IsGetEnabled()==false){
        return(false);
    }

    int s1=src1->GetNumeric(true);
    unsigned int    mask=1<<s1;
    Data=(Data&(~mask)) + (((src2->GetNumeric(true)>>src3->GetNumeric(true))&1)<<(s1));

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        if(Data!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data==src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    int d1=src1->GetNumeric(true);
    if(parent!=NULL){
        if(Data<=d1 && d1<=src2->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data!=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data>=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data>src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data<=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data<src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::MultSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    Data=GetNumeric(true) * src->GetNumeric(true);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::DivSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    if(r!=0){
        Data=GetNumeric(true) / r;
    }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::ModSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    if(r!=0){
        Data=GetNumeric(true) % r;
    }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::TWSetSeq(Sequence *parent,bool )
{
    Data=ThreadSequence::GetNowMiliSec();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      WordBaseOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      WordBaseOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      WordBaseOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        int len=src->GetStringCount();
        src->FlushSource();
        
        Data=len;

        parent->Add1NowLine();
    }
    return(true);
}

bool      WordBaseOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      WordBaseOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      WordBaseOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      WordBaseOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      WordBaseOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      WordBaseOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      WordBaseOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      WordBaseOperand::InputFromString(Sequence *parent,QString &Src)
{
	Data=Src.toInt();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      WordBaseOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *src)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    FloatOperand::GetName(void)
{
    return(QString("F")+QString::number(ID));
}

QString    LocalFloatOperand::GetName(void)
{
    return(QString("LF")+QString::number(ID));
}


Operand     *LocalFloatOperand::MakeDup(LocalReg *DestLReg)
{
    int id=GetID();
    LocalFloatOperand *b=(LocalFloatOperand *)DestLReg->LocalFloatOpe.GetItemFromID(id);
    b->Data=0;
    //b->Num =0;
    return(b);
}


FloatBaseOperand::FloatBaseOperand(SeqControl *baseParent):Operand(baseParent)
{
    Data=0.0;
    Num=0xFF;
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    FloatBaseOperand::Load(char buff[])
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   FloatBaseOperand::GetNumeric(bool SrcReconstruct)
{
    return((int)Data);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int    FloatBaseOperand::GetStringCount(void)
{
    QByteArray  A=GetString(false);
    return(A.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      FloatBaseOperand::GetString(bool ThreadMode)
{
    if(Num==0){
        static  char    rbuff[50];
        sprintf(rbuff,"%.0lf",Data);
        return(rbuff);
        }
    else
    if(Num!=0xFF){
        char    buff[50];
        char    mbuff[50];
        static  char    rbuff[50];
        sprintf(mbuff,"%d",(int)Num);
        strcpy(buff,"%.");
        strcat(buff,mbuff);
        strcat(buff,"lf");
        sprintf(rbuff,buff,Data);
        return(rbuff);
        }
    else{
        static  char    rbuff[50];
        sprintf(rbuff,"%lf",Data);
        return(rbuff);
        }
}

double    FloatBaseOperand::GetFloat(bool SrcReconstruct)
{
    if(Num==0xFF)
        return(Data);
    else{
        char    buff[50];
        char    rbuff[50];
        sprintf(rbuff,"%0d",(int)Num);
		strcpy(buff,"%.");
		strcat(buff,rbuff);
		strcat(buff,"lf");
        sprintf(rbuff,buff,Data);
        double  rData;
        sscanf(rbuff,"%lf",&rData);
        return(rData);
        }
}


void     FloatBaseOperand::SetData(const QByteArray &d)
{
    sscanf((char *)d.data(),"%lf",&Data);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::LetSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    Data=src->GetFloat(true);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::LetBSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    Data=src->GetFloat(true);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data=Data+src->GetFloat(true))!=0.0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data=Data-src->GetFloat(true))!=0.0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data=((int)Data)&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data=((int)Data)|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data=((int)Data)^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        if((Data=-Data)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
bool      FloatBaseOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::BitloadSeq(Sequence *parent,bool  ,Operand *src1 ,Operand *src2 ,Operand *src3)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        if(Data!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((((int)Data)&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((((int)Data)|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((((int)Data)^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data==src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        double  d1=src1->GetFloat(true);
        if(Data<=d1 && d1<=src2->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data!=src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data>=src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data>src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        if(Data<=src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data<src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::MultSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    Data=GetFloat(true) * src->GetFloat(true);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::DivSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    double	r=src->GetFloat(true);
    if(r!=0){
        Data=GetFloat(true) / r;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::ModSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int	r=src->GetFloat(true);
    if(r!=0){
        Data=((int)GetFloat(true)) % r;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::TWSetSeq(Sequence *parent,bool )
{
    Data=ThreadSequence::GetNowMiliSec();
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FloatBaseOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      FloatBaseOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      FloatBaseOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        int len=src->GetStringCount();
        src->FlushSource();
        Data=len;

        parent->Add1NowLine();;
        }
    return(true);
}

bool      FloatBaseOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      FloatBaseOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      FloatBaseOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      FloatBaseOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      FloatBaseOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      FloatBaseOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      FloatBaseOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      FloatBaseOperand::InputFromString(Sequence *parent,QString &Src)
{
    sscanf((char *)Src.data(),"%lf",&Data);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      FloatBaseOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);

    Num=(BYTE)r;
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
StringBaseOperand::StringBaseOperand(SeqControl *baseParent):Operand(baseParent)
{
    Data=/**/"";
}

StringBaseOperand::~StringBaseOperand(void)
{
    Data=/**/"";
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    StringBaseOperand::Load(char buff[])
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   StringBaseOperand::GetNumeric(bool SrcReconstruct)
{
    int n;
	bool ok;
	n=Data.toInt(&ok);
	if(ok==true){
        return(n);
    }
    return(-1);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    data
//    len
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/

void     StringBaseOperand::SetData(int d)
{
	QByteArray  A=QByteArray().setNum(d);
    Data=A;
}

void     StringBaseOperand::SetData(const QByteArray &d)
{
    Data=d;
}
void      StringBaseOperand::SetData(const QString &d)
{
    Operand::SetData(d);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    StringOperand::GetName(void)
{
    return(QString("C")+QString::number(ID));
}

QString    LocalStringOperand::GetName(void)
{
    return(QString("LC")+QString::number(ID));
}

Operand     *LocalStringOperand::MakeDup(LocalReg *DestLReg)
{
    int id=GetID();
    LocalStringOperand *b=(LocalStringOperand *)DestLReg->LocalStringOpe.GetItemFromID(id);
    b->Data=/**/"";
    return(b);
}



/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   StringBaseOperand::GetStringCount(void)
{
	return(Data.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      StringBaseOperand::GetString(bool ThreadMode)
{
    return(Data);
}

double    StringBaseOperand::GetFloat(bool SrcReconstruct)
{
    double  floatdata=0;
	floatdata=Data.toDouble();
    return(floatdata);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::LetSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  S =src->GetString();
    int     CCount=S.size();
    CommOperand *c=dynamic_cast<CommOperand*>(src);
    if(c!=NULL){
        if(c->TermNumb==0){
            if(CCount==0){
                if(c->IntoTime==0){
                    c->IntoTime=ThreadSequence::GetNowMiliSec();
                    }
                if(c->RxTimeoutMilisec!=0
                && ThreadSequence::GetNowMiliSec()-c->IntoTime>c->RxTimeoutMilisec){
                    if(parent!=NULL){
                        for(int i=0;i<parent->GetSLineNumb();i++){
                            if(parent->GetSLine(i)!=NULL
                            && parent->GetSLine(i)->LNumber==c->RxTimeoutAddress){
                                src->FlushSource();
                                c->IntoTime=0;
                                parent->SetNowLine(i);
                                return(true);
                            }
                        }
                    }
                }
                src->FlushSource();
                return(true);
                }
            }
        else{
            int n=c->ReceiveWaitTillTimeout();
            if(n==1){
                src->FlushSource();
                return(true);
                }
            else
            if(n==2){
                if(parent!=NULL){
                    for(int i=0;i<parent->GetSLineNumb();i++){
                        if(parent->GetSLine(i)!=NULL
                        && parent->GetSLine(i)->LNumber==c->RxTimeoutAddress){
                            src->FlushSource();
                            c->IntoTime=0;
                            parent->SetNowLine(i);
                            return(true);
                        }
                    }
                }
            }
        }
        c->IntoTime=0;
        }

    src->FlushSource();
    SetData(S);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::LetBSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    SetData(src->GetString());
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::AddSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

	Data=Data+src->GetString();
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::SubSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::AndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::OrSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::XorSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::NotSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
bool      StringBaseOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::AllocSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::BitloadSeq(Sequence *parent,bool ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
	    if(Data.length()==0){
            parent->SetFlag(FlagConnectedMode,false);
        }
        else{
            parent->SetFlag(FlagConnectedMode,true);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::CAndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::COrSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::CXorSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        QByteArray  S=src->GetString();
	    if(Data.length()==S.size()
	    && Data.compare(S)==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        src->FlushSource();

        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        QByteArray  S1=src1->GetString();
        QByteArray  S2=src2->GetString();
        int s1Len=S1.size();
	    if(Data.length()<=s1Len && s1Len<=S2.size()
	    && Data.compare(S1)<=0 && src1->GetString().compare(S2)<=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        src1->FlushSource();
        src2->FlushSource();

        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        QByteArray  S=src->GetString();
	    if(Data.length()<=S.size()
	    && Data.compare(S)==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else if(Data.length()>S.size()
	    	 && Data.compare(S)==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        src->FlushSource();

        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        QByteArray  S=src->GetString();
	    if(Data.length()==S.size()
	    	&& Data.compare(S)==0){
            parent->SetFlag(FlagConnectedMode,false);
        }
        else{
            parent->SetFlag(FlagConnectedMode,true);
        }
        src->FlushSource();
    
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::GreaterSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::LargeSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::LessSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::SmallSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::MultSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::DivSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::ModSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::StrMoveSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    int s2=src2->GetNumeric(true);
    Data=src1->GetString().mid(s2);
    src1->FlushSource();

    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::LowerSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=src->GetString();
	s=s.toLower();
    SetData(s);
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::UpperSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=src->GetString();
	s=s.toUpper();
    SetData(s);
    src->FlushSource();
    
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      StringBaseOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      StringBaseOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      StringBaseOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=QByteArray().setNum(src->GetStringCount());
    SetData(s);
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      StringBaseOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      StringBaseOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      StringBaseOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      StringBaseOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      StringBaseOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      StringBaseOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QString  s=GetString();
    QString  formatStr=src->GetString();
    bool    flag=GetSeqControl()->BPrintExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
    }
    if(flag==true){
        SetData(s);
        }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
bool      StringBaseOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QString  s=GetString();
    QString  formatStr=src->GetString();
    bool    flag=GetSeqControl()->BScanExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
    }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      StringBaseOperand::InputFromString(Sequence *parent,QString &Src)
{
    SetData(Src);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      StringBaseOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    SpecialOperand::GetName(void)
{
    return(QString("S")+QString::number(ID));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    SpecialOperand::Load(char buff[])
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialOperand::GetNumeric(bool SrcReconstruct)
{
    Sequence    *s;
    struct tm   *tmm;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                return(Indirect->GetNumeric(true));
            }
            break;
        case 10:
            return(ThreadSequence::GetNowMiliSec());
        case 11:
            for(s=GetSeqControl()->Seq.GetFirst();s!=NULL;s=s->GetNext()){
                if(s->GetSType()==SequenceStock::_Main){
                    return(s->GetNowLine());
                }
            }
            return(0);
        case 18:
            return(time(NULL));
        case 20:
            return(GetSeqControl()->S20Time);
        case 21:
            tmm=localtime(&GetSeqControl()->S20Time);
            return(tmm->tm_year %100);
        case 22:
            tmm=localtime(&GetSeqControl()->S20Time);
            return(tmm->tm_mon+1);
        case 23:
            tmm=localtime(&GetSeqControl()->S20Time);
            return(tmm->tm_mday);
        case 24:
            tmm=localtime(&GetSeqControl()->S20Time);
            return(tmm->tm_hour);
        case 25:
            tmm=localtime(&GetSeqControl()->S20Time);
            return(tmm->tm_min);
        case 26:
            tmm=localtime(&GetSeqControl()->S20Time);
            return(tmm->tm_sec);
        case 27:
            tmm=localtime(&GetSeqControl()->S20Time);
            return(tmm->tm_wday);
        default:
            if(GetSeqControl()->GetDataSpecialOperand!=NULL){
                return(GetSeqControl()->GetDataSpecialOperand(GetSeqControl()->GetLocalParamPointer(),ID));
            }
        }
    return(0);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void   SpecialOperand::SetNumeric(int d)
{
    NumberOperand   m(GetSeqControl());
    m.SetData(d);
    bool    flag=true;
    LetSeq(NULL,flag,&m);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialOperand::GetStringCount(void)
{
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                return(Indirect->GetStringCount());
            }
            return(0);
        default:
            break;
        }
    QString  A=QString().setNum(GetNumeric(true));
    return(A.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      SpecialOperand::GetString(bool ThreadMode)
{
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                return(Indirect->GetString());
            }
            return(/**/"");
        default:
            break;
        }
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(GetNumeric(true));
    return(A);
}

void     SpecialOperand::SetData(int d)
{
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        case 20:    GetSeqControl()->S20Time=d;
            break;
        default:
            if(GetSeqControl()->SetDataSpecialOperand!=NULL){
                GetSeqControl()->SetDataSpecialOperand(GetSeqControl()->GetLocalParamPointer(),ID,d);
            }
            break;
        }
}

void     SpecialOperand::SetData(const QByteArray &d)
{
	int nD=d.toInt();
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        default:
            if(GetSeqControl()->SetDataSpecialOperand!=NULL){
                GetSeqControl()->SetDataSpecialOperand(GetSeqControl()->GetLocalParamPointer(),ID,nD);
            }
            break;
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r=0;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->LetSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetNumeric(true);
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r=0;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->LetBSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetNumeric(true);
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r=0;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->AddSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetNumeric(true)+(src->GetNumeric(true));
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->SubSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetNumeric(true)-(src->GetNumeric(true));
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->AndSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetNumeric(true)&(src->GetNumeric(true));
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->OrSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetNumeric(true)|(src->GetNumeric(true));
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->XorSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetNumeric(true)^(src->GetNumeric(true));
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();;
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->NotSeq(parent,FlagConnectedMode);
            }
            break;
        default:
            r=~GetNumeric(true);
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::IndSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(0<=ID && ID<=9){
        Indirect=src;
        }
    //int r=GetNumeric(true);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=GetNumeric(true);
    if(parent!=NULL){
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)==src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        int d1=src1->GetNumeric(true);
        if(GetNumeric(true)<=d1 && d1<=src2->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)!=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)>=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)>src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)<=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)<src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->MultSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetNumeric(true)*(src->GetNumeric(true));
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r,q;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->DivSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            int d=src->GetNumeric(true);
            if(d!=0){
                r=GetNumeric(true);
                q=r/d;
                SetData(q);
                }
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r,q;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(Indirect!=NULL){
                Indirect->ModSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            int d=src->GetNumeric(true);
            if(d!=0){
                r=GetNumeric(true);
                q=r%d;
                SetData(q);
                }
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int len=src->GetStringCount();
    src->FlushSource();
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        default:
            SetData(len);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      SpecialOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      SpecialOperand::InputFromString(Sequence *parent,QString &Src)
{
    int r;
    switch(ID){
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        default:
			r=Src.toInt();;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    NumberOperand::GetName(void)
{
    return(QString().setNum(GetNumeric(true)));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    NumberOperand::Load(char buff[])
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   NumberOperand::GetNumeric(bool SrcReconstruct)
{
    return(Data);
}

void     NumberOperand::SetData(const QByteArray &d)
{
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   NumberOperand::GetStringCount(void)
{
    QString  A=QString().setNum(GetNumeric(true));
    return(A.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      NumberOperand::GetString(bool ThreadMode)
{
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(GetNumeric(true));
    return(A);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::LetSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::LetBSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::AddSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::SubSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::AndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::OrSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::XorSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::NotSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
bool      NumberOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        if(GetNumeric(true)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
		return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)==src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        int d1=src1->GetNumeric(true);
        if(GetNumeric(true)<=d1 && d1<=src2->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)!=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)>=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)>src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)<=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true)<src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::MultSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::DivSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::ModSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      NumberOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      NumberOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      NumberOperand::StrLenSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      NumberOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      NumberOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      NumberOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      NumberOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      NumberOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      NumberOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      NumberOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

bool      NumberOperand::InputFromString(Sequence *parent,QString &)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      NumberOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
CharOperand::CharOperand(SeqControl *baseParent):Operand(baseParent)
{
    Data=/**/"";
    ID=GetSeqControl()->CharOpe.GetNumber();
}

CharOperand::~CharOperand(void)
{
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    CharOperand::GetName(void)
{
    return(Data);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    CharOperand::Load(char buff[])
{
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   CharOperand::GetNumeric(bool )
{
	return(Data.toInt());
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    data
//    len
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void      CharOperand::SetData(const QByteArray &data)
{
    Data=data;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::LetSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::LetBSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::AddSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::SubSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::AndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::OrSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::XorSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::NotSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CharOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::FlagSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::CAndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::COrSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::CXorSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetStringCount()==src->GetStringCount()
	    	&& GetString().compare(src->GetString())==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    int DataLen=GetStringCount();
    int S1Len=src1->GetStringCount();
    if(parent!=NULL){
        if(DataLen<=S1Len && S1Len<=src2->GetStringCount()
	    	&& GetString().compare(src1->GetString())<=0 && src1->GetString().compare(src2->GetString())<=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    src1->FlushSource();
    src2->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetStringCount()<=src->GetStringCount()
	    	&& GetString().compare(src->GetString())==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else
        if(GetStringCount()>src->GetStringCount()
	    	&& GetString().compare(src->GetString())==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    src->FlushSource();
    
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetStringCount()==src->GetStringCount()
	    	&& GetString().compare(src->GetString())==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::GreaterSeq(Sequence *parent,bool ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::LargeSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::LessSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::SmallSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::MultSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::DivSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::ModSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      CharOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CharOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CharOperand::StrLenSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CharOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      CharOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      CharOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      CharOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      CharOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      CharOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      CharOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      CharOperand::InputFromString(Sequence *parent,QString &)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      CharOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}



GroupOperand::GroupOperand(SeqControl *baseParent):Operand(baseParent)
{
    for(int i=0;i<sizeof(EachBitName)/sizeof(EachBitName[0]);i++){
        EachBitPoint[i]=NULL;
        EachBitName [i]=/**/"";
        }
    ID=GetSeqControl()->GroupOpe.GetNumber();
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    GroupOperand::GetName(void)
{
    return(Name);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    GroupOperand::Load(char buff[])
{
    char    nbuff[100];
    char    *fp=buff;
    fp+=8;

    fp=GetTopString(fp);
    fp=GetWordCut(fp,nbuff);
    if(fp==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=':'){
        return(false);
    }
    fp++;
    fp=GetTopString(fp);
	QString	Q=QString(nbuff);
    SetName(Q);

    for(int i=0;i<sizeof(EachBitName)/sizeof(EachBitName[0]);i++){
        if(*fp=='0'){
            fp++;
            fp=GetTopString(fp);
            }
        else
        if(*fp!=','){
            fp=GetWordCut(fp,nbuff);
            if(fp==NULL){
                break;
            }
            EachBitName[i]=nbuff;
            fp=GetTopString(fp);
            }
        if(*fp==','){
            fp++;
            fp=GetTopString(fp);
            }
        else{
            break;
        }
    }
    if(*fp=='\n' || *fp==0){
        return(true);
    }

    return(false);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   GroupOperand::GetNumeric(bool )
{
    int D=0;
    for(int i=0;i<sizeof(EachBitPoint)/sizeof(EachBitPoint[0]);i++){
        if(EachBitPoint[i]!=NULL){
            D += (EachBitPoint[i]->GetNumeric()&1)<<i;
        }
    }

    return(D);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int    GroupOperand::GetStringCount(void)
{
    int D=GetNumeric();
    //static  QString  A;
	QString  A;
    A=QString().setNum(D);
    return(A.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      GroupOperand::GetString(bool ThreadMode)
{
    int D=GetNumeric();
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(D);
    return(A);
}

void      GroupOperand::SetData(int d)
{
    for(int i=0;i<sizeof(EachBitPoint)/sizeof(EachBitPoint[0]);i++){
        if(EachBitPoint[i]!=NULL){
            EachBitPoint[i]->SetData((d>>i)&1);
        }
    }
}
void      GroupOperand::SetData(const QByteArray &d)
{
	int nD=d.toInt();
    for(int i=0;i<sizeof(EachBitPoint)/sizeof(EachBitPoint[0]);i++){
        if(EachBitPoint[i]!=NULL){
            EachBitPoint[i]->SetData((nD>>i)&1);
        }
    }
}

void    GroupOperand::InitialConstruct(void)
{
    for(int i=0;i<sizeof(EachBitPoint)/sizeof(EachBitPoint[0]);i++){
        EachBitPoint[i]=GetSeqControl()->SearchReg(NULL,EachBitName[i]);
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::LetSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    SetData(r);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::LetBSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    SetData(r);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    int d=c+src->GetNumeric(true);
    SetData(d);
    if(parent!=NULL){
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    int d=c-src->GetNumeric(true);
    SetData(d);
    if(parent!=NULL){
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }

        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    int d=c&src->GetNumeric(true);
    SetData(d);
    if(parent!=NULL){
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    int d=c|src->GetNumeric(true);
    SetData(d);
    if(parent!=NULL){
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    int d=c^src->GetNumeric(true);
    SetData(d);
    if(parent!=NULL){
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    int c=GetNumeric(true);
    int d=~c;
    SetData(d);

    if(parent!=NULL){
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
bool      GroupOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::BitloadSeq(Sequence *parent,bool  ,Operand *src1 ,Operand *src2 ,Operand *src3)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }
    if(src3->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);

    int s1=src1->GetNumeric(true);
    unsigned int    mask=1<<s1;
    int d=(c&(~mask)) + (((src2->GetNumeric(true)>>src3->GetNumeric(true))&1)<<(s1));
    SetData(d);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    int c=GetNumeric(true);

    if(parent!=NULL){
        if(c!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if((c&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if((c|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if((c^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if(c==src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    int c1=src1->GetNumeric(true);
    if(parent!=NULL){
        if(GetNumeric(true)<=c1 && c1<=src2->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if(c!=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if(c>=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if(c>src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if(c<=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    if(parent!=NULL){
        if(c<src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::MultSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int c=GetNumeric(true);
    int d=c * src->GetNumeric(true);
    SetData(d);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::DivSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true) / r;
        SetData(d);
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::ModSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true) % r;
        SetData(d);
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::TWSetSeq(Sequence *parent,bool )
{
    int d=ThreadSequence::GetNowMiliSec();
    SetData(d);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      GroupOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      GroupOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      GroupOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        int len=src->GetStringCount();
        src->FlushSource();
        SetData(len);
        parent->Add1NowLine();;
        }
    return(true);
}

bool      GroupOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      GroupOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      GroupOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      GroupOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      GroupOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      GroupOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      GroupOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      GroupOperand::InputFromString(Sequence *parent,QString &Src)
{
	int d=Src.toInt();
    SetData(d);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      GroupOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


int     GroupOperand::GetBitCount(void)
{
    int N=0;
    for(int i=0;i<GroupBitCount;i++){
        if(EachBitPoint[i]!=NULL)
            N++;
        }
    return(N);
}


//==============================================================

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    SpecialBitOperand::GetName(void)
{
    return(QString("P")+QString::number(ID));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    SpecialBitOperand::Load(char buff[])
{
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void   SpecialBitOperand::SetNumeric(int d)
{
    d&=1;

    NumberOperand   m(GetSeqControl());
    m.SetID(d);
    bool    flag=true;
    LetSeq(NULL,flag,&m);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialBitOperand::GetNumeric(bool )
{
	if(GetSeqControl()->GetDataSpecialBitOperand!=NULL){
		if(GetSeqControl()->GetDataSpecialBitOperand(GetSeqControl()->GetLocalParamPointer(),ID)==true){
			return(1);
        }
		else{
			return(0);
        }
	}
    return(0);
}

void     SpecialBitOperand::SetData(int d)
{
	if(GetSeqControl()->SetDataSpecialBitOperand!=NULL){
		if(d!=0){
			GetSeqControl()->SetDataSpecialBitOperand(GetSeqControl()->GetLocalParamPointer(),ID,true);
        }
		else{
			GetSeqControl()->SetDataSpecialBitOperand(GetSeqControl()->GetLocalParamPointer(),ID,false);
        }
	}
}
void     SpecialBitOperand::SetData(const QByteArray &d)
{
	int nD=d.toInt();
	if(GetSeqControl()->SetDataSpecialBitOperand!=NULL){
		if(nD!=0){
			GetSeqControl()->SetDataSpecialBitOperand(GetSeqControl()->GetLocalParamPointer(),ID,true);
        }
		else{
			GetSeqControl()->SetDataSpecialBitOperand(GetSeqControl()->GetLocalParamPointer(),ID,false);
        }
	}
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialBitOperand::GetStringCount(void)
{
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                r=Indirect->GetStringCount();
                Indirect->FlushSource();
                return(r);
                }
            return(0);
        default:
            break;
        }
    QString  A=QString().setNum(GetNumeric(true));
    return(A.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      SpecialBitOperand::GetString(bool ThreadMode)
{
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                return(Indirect->GetString());
            }
            return(NULL);
        default:
            break;
        }
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(GetNumeric(true));
    return(A);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->LetSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetNumeric(true)&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->LetBSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetNumeric(true)&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->AddSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)+(src->GetNumeric(true)))&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->SubSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)-(src->GetNumeric(true)))&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->AndSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)&(src->GetNumeric(true)))&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->OrSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)|(src->GetNumeric(true)))&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->XorSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)^(src->GetNumeric(true)))&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->NotSeq(parent,FlagConnectedMode);
            }
            break;
        default:
            r=(~GetNumeric(true))&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialBitOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::IndSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(0<=ID && ID<=9){
        Indirect=src;
        }
    //int r=GetNumeric(true);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=GetNumeric()&1;
    if(parent!=NULL){
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(((GetNumeric(true)&src->GetNumeric(true))&1)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(((GetNumeric(true)|src->GetNumeric(true))&1)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(((GetNumeric(true)^src->GetNumeric(true))&1)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&1)==(src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    int d1=(src1->GetNumeric(true)&1);
    if(parent!=NULL){
        if((GetNumeric(true)&1)<=d1 && d1<=(src2->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&1)!=(src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&1)>=(src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&1)>(src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&1)<=(src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((GetNumeric(true)&1)<(src->GetNumeric(true)&1)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->MultSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)*(src->GetNumeric(true)))&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r,d;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->DivSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            d=src->GetNumeric(true)&1;
            if(d!=0){
                r=(GetNumeric(true)&1)/d;
                SetData(r);
                }
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r,d;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->ModSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            d=src->GetNumeric(true)&1;
            if(d!=0){
                r=(GetNumeric(true)&1)%d;
                SetData(r);
                }
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::FSetSeq(Sequence *parent,bool )
{
    switch(ID){
        case 9:
            break;
        default:
            SetData(1);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialBitOperand::FResetSeq(Sequence *parent,bool )
{
    switch(ID){
        case 9:
            break;
        default:
            SetData(0);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialBitOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialBitOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int len=src->GetStringCount();
    src->FlushSource();
    int r;
    switch(ID){
        case 9:
            break;
        default:
            r=len&1;
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialBitOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialBitOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      SpecialBitOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialBitOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialBitOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialBitOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      SpecialBitOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      SpecialBitOperand::InputFromString(Sequence *parent,QString &Src)
{
    int r;
    switch(ID){
        case 9:
            break;
        default:
            if(Src.compare("true")==0
            || Src=="1"){
                r=1;
            }
            else{
                r=0;
            }
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialBitOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


//==============================================================

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    SpecialStringOperand::GetName(void)
{
    return(QString("Q")+QString::number(ID));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    SpecialStringOperand::Load(char buff[])
{
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void   SpecialStringOperand::SetNumeric(int d)
{
    d&=1;

    NumberOperand   m(GetSeqControl());
    m.SetID(d);
    bool    flag=true;
    LetSeq(NULL,flag,&m);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialStringOperand::GetNumeric(bool )
{
    if(GetSeqControl()->GetDataSpecialStringOperand!=NULL){
		return(GetSeqControl()->GetDataSpecialStringOperand(GetSeqControl()->GetLocalParamPointer(),ID).toInt());
    }

    return(0);
}

void     SpecialStringOperand::SetData(int d)
{
    if(GetSeqControl()->SetDataSpecialStringOperand!=NULL){
///        GetSeqControl()->SetDataSpecialStringOperand(ID,d);	//D-20051026
        GetSeqControl()->SetDataSpecialStringOperand(GetSeqControl()->GetLocalParamPointer(),ID,QString().setNum(d));
    }
}
void     SpecialStringOperand::SetData(const QByteArray &d)
{
    if(GetSeqControl()->SetDataSpecialStringOperand!=NULL){
        GetSeqControl()->SetDataSpecialStringOperand(GetSeqControl()->GetLocalParamPointer(),ID,d);
    }
}
void      SpecialStringOperand::SetData(const QString &d)
{
    Operand::SetData(d);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialStringOperand::GetStringCount(void)
{
    if(GetSeqControl()->GetDataSpecialOperand!=NULL){
        QString  A=GetSeqControl()->GetDataSpecialStringOperand(GetSeqControl()->GetLocalParamPointer(),ID);
        return(A.length());
        }
    return(0);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      SpecialStringOperand::GetString(bool ThreadMode)
{
///    static  char    CBuff[1000];
    QString    CBuff;

    if(GetSeqControl()->GetDataSpecialStringOperand!=NULL){
        CBuff=GetSeqControl()->GetDataSpecialStringOperand(GetSeqControl()->GetLocalParamPointer(),ID);
        return(CBuff.toLocal8Bit());
	}
    return(/**/"");
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->LetSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetString(true);
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->LetBSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetString(true);
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->AddSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetString(true)+src->GetString(true);
            SetData(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::SubSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::AndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::OrSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::XorSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::NotSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialStringOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::FlagSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::CAndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::COrSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::CXorSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetStringCount()==src->GetStringCount()
	    	&& GetString().compare(src->GetString())==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::ZoneSeq(Sequence *parent,bool  ,Operand *,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    QByteArray  r=GetString(true);
    if(parent!=NULL){
        if(r.length()<=src->GetStringCount()
	    	&& r.compare(src->GetString())==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else
        if(r.length()>src->GetStringCount()
	    	&& r.compare(src->GetString())==0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetString(true)!=src->GetString(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetString(true)>=src->GetString(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetString(true)>src->GetString(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetString(true)<=src->GetString(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetString(true)<src->GetString(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::MultSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::DivSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::ModSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * src1 ,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    int s2=src2->GetNumeric(true);
    int DataLen=src1->GetStringCount()-s2;
    QByteArray  r;
    if(DataLen<0){
        r=/**/"";
        }
    else{
        r=src1->GetString()+QByteArray::number(s2);
        }
    SetData(r);
    src1->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::LowerSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=src->GetString();
	s=s.toLower();
    SetData(s);
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::UpperSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=src->GetString();
	s=s.toUpper();
    SetData(s);
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::StateSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialStringOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialStringOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialStringOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=QByteArray::number(src->GetStringCount());
    SetData(s);
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialStringOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialStringOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      SpecialStringOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialStringOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialStringOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialStringOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QString  s=GetString();
    QString  formatStr=src->GetString();
    bool    flag=GetSeqControl()->BPrintExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
    }
    if(flag==true){
        SetData(s);
        }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
bool      SpecialStringOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QString  s=GetString();
    QString  formatStr=src->GetString();
    bool    flag=GetSeqControl()->BScanExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
    }
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialStringOperand::InputFromString(Sequence *parent,QString &Src)
{
    //int DataLen=Src.length();
    QString  r=Src;
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialStringOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

//==============================================================================

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    SpecialFloatOperand::GetName(void)
{
    return(QString("R")+QString::number(ID));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    SpecialFloatOperand::Load(char buff[])
{
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void   SpecialFloatOperand::SetNumeric(int d)
{
    FloatOperand   m(GetSeqControl());
    m.SetID(d);
    bool    flag=true;
    LetSeq(NULL,flag,&m);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialFloatOperand::GetNumeric(bool )
{
	if(GetSeqControl()->GetDataSpecialFloatOperand!=NULL){
		double	d=GetSeqControl()->GetDataSpecialFloatOperand(GetSeqControl()->GetLocalParamPointer(),ID);
		return((int)d);
	}
    return(0);
}
double    SpecialFloatOperand::GetFloat(bool)
{
	if(GetSeqControl()->GetDataSpecialFloatOperand!=NULL){
		double	d=GetSeqControl()->GetDataSpecialFloatOperand(GetSeqControl()->GetLocalParamPointer(),ID);
		return(d);
	}
    return(0.0);
}

void     SpecialFloatOperand::SetData(int d)
{
	if(GetSeqControl()->SetDataSpecialFloatOperand!=NULL){
		GetSeqControl()->SetDataSpecialFloatOperand(GetSeqControl()->GetLocalParamPointer(),ID,d);
	}
}
void     SpecialFloatOperand::SetData(const QByteArray &d)
{
	double nD=d.toDouble();
	if(GetSeqControl()->SetDataSpecialFloatOperand!=NULL){
		GetSeqControl()->SetDataSpecialFloatOperand(GetSeqControl()->GetLocalParamPointer(),ID,nD);
	}
}
void      SpecialFloatOperand::SetFloat(double d)
{
	if(GetSeqControl()->SetDataSpecialFloatOperand!=NULL){
		GetSeqControl()->SetDataSpecialFloatOperand(GetSeqControl()->GetLocalParamPointer(),ID,d);
	}
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   SpecialFloatOperand::GetStringCount(void)
{
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                r=Indirect->GetStringCount();
                Indirect->FlushSource();
                return(r);
                }
            return(0);
        default:
            break;
        }
    QString  A=QString().setNum(GetFloat(true));
    return(A.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      SpecialFloatOperand::GetString(bool ThreadMode)
{
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                return(Indirect->GetString());
            }
            return(NULL);
        default:
            break;
        }
    //static  QString  A;
	QByteArray  A;
    A=QByteArray().setNum(GetFloat(true));
    return(A);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::LetSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    double r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->LetSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetFloat(true);
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::LetBSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    double r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->LetBSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=src->GetFloat(true);
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    double r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->AddSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetFloat(true)+(src->GetFloat(true)));
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    double r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->SubSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetFloat(true)-(src->GetFloat(true)));
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->AndSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)&(src->GetNumeric(true)));
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->OrSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)|(src->GetNumeric(true)));
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->XorSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=(GetNumeric(true)^(src->GetNumeric(true)));
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->NotSeq(parent,FlagConnectedMode);
            }
            break;
        default:
            r=(~GetNumeric(true));
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialFloatOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::IndSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(0<=ID && ID<=9){
        Indirect=src;
        }
    //double r=GetFloat(true);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=GetNumeric()&1;
    if(parent!=NULL){
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(((GetNumeric(true)&src->GetNumeric(true)))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(((GetNumeric(true)|src->GetNumeric(true))&1)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(((GetNumeric(true)^src->GetNumeric(true))&1)!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetFloat(true)==src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    double d1=src1->GetFloat(true);
    if(parent!=NULL){
        if(GetFloat(true)<=d1 && d1<=src2->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetFloat(true)!=src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetFloat(true)>=src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetFloat(true)>src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetFloat(true)<=src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetFloat(true)<src->GetFloat(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::MultSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    double	r;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->MultSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            r=GetFloat(true)*src->GetFloat(true);
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::DivSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    double r,d;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->DivSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            d=src->GetFloat(true);
            if(d!=0){
                r=GetFloat(true)/d;
                SetFloat(r);
                }
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::ModSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int	r,d;
    switch(ID){
        case 9:
            if(Indirect!=NULL){
                Indirect->ModSeq(parent,FlagConnectedMode ,src);
            }
            break;
        default:
            d=src->GetNumeric(true);
            if(d!=0){
                r=GetNumeric(true)%d;
                SetFloat(r);
                }
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::FSetSeq(Sequence *parent,bool )
{
    switch(ID){
        case 9:
            break;
        default:
            SetData(1);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      SpecialFloatOperand::FResetSeq(Sequence *parent,bool )
{
    switch(ID){
        case 9:
            break;
        default:
            SetData(0);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialFloatOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialFloatOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int len=src->GetStringCount();
    src->FlushSource();
    switch(ID){
        case 9:
            break;
        default:
            SetData(len);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialFloatOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialFloatOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
	return(true);
}
bool      SpecialFloatOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      SpecialFloatOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialFloatOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      SpecialFloatOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      SpecialFloatOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      SpecialFloatOperand::InputFromString(Sequence *parent,QString &Src)
{
    double r;
    switch(ID){
        case 9:
            break;
        default:
			sscanf((char *)Src.data(),"%lf",&r);
            SetFloat(r);
            break;
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      SpecialFloatOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


//==============================================================

//==============================================================

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
LanvarOperand::LanvarOperand(void)
{
    ID=GetSeqControl()->LanvarOpe.GetNumber();
    ReqPreparedMode=false;
}

QString    LanvarOperand::GetName(void)
{
    return(Name);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool    LanvarOperand::Load(char buff[])
{
    char    nbuff[100];

    char    *fp=buff;
    fp+=7;
    fp=GetTopString(fp);
    fp=GetWordCut(fp,nbuff);
    if(fp==NULL)
        return(false);
    fp=GetTopString(fp);
    if(*fp!=':')
        return(false);
    fp++;

    IP.RemoveAll();
    for(;;){
        fp=GetTopString(fp);

        char    n1[20];
        char    n2[20];
        char    n3[20];
        char    n4[20];

        if((fp=GetWordCut(fp,n1))==NULL)
            break;

        fp=GetTopString(fp);
        if(*fp==','){
            IPList  *p=new IPList(n1);
            IP.AppendList(p);
            fp++;
            continue;
            }
        else
        if(*fp!='.')
            return(false);
        fp++;

        if((fp=GetWordCut(fp,n2))==NULL)
            return(false);
        fp=GetTopString(fp);
        if(*fp!='.')
            return(false);
        fp++;

        if((fp=GetWordCut(fp,n3))==NULL)
            return(false);
        fp=GetTopString(fp);
        if(*fp!='.')
            return(false);
        fp++;

        if((fp=GetWordCut(fp,n4))==NULL)
            return(false);
        fp=GetTopString(fp);

        int d1=StrToIntDef(n1,-1);
        int d2=StrToIntDef(n2,-1);
        int d3=StrToIntDef(n3,-1);
        int d4=StrToIntDef(n4,-1);
        if(d1<0 || d1>255)
            return(false);
        if(d2<0 || d2>255)
            return(false);
        if(d3<0 || d3>255)
            return(false);
        if(d4<0 || d4>255)
            return(false);

        IPList  *p=new IPList();
        p->IPAddress=AnsiString(d1) + AnsiString(".")
                    +AnsiString(d2) + AnsiString(".")
                    +AnsiString(d3) + AnsiString(".")
                    +AnsiString(d4);
        IP.AppendList(p);
        fp=GetTopString(fp);
        if(*fp!=',')
            break;
        fp++;
        }

    SetName(nbuff);

    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
int   LanvarOperand::GetNumeric(bool )
{
    Initial();
    return(Data.ToIntDef(0));
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
int   LanvarOperand::GetStringCount(void)
{
    Initial();
    return(Data.Length());
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
char    *  LanvarOperand::GetString(bool ThreadMode)
{
    if(ThreadMode==true)
        Initial();
    else{
        GetSeqControl()->GetLanverReqMode=true;
        while(GetSeqControl()->GetLanverReqMode==true){
            if(GetSeqControl()->DoHalt==true)
                break;
            ThreadSequence::MSleep(10);
            }
        }
    return(Data.c_str());
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/

/*↓D-20051026------------------------------------------------------------------
static  int LanDebug;

void     LanvarOperand::Initial(void)
{
    for(IPList *p=IP.GetFirst();p!=NULL;p=p->GetNext()){
        if(p->Sock==NULL){
            p->Initial();
            p->Connect();
            if(p->IsConnected()==true){
                if(p->Sock==NULL)
                    return;
                p->SendConnection(GetName());
                p->ReqData(GetName());
                }
            }
        else
        if(p->IsConnected()==false){
            p->Connect();
            if(p->IsConnected()==true){
                if(p->Sock==NULL)
                    return;
                p->SendConnection(GetName());
                p->ReqData(GetName());
                }
            }
        else
        if(p->IsConnected()==true){
            if(p->Sock==NULL)
                return;
            p->ReqData(GetName());
            }
        }
    KNext:;
    for(LanVarSocketList *k=GetSeqControl()->LanVarSocket.GetFirst();k!=NULL;k=k->GetNext()){
        if(k->CliSock!=NULL
        && k->CliSock->State==wsClosed){
            if(k->OnConnectingMode==true)
                LanDebug=1;
            GetSeqControl()->LanVarSocket.RemoveList(k);
            for(LanvarOperand *c=GetSeqControl()->LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                IPNext:;
                for(IPList *p=c->IP.GetFirst();p!=NULL;p=p->GetNext()){
                    if(p->Sock==k){
                        c->IP.RemoveList(p);
                        goto    IPNext;
                        }
                    }
                }
            delete  k;
            goto    KNext;
            }
        }
}

void     LanvarOperand::ReqPrepare(void)
{
    for(IPList *p=IP.GetFirst();p!=NULL;p=p->GetNext()){
        if(p->Sock==NULL){
            p->Initial();
            p->Connect();
            if(p->IsConnected()==true){
                if(p->Sock==NULL)
                    return;
                p->SendConnection(GetName());
                p->ReqPrepare(GetName());
                }
            }
        else
        if(p->IsConnected()==false){
            p->Connect();
            if(p->IsConnected()==true){
                if(p->Sock==NULL)
                    return;
                p->SendConnection(GetName());
                p->ReqPrepare(GetName());
                }
            }
        else
        if(p->IsConnected()==true){
            if(p->Sock==NULL)
                return;
            p->ReqPrepare(GetName());
            }
        }
}

bool     LanvarOperand::ReqDone(void)
{
    for(IPList *p=IP.GetFirst();p!=NULL;p=p->GetNext()){
        if(p->ReqDone()==false)
            return(false);
        }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/

/*↓D-20051026------------------------------------------------------------------
void     LanvarOperand::SetData(int d)
{
    //Initial();

    Data=d;

}

void     LanvarOperand::SetData(AnsiString d)
{
    //Initial();
    Data=d;

}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::LetSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    AnsiString  A=src->GetString();
    src->FlushSource();
    SetData(A);

    if(parent!=NULL)
        parent->Add1NowLine();
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::LetBSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    AnsiString  A=src->GetString();
    src->FlushSource();
    SetData(A);

    if(parent!=NULL)
        parent->Add1NowLine();
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) + src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) - src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) & src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) | src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) ^ src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=~GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::FlushSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=Data.ToIntDef(0);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::BitloadSeq(Sequence *parent,bool ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    int r=Data.ToIntDef(0);

    if(parent!=NULL){
        if(r==0)
            parent->SetFlag(FlagConnectedMode,false);
        else
            parent->SetFlag(FlagConnectedMode,true);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) & src->GetNumeric(true);
    if(parent!=NULL){
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) | src->GetNumeric(true);
    if(parent!=NULL){
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) ^ src->GetNumeric(true);
    if(parent!=NULL){
        if(r!=0)
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) == src->GetNumeric(true))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false)
        return(false);
    if(src2->IsGetEnabled()==false)
        return(false);

    int d1=src1->GetNumeric(true);
    if(parent!=NULL){
        if(GetNumeric(true)<=d1 && d1<=src2->GetNumeric(true))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) != src->GetNumeric(true))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) >= src->GetNumeric(true))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) > src->GetNumeric(true))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) <= src->GetNumeric(true))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    if(parent!=NULL){
        if(GetNumeric(true) < src->GetNumeric(true))
            parent->SetFlag(FlagConnectedMode,true);
        else
            parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::MultSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=GetNumeric(true) * src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::DivSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true)/r;
        SetData(d);
        }

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::ModSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);

    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true)%r;
        SetData(d);
        }

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::StrMoveSeq(Sequence *parent,bool  ,Operand *src1 ,Operand *src2)
{
    if(src1->IsGetEnabled()==false)
        return(false);
    if(src2->IsGetEnabled()==false)
        return(false);
    Data="";
    int s2=src2->GetNumeric(true);
    int DataLen=src1->GetStringCount()-s2;

    if(DataLen>=0){
        char *tData=new char[DataLen+1];
        memcpy(tData,src1->GetString()+s2,DataLen);
        tData[DataLen]=0;
        Data=tData;
        delete  []tData;
        }
    src1->FlushSource();

    SetData(Data);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::LowerSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    AnsiString  s=src->GetString();
    src->FlushSource();
    s=LowerCase(s);
    SetData(s);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::UpperSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    AnsiString  s=src->GetString();
    src->FlushSource();
    s=UpperCase(s);
    SetData(s);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
		}
    src->FlushSource();
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::FSetSeq(Sequence *parent,bool )
{
    SetData(1);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
/*↓D-20051026------------------------------------------------------------------
bool      LanvarOperand::FResetSeq(Sequence *parent,bool )
{
    SetData(0);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

bool      LanvarOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

bool      LanvarOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    int r=src->GetStringCount();
    src->FlushSource();
    SetData(r);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}


bool      LanvarOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
}
bool      LanvarOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
}
bool      LanvarOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
}
bool      LanvarOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
}
bool      LanvarOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
}
bool      LanvarOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    AnsiString  s;
    AnsiString  formatStr=src->GetString();
    src->FlushSource();
    bool    flag=GetSeqControl()->BPrintExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
    }

    if(flag==true){
        SetData(s);
        }
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
bool      LanvarOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false)
        return(false);
    AnsiString  s=GetString();
    AnsiString  formatStr=src->GetString();
    src->FlushSource();
    bool    flag=GetSeqControl()->BScanExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
        parent->Add1NowLine();
    }
    return(true);
}
bool      LanvarOperand::InputFromString(Sequence *parent,AnsiString &Src)
{
    SetData(Src);

    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}

bool      LanvarOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL)
        parent->Add1NowLine();;
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
FifoOperand::FifoOperand(SeqControl *baseParent):Operand(baseParent)
{
    Data.RemoveAll();
    DataNumb	=0;
    ReqList		=false;
    ID=GetSeqControl()->FifoOpe.GetNumber();
	ReqListData	=NULL;
}

QString    FifoOperand::GetName(void)
{
    return(Name);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    FifoOperand::Load(char buff[])
{
    char    nbuff[100];

    char    *fp=buff;
    fp+=5;
    fp=GetTopString(fp);
    fp=GetWordCut(fp,nbuff);
	QString	Q=QString(nbuff);
    SetName(Q);

    return(true);
}

void      FifoOperand::GetStackedListInner(void)
{
    if(ReqList==true){
        ReqListData->clear();
        for(FifoClass *d=Data.GetFirst();d!=NULL;d=d->GetNext()){
			ReqListData->append(d->Str);
            }
        ReqList=false;
        }
}

int      FifoOperand::GetStackedList(QStringList *d)
{
    ReqListData=d;
    ReqList=true;
    while(ReqList==true){
        ThreadSequence::MSleep(20);
    }
    return(d->count());
}

int      FifoOperand::GetStackedNumb(void)
{
    return(DataNumb);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int   FifoOperand::GetNumeric(bool SrcReconstruct)
{
    if(SrcReconstruct==true){
        FifoClass   *c=Data.GetFirst();
        if(c==NULL){
            return(0);
        }
		Lock();
        Data.RemoveList(c);
		int n=c->Str.toInt();
        delete  c;
        DataNumb--;
		Unlock();
        return(n);
        }
    else{
        FifoClass   *c=Data.GetFirst();
        if(c==NULL){
            return(0);
        }
		return(c->Str.toInt());
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
int    FifoOperand::GetStringCount(void)
{
    FifoClass   *c=Data.GetFirst();
    if(c==NULL){
        return(0);
    }
    return(c->Str.length());
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QByteArray      FifoOperand::GetString(bool ThreadMode)
{
    FifoClass   *c=Data.GetFirst();
    if(c==NULL){
        return(/**/"");
    }
    return(c->Str);
}

bool     FifoOperand::IsGetEnabled(void)
{
    if(Data.GetFirst()==NULL){
        return(false);
    }
    return(true);
}

void     FifoOperand::FlushSource(void)
{
    FifoClass   *c=Data.GetFirst();
    if(c==NULL){
        return;
    }
	Lock();
    Data.RemoveList(c);
    delete  c;
    DataNumb--;
	Unlock();
}

void     FifoOperand::SetData(const QByteArray &d)
{
	Lock();
    Data.AppendList(new FifoClass(d));
    DataNumb++;
	Unlock();
}
void  FifoOperand::SetData(int d)
{
	Lock();
    Data.AppendList(new FifoClass(d));
    DataNumb++;
	Unlock();
}
void     FifoOperand::SetData(const QString &d)
{
	Lock();
    Data.AppendList(new FifoClass(d.toLocal8Bit()));
    DataNumb++;
	Unlock();
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::LetSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    QByteArray  A=src->GetString();
    src->FlushSource();
    SetData(A);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::LetBSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    QByteArray  A=src->GetString();
    src->FlushSource();
    SetData(A);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) + src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) - src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) & src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) | src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) ^ src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(IsGetEnabled()==false){
        return(false);
    }
    int r=~GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::FlushSeq(Sequence *parent,bool FlagConnectedMode)
{
    //if(IsGetEnabled()==false)
    //    return(false);
    //int r=GetNumeric(true);
    //SetData(r);

	Lock();
	Data.RemoveAll();
	Unlock();

    if(parent!=NULL){
        parent->Add1NowLine();
    }

    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src1
//    src2
//    src3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(IsGetEnabled()==false){
	    if(parent!=NULL){
		    parent->Add1NowLine();
    		parent->SetFlag(FlagConnectedMode,false);
        }
        return(true);
	}
    //int r=GetNumeric(true);

    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,true);
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) & src->GetNumeric(true);
    if(parent!=NULL){
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) | src->GetNumeric(true);
    if(parent!=NULL){
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) ^ src->GetNumeric(true);
    if(parent!=NULL){
        if(r!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true) == src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int d1=src1->GetNumeric(true);
    if(parent!=NULL){
        if(GetNumeric(true)<=d1 && d1<=src2->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true) != src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true) >= src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true) > src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true) <= src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric(true) < src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::MultSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=GetNumeric(true) * src->GetNumeric(true);
    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::DivSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }
    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true)/r;
        SetData(d);
        }

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::ModSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true)%r;
        SetData(d);
        }

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::StrMoveSeq(Sequence *parent,bool  ,Operand *src1 ,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  r=/**/"";
    int s2=src2->GetNumeric(true);
    int DataLen=src1->GetStringCount()-s2;

    if(DataLen>=0){
        r=src1->GetString().mid(s2);
        }
    src1->FlushSource();

    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::LowerSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=src->GetString();
    src->FlushSource();

	s=s.toLower();
    SetData(s);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::UpperSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  s=src->GetString();
    src->FlushSource();

	s=s.toUpper();
    SetData(s);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::TWSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::FSetSeq(Sequence *parent,bool )
{
    FlushSource();
    SetData(1);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      FifoOperand::FResetSeq(Sequence *parent,bool )
{
    FlushSource();
    SetData(0);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      FifoOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      FifoOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int r=src->GetStringCount();
    src->FlushSource();

    SetData(r);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


bool      FifoOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      FifoOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      FifoOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      FifoOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      FifoOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      FifoOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QString  s=GetString();
    QString  formatStr=src->GetString();
    src->FlushSource();
    bool    flag=GetSeqControl()->BPrintExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
    }
    if(flag==true){
        SetData(s);
    }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
bool      FifoOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(IsGetEnabled()==false){
        return(false);
    }
    QString  s=GetString();
    QString  formatStr=src->GetString();
    src->FlushSource();
    bool flag=GetSeqControl()->BScanExecute(parent,s, formatStr);
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,flag);
        parent->Add1NowLine();
    }
    return(true);
}

bool      FifoOperand::InputFromString(Sequence *parent,QString &Src)
{
    QString  s=Src;
    SetData(s);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      FifoOperand::FloatNumSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

//==============================================================

SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=0;
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=1;
    Param1=datastr.toLocal8Bit();
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int datastr)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=1;
    Param1.append((char *)&datastr,sizeof(datastr));
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int datastr1 ,int datastr2)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1.append((char *)&datastr1,sizeof(datastr1));
    Param2.append((char *)&datastr2,sizeof(datastr2));
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr1 ,int datastr2)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1=datastr1.toLocal8Bit();
    Param2.append((char *)&datastr2,sizeof(datastr2));
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr1 ,QString &datastr2)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1=datastr1.toLocal8Bit();
    Param2=datastr2.toLocal8Bit();
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QString &datastr1 ,QString &datastr2 ,int data3)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1=datastr1.toLocal8Bit();
    Param2=datastr2.toLocal8Bit();
    Param3.append((char *)&data3,sizeof(data3));
}

SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int data1 ,int data2 ,int data3)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1.append((char *)&data1,sizeof(data1));
    Param2.append((char *)&data2,sizeof(data2));
    Param3.append((char *)&data3,sizeof(data3));
}

SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,int data1 ,int data2 ,int data3 ,int data4)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1.append((char *)&data1,sizeof(data1));
    Param2.append((char *)&data2,sizeof(data2));
    Param3.append((char *)&data3,sizeof(data3));
    Param4.append((char *)&data4,sizeof(data4));
}


SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=1;
    Param1=datastr;
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr1 ,int datastr2)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1=datastr1;
    Param2.append((char *)&datastr2,sizeof(datastr2));
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr1 ,QByteArray &datastr2)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1=datastr1;
    Param2=datastr2;
}
SeqCommandList::SeqCommandList(SeqControl *baseParent,QString &cmdstr ,QByteArray &datastr1 ,QByteArray &datastr2 ,int data3)
:BaseParent(baseParent)
{
    if(GetSeqControl()->DLLSync==NULL){
        GetSeqControl()->DLLSync=new QMutex();
    }
    NowTime=ThreadSequence::GetNowMiliSec();
    Cmd=cmdstr;
    ParamNumb=2;
    Param1=datastr1;
    Param2=datastr2;
    Param3.append((char *)&data3,sizeof(data3));
}

void    SeqCommandList::SetResult(QString &datastr)
{
    ResParam1=datastr.toLocal8Bit();
}
void    SeqCommandList::SetResult(int datastr)
{
    ResParam1.append((char *)&datastr,sizeof(datastr));
}

void    SeqCommandList::SetResult(int datastr1 ,int datastr2)
{
    ResParam1.append((char *)&datastr1,sizeof(datastr1));
    ResParam2.append((char *)&datastr2,sizeof(datastr2));
}

void    SeqCommandList::SetResult(QString &datastr1 ,int data2)
{
    ResParam1=datastr1.toLocal8Bit();
    ResParam2.append((char *)&data2,sizeof(data2));
}

void    SeqCommandList::SetResult(QString &datastr1 ,QString &datastr2)
{
    ResParam1=datastr1.toLocal8Bit();
    ResParam2.append((char *)&datastr2,sizeof(datastr2));
}

void    SeqCommandList::SetResult(QString &datastr1 ,QString &datastr2 ,int data3)
{
    ResParam1=datastr1.toLocal8Bit();
    ResParam2=datastr2.toLocal8Bit();
    ResParam3.append((char *)&data3,sizeof(data3));
}
void    SeqCommandList::SetResult(int data1 ,int data2 ,int data3)
{
    ResParam1.append((char *)&data1,sizeof(data1));
    ResParam2.append((char *)&data2,sizeof(data2));
    ResParam3.append((char *)&data3,sizeof(data3));
}

void    SeqCommandList::SetResult(int data1 ,int data2 ,int data3 ,int data4)
{
    ResParam1.append((char *)&data1,sizeof(data1));
    ResParam2.append((char *)&data2,sizeof(data2));
    ResParam3.append((char *)&data3,sizeof(data3));
    ResParam4.append((char *)&data4,sizeof(data4));
}

void    SeqCommandList::SetResult(QByteArray &datastr)
{
    ResParam1=datastr;
}

void    SeqCommandList::SetResult(QByteArray &datastr1 ,int data2)
{
    ResParam1=datastr1;
    ResParam2.append((char *)&data2,sizeof(data2));
}

void    SeqCommandList::SetResult(QByteArray &datastr1 ,QByteArray &datastr2)
{
    ResParam1=datastr1;
    ResParam2=datastr2;
}

void    SeqCommandList::SetResult(QByteArray &datastr1 ,QByteArray &datastr2 ,int data3)
{
    ResParam1=datastr1;
    ResParam2=datastr2;
    ResParam3.append((char *)&data3,sizeof(data3));
}
QString  SeqCommandList::GetNowTimeString(void)
{
    DWORD   t=NowTime-GetSeqControl()->StartTickCount;
    time_t  d=GetSeqControl()->StartTime+t/1000;
    return(Time_tToDayTimeString(d) + QString(".") + QString().setNum(t%1000));
}



/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
QString    DLLVarOperand::GetName(void)
{
    return(Name);
}

DLLVarOperand::DLLVarOperand(SeqControl *baseParent)
:Operand(baseParent)
{
	Interface=new DLLVarInterface;
}
DLLVarOperand::DLLVarOperand(const DLLVarOperand &src)
    :Operand(((DLLVarOperand *)&src)->GetSeqControl())
{
    Interface   =new DLLVarInterface;
    Data        =src.Data;
    VersionStr  =src.VersionStr;
}
DLLVarOperand::~DLLVarOperand(void)
{
	if(Interface!=NULL){
		delete  Interface;
        Interface=NULL;
	}
}

bool    DLLVarOperand::IsDebugMode(void)
{
     return Interface->IsDebugMode();
}

void    DLLVarOperand::DLLDebug(QApplication *app)
{
    Interface->DLLDebug(app);
}


bool    DLLVarOperand::OpenInitialize(void)
{
	return Interface->OpenInitialize(BaseParent->GetLayersBase());
}

QString	DLLVarOperand::GetFileName(void)
{
    return Interface->GetFileName();
}
bool	DLLVarOperand::IsDLLVarDLL(void)
{
	 return Interface->IsDLLVarDLL();
}

bool	DLLVarOperand::LoadDLL(const QString &filename)
{
    LayersBase  *Base=BaseParent->GetLayersBase();
    if(Base!=NULL){
		Base->TestLoadDLL(Interface->GetFileName());
    }
    bool    Ret=Interface->LoadDLL(Base,filename);
	if(Base!=NULL){
		Base->InformToLoadDLL(filename);
	}
    return Ret;
}


void	DLLVarOperand::TransmitDirectly(GUIDirectMessage *packet)
{
	Interface->TransmitDirectly(packet);
}

bool	DLLVarOperand::GetRelatedDLL(QStringList &DLLFileNames)
{
	 return Interface->GetRelatedDLL(DLLFileNames);
}

char	*DLLVarOperand::GetRelatedDLLSystemVersion(const QString &DLLFileName ,VersionType vtype)
{
	 return Interface->GetRelatedDLLSystemVersion(DLLFileName ,vtype);
}

const char	*DLLVarOperand::GetSystemVersion(VersionType vtype)
{
	 return Interface->GetSystemVersion(vtype);
}

bool	DLLVarOperand::CheckSystemVersionFunc(QStringList &Str 
						   ,const QString &DLLType 
						   ,const QString &DLLRoot 
						   ,const QString &DLLName)
{
	 return Interface->CheckSystemVersionFunc(Str,DLLType,DLLRoot,DLLName);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    buff
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    DLLVarOperand::Load(char buff[])
{
    char    nbuff[100];

	CutComment(buff);
    char    *fp=buff;
    fp+=8;
    fp=GetTopString(fp);
    fp=GetWordCut(fp,nbuff);
    if(fp==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(*fp!=':'){
        return(false);
    }
    fp++;
    fp=GetTopString(fp);
	if(*fp!='\"'){
		return false;
    }
	fp++;
	char	PathBuff[1024];
	memset(PathBuff,0,sizeof(PathBuff));
	strncpy(PathBuff,fp,sizeof(PathBuff)-1);
	fp=strchr(PathBuff,',');
	char	*ParaP=NULL;
	if(fp!=NULL){
		ParaP=fp+1;
		fp--;
	}
	else{
		fp=strchr(PathBuff,0);
		if(fp>PathBuff){
			fp--;
        }
	}
	while(fp>PathBuff && (*fp==' ' || *fp=='\n' || *fp=='\t')){
		fp--;
    }
	if(fp<=PathBuff){
		return false;
    }
	if(*fp!='\"'){
		return false;
    }
	*fp=0;
	if(strlen(PathBuff)==0){
		return false;
    }
	int	len=strlen(PathBuff);
	if(len>4){
		if(stricmp(&PathBuff[len-4],".DLL")==0){
			PathBuff[len-4]=0;
        }
	}
	Interface->SetFileName(PathBuff);

	QString	Q=QString(nbuff);
	SetName(Q);
	
	if(ParaP!=NULL){
	    fp=GetTopString(ParaP);
		if(*fp!='\"'){
			return false;
        }
		fp++;
		strncpy(PathBuff,fp,sizeof(PathBuff)-1);
		fp=strchr(PathBuff,0);
		if(fp>PathBuff){
			fp--;
        }
		
		while(fp>PathBuff && (*fp==' ' || *fp=='\n' || *fp=='\t')){
			fp--;
        }
		if(fp<=PathBuff){
			return false;
        }
		if(*fp!='\"'){
			return false;
        }
		*fp=0;
		if(strlen(PathBuff)==0){
			return false;
        }
		Interface->SetParam(PathBuff);
	}

    return(true);
}


void     DLLVarOperand::SetData(int d)
{
    Data=QByteArray::number(d);
}

int   DLLVarOperand::GetNumeric(bool SrcReconstruct)
{
	return(Data.toInt());
}

int    DLLVarOperand::GetStringCount(void)
{
    return(Data.length());
}

QByteArray      DLLVarOperand::GetString(bool ThreadMode)
{
    return(Data);
}

void     DLLVarOperand::SetData(const QByteArray &d)
{
    Data=d;
}

bool      DLLVarOperand::LetSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    QByteArray  S =src->GetString();
    int     CCount=src->GetStringCount();
    CommOperand *c=dynamic_cast<CommOperand*>(src);
    if(c!=NULL){
        if(c->TermNumb==0){
            if(CCount==0){
                if(c->IntoTime==0){
                    c->IntoTime=ThreadSequence::GetNowMiliSec();
                    }
                if(c->RxTimeoutMilisec!=0
                && ThreadSequence::GetNowMiliSec()-c->IntoTime>c->RxTimeoutMilisec){
                    if(parent!=NULL){
                        for(int i=0;i<parent->GetSLineNumb();i++){
                            if(parent->GetSLine(i)!=NULL
                            && parent->GetSLine(i)->LNumber==c->RxTimeoutAddress){
                                src->FlushSource();
                                c->IntoTime=0;
                                parent->SetNowLine(i);
                                return(true);
                            }
                        }
                    }
                }
                src->FlushSource();
                return(true);
                }
            }
        c->IntoTime=0;
        }

    src->FlushSource();
    Data=S;
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::LetBSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int d=src->GetNumeric(true);
    Data=QByteArray((char *)&d,1);

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::AddSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        Data=Data+GetString();
        if(Data.size()!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::SubSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        int d=Data.toInt() - src->GetNumeric(true);
        Data=QByteArray((char *)&d,1);
	    if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::AndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        int d=Data.toInt() & src->GetNumeric(true);
        Data=QByteArray((char *)&d,1);
	    if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::OrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        int d=Data.toInt() | src->GetNumeric(true);
        Data=QByteArray((char *)&d,1);
	    if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::XorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        int d=Data.toInt() ^ src->GetNumeric(true);
        Data=QByteArray((char *)&d,1);
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::NotSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
        int d=~GetNumeric();
        Data=QByteArray((char *)&d,1);
        if(d!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
bool      DLLVarOperand::FlushSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::AllocSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::IndSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::BitloadSeq(Sequence *parent,bool  ,Operand * ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::FlagSeq(Sequence *parent,bool FlagConnectedMode)
{
    if(parent!=NULL){
	    if(Data!=QString::number(0)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::CAndSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
	    if((Data.toInt()&src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::COrSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if((Data.toInt()|src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::CXorSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
	    if((Data.toInt()^src->GetNumeric(true))!=0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::EqualSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data==src->GetString(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::ZoneSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1,Operand *src2)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }
    if(src2->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
	    if(Data.compare(src1->GetString(true))<0 && src1->GetString(true).compare(src2->GetString(true))<0){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::PartEqSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    return(EqualSeq(parent,FlagConnectedMode ,src));
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::UnequalSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(Data!=src->GetString(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::GreaterSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
	    if(Data.toInt()>=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::LargeSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
	    if(Data.toInt()>src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::LessSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
	    if(Data.toInt()<=src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::SmallSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    if(parent!=NULL){
        if(GetNumeric()<src->GetNumeric(true)){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::MultSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    int d=GetNumeric(true) * src->GetNumeric(true);
    Data=QByteArray((char *)&d,1);
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::DivSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true) / r;
        Data=QByteArray((char *)&d,1);
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::ModSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }

    int r=src->GetNumeric(true);
    if(r!=0){
        int d=GetNumeric(true) % r;
        Data=QByteArray((char *)&d,1);
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::StrMoveSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::LowerSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::UpperSeq(Sequence *parent,bool  ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::StateSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
	if(GetSeqControl()->StateOut!=NULL){
		QByteArray	Q=src->GetString();
        GetSeqControl()->StateOut(GetNumeric(true),Q);
	}
    src->FlushSource();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//    src
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::TWSetSeq(Sequence *parent,bool )
{
    int d=ThreadSequence::GetNowMiliSec();
    Data=QByteArray((char *)&d,sizeof(int));
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::FSetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool      DLLVarOperand::FResetSeq(Sequence *parent,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::RxTimeoutSeq(Sequence *parent,bool  ,Operand * ,Operand *)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::StrLenSeq(Sequence *parent,bool  ,Operand *src)
{
    if(src->IsGetEnabled()==false){
        return(false);
    }
    if(parent!=NULL){
        int len=src->GetStringCount();
        src->FlushSource();

        Data=QByteArray((char *)&len,sizeof(len));
        parent->Add1NowLine();;
        }
    return(true);
}

bool      DLLVarOperand::AddFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      DLLVarOperand::OpenLFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      DLLVarOperand::LoadFileSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src)
{
	return(true);
}
bool      DLLVarOperand::CloseFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      DLLVarOperand::DeleteFileSeq(Sequence *parent,bool FlagConnectedMode)
{
	return(true);
}
bool      DLLVarOperand::BPrintSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
bool      DLLVarOperand::BScanSeq(Sequence *parent,bool FlagConnectedMode ,Operand *)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::InputFromString(Sequence *parent,QString &Src)
{
    Data=Src.toLocal8Bit();
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::FDLLCmdSeq(Sequence *parent,bool FlagConnectedMode ,Operand *src1 ,Operand *src2 ,Operand *src3 ,Operand *src4 ,Operand *src5)
{
    if(src1->IsGetEnabled()==false){
        return(false);
    }

    if(src2==NULL){
        if(Interface->DLLCmd!=NULL){
            SeqCommandList *c=NULL;
            QString    cmdstr=src1->GetString();
            if(GetSeqControl()->DLLDebugMode==true){
                c=new SeqCommandList(GetSeqControl(),cmdstr);
				GetSeqControl()->DLLSync->lock();
                GetSeqControl()->CmdList.AppendList(c);
				GetSeqControl()->DLLSync->unlock();
                }
			QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
			bool    flag= Interface->DLLCmd(Interface->Handle,*A,cmdstr);
            if(parent!=NULL){
                parent->SetFlag(FlagConnectedMode,flag);
            }
        }
    }
    else{
        if(src2->IsGetEnabled()==false){
            return(false);
        }

        if(src2->GetKindCode()==KindCodeIO
        || src2->GetKindCode()==KindCodeBit
        || src2->GetKindCode()==KindCodeLocalBit
        || src2->GetKindCode()==KindCodeWord
        || src2->GetKindCode()==KindCodeLocalWord
        || src2->GetKindCode()==KindCodeSpecial
        || src2->GetKindCode()==KindCodeSpeicalBit
        || src2->GetKindCode()==KindCodeGroup){
            if(src3!=NULL
            && (src3->GetKindCode()==KindCodeIO
             || src3->GetKindCode()==KindCodeBit
             || src3->GetKindCode()==KindCodeLocalBit
             || src3->GetKindCode()==KindCodeWord
             || src3->GetKindCode()==KindCodeLocalWord
             || src3->GetKindCode()==KindCodeSpecial
             || src3->GetKindCode()==KindCodeSpeicalBit
             || src3->GetKindCode()==KindCodeGroup)){
	            if(src4!=NULL
		        && (src4->GetKindCode()==KindCodeIO
			     || src4->GetKindCode()==KindCodeBit
				 || src4->GetKindCode()==KindCodeLocalBit
				 || src4->GetKindCode()==KindCodeWord
	             || src4->GetKindCode()==KindCodeLocalWord
		         || src4->GetKindCode()==KindCodeSpecial
			     || src4->GetKindCode()==KindCodeSpeicalBit
				 || src4->GetKindCode()==KindCodeGroup)){
		            if(src5!=NULL
			        && (src5->GetKindCode()==KindCodeIO
				     || src5->GetKindCode()==KindCodeBit
					 || src5->GetKindCode()==KindCodeLocalBit
					 || src5->GetKindCode()==KindCodeWord
		             || src5->GetKindCode()==KindCodeLocalWord
			         || src5->GetKindCode()==KindCodeSpecial
				     || src5->GetKindCode()==KindCodeSpeicalBit
					 || src5->GetKindCode()==KindCodeGroup)){
		                int d1=src2->GetNumeric();
				        int d2=src3->GetNumeric();
						int d3=src4->GetNumeric();
						int d4=src5->GetNumeric();
		                if(Interface->DLLCmdInt4!=NULL){
				            SeqCommandList *c=NULL;
						    QString    cmdstr=src1->GetString();
			                if(GetSeqControl()->DLLDebugMode==true){
				                c=new SeqCommandList(GetSeqControl(),cmdstr,d1,d2,d3,d4);
								GetSeqControl()->DLLSync->lock();
		                        GetSeqControl()->CmdList.AppendList(c);
								GetSeqControl()->DLLSync->unlock();
						        }
							QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
							bool    flag=Interface->DLLCmdInt4(Interface->Handle,*A,cmdstr,&d1,&d2,&d3,&d4);
                            if(parent!=NULL){
						        parent->SetFlag(FlagConnectedMode,flag);
                            }
		                    if(GetSeqControl()->DLLDebugMode==true){
								GetSeqControl()->DLLSync->lock();
						        c->SetResult(d1,d2 ,d3 ,d4);
								GetSeqControl()->DLLSync->unlock();
		                        }
				            }
						src2->SetData(d1);
						src3->SetData(d2);
						src4->SetData(d3);
						src5->SetData(d4);
					}
					else if(src5==NULL){
		                int d1=src2->GetNumeric();
				        int d2=src3->GetNumeric();
						int d3=src4->GetNumeric();
		                if(Interface->DLLCmdInt3!=NULL){
				            SeqCommandList *c=NULL;
						    QString    cmdstr=src1->GetString();
			                if(GetSeqControl()->DLLDebugMode==true){
				                c=new SeqCommandList(GetSeqControl(),cmdstr,d1,d2,d3);
								GetSeqControl()->DLLSync->lock();
		                        GetSeqControl()->CmdList.AppendList(c);
								GetSeqControl()->DLLSync->unlock();
						        }
							QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
							bool    flag=Interface->DLLCmdInt3(Interface->Handle,*A,cmdstr,&d1,&d2,&d3);
                            if(parent!=NULL){
						        parent->SetFlag(FlagConnectedMode,flag);
                            }
		                    if(GetSeqControl()->DLLDebugMode==true){
								GetSeqControl()->DLLSync->lock();
						        c->SetResult(d1,d2,d3);
								GetSeqControl()->DLLSync->unlock();
		                    }
				        }
						src2->SetData(d1);
						src3->SetData(d2);
						src4->SetData(d3);
					}
				}
				else if(src4==NULL){
	                int d1=src2->GetNumeric();
		            int d2=src3->GetNumeric();
			        if(Interface->DLLCmdInt2!=NULL){
				        SeqCommandList *c=NULL;
					    QString    cmdstr=src1->GetString();
	                    if(GetSeqControl()->DLLDebugMode==true){
		                    c=new SeqCommandList(GetSeqControl(),cmdstr,d1,d2);
							GetSeqControl()->DLLSync->lock();
				            GetSeqControl()->CmdList.AppendList(c);
							GetSeqControl()->DLLSync->unlock();
						    }
						QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
						bool    flag=Interface->DLLCmdInt2(Interface->Handle,*A,cmdstr,&d1,&d2);
                        if(parent!=NULL){
		                    parent->SetFlag(FlagConnectedMode,flag);
                        }
			            if(GetSeqControl()->DLLDebugMode==true){
							GetSeqControl()->DLLSync->lock();
					        c->SetResult(d1,d2);
							GetSeqControl()->DLLSync->unlock();
						}
                    }
					src2->SetData(d1);
					src3->SetData(d2);
                }
			 }
            else
            if(src3!=NULL
            && src3->GetKindCode()==KindCodeNumber){
                int d1=src2->GetNumeric();
                int d2=src3->GetNumeric();
                if(Interface->DLLCmdInt2!=NULL){
                    SeqCommandList *c=NULL;
                    QString    cmdstr=src1->GetString();
                    if(GetSeqControl()->DLLDebugMode==true){
                        c=new SeqCommandList(GetSeqControl(),cmdstr,d1,d2);
						GetSeqControl()->DLLSync->lock();
                        GetSeqControl()->CmdList.AppendList(c);
						GetSeqControl()->DLLSync->unlock();
                        }
					QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
					bool    flag=Interface->DLLCmdInt2(Interface->Handle,*A,cmdstr,&d1,&d2);
                    if(parent!=NULL){
                        parent->SetFlag(FlagConnectedMode,flag);
                    }
                    if(GetSeqControl()->DLLDebugMode==true){
						GetSeqControl()->DLLSync->lock();
                        c->SetResult(d1,d2);
						GetSeqControl()->DLLSync->unlock();
                        }
                    }
                src2->SetData(d1);
                }
            else{
                int d=src2->GetNumeric();
                if(Interface->DLLCmdInt!=NULL){
                    SeqCommandList *c=NULL;
                    QString    cmdstr=src1->GetString();
                    if(GetSeqControl()->DLLDebugMode==true){
                        c=new SeqCommandList(GetSeqControl(),cmdstr,d);
						GetSeqControl()->DLLSync->lock();
                        GetSeqControl()->CmdList.AppendList(c);
						GetSeqControl()->DLLSync->unlock();
                        }
					QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
					bool    flag=Interface->DLLCmdInt(Interface->Handle,*A,cmdstr,&d);
                    if(parent!=NULL){
                        parent->SetFlag(FlagConnectedMode,flag);
                    }
                    if(GetSeqControl()->DLLDebugMode==true){
						GetSeqControl()->DLLSync->lock();
                        c->SetResult(d);
						GetSeqControl()->DLLSync->unlock();
                        }
                    }
                src2->SetData(d);
                }
            }
        else
        if(src2->GetKindCode()==KindCodeNumber){
            if(src3!=NULL
            && (src3->GetKindCode()==KindCodeIO
             || src3->GetKindCode()==KindCodeBit
             || src3->GetKindCode()==KindCodeLocalBit
             || src3->GetKindCode()==KindCodeWord
             || src3->GetKindCode()==KindCodeLocalWord
             || src3->GetKindCode()==KindCodeSpecial
             || src3->GetKindCode()==KindCodeSpeicalBit
             || src3->GetKindCode()==KindCodeGroup)){
                int d1=src2->GetNumeric();
                int d2=src3->GetNumeric();
                if(Interface->DLLCmdInt2!=NULL){
                    SeqCommandList *c=NULL;
                    QString    cmdstr=src1->GetString();
                    if(GetSeqControl()->DLLDebugMode==true){
                        c=new SeqCommandList(GetSeqControl(),cmdstr,d1,d2);
						GetSeqControl()->DLLSync->lock();
                        GetSeqControl()->CmdList.AppendList(c);
						GetSeqControl()->DLLSync->unlock();
                        }
					QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
					bool    flag=Interface->DLLCmdInt2(Interface->Handle,*A,cmdstr,&d1,&d2);
                    if(parent!=NULL){
                        parent->SetFlag(FlagConnectedMode,flag);
                    }
                    if(GetSeqControl()->DLLDebugMode==true){
						GetSeqControl()->DLLSync->lock();
                        c->SetResult(d1,d2);
						GetSeqControl()->DLLSync->unlock();
                        }
                    }
                src3->SetData(d2);
                }
            else
            if(src3!=NULL
            && src3->GetKindCode()==KindCodeNumber){
                int d1=src2->GetNumeric();
                int d2=src3->GetNumeric();
                if(Interface->DLLCmdInt2!=NULL){
                    SeqCommandList *c=NULL;
                    QString    cmdstr=src1->GetString();
                    if(GetSeqControl()->DLLDebugMode==true){
                        c=new SeqCommandList(GetSeqControl(),cmdstr,d1,d2);
						GetSeqControl()->DLLSync->lock();
                        GetSeqControl()->CmdList.AppendList(c);
						GetSeqControl()->DLLSync->unlock();
                        }
					QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
					bool    flag=Interface->DLLCmdInt2(Interface->Handle,*A,cmdstr,&d1,&d2);
                    if(parent!=NULL){
                        parent->SetFlag(FlagConnectedMode,flag);
                    }
                    if(GetSeqControl()->DLLDebugMode==true){
						GetSeqControl()->DLLSync->lock();
                        c->SetResult(d1,d2);
						GetSeqControl()->DLLSync->unlock();
                        }
                    }
                }
            else{
                int d=src2->GetNumeric();
                if(Interface->DLLCmdInt!=NULL){
                    SeqCommandList *c=NULL;
                    QString    cmdstr=src1->GetString();
                    if(GetSeqControl()->DLLDebugMode==true){
                        c=new SeqCommandList(GetSeqControl(),cmdstr,d);
						GetSeqControl()->DLLSync->lock();
                        GetSeqControl()->CmdList.AppendList(c);
						GetSeqControl()->DLLSync->unlock();
                        }
					QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
					bool    flag=Interface->DLLCmdInt(Interface->Handle,*A,cmdstr,&d);
                    if(parent!=NULL){
                        parent->SetFlag(FlagConnectedMode,flag);
                    }
                    if(GetSeqControl()->DLLDebugMode==true){
						GetSeqControl()->DLLSync->lock();
                        c->SetResult(d);
						GetSeqControl()->DLLSync->unlock();
                        }
                    }
                }
            }
        else
        if(src2->GetKindCode()==KindCodeString){
            QByteArray    RetBuff;
            if(src3!=NULL
            && (src3->GetKindCode()==KindCodeIO
             || src3->GetKindCode()==KindCodeBit
             || src3->GetKindCode()==KindCodeLocalBit
             || src3->GetKindCode()==KindCodeWord
             || src3->GetKindCode()==KindCodeLocalWord
             || src3->GetKindCode()==KindCodeSpecial
             || src3->GetKindCode()==KindCodeSpeicalBit
             || src3->GetKindCode()==KindCodeGroup)){
                int d2=src3->GetNumeric();
                if(src2->GetString().isEmpty()==false){
                    RetBuff=src2->GetString();
                }

                SeqCommandList *c=NULL;
                QString    cmdstr=src1->GetString();
                QByteArray datastr1=src2->GetString();
                if(GetSeqControl()->DLLDebugMode==true){
                    c=new SeqCommandList(GetSeqControl(),cmdstr,datastr1,RetBuff,d2);
					GetSeqControl()->DLLSync->lock();
                    GetSeqControl()->CmdList.AppendList(c);
					GetSeqControl()->DLLSync->unlock();
                    }
				QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
				bool    flag=Interface->DLLCmdStrRetInt(Interface->Handle,*A,cmdstr,datastr1,RetBuff ,&d2);
                if(parent!=NULL){
                    parent->SetFlag(FlagConnectedMode,flag);
                }
                src3->SetData(d2);
                src2->SetData(RetBuff);
                if(GetSeqControl()->DLLDebugMode==true){
					GetSeqControl()->DLLSync->lock();
                    c->SetResult(datastr1,RetBuff ,d2);
					GetSeqControl()->DLLSync->unlock();
                    }
                }
             else{
                if(Interface->DLLCmdStrRet!=NULL){
                    if(src2->GetString().isEmpty()==false){
                        RetBuff=src2->GetString();
                    }
                    SeqCommandList *c=NULL;
                    QString    cmdstr=src1->GetString();
                    QByteArray datastr1=src2->GetString();
                    if(GetSeqControl()->DLLDebugMode==true){
                        c=new SeqCommandList(GetSeqControl(),cmdstr,datastr1,RetBuff);
						GetSeqControl()->DLLSync->lock();
                        GetSeqControl()->CmdList.AppendList(c);
						GetSeqControl()->DLLSync->unlock();
                        }
					QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
					bool    flag=Interface->DLLCmdStrRet(Interface->Handle,*A,cmdstr,datastr1,RetBuff);
                    if(parent!=NULL){
                        parent->SetFlag(FlagConnectedMode,flag);
                    }
                    src2->SetData(RetBuff);
                    if(GetSeqControl()->DLLDebugMode==true){
						GetSeqControl()->DLLSync->lock();
                        c->SetResult(datastr1,RetBuff);
						GetSeqControl()->DLLSync->unlock();
                        }
                    }
				else{
		            if(Interface->DLLCmdStr!=NULL){
			            SeqCommandList *c=NULL;
				        QString    cmdstr=src1->GetString();
					    QByteArray datastr1=src2->GetString();
						if(GetSeqControl()->DLLDebugMode==true){
							c=new SeqCommandList(GetSeqControl(),cmdstr,datastr1);
							GetSeqControl()->DLLSync->lock();
		                    GetSeqControl()->CmdList.AppendList(c);
							GetSeqControl()->DLLSync->unlock();
				            }
						QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
						bool    flag=Interface->DLLCmdStr(Interface->Handle,*A,cmdstr,datastr1);
                        if(parent!=NULL){
		                    parent->SetFlag(FlagConnectedMode,flag);
                        }
						//src2->SetData(RetBuff);
				        if(GetSeqControl()->DLLDebugMode==true){
							GetSeqControl()->DLLSync->lock();
						    c->SetResult(datastr1);
							GetSeqControl()->DLLSync->unlock();
						}
                    }
                }
			}
		}
        else
        if(src2->GetKindCode()==KindCodeCharacter){
            if(Interface->DLLCmdStrInt!=NULL
			&& src3!=NULL
            && (src3->GetKindCode()==KindCodeIO
             || src3->GetKindCode()==KindCodeBit
             || src3->GetKindCode()==KindCodeLocalBit
             || src3->GetKindCode()==KindCodeWord
             || src3->GetKindCode()==KindCodeLocalWord
             || src3->GetKindCode()==KindCodeSpecial
             || src3->GetKindCode()==KindCodeSpeicalBit
             || src3->GetKindCode()==KindCodeGroup)){
                int d2=src3->GetNumeric();
                SeqCommandList *c=NULL;
                QString    cmdstr=src1->GetString();
                QByteArray datastr1=src2->GetString();
                if(GetSeqControl()->DLLDebugMode==true){
                    c=new SeqCommandList(GetSeqControl(),cmdstr,datastr1,d2);
					GetSeqControl()->DLLSync->lock();
                    GetSeqControl()->CmdList.AppendList(c);
					GetSeqControl()->DLLSync->unlock();
                    }
				QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
				bool    flag=Interface->DLLCmdStrInt(Interface->Handle,*A,cmdstr,datastr1,&d2);
                if(parent!=NULL){
                    parent->SetFlag(FlagConnectedMode,flag);
                }
                src3->SetData(d2);
				//src2->SetData(RetBuff);
                if(GetSeqControl()->DLLDebugMode==true){
					GetSeqControl()->DLLSync->lock();
                    c->SetResult(datastr1,d2);
					GetSeqControl()->DLLSync->unlock();
                    }
                }
            else if(Interface->DLLCmdStrRet!=NULL
			&& src3!=NULL
            && (src3->GetKindCode()==KindCodeString
			|| src3->GetKindCode()==KindCodeLocalString)){
	            QByteArray    RetBuff;
				if(src2->GetString().isEmpty()==false){
					RetBuff=src2->GetString();
                }
				SeqCommandList *c=NULL;
				QString    cmdstr=src1->GetString();
				QByteArray datastr1=RetBuff;
				if(GetSeqControl()->DLLDebugMode==true){
					c=new SeqCommandList(GetSeqControl(),cmdstr,datastr1,RetBuff);
					GetSeqControl()->DLLSync->lock();
					GetSeqControl()->CmdList.AppendList(c);
					GetSeqControl()->DLLSync->unlock();
				}
				QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
				bool    flag=Interface->DLLCmdStrRet(Interface->Handle,*A,cmdstr,datastr1,RetBuff);
                if(parent!=NULL){
			    	parent->SetFlag(FlagConnectedMode,flag);
                }
				src3->SetData(RetBuff);
				if(GetSeqControl()->DLLDebugMode==true){
					GetSeqControl()->DLLSync->lock();
					c->SetResult(datastr1,RetBuff);
					GetSeqControl()->DLLSync->unlock();
				}
			}
			else{
                if(Interface->DLLCmdStr!=NULL){
                    SeqCommandList *c=NULL;
                    QString    cmdstr=src1->GetString();
                    QByteArray datastr1=src2->GetString();
                    if(GetSeqControl()->DLLDebugMode==true){
                        c=new SeqCommandList(GetSeqControl(),cmdstr,datastr1);
						GetSeqControl()->DLLSync->lock();
                        GetSeqControl()->CmdList.AppendList(c);
						GetSeqControl()->DLLSync->unlock();
                        }
					QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
					bool    flag=Interface->DLLCmdStr(Interface->Handle,*A,cmdstr,datastr1);
                    if(parent!=NULL){
                        parent->SetFlag(FlagConnectedMode,flag);
                    }
					//src2->SetData(RetBuff);
                    if(GetSeqControl()->DLLDebugMode==true){
						GetSeqControl()->DLLSync->lock();
                        c->SetResult(datastr1);
						GetSeqControl()->DLLSync->unlock();
                        }
                    }
				}
            }
        else
        if(src2->GetKindCode()==KindCodeFloat || src2->GetKindCode()==KindCodeSpeicalFloat){
            if(Interface->DLLCmdFloat!=NULL && src3==NULL){
                SeqCommandList *c=NULL;
                QString    cmdstr=src1->GetString();
                double		data1=src2->GetFloat();
                if(GetSeqControl()->DLLDebugMode==true){
                    c=new SeqCommandList(GetSeqControl(),cmdstr,data1);
					GetSeqControl()->DLLSync->lock();
                    GetSeqControl()->CmdList.AppendList(c);
					GetSeqControl()->DLLSync->unlock();
                    }
				QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
				bool    flag=Interface->DLLCmdFloat(Interface->Handle,*A,cmdstr,&data1);
                if(parent!=NULL){
                    parent->SetFlag(FlagConnectedMode,flag);
                }
				src2->SetFloat(data1);
                if(GetSeqControl()->DLLDebugMode==true){
					GetSeqControl()->DLLSync->lock();
                    c->SetResult(data1);
					GetSeqControl()->DLLSync->unlock();
                    }
                }
            }
		else{
            if(Interface->DLLCmdStrInt!=NULL 
			&& src3!=NULL
            && (src3->GetKindCode()==KindCodeIO
             || src3->GetKindCode()==KindCodeBit
             || src3->GetKindCode()==KindCodeLocalBit
             || src3->GetKindCode()==KindCodeWord
             || src3->GetKindCode()==KindCodeLocalWord
             || src3->GetKindCode()==KindCodeSpecial
             || src3->GetKindCode()==KindCodeSpeicalBit
             || src3->GetKindCode()==KindCodeGroup)){
                int d2=src3->GetNumeric();
                SeqCommandList *c=NULL;
                QString    cmdstr=src1->GetString();
                QByteArray datastr1=src2->GetString();
                if(GetSeqControl()->DLLDebugMode==true){
                    c=new SeqCommandList(GetSeqControl(),cmdstr,datastr1,d2);
					GetSeqControl()->DLLSync->lock();
                    GetSeqControl()->CmdList.AppendList(c);
					GetSeqControl()->DLLSync->unlock();
                    }
				QApplication	*A=dynamic_cast<QApplication *>(QApplication::instance());
				bool    flag=Interface->DLLCmdStrInt(Interface->Handle,*A,cmdstr,datastr1,&d2);
                if(parent!=NULL){
                    parent->SetFlag(FlagConnectedMode,flag);
                }
                src3->SetData(d2);
                if(GetSeqControl()->DLLDebugMode==true){
					GetSeqControl()->DLLSync->lock();
                    c->SetResult(datastr1,d2);
					GetSeqControl()->DLLSync->unlock();
                    }
                }
            }
        }

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

bool      DLLVarOperand::FloatNumSeq(Sequence *parent,bool ,Operand *src)
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}


//==============================================================


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
SeqLine::SeqLine(SeqControl	*baseParent)
:BaseParent(baseParent)
{
    Op1=NULL;
    Op2=NULL;
    Op3=NULL;
    Op4=NULL;
	Op5=NULL;
	Op6=NULL;
	LNumber	=0;
	LCode	=-1;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
SeqLine::~SeqLine(void)
{
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    lnumb
//    cond
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqLine::Set(int lnumb , ExecuteCondition )
{
    LNumber=lnumb;
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    lnumb
//    cond
//    ope1
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqLine::Set(int lnumb , ExecuteCondition  ,Operand *ope1)
{
    LNumber=lnumb;
    Op1=ope1;
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    lnumb
//    cond
//    ope1
//    ope2
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqLine::Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2)
{
    LNumber=lnumb;
    Op1=ope1;
    Op2=ope2;
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    lnumb
//    cond
//    ope1
//    ope2
//    ope3
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqLine::Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3)
{
    LNumber=lnumb;
    Op1=ope1;
    Op2=ope2;
    Op3=ope3;
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    lnumb
//    cond
//    ope1
//    ope2
//    ope3
//    ope4
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqLine::Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3 ,Operand *ope4)
{
    LNumber=lnumb;
    Op1=ope1;
    Op2=ope2;
    Op3=ope3;
    Op4=ope4;
}
void    SeqLine::Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3 ,Operand *ope4 ,Operand *ope5)
{
    LNumber=lnumb;
    Op1=ope1;
    Op2=ope2;
    Op3=ope3;
    Op4=ope4;
	Op5=ope5;
}
void    SeqLine::Set(int lnumb , ExecuteCondition cond ,Operand *ope1 ,Operand *ope2 ,Operand *ope3 ,Operand *ope4 ,Operand *ope5 ,Operand *ope6)
{
    LNumber=lnumb;
    Op1=ope1;
    Op2=ope2;
    Op3=ope3;
    Op4=ope4;
	Op5=ope5;
	Op6=ope6;
}

void    SeqLine::Copy(LocalReg *DestLReg ,SeqLine *dest)
{
    dest->LNumber =LNumber;
    dest->eFlag   =eFlag;

    Operand *o1=NULL;
    Operand *o2=NULL;
    Operand *o3=NULL;
    Operand *o4=NULL;
    if(Op1!=NULL){
        o1=Op1->MakeDup(DestLReg);
    }
    if(Op2!=NULL){
        o2=Op2->MakeDup(DestLReg);
    }
    if(Op3!=NULL){
        o3=Op3->MakeDup(DestLReg);
    }
    if(Op4!=NULL){
        o4=Op4->MakeDup(DestLReg);
    }

    if(o1!=NULL){
        dest->Op1=o1;
    }
    else{
        dest->Op1=Op1;
    }
    if(o2!=NULL){
        dest->Op2=o2;
    }
    else{
        dest->Op2=Op2;
    }
    if(o3!=NULL){
        dest->Op3=o3;
    }
    else{
        dest->Op3=Op3;
    }
    if(o4!=NULL){
        dest->Op4=o4;
    }
    else{
        dest->Op4=Op4;
    }
}

Operand *SeqLine::GetOpe(int n)
{
	switch(n){
		case 0:	return Op1;
		case 1:	return Op2;
		case 2:	return Op3;
		case 3:	return Op4;
	}
	return NULL;
}

//==============================================================
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LetSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    return  Op1->LetSeq(parent,FlagConnectedMode,Op2);
}

SeqLine *LetSeq::MakeDup(LocalReg *DestLReg)
{
    LetSeq  *L=new LetSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LetBSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    return  Op1->LetBSeq(parent,FlagConnectedMode,Op2);
}

SeqLine *LetBSeq::MakeDup(LocalReg *DestLReg)
{
    LetBSeq  *L=new LetBSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  AddSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->AddSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *AddSeq::MakeDup(LocalReg *DestLReg)
{
    AddSeq  *L=new AddSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  SubSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->SubSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *SubSeq::MakeDup(LocalReg *DestLReg)
{
    SubSeq  *L=new SubSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  AndSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->AndSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *AndSeq::MakeDup(LocalReg *DestLReg)
{
    AndSeq  *L=new AndSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  OrSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->OrSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *OrSeq::MakeDup(LocalReg *DestLReg)
{
    OrSeq  *L=new OrSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  XorSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->XorSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *XorSeq::MakeDup(LocalReg *DestLReg)
{
    XorSeq  *L=new XorSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  NotSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->NotSeq(parent,FlagConnectedMode);
    return  r;
}

SeqLine *NotSeq::MakeDup(LocalReg *DestLReg)
{
    NotSeq  *L=new NotSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

bool  FlushSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->FlushSeq(parent,FlagConnectedMode);
    return  r;
}
SeqLine *FlushSeq::MakeDup(LocalReg *DestLReg)
{
    FlushSeq  *L=new FlushSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  AllocSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->AllocSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *AllocSeq::MakeDup(LocalReg *DestLReg)
{
    AllocSeq  *L=new AllocSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  IndSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->IndSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *IndSeq::MakeDup(LocalReg *DestLReg)
{
    IndSeq  *L=new IndSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  BitloadSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->BitloadSeq(parent,FlagConnectedMode,Op2,Op3,Op4);
    return  r;
}
SeqLine *BitloadSeq::MakeDup(LocalReg *DestLReg)
{
    BitloadSeq  *L=new BitloadSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  GotoSeq::Execute(Sequence *parent ,bool )
{
    int r=Op1->GetNumeric();
    if(parent!=NULL){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("Goto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *GotoSeq::MakeDup(LocalReg *DestLReg)
{
    GotoSeq  *L=new GotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  EqualGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->EqualSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("EqualGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *EqualGotoSeq::MakeDup(LocalReg *DestLReg)
{
    EqualGotoSeq  *L=new EqualGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  NotEqualGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->UnequalSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("NotEqualGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *NotEqualGotoSeq::MakeDup(LocalReg *DestLReg)
{
    NotEqualGotoSeq  *L=new NotEqualGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LargeGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->LargeSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("LargeGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *LargeGotoSeq::MakeDup(LocalReg *DestLReg)
{
    LargeGotoSeq  *L=new LargeGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  GreaterGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->GreaterSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("GreaterGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *GreaterGotoSeq::MakeDup(LocalReg *DestLReg)
{
    GreaterGotoSeq  *L=new GreaterGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  SmallGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->SmallSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("SmallGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *SmallGotoSeq::MakeDup(LocalReg *DestLReg)
{
    SmallGotoSeq  *L=new SmallGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LessGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->LessSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("LessGotgo Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *LessGotoSeq::MakeDup(LocalReg *DestLReg)
{
    LessGotoSeq  *L=new LessGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  AndGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->CAndSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("AndGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *AndGotoSeq::MakeDup(LocalReg *DestLReg)
{
    AndGotoSeq  *L=new AndGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  OrGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->COrSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("OrGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *OrGotoSeq::MakeDup(LocalReg *DestLReg)
{
    OrGotoSeq  *L=new OrGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  XorGotoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    Op1->CXorSeq(parent,FlagConnectedMode,Op2);
    int r=Op3->GetNumeric();
    if(parent!=NULL && parent->GetLatestFlag()==true){
        if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
            parent->SetNowLine(parent->GetSLineIndex(r));
        }
        else{
            parent->Add1NowLine();;
			QMessageBox Q( "Error"
				, QString("XorGoto Line adress is not found : ")+QString::number(r)
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            }
        }
    return  true;
}
SeqLine *XorGotoSeq::MakeDup(LocalReg *DestLReg)
{
    XorGotoSeq  *L=new XorGotoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  SetSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,true);
        parent->Add1NowLine();
    }
    return(true);
}
SeqLine *SetSeq::MakeDup(LocalReg *DestLReg)
{
    SetSeq  *L=new SetSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  ResetSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->Add1NowLine();
    }
    return(true);
}
SeqLine *ResetSeq::MakeDup(LocalReg *DestLReg)
{
    ResetSeq  *L=new ResetSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  ReturnSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    if(parent!=NULL){
        parent->SetFlag(FlagConnectedMode,false);
        parent->SetNowLine(parent->GetSLineNumb());
    }
    return(true);
}
SeqLine *ReturnSeq::MakeDup(LocalReg *DestLReg)
{
    ReturnSeq  *L=new ReturnSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  FlagSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->FlagSeq(parent,FlagConnectedMode);
    return  r;
}
SeqLine *FlagSeq::MakeDup(LocalReg *DestLReg)
{
    FlagSeq  *L=new FlagSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  CAndSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->CAndSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *CAndSeq::MakeDup(LocalReg *DestLReg)
{
    CAndSeq  *L=new CAndSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  COrSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->COrSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *COrSeq::MakeDup(LocalReg *DestLReg)
{
    COrSeq  *L=new COrSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  CXorSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->CXorSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *CXorSeq::MakeDup(LocalReg *DestLReg)
{
    CXorSeq  *L=new CXorSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  WaitSeq::Execute(Sequence *parent ,bool )
{
    if(parent!=NULL){
        if(parent->GetWaitMode()==false){
            parent->SetWaitStartTime(ThreadSequence::GetNowMiliSec());
            parent->SetWaitMode(true);
            }
        else{
            if(ThreadSequence::GetNowMiliSec() - parent->GetWaitStartTime()>=(DWORD)Op1->GetNumeric()){
                parent->Add1NowLine();;
                parent->SetWaitMode(false);
                }
            }
        }
    return  true;
}
SeqLine *WaitSeq::MakeDup(LocalReg *DestLReg)
{
    WaitSeq  *L=new WaitSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  EqualSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->EqualSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *EqualSeq::MakeDup(LocalReg *DestLReg)
{
    EqualSeq  *L=new EqualSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  ZoneSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->ZoneSeq(parent,FlagConnectedMode,Op2,Op3);
    return  r;
}
SeqLine *ZoneSeq::MakeDup(LocalReg *DestLReg)
{
    ZoneSeq  *L=new ZoneSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  PartEqSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->PartEqSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *PartEqSeq::MakeDup(LocalReg *DestLReg)
{
    PartEqSeq  *L=new PartEqSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  UnequalSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->UnequalSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *UnequalSeq::MakeDup(LocalReg *DestLReg)
{
    UnequalSeq  *L=new UnequalSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  GreaterSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->GreaterSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *GreaterSeq::MakeDup(LocalReg *DestLReg)
{
    GreaterSeq  *L=new GreaterSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LargeSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->LargeSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *LargeSeq::MakeDup(LocalReg *DestLReg)
{
    LargeSeq  *L=new LargeSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LessSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->LessSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *LessSeq::MakeDup(LocalReg *DestLReg)
{
    LessSeq  *L=new LessSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  SmallSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->SmallSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *SmallSeq::MakeDup(LocalReg *DestLReg)
{
    SmallSeq  *L=new SmallSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  MultSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->MultSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *MultSeq::MakeDup(LocalReg *DestLReg)
{
    MultSeq  *L=new MultSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  DivSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->DivSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *DivSeq::MakeDup(LocalReg *DestLReg)
{
    DivSeq  *L=new DivSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  ModSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->ModSeq(parent,FlagConnectedMode,Op2);
    return  r;
}

SeqLine *ModSeq::MakeDup(LocalReg *DestLReg)
{
    ModSeq  *L=new ModSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  MOutSeq::Execute(Sequence *parent ,bool )
{
	if(GetSeqControl()->OutSequenceMessageForm->OnAwake==false){
		QString	Q=Op1->GetString();
        GetSeqControl()->MessageOut(Q);
	}
    while(GetSeqControl()->OutSequenceMessageForm->OnAwake==false){
        ThreadSequence::MSleep(10);
        }

    while(GetSeqControl()->OutSequenceMessageForm->OnAwake==true){
        ThreadSequence::MSleep(10);
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return  true;
}

SeqLine *MOutSeq::MakeDup(LocalReg *DestLReg)
{
    MOutSeq  *L=new MOutSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  MYesNoSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
	if(GetSeqControl()->OutSequenceYesNoForm->OnAwake==false){
		QString	Q=Op1->GetString();
        GetSeqControl()->MessageYesNoOut(Q);
	}
    while(GetSeqControl()->OutSequenceYesNoForm->OnAwake==false){
        ThreadSequence::MSleep(10);
    }

    while(GetSeqControl()->OutSequenceYesNoForm->OnAwake==true){
        ThreadSequence::MSleep(10);
    }

    if(parent!=NULL){
        if(GetSeqControl()->OutSequenceYesNoForm->OKMode==true){
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
        }
        parent->Add1NowLine();
    }
    return  true;
}

SeqLine *MYesNoSeq::MakeDup(LocalReg *DestLReg)
{
    MYesNoSeq  *L=new MYesNoSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  ShowOnSeq::Execute(Sequence *parent ,bool )
{
	if(OpeNumb==1){
		QString	Q=Op1->GetString();
        GetSeqControl()->MessageShowOn(Q);
	}
    else if(OpeNumb==2){
		QString	Q=Op1->GetString();
        GetSeqControl()->MessageShowOn(Q ,Op2->GetNumeric(true));
	}
    else if(OpeNumb==3){
        QString	Q=Op1->GetString();
        GetSeqControl()->MessageShowOn(Q ,Op2->GetNumeric(true) ,Op3->GetID(),parent ,Op3->GetKindCode());
	}

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return  true;
}

SeqLine *ShowOnSeq::MakeDup(LocalReg *DestLReg)
{
    ShowOnSeq  *L=new ShowOnSeq(GetSeqControl());
    Copy(DestLReg,L);
    L->PageNumber  =PageNumber;
    L->RegNumber   =RegNumber;
    L->OpeNumb     =OpeNumb;
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  ShowOffSeq::Execute(Sequence *parent ,bool )
{
    GetSeqControl()->MessageShowOff();

    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return  true;
}
SeqLine *ShowOffSeq::MakeDup(LocalReg *DestLReg)
{
    ShowOffSeq  *L=new ShowOffSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  NopSeq::Execute(Sequence *parent ,bool )
{
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return  true;
}
SeqLine *NopSeq::MakeDup(LocalReg *DestLReg)
{
    NopSeq  *L=new NopSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  StrMoveSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->StrMoveSeq(parent,FlagConnectedMode,Op2,Op3);
    return  r;
}
SeqLine *StrMoveSeq::MakeDup(LocalReg *DestLReg)
{
    StrMoveSeq  *L=new StrMoveSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LowerSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->LowerSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *LowerSeq::MakeDup(LocalReg *DestLReg)
{
    LowerSeq  *L=new LowerSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  UpperSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->UpperSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *UpperSeq::MakeDup(LocalReg *DestLReg)
{
    UpperSeq  *L=new UpperSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  StateSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->StateSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *StateSeq::MakeDup(LocalReg *DestLReg)
{
    StateSeq  *L=new StateSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  TWSetSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->TWSetSeq(parent,FlagConnectedMode);
    return  r;
}

SeqLine *TWSetSeq::MakeDup(LocalReg *DestLReg)
{
    TWSetSeq  *L=new TWSetSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  TWaitLessSeq::Execute(Sequence *parent ,bool )
{
    int r=Op3->GetNumeric();
    if(parent!=NULL){
        DWORD   nowk=ThreadSequence::GetNowMiliSec();
        nowk-=Op1->GetNumeric();
        if(nowk<=(DWORD)Op2->GetNumeric()){
            if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
                parent->SetNowLine(parent->GetSLineIndex(r));
            }
            else{
	            parent->Add1NowLine();;
				QMessageBox Q( "Error"
					, QString("TWaitLess number is not found : ")+QString::number(r)
					, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
				Q.exec();
                }
            }
        else{
            parent->Add1NowLine();;
            }
        }
    return  true;
}
SeqLine *TWaitLessSeq::MakeDup(LocalReg *DestLReg)
{
    TWaitLessSeq  *L=new TWaitLessSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  TWaitGreaterSeq::Execute(Sequence *parent ,bool )
{
    int r=Op3->GetNumeric();
    if(parent!=NULL){
        DWORD   nowk=ThreadSequence::GetNowMiliSec();
        nowk-=Op1->GetNumeric();
        if(nowk>=Op2->GetNumeric()){
            if(r>=0 && r<parent->GetMaxLineNumb() && parent->GetSLineIndex(r)>=0){
                parent->SetNowLine(parent->GetSLineIndex(r));
            }
            else{
	            parent->Add1NowLine();;
				QMessageBox Q( "Error"
					, QString("TWaitGreater number is not found : ")+QString::number(r)
					, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
				Q.exec();
                }
            }
        else{
            parent->Add1NowLine();;
            }
        }
    return  true;
}
SeqLine *TWaitGreaterSeq::MakeDup(LocalReg *DestLReg)
{
    TWaitGreaterSeq  *L=new TWaitGreaterSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  FSetSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->FSetSeq(parent,FlagConnectedMode);
    return  r;
}

SeqLine *FSetSeq::MakeDup(LocalReg *DestLReg)
{
    FSetSeq  *L=new FSetSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  FResetSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->FResetSeq(parent,FlagConnectedMode);
    return  r;
}
SeqLine *FResetSeq::MakeDup(LocalReg *DestLReg)
{
    FResetSeq  *L=new FResetSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  RxTimeoutSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->RxTimeoutSeq(parent,FlagConnectedMode,Op2,Op3);
    return  r;
}

SeqLine *RxTimeoutSeq::MakeDup(LocalReg *DestLReg)
{
    RxTimeoutSeq  *L=new RxTimeoutSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  StrLenSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->StrLenSeq(parent,FlagConnectedMode,Op2);
    return  r;
}

SeqLine *StrLenSeq::MakeDup(LocalReg *DestLReg)
{
    StrLenSeq  *L=new StrLenSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  AddFileSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->AddFileSeq(parent,FlagConnectedMode,Op2);
    return  r;
}

SeqLine *AddFileSeq::MakeDup(LocalReg *DestLReg)
{
    AddFileSeq  *L=new AddFileSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  OpenLFileSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->OpenLFileSeq(parent,FlagConnectedMode,Op2);
    return  r;
}

SeqLine *OpenLFileSeq::MakeDup(LocalReg *DestLReg)
{
    OpenLFileSeq  *L=new OpenLFileSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  LoadFileSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->LoadFileSeq(parent,FlagConnectedMode,Op2);
    return  r;
}
SeqLine *LoadFileSeq::MakeDup(LocalReg *DestLReg)
{
    LoadFileSeq  *L=new LoadFileSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  CloseFileSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->CloseFileSeq(parent,FlagConnectedMode);
    return  r;
}

SeqLine *CloseFileSeq::MakeDup(LocalReg *DestLReg)
{
    CloseFileSeq  *L=new CloseFileSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  DeleteFileSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->DeleteFileSeq(parent,FlagConnectedMode);
    return  r;
}

SeqLine *DeleteFileSeq::MakeDup(LocalReg *DestLReg)
{
    DeleteFileSeq  *L=new DeleteFileSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  BPrintSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->BPrintSeq(parent,FlagConnectedMode,Op2);
    return  r;
}

SeqLine *BPrintSeq::MakeDup(LocalReg *DestLReg)
{
    BPrintSeq  *L=new BPrintSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  BScanSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->BScanSeq(parent,FlagConnectedMode,Op2);
    return  r;
}

SeqLine *BScanSeq::MakeDup(LocalReg *DestLReg)
{
    BScanSeq  *L=new BScanSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  SyncGetSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
/*↓D-20051026------------------------------------------------------------------
    if(parent!=NULL){
        LanvarOperand   *op2=dynamic_cast<LanvarOperand *>(Op2);
        if(op2==NULL)
            parent->Add1NowLine();
        else{
            if(op2->IsGetEnabled()==false)
                return(false);
            if(op2->ReqPreparedMode==false){
                op2->ReqPrepare();
                op2->ReqPreparedMode=true;
                }
            else{
                if(op2->ReqDone()==false)
                    return(false);
                CharOperand G;
                G.SetData((BYTE *)(op2->Data.c_str()),op2->Data.Length());
                Op1->LetSeq(parent,FlagConnectedMode ,&G);
                op2->ReqPreparedMode=false;
                return(true);
                }
            }
        }
↑D-20051026------------------------------------------------------------------*/
    return  true;
}

SeqLine *SyncGetSeq::MakeDup(LocalReg *DestLReg)
{
    SyncGetSeq  *L=new SyncGetSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  DLLCmdSeq::Execute(Sequence *SParent ,bool FlagConnectedMode)
{
    if(SParent!=NULL){
        DLLVarOperand   *DLLOp1=dynamic_cast<DLLVarOperand *>(Op1);
        if(DLLOp1!=NULL){
            bool    r;
            if(OpeNumb==1){
                r=DLLOp1->FDLLCmdSeq(SParent,FlagConnectedMode);
            }
            else
            if(OpeNumb==2){
                r=DLLOp1->FDLLCmdSeq(SParent,FlagConnectedMode ,Op2);
            }
            else
            if(OpeNumb==3){
                r=DLLOp1->FDLLCmdSeq(SParent,FlagConnectedMode ,Op2,Op3);
            }
            else
            if(OpeNumb==4){
                r=DLLOp1->FDLLCmdSeq(SParent,FlagConnectedMode ,Op2,Op3,Op4);
            }
            else
            if(OpeNumb==5){
                r=DLLOp1->FDLLCmdSeq(SParent,FlagConnectedMode ,Op2,Op3,Op4,Op5);
            }
            else
            if(OpeNumb==6){
                r=DLLOp1->FDLLCmdSeq(SParent,FlagConnectedMode ,Op2,Op3,Op4,Op5,Op6);
            }
			else{
				QMessageBox Q( "Error"
					, QString("No DLLVar instance or register : ")+QString::number(SParent->GetNowLine())
					, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
				Q.exec();
			}
        }
    }
    return  true;
}
SeqLine *DLLCmdSeq::MakeDup(LocalReg *DestLReg)
{
    DLLCmdSeq  *L=new DLLCmdSeq(GetSeqControl());
    Copy(DestLReg,L);
    L->OpeNumb=OpeNumb;
    return(L);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  MInputSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
	if(GetSeqControl()->OutSequenceInputForm->OnAwake==false){
		QString	Q1=Op1->GetString();
		QString	Q2=Op2->GetString();
        GetSeqControl()->MessageInputOut(Q1 ,Q2);
	}
    while(GetSeqControl()->OutSequenceInputForm->OnAwake==false){
        ThreadSequence::MSleep(10);
    }

    while(GetSeqControl()->OutSequenceInputForm->OnAwake==true){
        ThreadSequence::MSleep(10);
    }

    if(parent!=NULL){
        if(GetSeqControl()->OutSequenceInputForm->OKMode==true){
            Op1->InputFromString(parent ,GetSeqControl()->OutSequenceInputForm->Ret);
            parent->SetFlag(FlagConnectedMode,true);
        }
        else{
            parent->SetFlag(FlagConnectedMode,false);
            parent->Add1NowLine();
        }
    }

    return  true;
}

SeqLine *MInputSeq::MakeDup(LocalReg *DestLReg)
{
    MInputSeq  *L=new MInputSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  FloatNumSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    bool    r=Op1->FloatNumSeq(parent,FlagConnectedMode,Op2);
    return  r;
}

SeqLine *FloatNumSeq::MakeDup(LocalReg *DestLReg)
{
    FloatNumSeq  *L=new FloatNumSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  CallSeq::Execute(Sequence *parent ,bool )
{
    QString    fp=Op1->GetString();
    for(SequenceStock *s=GetSeqControl()->SeqStock.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->GetSType()!=SequenceStock::_Subroutine){
            continue;
        }
        if(s->GetName()==fp){
            Sequence    *q=new Sequence(GetSeqControl());
            q->LoadFromStock(s);
            if(parent!=NULL){
                parent->SubroutineCall=q;
                parent->NowOnSubroutine=true;
            }
            q->SubroutineParent=parent;
            q->Start();
            break;
            }
        }
    return(true);
}

SeqLine *CallSeq::MakeDup(LocalReg *DestLReg)
{
    CallSeq  *L=new CallSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    parent
//    flag
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool  MessageColorSeq::Execute(Sequence *parent ,bool FlagConnectedMode)
{
    if(Op1->IsGetEnabled()==true){
        //int r=Op1->GetNumeric(true);
///        GetSeqControl()->MessageCol=(TColor)r;	//D-20051026
        }
    if(parent!=NULL){
        parent->Add1NowLine();
    }
    return(true);
}

SeqLine *MessageColorSeq::MakeDup(LocalReg *DestLReg)
{
    MessageColorSeq  *L=new MessageColorSeq(GetSeqControl());
    Copy(DestLReg,L);
    return(L);
}

//==============================================================
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
SequenceStock::SequenceStock(SeqControl *baseParent)
:LoadedLocalReg(baseParent)
{
	BaseParent=baseParent;
    Cond=NULL;
    Name=/**/"";

    SLine		=NULL;
    SLineNumb	=0;
    SLineIndex	=NULL;
    MaxLineNumb	=0;
    stype		=_Main;
    GlanceTime	=0;
    SCode		=-1;          //シーケンス識別番号
}
Sequence::Sequence(SeqControl *baseParent)
:BaseParent(baseParent),LocalRegs(baseParent)
{
    NowLine=-1;
    LastExecuted=false;

    SLine=NULL;
    WaitMode=false;
    WaitStartTime=0;

    NowOnSubroutine			=false;
    SubroutineCall			=NULL;
    SubroutineParent		=NULL;
    ShouldDeleteSubroutine	=false;
	SPoint					=NULL;

    TimingDataI				=0;
    TimingDataF				=0;
    TimingDataB				=NULL;
    TimingDataBAllocedSize	=0;
    TimingDataLen			=0;
    TimingWriteMode			=false;
	TimingDataType			=0;

	StopExecute				=false;
    BreakPointNumb			=0;
    GoMode					=false;
    StepBreak				=false;
    StepBreakMode			=false;
    DebugMode				=false;
    IsDebugStopped			=false;
	for(int i=0;i<MaxBreakPoint;i++){
		BreakPoint[i]=-1;
	}
}

LocalReg::LocalReg(SeqControl *baseParent)
:BaseParent(baseParent)
{
    for(int i=0;i<MaxBitOperand;i++){
        LocalBitOperand  *d=new LocalBitOperand(BaseParent);
        d->SetID(i);
        LocalBitOpe.AppendList(d);
        }
    for(int i=0;i<MaxWordOperand;i++){
        LocalWordOperand  *d=new LocalWordOperand(BaseParent);
        d->SetID(i);
        LocalWordOpe.AppendList(d);
        }
    for(int i=0;i<MaxFloatOperand;i++){
        LocalFloatOperand  *d=new LocalFloatOperand(BaseParent);
        d->SetID(i);
        LocalFloatOpe.AppendList(d);
        }
    for(int i=0;i<MaxStringOperand;i++){
        LocalStringOperand  *d=new LocalStringOperand(BaseParent);
        d->SetID(i);
        LocalStringOpe.AppendList(d);
        }
}

int		Sequence::GetSLineIndex(int n)
{   
	if(0<=n && n<SPoint->MaxLineNumb){
		return(SPoint->SLineIndex[n]);
	}
	return -1;
}

SeqLine *Sequence::GetSLine(int n)
{
	if(0<=n && n<GetSLineNumb()){
		return(SLine[n]);
	}
	return NULL;
}


Operand *Sequence::SearchReg(QString regname)
{
    return(LocalRegs.SearchReg(regname));
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
SequenceStock::~SequenceStock(void)
{
    Clear();
}

Sequence::~Sequence(void)
{
    Clear();
    if(SLine!=NULL){
        for(int i=0;i<GetSLineNumb();i++){
            if(SLine[i]!=NULL){
                delete  SLine[i];
            }
        }
        delete  []SLine;
    }
    SLine=NULL;
}


FlagBase::FlagBase(void)
{
    Parent=NULL;
    ParentNumb=0;
    NegMode=false;
}

FlagBase::~FlagBase(void)
{
    for(int i=0;i<ParentNumb;i++){
        if(Parent[i]!=NULL){
            Parent[i]->SearchAndSetNull(this);
        }
    }
    if(Parent!=NULL){
        delete  []Parent;
    }
    Parent=NULL;

}

void    FlagBase::SetParent(FlagBase *parent)
{
    FlagBase    **B=new FlagBase *[ParentNumb+1];
    for(int i=0;i<ParentNumb;i++){
        B[i]=Parent[i];
        }
    B[ParentNumb]=parent;
    ParentNumb++;
    if(Parent!=NULL){
        delete  []Parent;
    }
    Parent=B;
}

void    FlagBase::ClearParent(void)
{
    if(Parent!=NULL){
        delete  []Parent;
    }
    Parent=NULL;
    ParentNumb=0;
}

void    FlagBase::Copy(FlagBase &src)
{
    if(Parent!=NULL){
        delete  []Parent;
    }
    Parent=NULL;
    ParentNumb=0;
    for(int i=0;i<src.ParentNumb;i++){
        SetParent(src.Parent[i]);
        }
}

void    FlagBase::SearchParentAndSetNull(FlagBase *parent)
{
    for(int i=0;i<ParentNumb;){
        if(Parent[i]==parent){
            if((i+1)<ParentNumb){
                memmove(Parent[i],Parent[i+1],(ParentNumb-i-1)*sizeof(Parent[0]));
            }
            ParentNumb--;
        }
        else{
            i++;
        }
    }
}

FlagOrNode::FlagOrNode(void)
{
    OrChildren=NULL;
    OrChildrenNumb=0;
    LogicConnection=false;
}
FlagOrNode::~FlagOrNode(void)
{
    for(int i=0;i<OrChildrenNumb;i++){
        if(OrChildren[i]!=NULL){
            OrChildren[i]->SearchParentAndSetNull(this);
            delete  OrChildren[i];
            }
        OrChildren[i]=NULL;
        }
    if(OrChildren!=NULL){
        delete  []OrChildren;
    }
    OrChildren=NULL;
    OrChildrenNumb=0;
}

QString  FlagOrNode::GetFlagString(void)
{
    if(LogicConnection==true){
        return("+");
    }
    if(OrChildrenNumb<0){
        return(/**/"");
    }
    if(OrChildrenNumb==1){
        return(OrChildren[0]->GetFlagString());
    }
    QString  ret;
    for(int i=0;i<OrChildrenNumb;i++){
        ret=ret+QString("(")
                +OrChildren[i]->GetFlagString()
                +QString(")");
        if(i<OrChildrenNumb-1){
            ret=ret+QString("|");
        }
    }
    return(ret);
}

bool        FlagOrNode::IsConnection(void)     //論理結合のときtrue
{
    return(LogicConnection);
}

int NewNumb=0;
int DelNumb=0;

FlagAnd::FlagAnd(void)
{
	Flag	=_Unconditional;
    Child	=NULL;
    NewNumb++;
}
FlagAnd::~FlagAnd(void)
{
    if(Child!=NULL){
        FlagBase    *R=Child;
        Child->SearchParentAndSetNull(this);
        delete  R;
        }
    Child=NULL;
    DelNumb++;
}


QString  FlagAnd::GetFlagString(void)
{
    QString  ret;
    switch(Flag){
        case _Unconditional:
            ret="N";
            break;
        case _ExeTrue:
            ret="T";
            break;
        case _ExeFalse:
            ret="F";
            break;
        }
    if(Child!=NULL){
        ret=ret+Child->GetFlagString();
    }
    return(ret);
}

void    FlagOrNode::SearchAndSetNull(FlagBase *child)
{
    for(int i=0;i<OrChildrenNumb;i++){
        if(OrChildren[i]==child){
            OrChildren[i]=NULL;
            return;
            }
        }
}

void    FlagAnd::SearchAndSetNull(FlagBase *child)
{
    if(Child==child){
        Child=NULL;
    }
}

void    FlagOrNode::AppendLastToEach(FlagBase *child)
{
    for(int i=0;i<OrChildrenNumb;i++){
        OrChildren[i]->AppendLastToEach(child);
        }
}
void    FlagAnd::AppendLastToEach(FlagBase *child)
{
    if(Child==NULL){
        AppendList(child);
    }
    else{
        Child->AppendLastToEach(child);
    }
}


void    FlagOrNode::AddChild(FlagBase *item)
{
    FlagBase **tmpOrChildren=new FlagBase *[OrChildrenNumb+1];

    for(int i=0;i<OrChildrenNumb;i++){
        tmpOrChildren[i]=OrChildren[i];
        OrChildren[i]=NULL;
        }
    if(OrChildren!=NULL){
        delete  []OrChildren;
    }
    OrChildren=tmpOrChildren;

    OrChildren[OrChildrenNumb]=item;
    item->SetParent(this);
    OrChildrenNumb++;
}

void    FlagAnd::AppendList(FlagBase *item)
{
    item->SetParent(this);
    Child=item;
}


QChar    *FlagAnd::Get(QChar *fp)
{
    if(*fp=='N' || *fp=='n'){
        Flag=_Unconditional;
    }
    else
    if(*fp=='F' || *fp=='f'){
        Flag=_ExeFalse;
    }
    else
    if(*fp=='T' || *fp=='t'){
        Flag=_ExeTrue;
    }
    return(fp+1);
}


bool    FlagOrNode::Compare(bool *Flag, int flagLen)
{
    if(GetNegMode()==true){
        for(int i=0;i<OrChildrenNumb;i++){
            if(OrChildren[i]->Compare(Flag, flagLen)==true){
                return(false);
                }
            }
        return(true);
        }
    else{
        for(int i=0;i<OrChildrenNumb;i++){
            if(OrChildren[i]->Compare(Flag, flagLen)==true){
                return(true);
                }
            }
        return(false);
        }
}

bool    FlagAnd::Compare(bool *flag, int flagLen)
{
    if(GetNegMode()==false){
        switch(Flag){
            case _Unconditional:
                if(Child!=NULL){
                    return(Child->Compare(&flag[1], flagLen-1));
                }
                else{
                    return(true);
                }
            case _ExeTrue:
                if(flagLen<=0){
                    return(false);
                }
                if(flag[0]==true){
                    if(Child!=NULL){
                        return(Child->Compare(&flag[1], flagLen-1));
                    }
                    else
                    if(flagLen==1){
                        return(true);
                    }
                    else{
                        return(false);
                    }
                }
                else{
                    return(false);
                }
            case _ExeFalse:
                if(flagLen<=0){
                    return(false);
                }
                if(flag[0]==false){
                    if(Child!=NULL){
                        return(Child->Compare(&flag[1], flagLen-1));
                    }
                    else
                    if(flagLen==1){
                        return(true);
                    }
                    else{
                        return(false);
                    }
                }
                else{
                    return(false);
                }
            }
        }
    else{
        switch(Flag){
            case _Unconditional:
                return(true);
            case _ExeTrue:
                if(flagLen<=0){
                    return(false);
                }
                if(flag[0]==false){
                    if(Child!=NULL){
                        return(Child->Compare(&flag[1], flagLen-1));
                    }
                    else{
                        return(true);
                    }
                }
                else{
                    return(false);
                }
            case _ExeFalse:
                if(flagLen<=0){
                    return(false);
                }
                if(flag[0]==true){
                    if(Child!=NULL){
                        return(Child->Compare(&flag[1], flagLen-1));
                    }
                    else{
                        return(true);
                    }
                }
                else{
                    return(false);
                }
            }
        }
    return(true);
}

FlagOrNode  &FlagOrNode::operator=(FlagOrNode &src)
{
	if(this!=&src){
	    Copy(src);
		SetNegMode(src.GetNegMode());

	    if(OrChildren!=NULL){
		    for(int i=0;i<OrChildrenNumb;i++){
			    delete  OrChildren[i];
			}
		}
	    OrChildrenNumb=0;
		OrChildren=NULL;
	    LogicConnection=src.LogicConnection;

	    for(int i=0;i<src.OrChildrenNumb;i++){
		    FlagBase *c=src.OrChildren[i];
			FlagAnd     *s1=dynamic_cast<FlagAnd *>(c);
	        FlagOrNode  *s2=dynamic_cast<FlagOrNode *>(c);
		    if(s1!=NULL){
			    FlagAnd *d=new FlagAnd();
				*d=*s1;
	            d->ClearParent();
		        AddChild(d);
            }
	        else if(s2!=NULL){
		        FlagOrNode *d=new FlagOrNode();
			    *d=*s2;
				d->ClearParent();
	            AddChild(d);
            }
        }
	}
    return(*this);
}
FlagAnd &FlagAnd::operator=(FlagAnd &src)
{
    Copy(src);
    SetNegMode(src.GetNegMode());

    Flag=src.Flag;
    if(Child!=NULL)
        delete  Child;
    if(src.Child!=NULL){
        FlagAnd     *s1=dynamic_cast<FlagAnd *>(src.Child);
        FlagOrNode  *s2=dynamic_cast<FlagOrNode *>(src.Child);
        if(s1!=NULL){
            FlagAnd *d=new FlagAnd();
            *d=*s1;
            d->ClearParent();
            AppendList(d);
            }
        else if(s2!=NULL){
            FlagOrNode *d=new FlagOrNode();
            *d=*s2;
            d->ClearParent();
            AppendList(d);
            }
        }
    return(*this);
}

int     FlagOrNode::GetLen(void)
{
    int K=0;
    for(int i=0;i<OrChildrenNumb;i++){
        int L=OrChildren[i]->GetLen();
        if(L>K){
            K=L;
        }
    }
    return(K);
}

int     FlagAnd::GetLen(void)
{
    if(Child!=NULL){
        return(Child->GetLen()+1);
    }
    return(1);
}

TmpLoadFlags::TmpLoadFlags(void)
{
    FlagSign=/**/"";
    AllocNumb=0;
    Items   =NULL;
    Kind    =__FFNone;
}
TmpLoadFlags::~TmpLoadFlags(void)
{
    FlagSign=/**/"";

    if(Items!=NULL){
        delete  Items;
    }
    Items=NULL;
}

void    TmpLoadFlags::AddSign(QString c)
{
    FlagSign+=c;
}
void    TmpLoadFlags::MakeFlagSignItem(void)
{
    FlagAnd *LastC=NULL;
    for(QChar *fp=FlagSign.data();*fp!=0;fp++){
        FlagAnd *c=new FlagAnd();
        c->Get(fp);
        if(Items==NULL){
            Items=c;
        }
        else{
            LastC->AppendList(c);
        }
        LastC=c;
    }
}

void    FlagOrNode::Balansize(void)    //不要なツリーを排除する
{
    StartB:;
    for(int i=0;i<OrChildrenNumb;i++){
        FlagOrNode  *d=dynamic_cast<FlagOrNode *>(OrChildren[i]);
        if(d!=NULL){
            FlagBase **tmpOrChildren=new FlagBase *[OrChildrenNumb-1+d->GetOrNumb()];
            int j,m=0;
            for(j=0;j<i;j++,m++){
                tmpOrChildren[j]=OrChildren[m];
                OrChildren[m]=NULL;
                }
            for(int k=0;k<d->GetOrNumb();k++,j++){
                tmpOrChildren[j]=d->OrChildren[k];
                d->OrChildren[k]=NULL;
                }
            for(;m<OrChildrenNumb;m++){
                tmpOrChildren[j]=OrChildren[m];
                OrChildren[m]=NULL;
                }

            OrChildrenNumb=OrChildrenNumb-1+d->GetOrNumb();
            delete  d;

            delete  []OrChildren;
            OrChildren=tmpOrChildren;
            goto    StartB;
            }
        }
    for(int i=0;i<OrChildrenNumb;i++){
        OrChildren[i]->Balansize();
        }
}

void    FlagAnd::Balansize(void)    //不要なツリーを排除する
{
    if(Child!=NULL){
        Child->Balansize();
    }
}

char    *SequenceStock::LoadFlag(FlagOrNode *eFlag,char *fp)
{
    char *gp=fp;
    int N=0;
    if(*fp=='+'){
        eFlag->SetLogicConnectionTrue();
        return(fp+1);
        }
    for(;;){
        if(strchr("NTFntf()|!",*gp)!=NULL){
            N++;
            gp++;
            }
        else
        if(*gp==' ' || *gp=='\t'){
            gp++;
        }
        else{
            break;
        }
    }
    TmpLoadFlags    *tmpFlagData=new TmpLoadFlags[N];
    TmpLoadFlags    **tmpFlagDataIndex=new TmpLoadFlags*[N];

    int DIndex=0;
    int KKNestLevel=0;
    for(;;){
        if(strchr("NTFntf",*fp)!=NULL){
			QString	Q=QString(*fp);
            tmpFlagData[DIndex].AddSign(Q);
            tmpFlagData[DIndex].Kind=TmpLoadFlags::__FlagSign;
            fp++;
            while(strchr("NTFntf",*fp)!=NULL){
				QString	Qx=QString(*fp);
                tmpFlagData[DIndex].AddSign(Qx);
                fp++;
                }
            DIndex++;
            }
        else
        if(*fp=='('){
            tmpFlagData[DIndex].Kind=TmpLoadFlags::__StartKK;
            fp++;
            KKNestLevel++;
            DIndex++;
            }
        else
        if(*fp==')'){
            tmpFlagData[DIndex].Kind=TmpLoadFlags::__EndKK;
            fp++;
            KKNestLevel--;
            DIndex++;
            }
        else
        if(*fp=='|'){
            tmpFlagData[DIndex].Kind=TmpLoadFlags::__OrKK;
            fp++;
            DIndex++;
            }
        else
        if(*fp=='!'){
            tmpFlagData[DIndex].Kind=TmpLoadFlags::__NegSign;
            fp++;
            DIndex++;
            }
        else
        if(*fp==' ' || *fp=='\t'){
            if(KKNestLevel==0){
                break;
            }
            fp++;
            DIndex++;
        }
        else{
            break;
        }
    }
    for(int i=0;i<DIndex;i++){
        tmpFlagDataIndex[i]=&tmpFlagData[i];
        if(tmpFlagData[i].Kind==TmpLoadFlags::__FlagSign){
            tmpFlagData[i].MakeFlagSignItem();
        }
    }
    bool    CFlag;
    do{
        CFlag=false;
        //A|Bをまとめる
        for(int i=0;i<DIndex-2;){
            if(tmpFlagDataIndex[i]->Kind==TmpLoadFlags::__FlagSign
            && tmpFlagDataIndex[i+1]->Kind==TmpLoadFlags::__OrKK
            && tmpFlagDataIndex[i+2]->Kind==TmpLoadFlags::__FlagSign){
                FlagOrNode  *t=new FlagOrNode();
                t->AddChild(tmpFlagDataIndex[i]->Items);
                t->AddChild(tmpFlagDataIndex[i+2]->Items);
                tmpFlagDataIndex[i]->Items=t;
                tmpFlagDataIndex[i+1]->Items=NULL;
                tmpFlagDataIndex[i+2]->Items=NULL;
                memmove(&tmpFlagDataIndex[i+1],&tmpFlagDataIndex[i+3],(DIndex-i-3)*sizeof(tmpFlagDataIndex[0]));
                DIndex-=2;
                CFlag=true;
                }
            else{
                i++;
            }
        }
        //(A)をまとめる
        for(int i=0;i<DIndex-2;){
            if(tmpFlagDataIndex[i]->Kind==TmpLoadFlags::__StartKK
            && tmpFlagDataIndex[i+1]->Kind==TmpLoadFlags::__FlagSign
            && tmpFlagDataIndex[i+2]->Kind==TmpLoadFlags::__EndKK){
                tmpFlagDataIndex[i]->Items=tmpFlagDataIndex[i+1]->Items;
                tmpFlagDataIndex[i]->Kind=TmpLoadFlags::__FlagSign;
                tmpFlagDataIndex[i+1]->Items=NULL;
                tmpFlagDataIndex[i+2]->Items=NULL;
                memmove(&tmpFlagDataIndex[i+1],&tmpFlagDataIndex[i+3],(DIndex-i-3)*sizeof(tmpFlagDataIndex[0]));
                DIndex-=2;
                CFlag=true;
                }
            else{
                i++;
            }
        }
        //!Aをまとめる
        for(int i=0;i<DIndex-1;){
            if(tmpFlagDataIndex[i  ]->Kind==TmpLoadFlags::__NegSign
            && tmpFlagDataIndex[i+1]->Kind==TmpLoadFlags::__FlagSign){
                tmpFlagDataIndex[i]->Items=tmpFlagDataIndex[i+1]->Items;
                tmpFlagDataIndex[i]->Items->SetNegMode(true);
                tmpFlagDataIndex[i]->Kind=TmpLoadFlags::__FlagSign;
                tmpFlagDataIndex[i+1]->Items=NULL;
                memmove(&tmpFlagDataIndex[i+1],&tmpFlagDataIndex[i+2],(DIndex-i-2)*sizeof(tmpFlagDataIndex[0]));
                DIndex--;
                CFlag=true;
                }
            else{
                i++;
            }
        }
        //ABをまとめる
        for(int i=0;i<DIndex-1;){
            if(tmpFlagDataIndex[i  ]->Kind==TmpLoadFlags::__FlagSign
            && tmpFlagDataIndex[i+1]->Kind==TmpLoadFlags::__FlagSign){
                tmpFlagDataIndex[i]->Items->AppendLastToEach(tmpFlagDataIndex[i+1]->Items);
                tmpFlagDataIndex[i+1]->Items=NULL;
                memmove(&tmpFlagDataIndex[i+1],&tmpFlagDataIndex[i+2],(DIndex-i-2)*sizeof(tmpFlagDataIndex[0]));
                DIndex--;
                CFlag=true;
                }
            else{
                i++;
            }
        }
    }while(DIndex>1 && CFlag==true);
    if(DIndex!=1){
        delete  []tmpFlagDataIndex;
        delete  []tmpFlagData;
        return NULL;
        }
    FlagOrNode *ps;
    if((ps=dynamic_cast<FlagOrNode *>(tmpFlagDataIndex[0]->Items))!=NULL){
        *eFlag=*ps;
        }
    else{
        eFlag->AddChild(tmpFlagDataIndex[0]->Items);
        tmpFlagDataIndex[0]->Items=NULL;
        }
    eFlag->Balansize();
    delete  []tmpFlagDataIndex;
    delete  []tmpFlagData;
    return fp;
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    fp
//    file
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
volatile    bool    SequenceStock::Load(char *fp ,QFile &file)
{
    char    nbuff[100];
    char    *hp;

    fp+=strlen("#sequence");
    fp=GetTopString(fp);
    fp=GetWordCut(fp,nbuff);
    if(fp==NULL){
        return(false);
    }
    Name=QString(nbuff);

    fp=GetTopString(fp);
    if(*fp!=':'){
        return(false);
    }
    fp++;

    char    n1[20];

    if((fp=GetWordCut(fp,n1))==NULL){
        return(false);
    }
    fp=GetTopString(fp);
    if(strnicmp(n1,"Main",4)==0){
        if(*fp!='{'){
            return(false);
        }
        stype=_Main;
        }
    else if(strnicmp(n1,"Glance",6)==0){
        if(*fp!='{'){
            return(false);
        }
        stype=_Glance;
        }
    else if(strnicmp(n1,"Watch",5)==0){
        if(*fp!='{'){
            return(false);
        }
        stype=_Watch;
        }
    else if(strnicmp(n1,"Begin",5)==0){
        if(*fp!='{'){
            return(false);
        }
        stype=_Begin;
        }
    else if(strnicmp(n1,"End",3)==0){
        if(*fp!='{'){
            return(false);
        }
        stype=_End;
        }
    else if(strnicmp(n1,"Subroutine",10)==0){
        if(*fp!='{'){
            return(false);
        }
        stype=_Subroutine;
        }
    else if(strnicmp(n1,"Condition",9)==0){
        Operand *ope1=NULL;
        if((fp=LoadOpe(NULL,fp,&ope1))==NULL){
            return(false);
        }
        fp=GetTopString(fp);
        if(*fp!='='){
            return(false);
        }
        fp++;
        fp=GetTopString(fp);
        Operand *ope2=NULL;
        if((fp=LoadOpe(NULL,fp,&ope2))==NULL){
            return(false);
        }
        fp=GetTopString(fp);
        if(*fp!='{'){
            return(false);
        }
        Cond=new EqualSeq(GetSeqControl());
        Cond->LNumber=0;
        Cond->Op1=ope1;
        Cond->Op2=ope2;
        stype=_Condition;
        }
    else if(strnicmp(n1,"Immidiate",9)==0){
        Operand *ope1=NULL;
        if((fp=LoadOpe(NULL,fp,&ope1))==NULL){
            return(false);
        }
        fp=GetTopString(fp);
        if(*fp!='='){
            return(false);
        }
        fp++;
        fp=GetTopString(fp);
        Operand *ope2=NULL;
        if((fp=LoadOpe(NULL,fp,&ope2))==NULL){
            return(false);
        }
        fp=GetTopString(fp);
        if(*fp!='{'){
            return(false);
        }
        Cond=new EqualSeq(GetSeqControl());
        Cond->LNumber=0;
        Cond->Op1=ope1;
        Cond->Op2=ope2;
        stype=_Immidiate;
        }
    else if(strnicmp(n1,"Event",5)==0){
        Operand *ope1=NULL;
        if((fp=LoadOpe(NULL,fp,&ope1))==NULL){
            return(false);
        }
        CommandName=ope1->GetName();
        fp=GetTopString(fp);
        if(*fp!='{'){
            return(false);
        }
        stype=_Event;
    }
    else{
        return(false);
    }

    char    Buff[2560];
    NPListPack<SeqLine> TmpSeq;

	while(file.readLine(Buff,sizeof(Buff))!=-1){
        GetSeqControl()->ErrorLine=Buff;
        fp=Buff;
        if((hp=strstr(fp,"//"))!=NULL){
            *hp=0;
        }
        fp=GetTopString(fp);
        if(*fp=='}'){
            break;
        }
        if(*fp==0 || *fp=='\n'){
            continue;
        }
        char    n1[20];
        char    n3[20];
        int L=-1;
        ExecuteCondition   cond=_Unconditional;
        FlagOrNode  tmpFlag;
        char    *gp=fp;

		gp=GetWordCut(fp,n1);
		bool ok;
		L=QString(n1).toInt(&ok);
		if(ok==false){
            L=-1;
        }

        if(gp!=NULL && L!=-1){
            fp=GetTopString(gp);
            if(*fp!=':'){
                return(false);
            }
            fp++;
            fp=GetTopString(fp);
            if(*fp==0 || *fp=='\n'){
                SeqLine *s=new NopSeq(GetSeqControl());
                s->Set(L,cond);
                LoadFlag(&tmpFlag,(char *)"N ");
                s->eFlag=tmpFlag;
                TmpSeq.AppendList(s);
                continue;
                }
            }
        fp=LoadFlag(&tmpFlag,fp);
        if(fp==NULL){
            return(false);
        }


        fp=GetTopString(fp);
        if(*fp==0 || *fp=='\n'){
            return(false);
        }
        if((fp=GetWordCut(fp,n3))==NULL){
            return(false);
        }
        fp=GetTopString(fp);
        SeqLine *s=NULL;
        Operand *ope1;
        Operand *ope2;
        Operand *ope3;
        Operand *ope4;
		Operand *ope5;
		Operand *ope6;
        if(stricmp(n3,"LetB")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new LetBSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
            }
        else if(stricmp(n3,"Let")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new LetSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Add")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new AddSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Sub")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new SubSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
            }
        else if(stricmp(n3,"And")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new AndSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
            }
        else if(stricmp(n3,"Or")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new OrSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Xor")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new XorSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Not")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new NotSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"Flush")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new FlushSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"Alloc")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new AllocSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Ind")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new IndSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Bitload")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope4))==NULL){
                return(false);
            }
            s=new BitloadSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3,ope4);
        }
        else if(stricmp(n3,"Goto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new GotoSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"EqualGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new EqualGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"NotEqualGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new NotEqualGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"LargeGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new LargeGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"GreaterGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new GreaterGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"SmallGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new SmallGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"LessGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new LessGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"AndGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new AndGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"OrGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new OrGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"XorGoto")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new XorGotoSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"Set")==0){
            s=new SetSeq(GetSeqControl());
            s->Set(L,cond);
            }
        else if(stricmp(n3,"Reset")==0){
            s=new ResetSeq(GetSeqControl());
            s->Set(L,cond);
            }
        else if(stricmp(n3,"Return")==0){
            s=new ReturnSeq(GetSeqControl());
            s->Set(L,cond);
            }
        else if(stricmp(n3,"Flag")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new FlagSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"CAnd")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new CAndSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"COr")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new COrSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"CXor")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new CXorSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Wait")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new WaitSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"Equal")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new EqualSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Zone")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new ZoneSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"PartEq")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new PartEqSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Unequal")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new UnequalSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Greater")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new GreaterSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Large")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new LargeSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Less")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new LessSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Small")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new SmallSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"MOut")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new MOutSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"MYesNo")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new MYesNoSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"Mul")==0 || stricmp(n3,"Mult")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new MultSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Div")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new DivSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Mod")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new ModSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"StrMove")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new StrMoveSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"Lower")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new LowerSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Upper")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new UpperSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"State")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new StateSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"TWSet")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new TWSetSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"TWaitLess")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new TWaitLessSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"TWaitGreater")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new TWaitGreaterSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"FSet")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new FSetSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"FReset")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new FResetSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"RxTimeout")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                return(false);
            }
            s=new RxTimeoutSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2,ope3);
        }
        else if(stricmp(n3,"StrLen")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new StrLenSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"AddFile")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new AddFileSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"OpenLFile")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new OpenLFileSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"LoadFile")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new LoadFileSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"CloseFile")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new CloseFileSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"DeleteFile")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new DeleteFileSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else if(stricmp(n3,"BPrint")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new BPrintSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"BScan")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new BScanSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"SyncGet")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new SyncGetSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"DLLCmd")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp==','){
                fp++;
                if(*fp==0 || *fp=='\n'){
                    return(false);
                }
                if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                    return(false);
                }

                fp=GetTopString(fp);
                if(*fp==','){
                    fp++;
                    if(*fp==0 || *fp=='\n'){
                        return(false);
                    }
                    if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                        return(false);
                    }

                    fp=GetTopString(fp);
                    if(*fp==','){
                        fp++;
                        if(*fp==0 || *fp=='\n'){
                            return(false);
                        }
                        if((fp=LoadOpe(this ,fp,&ope4))==NULL){
                            return(false);
                        }

	                    fp=GetTopString(fp);
		                if(*fp==','){
			                fp++;
				            if(*fp==0 || *fp=='\n'){
					            return(false);
                            }
						    if((fp=LoadOpe(this ,fp,&ope5))==NULL){
							    return(false);
                            }

		                    fp=GetTopString(fp);
			                if(*fp==','){
				                fp++;
					            if(*fp==0 || *fp=='\n'){
						            return(false);
                                }
							    if((fp=LoadOpe(this ,fp,&ope6))==NULL){
								    return(false);
                                }
								DLLCmdSeq  *dllv=new DLLCmdSeq(GetSeqControl());
			                    s=dllv;
				                s->Set(L,cond,ope1,ope2,ope3,ope4,ope5,ope6);
					            dllv->OpeNumb=6;
							}
							else{
								DLLCmdSeq  *dllv=new DLLCmdSeq(GetSeqControl());
			                    s=dllv;
				                s->Set(L,cond,ope1,ope2,ope3,ope4,ope5);
					            dllv->OpeNumb=5;
							}
						}
						else{
							DLLCmdSeq  *dllv=new DLLCmdSeq(GetSeqControl());
		                    s=dllv;
			                s->Set(L,cond,ope1,ope2,ope3,ope4);
				            dllv->OpeNumb=4;
						}
                    }
                    else{
                        DLLCmdSeq  *dllv=new DLLCmdSeq(GetSeqControl());
                        s=dllv;
                        s->Set(L,cond,ope1,ope2,ope3);
                        dllv->OpeNumb=3;
                    }
                }
                else{
                    DLLCmdSeq  *dllv=new DLLCmdSeq(GetSeqControl());
                    s=dllv;
                    s->Set(L,cond,ope1,ope2);
                    dllv->OpeNumb=2;
                    }
            }
            else{
                DLLCmdSeq  *dllv=new DLLCmdSeq(GetSeqControl());
                s=dllv;
                s->Set(L,cond,ope1);
                dllv->OpeNumb=1;
            }
        }
        else if(stricmp(n3,"ShowOn")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            ShowOnSeq   *Dss=new ShowOnSeq(GetSeqControl());
            s=Dss;
            if(*fp==','){
                fp++;
                if(*fp==0 || *fp=='\n'){
                    return(false);
                }
                if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                    return(false);
                }
                fp=GetTopString(fp);
                if(*fp==','){
                    fp++;
                    if(*fp==0 || *fp=='\n'){
                        return(false);
                    }
                    if((fp=LoadOpe(this ,fp,&ope3))==NULL){
                        return(false);
                    }

                    s->Set(L,cond,ope1,ope2,ope3);
                    Dss->OpeNumb=3;
                    }
                else{
                    s->Set(L,cond,ope1,ope2);
                    Dss->OpeNumb=2;
                    }
                }
            else{
                s->Set(L,cond,ope1);
                Dss->OpeNumb=1;
                }
            }
        else if(stricmp(n3,"ShowOff")==0){
            s=new ShowOffSeq(GetSeqControl());
            s->Set(L,cond);
            }
        else if(stricmp(n3,"MessageColor")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new MessageColorSeq(GetSeqControl());
            s->Set(L,cond,ope1);
            }
        else if(stricmp(n3,"Nop")==0){
            s=new NopSeq(GetSeqControl());
            s->Set(L,cond);
            }
        else if(stricmp(n3,"MInput")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new MInputSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
            }
        else if(stricmp(n3,"FloatNum")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=','){
                return(false);
            }
            fp++;
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope2))==NULL){
                return(false);
            }
            s=new FloatNumSeq(GetSeqControl());
            s->Set(L,cond,ope1,ope2);
        }
        else if(stricmp(n3,"Call")==0){
            if(*fp==0 || *fp=='\n'){
                return(false);
            }
            if((fp=LoadOpe(this ,fp,&ope1))==NULL){
                return(false);
            }
            s=new CallSeq(GetSeqControl());
            s->Set(L,cond,ope1);
        }
        else
        if(s==NULL){
            return(false);
        }

        s->eFlag=tmpFlag;
        TmpSeq.AppendList(s);
    }
    if(SLine!=NULL){
        for(int i=0;i<SLineNumb;i++){
            if(SLine[i]!=NULL){
                delete  SLine[i];
            }
        }
        delete  []SLine;
    }
    SLine=new SeqLine*[TmpSeq.GetNumber()];
    SLineNumb=0;
    SeqLine *s;
    while((s=TmpSeq.GetFirst())!=NULL){
        TmpSeq.RemoveList(s);
        s->LCode=SLineNumb;
        SLine[SLineNumb]=s;
        SLineNumb++;
        }
    MaxLineNumb=0;
    if(SLineIndex!=NULL){
        delete  []SLineIndex;
    }
    for(int i=0;i<SLineNumb;i++){
        if(SLine[i]->LNumber>MaxLineNumb){
            MaxLineNumb=SLine[i]->LNumber;
        }
    }
    MaxLineNumb++;
    SLineIndex=new int[MaxLineNumb];
    for(int i=0;i<MaxLineNumb;i++){
        SLineIndex[i]=-1;
        }
    for(int i=0;i<SLineNumb;i++){
        if(SLine[i]->LNumber>=0){
            SLineIndex[SLine[i]->LNumber]=i;
        }
    }
    int LastLNumber=-1;
    for(int i=0;i<SLineNumb-1;i++){
        if(SLine[i]->LNumber>=0 && SLine[i]->LNumber<=LastLNumber){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" is duplicated or downward")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        if(SLine[i]->LNumber>=0){
            LastLNumber=SLine[i]->LNumber;
        }
    }
    for(int i=0;i<SLineNumb;i++){
        GotoSeq *a=dynamic_cast<GotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op1==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op1);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No GOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        EqualGotoSeq *a=dynamic_cast<EqualGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No EQUALGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        NotEqualGotoSeq *a=dynamic_cast<NotEqualGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No NOTEQUALGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        LargeGotoSeq *a=dynamic_cast<LargeGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No LARGEGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        GreaterGotoSeq *a=dynamic_cast<GreaterGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No GREATERGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        SmallGotoSeq *a=dynamic_cast<SmallGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No SMALLGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        LessGotoSeq *a=dynamic_cast<LessGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No LESSGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        AndGotoSeq *a=dynamic_cast<AndGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No ANDGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        OrGotoSeq *a=dynamic_cast<OrGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No ORGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        XorGotoSeq *a=dynamic_cast<XorGotoSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" has No XORGOTO address line")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        TWaitLessSeq *a=dynamic_cast<TWaitLessSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op1==NULL || a->Op2==NULL || a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" TWaitLess (")+QString::number(d)+QString(") doesn't exist")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    for(int i=0;i<SLineNumb;i++){
        TWaitGreaterSeq *a=dynamic_cast<TWaitGreaterSeq *>(SLine[i]);
        if(a==NULL){
            continue;
        }
        if(a->Op1==NULL || a->Op2==NULL || a->Op3==NULL){
            continue;
        }
        NumberOperand   *b=dynamic_cast<NumberOperand *>(a->Op3);
        if(b==NULL){
            continue;
        }
        int d=b->GetNumeric();
        int j;
        for(j=0;j<SLineNumb;j++){
            if(SLine[j]->LNumber==d){
                break;
            }
        }
        if(j>=SLineNumb || d<0){
			QMessageBox Q( "Error"
				, QString("Line:")+QString::number(SLine[i]->LNumber)+QString(" TWaitGreater (")+QString::number(d)+QString(") doesn't exist")
				, QMessageBox::Critical
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
            break;
            }
        }
    return(true);
}

bool    SeqControl::CheckCall(void)
{
    for(SequenceStock *s=SeqStock.GetFirst();s!=NULL;s=s->GetNext()){
        for(int i=0;i<s->GetSLineNumb();i++){
            CallSeq *a=dynamic_cast<CallSeq *>(s->GetSLine(i));
            if(a==NULL){
                continue;
            }
            if(a->Op1==NULL){
                continue;
            }
            CharOperand   *c=dynamic_cast<CharOperand *>(a->Op1);
            if(c==NULL){
                continue;
            }
            QString d=c->GetString();

            SequenceStock *t;
            for(t=SeqStock.GetFirst();t!=NULL;t=t->GetNext()){
                if(QString(t->GetName())==d){
                    break;
                }
            }
            if(t==NULL){
				QMessageBox Q( "Error"
					, QString("Line : ")+QString::number(s->GetSLine(i)->LNumber)+QString(" Call line address(")+d+QString(") doesn't exist")
					, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
				Q.exec();
				return(false);
                }
            }
        }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    fp
//    ope
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
char    *SequenceStock::LoadOpe(SequenceStock *seq ,char *fp ,Operand **ope)
{
    fp=GetTopString(fp);
    for(IOOperand *c=GetSeqControl()->IOOpe.GetFirst();c!=NULL;c=c->GetNext()){
        int len=c->Name.length();
///        if(strnicmp(fp,c->Name,len)==0
		if(QString::compare(QString(fp).left(len).toLower(),c->Name.toLower())==0
        && (strchr(Dellimiter ,*(fp+len))!=0 || *(fp+len)==0)){
            *ope=c;
            fp+=len;
            fp=GetTopString(fp);
            return(fp);
            }
        }
    for(CommOperand *c=GetSeqControl()->CommOpe.GetFirst();c!=NULL;c=c->GetNext()){
		int len=c->Name.length();
        if(QString::compare(QString(fp).left(len).toLower(),c->Name.toLower())==0
        && (strchr(Dellimiter ,*(fp+len))!=0 || *(fp+len)==0)){
            *ope=c;
            fp+=len;
            fp=GetTopString(fp);
            return(fp);
            }
        }
    for(GroupOperand *c=GetSeqControl()->GroupOpe.GetFirst();c!=NULL;c=c->GetNext()){
		int len=c->Name.length();
        if(QString::compare(QString(fp).left(len).toLower(),c->Name.toLower())==0
        && (strchr(Dellimiter ,*(fp+len))!=0 || *(fp+len)==0)){
            *ope=c;
            fp+=len;
            fp=GetTopString(fp);
            return(fp);
            }
        }
/*↓D-20051026------------------------------------------------------------------
    for(LanvarOperand *c=GetSeqControl()->LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
        int len=strlen(c->Name);
        if(strnicmp(fp,c->Name,len)==0
        && (strchr(Dellimiter ,*(fp+len))!=0 || *(fp+len)==0)){
            *ope=c;
            fp+=len;
            fp=GetTopString(fp);
            return(fp);
            }
        }
↑D-20051026------------------------------------------------------------------*/
    for(FifoOperand *c=GetSeqControl()->FifoOpe.GetFirst();c!=NULL;c=c->GetNext()){
		int len=c->Name.length();
        if(QString::compare(QString(fp).left(len).toLower(),c->Name.toLower())==0
        && (strchr(Dellimiter ,*(fp+len))!=0 || *(fp+len)==0)){
            *ope=c;
            fp+=len;
            fp=GetTopString(fp);
            return(fp);
            }
        }
    for(DLLVarOperand *c=GetSeqControl()->DLLVarOpe.GetFirst();c!=NULL;c=c->GetNext()){
		int len=c->Name.length();
        if(QString::compare(QString(fp).left(len).toLower(),c->Name.toLower())==0
        && (strchr(Dellimiter ,*(fp+len))!=0 || *(fp+len)==0)){
            *ope=c;
            fp+=len;
            fp=GetTopString(fp);
            return(fp);
            }
        }
    int N;
    char    *hp;
    if((*fp=='B' || *fp=='b')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(BitOperand *c=GetSeqControl()->BitOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }

    if((*fp=='W' || *fp=='w')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(WordOperand *c=GetSeqControl()->WordOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }
    if((*fp=='F' || *fp=='f')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(FloatOperand *c=GetSeqControl()->FloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }

    if((*fp=='C' || *fp=='c')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(StringOperand *c=GetSeqControl()->StringOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }

    if((*fp=='S' || *fp=='s')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(SpecialOperand *c=GetSeqControl()->SpecialOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }
    if((*fp=='P' || *fp=='p')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(SpecialBitOperand *c=GetSeqControl()->SpecialBitOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }
    if((*fp=='Q' || *fp=='q')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(SpecialStringOperand *c=GetSeqControl()->SpecialStringOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }
    if((*fp=='R' || *fp=='r')
    && (hp=FpToInt(fp+1,N))!=NULL){
        for(SpecialFloatOperand *c=GetSeqControl()->SpecialFloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetID()==N){
                *ope=c;
                return(hp);
                }
            }
        return(NULL);
        }
    if(seq!=NULL && (*fp=='L' || *fp=='l')){
        if((*(fp+1)=='B' || *(fp+1)=='b')
        && (hp=FpToInt(fp+2,N))!=NULL){
            for(LocalBitOperand *c=seq->LoadedLocalReg.LocalBitOpe.GetFirst();c!=NULL;c=c->GetNext()){
                if(c->GetID()==N){
                    *ope=c;
                    return(hp);
                    }
                }
            return(NULL);
            }

        if((*(fp+1)=='W' || *(fp+1)=='w')
        && (hp=FpToInt(fp+2,N))!=NULL){
            for(LocalWordOperand *c=seq->LoadedLocalReg.LocalWordOpe.GetFirst();c!=NULL;c=c->GetNext()){
                if(c->GetID()==N){
                    *ope=c;
                    return(hp);
                    }
                }
            return(NULL);
            }
        if((*(fp+1)=='F' || *(fp+1)=='f')
        && (hp=FpToInt(fp+2,N))!=NULL){
            for(LocalFloatOperand *c=seq->LoadedLocalReg.LocalFloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
                if(c->GetID()==N){
                    *ope=c;
                    return(hp);
                    }
                }
            return(NULL);
            }

        if((*(fp+1)=='C' || *(fp+1)=='c')
        && (hp=FpToInt(fp+2,N))!=NULL){
            for(LocalStringOperand *c=seq->LoadedLocalReg.LocalStringOpe.GetFirst();c!=NULL;c=c->GetNext()){
                if(c->GetID()==N){
                    *ope=c;
                    return(hp);
                    }
                }
            return(NULL);
            }
        return(NULL);
        }
    hp=LoadInt(fp ,ope);
    if(hp!=NULL){
        return(hp);
    }
    hp=LoadString(fp ,ope);
    if(hp!=NULL){
        return(hp);
    }
    return(NULL);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    fp
//    ope
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
char    *SequenceStock::LoadInt(char *fp ,Operand **ope)
{
    char    *hp;
    double N;
    if((hp=FpToHex(fp,N))!=NULL){
        for(NumberOperand *c=GetSeqControl()->NumberOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetFloat()==N){
                *ope=c;
                return(hp);
                }
            }
        NumberOperand *c2=new NumberOperand(GetSeqControl());
        c2->SetData(N);
        *ope=c2;
        GetSeqControl()->NumberOpe.AppendList(c2);
        return(hp);
        }
    if((hp=FpToBinary(fp,N))!=NULL){
        for(NumberOperand *c=GetSeqControl()->NumberOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetFloat()==N){
                *ope=c;
                return(hp);
                }
            }
        NumberOperand *c2=new NumberOperand(GetSeqControl());
        c2->SetData(N);
        *ope=c2;
        GetSeqControl()->NumberOpe.AppendList(c2);
        return(hp);
        }
    if((hp=FpToFloat(fp,N))!=NULL){
        for(NumberOperand *c=GetSeqControl()->NumberOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(c->GetFloat()==N){
                *ope=c;
                return(hp);
                }
            }
        NumberOperand *c2=new NumberOperand(GetSeqControl());
        c2->SetData(N);
        *ope=c2;
        GetSeqControl()->NumberOpe.AppendList(c2);
        return(hp);
        }
    return(NULL);
}
/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    fp
//    ope
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
char    *SequenceStock::LoadString(char *fp ,Operand **ope)
{
    if(*fp=='\"'){
        char    Buff[2560];
        int     n=0;
        fp++;
        while(*fp!=0){
            if(*fp=='\"'){
                Buff[n]=0;
                //n++;
                fp++;
                break;
                }
            if(*fp=='\\' && (*(fp+1)=='x' || *(fp+1)=='X')){
                if(isxdigit(*(fp+2))){
                    if(isxdigit(*(fp+3))){
                        BYTE    k=ToXDigit(*(fp+2));
                        k*=(BYTE)16;
                        k+=ToXDigit(*(fp+3));
                        fp+=4;
                        Buff[n]=k;
                        n++;
                        }
                    else{
                        Buff[n]=ToXDigit(*(fp+2));
                        fp+=3;
                        n++;
                        }
                    }
                else{
                    Buff[n]=*fp;
                    n++;
                    }
                }
            else if(*fp=='\\' && isdigit(*(fp+1))){
                if(isdigit(*(fp+2))){
                    BYTE    k=ToXDigit(*(fp+1));
                    k*=(BYTE)10;
                    k+=ToXDigit(*(fp+2));
                    fp+=3;
                    Buff[n]=k;
                    n++;
                    }
                else{
                    Buff[n]=ToXDigit(*(fp+1));
                    fp+=2;
                    n++;
                    }
                }
            else if(*fp=='\\' && *(fp+1)=='\"'){
                Buff[n]='\"';
                n++;
                fp+=2;
                }
            else if(*fp=='\\' && *(fp+1)=='\''){
                Buff[n]='\'';
                n++;
                fp+=2;
                }
            else if(*fp=='\\' && *(fp+1)=='\\'){
                Buff[n]='\\';
                n++;
                fp+=2;
                }
            else if(*fp=='\\' && *(fp+1)=='n'){
                Buff[n]='\n';
                n++;
                fp+=2;
                }
            else if(*fp=='\\' && *(fp+1)=='r'){
                Buff[n]='\r';
                n++;
                fp+=2;
                }
            else if(*fp=='\\' && *(fp+1)=='a'){
                Buff[n]='\a';
                n++;
                fp+=2;
                }
            else if(*fp=='\\' && *(fp+1)=='d'){
                Buff[n]='\x0d';
                n++;
                fp+=2;
                }
			/*
            else if(_ismbclegal(SwapHL(*((unsigned short *)fp)))){
                Buff[n]=*fp;
                Buff[n+1]=*(fp+1);
                n+=2;
                fp+=2;
                }
			*/
			else if((0x7F<=((unsigned char )*fp) && ((unsigned char )*fp)<0xa1) || (0xE0<=((unsigned char )*fp) && ((unsigned char )*fp)<=0xFF)){
                Buff[n]=*fp;
                Buff[n+1]=*(fp+1);
                n+=2;
                fp+=2;
			}
            else{
                Buff[n]=*fp;
                n++;
                fp++;
                }
            }
        for(CharOperand *c=GetSeqControl()->CharOpe.GetFirst();c!=NULL;c=c->GetNext()){
            if(n==c->GetStringCount()
			&& c->GetString().compare(Buff)==0){
                *ope=c;
                return(fp);
                }
            }
        CharOperand *c2=new CharOperand(GetSeqControl());
///        c->SetData((BYTE *)Buff,n);
        QByteArray  BStr(Buff,n);
        c2->SetData(BStr);
        //c2->SetData()Buff);
        *ope=c2;
        GetSeqControl()->CharOpe.AppendList(c2);
        return(fp);
        }
    return(NULL);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    fp
//    N
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
char    *SequenceStock::FpToInt(char *fp ,int &N)
{
    int Sign=1;
    N=0;
    if(*fp=='-'){
        Sign=-1;
        fp++;
        }
    else
    if(*fp=='+'){
        Sign=1;
        fp++;
        }

    if(!isdigit(*fp)){
        return(NULL);
    }

    while('0'<=*fp && *fp<='9'){
        N*=10;
        N+=*fp-'0';
        fp++;
        }
    N=N*Sign;
    return(fp);
}

char    *SequenceStock::FpToBinary(char *fp ,double &N)
{
    int Sign=1;
    N=0;
    if(*fp=='-'){
        Sign=-1;
        fp++;
        }
    else
    if(*fp=='+'){
        Sign=1;
        fp++;
        }
    while(*fp==' ' || *fp=='\t'){
        fp++;
    }

    if(*fp=='0' || *fp=='1'){
        while(*fp=='0' || *fp=='1'){
            N*=2.0;
            N+=(int)(*fp-'0');
            fp++;
            }
        if((*fp=='b' || *fp=='B') && strchr(" \t,\n\r\a+-()=^/*",*(fp+1))!=NULL){
            N=N*Sign;
            return(fp);
            }
        }
    return(NULL);
}

char    *SequenceStock::FpToHex(char *fp ,double &N)
{
    int Sign=1;
    N=0;
    if(*fp=='-'){
        Sign=-1;
        fp++;
        }
    else
    if(*fp=='+'){
        Sign=1;
        fp++;
        }
    while(*fp==' ' || *fp=='\t'){
        fp++;
    }

    if(ToXDigitOrError(*fp)!=0xff){
        int n;
        while((n=ToXDigitOrError(*fp))!=0xff){
            N*=16.0;
            N+=(int)n;
            fp++;
            }
        if((*fp=='h' || *fp=='H') && strchr(" \t,\n\r\a+-()=^/*",*(fp+1))!=NULL){
            N=N*Sign;
            return(fp);
            }
        }
    return(NULL);
}


char    *SequenceStock::FpToFloat(char *fp ,double &N)
{
    int Sign=1;
    N=0;
    if(*fp=='-'){
        Sign=-1;
        fp++;
        }
    else
    if(*fp=='+'){
        Sign=1;
        fp++;
        }
    while(*fp==' ' || *fp=='\t'){
        fp++;
    }

    N=0;
    if(isdigit(*fp)==0 && *fp!='.'){
        return(NULL);
    }
    while('0'<=*fp && *fp<='9'){
        N*=10.0;
        N+=(int)(*fp-'0');
        fp++;
        }
    while(*fp==' ' || *fp=='\t'){
        fp++;
    }
    if(*fp=='.'){
        fp++;
        double  d=0.1;

	    while('0'<=*fp && *fp<='9'){
            N+=(*fp-'0')*d;
            d/=10.0;
            fp++;
            }
        }
    while(*fp==' ' || *fp=='\t'){
        fp++;
    }
    if(*fp=='E' || *fp=='e'){
        fp++;
        double  ESign=1;
        if(*fp=='-'){
            ESign=-1;
            fp++;
            }
        else
        if(*fp=='+'){
            ESign=1;
            fp++;
            }
        while(*fp==' ' || *fp=='\t'){
            fp++;
        }

        double  EN=0.0;
        while('0'<=*fp && *fp<='9'){
            EN*=10.0;
            EN+=(int)(*fp-'0');
            fp++;
            }
        while(*fp==' ' || *fp=='\t'){
            fp++;
        }
        if(*fp=='.'){
            fp++;
            double  d=0.1;

			while('0'<=*fp && *fp<='9'){
                EN+=(*fp-'0')*d;
                d/=10.0;
                fp++;
                }
            }
        N=N*(double)Sign*pow(10.0,ESign*EN);
        }
    else{
        N=N*Sign;
    }

    return(fp);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    d
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
BYTE    SequenceStock::ToXDigit(char d)
{
    switch(d){
        case '0':   return(0);
        case '1':   return(1);
        case '2':   return(2);
        case '3':   return(3);
        case '4':   return(4);
        case '5':   return(5);
        case '6':   return(6);
        case '7':   return(7);
        case '8':   return(8);
        case '9':   return(9);
        case 'A':   return(10);
        case 'a':   return(10);
        case 'B':   return(11);
        case 'b':   return(11);
        case 'C':   return(12);
        case 'c':   return(12);
        case 'D':   return(13);
        case 'd':   return(13);
        case 'E':   return(14);
        case 'e':   return(14);
        case 'F':   return(15);
        case 'f':   return(15);
        }
    return(0);
}

BYTE    SequenceStock::ToXDigitOrError(char d)
{
    switch(d){
        case '0':   return(0);
        case '1':   return(1);
        case '2':   return(2);
        case '3':   return(3);
        case '4':   return(4);
        case '5':   return(5);
        case '6':   return(6);
        case '7':   return(7);
        case '8':   return(8);
        case '9':   return(9);
        case 'A':   return(10);
        case 'a':   return(10);
        case 'B':   return(11);
        case 'b':   return(11);
        case 'C':   return(12);
        case 'c':   return(12);
        case 'D':   return(13);
        case 'd':   return(13);
        case 'E':   return(14);
        case 'e':   return(14);
        case 'F':   return(15);
        case 'f':   return(15);
        }
    return(0xFF);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
volatile    bool    Sequence::Start(void)
{
    LastExecuted=false;
    NowLine=0;
    return(true);
}

volatile    bool    Sequence::IsEnd(void)
{
    if(NowLine>=GetSLineNumb()){
        return(true);
    }
    return(false);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
volatile    void    SequenceStock::Clear(void)
{
    if(Cond!=NULL){
        delete  Cond;
    }
    Cond=NULL;
    Name=/**/"";
    if(SLine!=NULL){
        for(int i=0;i<SLineNumb;i++){
            if(SLine[i]!=NULL){
                delete  SLine[i];
            }
        }
        delete  []SLine;
    }
    SLine=NULL;

    if(SLineIndex!=NULL){
        delete  []SLineIndex;
    }
    SLineIndex=NULL;
}

volatile    void    Sequence::Clear(void)
{
    if(TimingDataB!=NULL){
        delete  []TimingDataB;
    }
    TimingDataB=NULL;
    TimingDataLen=0;

    ClearBreak();
    if(SubroutineCall!=NULL){
        delete  SubroutineCall;
    }
    SubroutineCall=NULL;
}

void  Sequence::SetFlag(bool FlagConnectedMode ,bool Flag)
{
    if(FlagConnectedMode==true){
        eFlag.AddFlag(Flag);
        }
    else{
        eFlag.SetFlag(Flag);
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
volatile    bool  Sequence::StepExecute(void)
{
    if(DebugMode==true){
        if(StopExecute==true){
            IsDebugStopped=true;
            return(true);
            }
        if(StepBreakMode==true && StepBreak==true){
            IsDebugStopped=true;
            return(true);
            }
        if(GoMode==false){
            for(int i=0;i<BreakPointNumb;i++){
                if(BreakPoint[i]==NowLine){
                    IsDebugStopped=true;
                    return(true);
                    }
                }
            }
        GoMode=false;
        }

    if(ShouldDeleteSubroutine==true){
        if(SubroutineCall!=NULL){
            delete  SubroutineCall;
        }
        SubroutineCall=NULL;
        ShouldDeleteSubroutine=false;
    }
    if(NowLine==-1){
        NowLine=0;
    }
    if(NowLine<GetSLineNumb()){
        bool    ret=false;
		Lock();
        if(SLine!=NULL
        && (SLine[NowLine]->ExecuteEOk(this,eFlag)==true)){
            bool    FlagConnectedMode=SLine[NowLine]->GetFlagConnectedMode();
            if(NowOnSubroutine==false){
                int LastNowLine=NowLine;
                ret=SLine[NowLine]->Execute(this,FlagConnectedMode);
                if(LastNowLine!=NowLine){
                    }
                }
            else{
                if(SubroutineCall!=NULL){
                    SubroutineCall->StepExecute();
                    }
                }
            }
        else{
            NowLine++;
            //eFlag.AddFlag(Flag);
            ret=true;
            }
		Unlock();

        if(TimingWriteMode==true){
            GetSeqControl()->WriteTimingSeq(this);
        }
        //LastFlag=Flag;
        TimingWriteMode=false;

        if(NowLine>=GetSLineNumb()){
            if(GetSType()==SequenceStock::_Watch
            || GetSType()==SequenceStock::_Glance
            || GetSType()==SequenceStock::_Condition){
                Start();
            }
            else
            if(GetSType()==SequenceStock::_Subroutine){
                SubroutineParent->NowOnSubroutine=false;
                SubroutineParent->ShouldDeleteSubroutine=true;
                SubroutineParent->SetNowLine(SubroutineParent->GetNowLine()+1);
                }
            }
        if(StepBreakMode==true){
            StepBreak=true;
        }
        return(ret);
        }
    return(false);
}

bool    Sequence::IsAliveExecuting(void)
{
    if(NowLine>=GetSLineNumb()){
        return(false);
    }
    return(true);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    Sequence::ClearBreak(void)
{
    StopExecute=false;
    BreakPointNumb=0;
    GoMode=true;
    StepBreakMode=false;
    StepBreak=false;
    DebugMode=false;
}

PIOClass	*SeqControl::FindPIO(const QString &PIOName)
{
    if(PIO!=NULL){
	    if(PIOName.isEmpty()==false){
	    	if(PIO->GetName()==PIOName){
	    		return PIO;
            }
	    	return NULL;
	    }
    }
	return PIO;
}
PIOClass	*SeqControl::GetFirstPIO(void)
{
    if(PIO!=NULL){
        return PIO;
    }
    return NULL;
}
void	SeqControl::LoopOnIdle(void)
{
    if(PIO!=NULL){
	    PIO->LoopOnIdle();
    }
}
//==============================================================

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    file
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    SeqControl::Load(QFile &file)
{
    char    buff[256];

    HaltThread();

///    for(Sequence *s=Seq.GetFirst();s!=NULL;s=s->GetNext()){	//D-20051026
///        s->Clear();
///        }
///    Seq.RemoveAll();	//D-20051026

    SeqNumb=0;
    IOOpe           .RemoveAll();
    CommOpe         .RemoveAll();
    BitOpe          .RemoveAll();
    WordOpe         .RemoveAll();
    FloatOpe        .RemoveAll();
    StringOpe       .RemoveAll();
    SpecialOpe      .RemoveAll();
    NumberOpe       .RemoveAll();
    CharOpe         .RemoveAll();
    GroupOpe        .RemoveAll();
    SpecialBitOpe   .RemoveAll();
    SpecialStringOpe.RemoveAll();
///    LanvarOpe       .RemoveAll();	//D-20051026
    FifoOpe         .RemoveAll();
    DLLVarOpe       .RemoveAll();

    for(int i=0;i<MaxBitOperand;i++){
        BitOperand  *d=new BitOperand(this);
        d->SetID(i);
        BitOpe.AppendList(d);
        }
    for(int i=0;i<MaxWordOperand;i++){
        WordOperand  *d=new WordOperand(this);
        d->SetID(i);
        WordOpe.AppendList(d);
        }
    for(int i=0;i<MaxFloatOperand;i++){
        FloatOperand  *d=new FloatOperand(this);
        d->SetID(i);
        FloatOpe.AppendList(d);
        }
    for(int i=0;i<MaxStringOperand;i++){
        StringOperand  *d=new StringOperand(this);
        d->SetID(i);
        StringOpe.AppendList(d);
        }
    AddSpecialOperand(0);
    AddSpecialOperand(1);
    AddSpecialOperand(2);
    AddSpecialOperand(3);
    AddSpecialOperand(4);
    AddSpecialOperand(5);
    AddSpecialOperand(6);
    AddSpecialOperand(7);
    AddSpecialOperand(8);
    AddSpecialOperand(9);
    AddSpecialOperand(10);
    AddSpecialOperand(11);
    AddSpecialOperand(18);
    AddSpecialOperand(20);
    AddSpecialOperand(21);
    AddSpecialOperand(22);
    AddSpecialOperand(23);
    AddSpecialOperand(24);
    AddSpecialOperand(25);
    AddSpecialOperand(26);
    AddSpecialOperand(27);

    if(XSeqLocalInit!=NULL){
        XSeqLocalInit(GetLocalParamPointer(),this);
    }

	while(file.readLine(buff,sizeof(buff))!=-1){
        ErrorLine=buff;

        char    *fp=buff;
        fp=GetTopString(fp);
        if(strnicmp(fp,"#iodefine",9)==0){
            IOOperand   *d=new IOOperand(this);
            IOOpe.AppendList(d);
            if(d->Load(fp)==false){
                return(false);
            }
        }
        else
        if(strnicmp(fp,"#iogroup",8)==0){
            GroupOperand   *d=new GroupOperand(this);
            GroupOpe.AppendList(d);
            if(d->Load(fp)==false){
                return(false);
            }
        }
        else
        if(strnicmp(fp,"#lanvar",7)==0){
/*↓D-20051026------------------------------------------------------------------
            LanvarOperand   *d=new LanvarOperand(this);
            LanvarOpe.AppendList(d);
            if(d->Load(fp)==false)
                return(false);
↑D-20051026------------------------------------------------------------------*/
            }
        else
        if(strnicmp(fp,"#Fifo",5)==0){
            FifoOperand   *d=new FifoOperand(this);
            FifoOpe.AppendList(d);
            if(d->Load(fp)==false){
                return(false);
            }
        }
        else
        if(strnicmp(fp,"#DLLVar",7)==0){
            DLLVarOperand   *d=new DLLVarOperand(this);
            DLLVarOpe.AppendList(d);
            if(d->Load(fp)==false)
                return(false);
            if(d->OpenInitialize()==false){
				return false;
            }
        }
        else
        if(strnicmp(fp,"#title",6)==0){
            fp+=6;
            fp=GetTopString(fp);
            Operand *tmpOp;
            //fp=SequenceStock::LoadString(fp ,&tmpOp);
			
			fp=SequenceStock(this).LoadString(fp ,&tmpOp);
            if(fp!=NULL){
                SeqTitle=tmpOp->GetString();
                }
            }
        else
        if(strnicmp(fp,"#TimingPath",11)==0){
            fp+=11;
            fp=GetTopString(fp);
            Operand *tmpOp;
            //fp=SequenceStock::LoadString(fp ,&tmpOp);
			fp=SequenceStock(this).LoadString(fp ,&tmpOp);
            if(fp!=NULL){
                TimingPath=tmpOp->GetString();
                }
            }
        else
        if(strnicmp(fp,"#DebugMode",10)==0){
            fp+=10;
            DLLDebugMode=true;
            }
        else if(strnicmp(fp,"#Commdefine",11)==0){
            CommOperand   *d=new CommOperand(this);
            CommOpe.AppendList(d);
            if(d->Load(fp)==false){
                return(false);
            }
        }
        else if(strnicmp(fp,"#CommTerm",9)==0){
            fp+=9;
            fp=GetTopString(fp);
            char    nbuff[64];
            fp=GetWordCut(fp,nbuff);
            fp=GetTopString(fp);
            if(*fp!=':'){
                return(false);
            }
            fp++;
            fp=GetTopString(fp);
            Operand *tmpOp;
            char    *hp;
            for(CommOperand   *p=CommOpe.GetFirst();p!=NULL;p=p->GetNext()){
				if(p->GetName().compare(nbuff)==0){
                    for(int i=0;i<16;i++){
                        //hp=SequenceStock::LoadString(fp,&tmpOp);
						hp=SequenceStock(this).LoadString(fp ,&tmpOp);
                        if(hp==NULL){
                            //hp=SequenceStock::LoadInt(fp,&tmpOp);
							hp=SequenceStock(this).LoadInt(fp ,&tmpOp);
                            if(hp==NULL)
                                break;
                            }
						char	TermBuff[1000];
						int	TermLen=QString2Char(tmpOp->GetString(),TermBuff,sizeof(TermBuff));
                        p->TermChar[p->TermNumb]=new char[TermLen+1];
						strcpy(p->TermChar[p->TermNumb],TermBuff);
                        p->TermNumb++;
                        fp=hp;
                        fp=GetTopString(fp);
                        if(*fp==','){
                            fp++;
                        }
                        else{
                            break;
                        }
                        fp=GetTopString(fp);
                    }
                    break;
                }
            }
        }
        else if(strnicmp(fp,"#CommIgnore",11)==0){
            fp+=11;
            fp=GetTopString(fp);
            char    nbuff[64];
            fp=GetWordCut(fp,nbuff);
            fp=GetTopString(fp);
            if(*fp!=':'){
                return(false);
            }
            fp++;
            fp=GetTopString(fp);
            Operand *tmpOp;
            char    *hp;
            for(CommOperand   *p=CommOpe.GetFirst();p!=NULL;p=p->GetNext()){
				if(p->GetName().compare(nbuff)==0){
                    for(int i=0;i<16;i++){
                        //hp=SequenceStock::LoadString(fp,&tmpOp);
						hp=SequenceStock(this).LoadString(fp ,&tmpOp);
                        if(hp==NULL){
                            //hp=SequenceStock::LoadInt(fp,&tmpOp);
							hp=SequenceStock(this).LoadInt(fp ,&tmpOp);
                            if(hp==NULL){
                                break;
                            }
                        }
						char	IgnoreBuff[1000];
						int	IgnoreLen=QString2Char(tmpOp->GetString(),IgnoreBuff,sizeof(IgnoreBuff));
                        p->IgnoreChar[p->IgnoreNumb]=new char[IgnoreLen+1];
						strcpy(p->IgnoreChar[p->IgnoreNumb],IgnoreBuff);
                        p->IgnoreNumb++;
                        fp=hp;
                        fp=GetTopString(fp);
                        if(*fp==','){
                            fp++;
                        }
                        else{
                            break;
                        }
                        fp=GetTopString(fp);
                    }
                    break;
                }
            }
        }
        else if(strnicmp(fp,"#memcomment",11)==0){
            fp+=11;
            fp=GetTopString(fp);
            char    nbuff[128];
            fp=GetWordCut(fp,nbuff);
            if(fp==NULL){
                return(false);
            }
            fp=GetTopString(fp);
            if(*fp!=':'){
                return(false);
            }
            fp++;
            fp=GetTopString(fp);
            char    *ep=strchr(fp,'\n');
            if(ep!=NULL){
                *ep=0;
            }
            Operand *rg=SearchReg(NULL,nbuff);
            if(rg!=NULL){
                rg->Comment=fp;
            }
        }
        else if(strnicmp(fp,"#StepTime",9)==0){
            fp+=9;
            fp=GetTopString(fp);
            char    nbuff[64];
            fp=GetWordCut(fp,nbuff);
			StepTime=QString(nbuff).toInt();
            fp=GetTopString(fp);
            }
        /*
        else if(strnicmp(fp,"#Version",8)==0){
            fp+=8;
            fp=GetTopString(fp);
            char    nbuff[64];
            fp=GetWordCut(fp,nbuff);
            GrammerVersion=StrToIntDef(AnsiString(nbuff),0);
            fp=GetTopString(fp);
            }
        */
        else if(strnicmp(fp,"#Sequence",9)==0){
            SequenceStock    *s=new SequenceStock(this);
            s->SetSCode(SeqNumb);
            if(s->Load(fp,file)==false){
                return(false);
            }
            SeqStock.AppendList(s);

            Sequence    *q=new Sequence(this);
            q->LoadFromStock(s);
            Seq.AppendList(q);
            SeqNumb++;
            }
        }
    GlanceFreq=0;
    for(SequenceStock *s=SeqStock.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->GetSType()==SequenceStock::_Glance){
            GlanceFreq++;
            }
        }

    if(CheckCall()==false){
        return(false);
    }
    for(GroupOperand *g=GroupOpe.GetFirst();g!=NULL;g=g->GetNext()){
        g->InitialConstruct();
        }
    NetInitial();
    if(LanVarCSection==NULL)
        //LanVarCSection=new QMutex();
///    for(LanvarOperand *c=SeqControl::LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){	//D-20051026
///        c->Initial();
///        }
    RestartThread();

    return(true);
}

bool    SeqControl::ReLoad(QFile &file)
{
    HaltThread();

    NPListPack<TmpNameValue>    tmpIOOpe;
    NPListPack<TmpNameValue>    tmpCommOpe;
    NPListPack<TmpNameValue>    tmpBitOpe;
    NPListPack<TmpNameValue>    tmpWordOpe;
    NPListPack<TmpNameValue>    tmpFloatOpe;
    NPListPack<TmpNameValue>    tmpStringOpe;
    NPListPack<TmpNameValue>    tmpLanvarOpe;
    NPListPack<TmpNameValue>    tmpFifoOpe;

    for(IOOperand *c=IOOpe.GetFirst();c!=NULL;c=c->GetNext()){
        int d=c->GetOutData();
		if(d>=0){
			QString	Q=c->GetName();
            tmpIOOpe.AppendList(new TmpNameValue(Q,d));
		}
        }
    for(CommOperand *c=CommOpe.GetFirst();c!=NULL;c=c->GetNext()){
		QString	Q1=c->GetName();
		QString	Q2=c->GetString();
        tmpCommOpe.AppendList(new TmpNameValue(Q1,Q2));
        }
    for(BitOperand *c=BitOpe.GetFirst();c!=NULL;c=c->GetNext()){
		QString	Q1=c->GetName();
		int	Q2=c->GetNumeric();
        tmpBitOpe.AppendList(new TmpNameValue(Q1,Q2));
        }
    for(WordOperand *c=WordOpe.GetFirst();c!=NULL;c=c->GetNext()){
		QString	Q1=c->GetName();
		int	Q2=c->GetNumeric();
        tmpWordOpe.AppendList(new TmpNameValue(Q1,Q2));
        }
    for(FloatOperand *c=FloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
		QString	Q1=c->GetName();
		int	Q2=c->GetNumeric();
		tmpFloatOpe.AppendList(new TmpNameValue(Q1,Q2));
        }
    for(StringOperand *c=StringOpe.GetFirst();c!=NULL;c=c->GetNext()){
		QString	Q1=c->GetName();
		QString	Q2=c->GetString();
        tmpStringOpe.AppendList(new TmpNameValue(Q1,Q2));
        }
///    for(LanvarOperand *c=LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){	//D-20051026
///        tmpLanvarOpe.AppendList(new TmpNameValue(c->GetName(),c->GetString()));
///        }
    for(FifoOperand *c=FifoOpe.GetFirst();c!=NULL;c=c->GetNext()){
        TmpNameValue    *d=new TmpNameValue();
        d->lValue=new QStringList();
        for(FifoClass *k=c->Data.GetFirst();k!=NULL;k=k->GetNext()){
			d->lValue->append(k->Str);
            }
        tmpFifoOpe.AppendList(d);
        }

    RestartThread();
    return(true);
}

void    SeqControl::AddSpecialOperand(int id)
{
    SpecialOperand  *sd=new SpecialOperand(this);
    sd->SetID(id);
    SpecialOpe.AppendList(sd);
}
void    SeqControl::AddSpecialBitOperand(int id)
{
    SpecialBitOperand   *sd=new SpecialBitOperand(this);
    sd->SetID(id);
    SpecialBitOpe.AppendList(sd);
}
void    SeqControl::AddSpecialStringOperand(int id)
{
    SpecialStringOperand   *sd=new SpecialStringOperand(this);
    sd->SetID(id);
    SpecialStringOpe.AppendList(sd);
}
void    SeqControl::AddSpecialFloatOperand(int id)
{
    SpecialFloatOperand   *sd=new SpecialFloatOperand(this);
    sd->SetID(id);
    SpecialFloatOpe.AppendList(sd);
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    SeqControl::StepExecute(void)
{
    if(ReqHalt==1){
        ReqHalt=2;
        while(ReqHalt!=0){
            ThreadSequence::MSleep(10);
            }
        }
    static  int EntrantCount=0;
    if((EntrantCount&7)==0){
        bool    Flag;
        do{
            Flag=false;
            for(CommOperand *c=CommOpe.GetFirst();c!=NULL;c=c->GetNext()){
                if(c->ReceiveLoop()==true){
                    Flag=true;
                }
            }
            if(ReqHalt==1){
                ReqHalt=2;
                while(ReqHalt!=0){
                    ThreadSequence::MSleep(10);
                }
            }
            }while(Flag==true);
        }

    for(Sequence *s=Seq.GetFirst();s!=NULL;s=s->GetNext()){
		if(qApp->closingDown()==true){
            break;
        }
        if(s->GetSType()==SequenceStock::_Subroutine){
            continue;
            }
        if(s->GetSType()==SequenceStock::_Main
        || s->GetSType()==SequenceStock::_Watch
        || (s->GetSType()==SequenceStock::_Glance && ((SeqControl::NowGlanceTime%SeqControl::GlanceFreq)==s->GetGlanceTime()))
        || s->GetSType()==SequenceStock::_Subroutine){
            s->StepExecute();
            if(PIO!=NULL){
                PIO->LoopIO();
            }
        }
        if(ReqHalt==1){
            ReqHalt=2;
            while(ReqHalt!=0){
                ThreadSequence::MSleep(10);
            }
        }
    }
    EntrantCount++;
    return(true);
}

bool  SeqControl::EventStart(QString &commandname)
{
    int     EventCount=0;
    for(Sequence *s=Seq.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->GetSType()==SequenceStock::_Event && s->GetCommandName()==commandname)
            EventCount++;
        }
    if(EventCount==0){
        return(false);
    }

    ReqHalt=1;
    for(Sequence *s=Seq.GetFirst();s!=NULL;s=s->GetNext()){
        if(qApp->closingDown()==true){
            break;
        }
        if(s->GetSType()==SequenceStock::_Event && s->GetCommandName()==commandname){
            s->Start();
            while(ReqHalt==1 && SeqControl::OnStepping==true){
                if(qApp->closingDown()==true){
                    break;
                }
                ThreadSequence::MSleep(10);
            }
            while(s->IsEnd()!=true){
                if(qApp->closingDown()==true){
                    break;
                }
                s->StepExecute();
                if(PIO!=NULL){
                    PIO->LoopIO();
                }
            }
        }
    }
    while(ReqHalt==1){
        ThreadSequence::MSleep(10);
    }
    ReqHalt=0;
    return(true);
}


/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqControl::Start(void)
{
	if(OutSequenceYesNoForm==NULL){
		OutSequenceYesNoForm=new OutSequenceYesNo(this);
    }
	if(OutSequenceShowYesNoForm==NULL){
		OutSequenceShowYesNoForm=new OutSequenceShowYesNo(this);
    }
	if(OutSequenceYesNoForm==NULL){
		OutSequenceYesNoForm=new OutSequenceYesNo(this);
    }
	if(OutSequenceShowYesNoForm==NULL){
		OutSequenceShowYesNoForm=new OutSequenceShowYesNo(this);
    }
	if(OutSequenceShowForm==NULL){
		OutSequenceShowForm=new OutSequenceShow(this);
    }
	if(OutSequenceShowOKForm==NULL){
		OutSequenceShowOKForm=new OutSequenceShowOK(this);
    }
	if(OutSequenceMessageForm==NULL){
		OutSequenceMessageForm=new OutSequenceMessage(this);
    }
	if(OutSequenceInputForm==NULL){
		OutSequenceInputForm=new OutSequenceInput(this);
    }

    if(StartTickCount==0){
        StartTickCount=ThreadSequence::GetNowMiliSec();
        StartTime     =time(NULL);
        }
    if(Started==true){
        return;
    }
    Started=true;
    if(WriteTimingFile==NULL){
        WriteTimingFileTop();
        }

    LastOperationTime=ThreadSequence::GetNowMiliSec();
    for(Sequence *s=Seq.GetFirst();s!=NULL;s=s->GetNext()){
        s->Start();
        }
}

void    SeqControl::Stop(void)
{
    Started=false;
}

void    SeqControl::HaltThread(void)
{
    if(Started==false){
        return;
    }
    DoHalt=true;
    for(DWORD t=ThreadSequence::GetNowMiliSec();OnHalting==false && ThreadSequence::GetNowMiliSec()-t<1000;){
        if(OutSequenceMessageForm->OnAwake==true){	//D-20051026
            break;
        }
        if(OutSequenceYesNoForm->OnAwake==true){
            break;
        }
    }
}
void    SeqControl::RestartThread(void)
{
    if(Started==false){
        return;
    }
    DoHalt=false;
    while(OnHalting==true){
        ThreadSequence::MSleep(10);
    }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    s
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqControl::MessageOut(QString &s)
{
    ThreadSequence *p=dynamic_cast<ThreadSequence *>(Parent);
    if(p!=NULL){
        p->MessageOut(s);
        }
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    s
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
bool    SeqControl::MessageYesNoOut(QString &s)
{
    ThreadSequence *p=dynamic_cast<ThreadSequence *>(Parent);
    if(p!=NULL){
        return(p->MessageYesNoOut(s));
        }
    return(false);
}

bool    SeqControl::MessageInputOut(QString &defaultStr ,QString &msg)
{
    ThreadSequence *p=dynamic_cast<ThreadSequence *>(Parent);
    if(p!=NULL){
        return(p->MessageInputOut(defaultStr ,msg));
        }
    return(false);
}

void    SeqControl::MessageShowOn(QString &s ,int PageCode ,int WRegID ,Sequence *seq ,int RegKind)
{
    ThreadSequence *p=dynamic_cast<ThreadSequence *>(Parent);
    if(p!=NULL){
        p->MessageShowOn(s ,PageCode ,WRegID ,seq ,RegKind);
        }
}
void    SeqControl::MessageShowOff(void)
{
    ThreadSequence *p=dynamic_cast<ThreadSequence *>(Parent);
    if(p!=NULL){
        p->MessageShowOff();
        }
}

void    SeqControl::SetWReg(Sequence *seq ,int regkindcode ,int regid ,int data)
{
    if(regkindcode==KindCodeWord){
        Operand *r=SearchReg(seq ,&WordOpe ,regid);
        if(r!=NULL){
            r->SetData(data);
            }
        }
    else
    if(regkindcode==KindCodeLocalWord){
        Operand *r=seq->LocalRegs.LocalWordOpe.GetItemFromID(regid);
        if(r!=NULL){
            r->SetData(data);
            }
        }
}



/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/
void    SeqControl::Release(void)
{
    for(Sequence *s=Seq.GetFirst();s!=NULL;s=s->GetNext()){
        s->Clear();
    }

    for(SequenceStock *s=SeqStock.GetFirst();s!=NULL;s=s->GetNext()){
        s->Clear();
    }

    if(WriteTimingFile!=NULL){
        delete  WriteTimingFile;
    }
    WriteTimingFile=NULL;

    CloseLanPort();
///    if(ServerSock!=NULL){	//D-20051026
///        ServerSock->Close();
///        //ServerSock->WaitForClose();
///        }
    if(PIO!=NULL){
        PIOClass    *p=PIO;
        PIO=NULL;
        delete  p;
    }
    IOOpe           .RemoveAll();
    CommOpe         .RemoveAll();
    BitOpe          .RemoveAll();
    WordOpe         .RemoveAll();
    FloatOpe        .RemoveAll();
    StringOpe       .RemoveAll();
    SpecialOpe      .RemoveAll();
    NumberOpe       .RemoveAll();
    CharOpe         .RemoveAll();
    GroupOpe        .RemoveAll();
    SpecialBitOpe   .RemoveAll();
    SpecialStringOpe.RemoveAll();
///    LanvarOpe       .RemoveAll();	//D-20051026
    FifoOpe         .RemoveAll();
    DLLVarOpe       .RemoveAll();

    if(LanVarCSection!=NULL){
        delete  LanVarCSection;
    }
    LanVarCSection=NULL;
    if(DLLSync!=NULL){
        delete  DLLSync;
    }
    DLLSync=NULL;

	if(OutSequenceYesNoForm!=NULL){
		//delete	OutSequenceYesNoForm;
		OutSequenceYesNoForm->deleteLater();
		OutSequenceYesNoForm=NULL;
	}

	if(OutSequenceShowYesNoForm!=NULL){
		//delete	OutSequenceShowYesNoForm;
		OutSequenceShowYesNoForm->deleteLater();
		OutSequenceShowYesNoForm=NULL;
	}

	if(OutSequenceShowForm!=NULL){
		//delete	OutSequenceShowForm;
		OutSequenceShowForm->deleteLater();
		OutSequenceShowForm=NULL;
	}

	if(OutSequenceShowOKForm!=NULL){
		//delete	OutSequenceShowOKForm;
		OutSequenceShowOKForm->deleteLater();
		OutSequenceShowOKForm=NULL;
	}

	if(OutSequenceMessageForm!=NULL){
		//delete	OutSequenceMessageForm;
		OutSequenceMessageForm->deleteLater();
		OutSequenceMessageForm=NULL;
	}

	if(OutSequenceInputForm!=NULL){
		//delete	OutSequenceInputForm;
		OutSequenceInputForm->deleteLater();
		OutSequenceInputForm=NULL;
	}
}
void    SeqControl::CloseLanPort(void)
{
///    for(LanVarSocketList *c=LanVarSocket.GetFirst();c!=NULL;c=c->GetNext()){	//D-20051026
///        //c->Close();
///        }
}


static  char    *GetNumberOnly(char *fp ,int &N ,int bitnumb)
{
    int numb=0;
    N=0;
    bool    sign=false;
    if(*fp=='-'){
        sign=true;
        fp++;
        while(*fp==' ' || *fp=='\t'){
            fp++;
        }
    }
    if(*fp=='0' && (*(fp+1)=='x' || *(fp+1)=='X')){
        fp+=2;
        for(;;){
            if(numb*4>bitnumb){
                break;
            }
            switch(*fp){
                case '0':
                    N<<=4;
                    N+=0;
                    fp++;
                    break;
                case '1':
                    N<<=4;
                    N+=1;
                    fp++;
                    break;
                case '2':
                    N<<=4;
                    N+=2;
                    fp++;
                    break;
                case '3':
                    N<<=4;
                    N+=3;
                    fp++;
                    break;
                case '4':
                    N<<=4;
                    N+=4;
                    fp++;
                    break;
                case '5':
                    N<<=4;
                    N+=5;
                    fp++;
                    break;
                case '6':
                    N<<=4;
                    N+=6;
                    fp++;
                    break;
                case '7':
                    N<<=4;
                    N+=7;
                    fp++;
                    break;
                case '8':
                    N<<=4;
                    N+=8;
                    fp++;
                    break;
                case '9':
                    N<<=4;
                    N+=9;
                    fp++;
                    break;
                case 'a':
                case 'A':
                    N<<=4;
                    N+=10;
                    fp++;
                    break;
                case 'b':
                case 'B':
                    N<<=4;
                    N+=11;
                    fp++;
                    break;
                case 'c':
                case 'C':
                    N<<=4;
                    N+=12;
                    fp++;
                    break;
                case 'd':
                case 'D':
                    N<<=4;
                    N+=13;
                    fp++;
                    break;
                case 'e':
                case 'E':
                    N<<=4;
                    N+=14;
                    fp++;
                    break;
                case 'f':
                case 'F':
                    N<<=4;
                    N+=15;
                    fp++;
                    break;
                default:
                    goto    RHex;
                }
            numb++;
            }
        RHex:;
        }
    else
    if(*fp=='0' && (*(fp+1)=='b' || *(fp+1)=='B')){
        fp+=2;
        for(;;){
            if(numb>bitnumb){
                break;
            }
            switch(*fp){
                case '0':
                    N<<=1;
                    N+=0;
                    fp++;
                    break;
                case '1':
                    N<<=1;
                    N+=1;
                    fp++;
                    break;
                default:
                    goto    RBin;
                }
            numb++;
            }
        RBin:;
        }
    else{
        double  AddedNumb=log(10.0)/log(2.0);
        for(;;){
            if(numb*AddedNumb>bitnumb){
                break;
            }
            switch(*fp){
                case '0':
                    N*=10;
                    N+=0;
                    fp++;
                    break;
                case '1':
                    N*=10;
                    N+=1;
                    fp++;
                    break;
                case '2':
                    N*=10;
                    N+=2;
                    fp++;
                    break;
                case '3':
                    N*=10;
                    N+=3;
                    fp++;
                    break;
                case '4':
                    N*=10;
                    N+=4;
                    fp++;
                    break;
                case '5':
                    N*=10;
                    N+=5;
                    fp++;
                    break;
                case '6':
                    N*=10;
                    N+=6;
                    fp++;
                    break;
                case '7':
                    N*=10;
                    N+=7;
                    fp++;
                    break;
                case '8':
                    N*=10;
                    N+=8;
                    fp++;
                    break;
                case '9':
                    N*=10;
                    N+=9;
                    fp++;
                    break;
                default:
                    goto    RDec;
                }
            numb++;
            }
        RDec:;
        }
    if(numb==0){
        return(NULL);
    }
    if(sign==true){
        N=-N;
    }
    return(fp);
}

static  QChar    *GetNumberOnly(QChar *fp ,int &N ,int bitnumb)
{
    int numb=0;
    N=0;
    bool    sign=false;
    if(*fp=='-'){
        sign=true;
        fp++;
        while(*fp==' ' || *fp=='\t'){
            fp++;
        }
        }
    if(*fp=='0' && (*(fp+1)=='x' || *(fp+1)=='X')){
        fp+=2;
        for(;;){
            if(numb*4>bitnumb){
                break;
            }
			if(*fp=='0'){
				N<<=4;
				N+=0;
				fp++;
			}
			else if(*fp=='1'){
                N<<=4;
                N+=1;
                fp++;
			}
			else if(*fp=='2'){
                N<<=4;
                N+=2;
                fp++;
			}
			else if(*fp=='3'){
                N<<=4;
                N+=3;
                fp++;
			}
			else if(*fp=='4'){
				N<<=4;
				N+=4;
                fp++;
			}
			else if(*fp=='5'){
                N<<=4;
                N+=5;
                fp++;
			}
			else if(*fp=='6'){
                N<<=4;
                N+=6;
                fp++;
			}
			else if(*fp=='7'){
                N<<=4;
                N+=7;
                fp++;
			}
			else if(*fp=='8'){
                N<<=4;
                N+=8;
                fp++;
			}
			else if(*fp=='9'){
                N<<=4;
                N+=9;
                fp++;
			}
			else if(*fp=='a' || *fp=='A'){
                N<<=4;
                N+=10;
                fp++;
			}
			else if(*fp=='b' || *fp=='B'){
                N<<=4;
                N+=11;
				fp++;
			}
			else if(*fp=='c' || *fp=='C'){
                N<<=4;
                N+=12;
                fp++;
			}
			else if(*fp=='d' || *fp=='D'){
                N<<=4;
                N+=13;
                fp++;
			}
			else if(*fp=='e' || *fp=='E'){
                N<<=4;
                N+=14;
                fp++;
			}
			else if(*fp=='f' || *fp=='F'){
                N<<=4;
                N+=15;
                fp++;
			}
			else{
				goto    RHex;
			}
            numb++;
		}
        RHex:;
	}
    else
    if(*fp=='0' && (*(fp+1)=='b' || *(fp+1)=='B')){
        fp+=2;
        for(;;){
            if(numb>bitnumb){
                break;
            }
			if(*fp=='0'){
                N<<=1;
                N+=0;
                fp++;
			}
			else if(*fp=='1'){
                N<<=1;
                N+=1;
                fp++;
			}
			else{
                goto    RBin;
            }
            numb++;
        }
        RBin:;
    }
    else{
        double  AddedNumb=log(10.0)/log(2.0);
        for(;;){
            if(numb*AddedNumb>bitnumb){
                break;
            }
			if(*fp=='0'){
                N*=10;
                N+=0;
                fp++;
			}
			else if(*fp=='1'){
                N*=10;
                N+=1;
                fp++;
			}
			else if(*fp=='2'){
                N*=10;
                N+=2;
                fp++;
			}
			else if(*fp=='3'){
                N*=10;
                N+=3;
                fp++;
			}
			else if(*fp=='4'){
                N*=10;
                N+=4;
                fp++;
			}
			else if(*fp=='5'){
                N*=10;
                N+=5;
                fp++;
			}
			else if(*fp=='6'){
                N*=10;
                N+=6;
                fp++;
			}
			else if(*fp=='7'){
                N*=10;
                N+=7;
                fp++;
			}
			else if(*fp=='8'){
                N*=10;
                N+=8;
                fp++;
			}
			else if(*fp=='9'){
                N*=10;
                N+=9;
                fp++;
			}
			else{
                goto    RDec;
            }
            numb++;
        }
        RDec:;
    }
    if(numb==0){
        return(NULL);
    }
    if(sign==true){
        N=-N;
    }
    return(fp);
}

static  char    *GetNumberOnlyBySourceNumb(char *fp ,int &N ,int snumb)
{
    int numb=0;
    N=0;
    bool    sign=false;
    if(*fp=='-'){
        sign=true;
        fp++;
        while(*fp==' ' || *fp=='\t'){
            fp++;
        }
    }
    if(*fp=='0' && (*(fp+1)=='x' || *(fp+1)=='X')){
        fp+=2;
        for(;;){
            if(numb>snumb){
                break;
            }
            switch(*fp){
                case '0':
                    N<<=4;
                    N+=0;
                    fp++;
                    break;
                case '1':
                    N<<=4;
                    N+=1;
                    fp++;
                    break;
                case '2':
                    N<<=4;
                    N+=2;
                    fp++;
                    break;
                case '3':
                    N<<=4;
                    N+=3;
                    fp++;
                    break;
                case '4':
                    N<<=4;
                    N+=4;
                    fp++;
                    break;
                case '5':
                    N<<=4;
                    N+=5;
                    fp++;
                    break;
                case '6':
                    N<<=4;
                    N+=6;
                    fp++;
                    break;
                case '7':
                    N<<=4;
                    N+=7;
                    fp++;
                    break;
                case '8':
                    N<<=4;
                    N+=8;
                    fp++;
                    break;
                case '9':
                    N<<=4;
                    N+=9;
                    fp++;
                    break;
                case 'a':
                case 'A':
                    N<<=4;
                    N+=10;
                    fp++;
                    break;
                case 'b':
                case 'B':
                    N<<=4;
                    N+=11;
                    fp++;
                    break;
                case 'c':
                case 'C':
                    N<<=4;
                    N+=12;
                    fp++;
                    break;
                case 'd':
                case 'D':
                    N<<=4;
                    N+=13;
                    fp++;
                    break;
                case 'e':
                case 'E':
                    N<<=4;
                    N+=14;
                    fp++;
                    break;
                case 'f':
                case 'F':
                    N<<=4;
                    N+=15;
                    fp++;
                    break;
                default:
                    goto    RHex;
                }
            numb++;
            }
        RHex:;
        }
    else
    if(*fp=='0' && (*(fp+1)=='b' || *(fp+1)=='B')){
        fp+=2;
        for(;;){
            if(numb>snumb){
                break;
            }
            switch(*fp){
                case '0':
                    N<<=1;
                    N+=0;
                    fp++;
                    break;
                case '1':
                    N<<=1;
                    N+=1;
                    fp++;
                    break;
                default:
                    goto    RBin;
                }
            numb++;
            }
        RBin:;
        }
    else{
        for(;;){
            if(numb>snumb){
                break;
            }
            switch(*fp){
                case '0':
                    N*=10;
                    N+=0;
                    fp++;
                    break;
                case '1':
                    N*=10;
                    N+=1;
                    fp++;
                    break;
                case '2':
                    N*=10;
                    N+=2;
                    fp++;
                    break;
                case '3':
                    N*=10;
                    N+=3;
                    fp++;
                    break;
                case '4':
                    N*=10;
                    N+=4;
                    fp++;
                    break;
                case '5':
                    N*=10;
                    N+=5;
                    fp++;
                    break;
                case '6':
                    N*=10;
                    N+=6;
                    fp++;
                    break;
                case '7':
                    N*=10;
                    N+=7;
                    fp++;
                    break;
                case '8':
                    N*=10;
                    N+=8;
                    fp++;
                    break;
                case '9':
                    N*=10;
                    N+=9;
                    fp++;
                    break;
                default:
                    goto    RDec;
                }
            numb++;
            }
        RDec:;
        }
    if(numb==0){
        return(NULL);
    }
    if(sign==true){
        N=-N;
    }
    return(fp);
}

bool    SeqControl::BPrintExecute(Sequence *seq ,QString &src, QString &formatStr)
{
    char    SBuff[1024];

    char    *sp=SBuff;
    int     slen=0;
    QChar    *dp=formatStr.data();

    while(*dp!=0){
        if(*dp=='[' && *(dp+1)!='['){
            dp++;
            while(*dp==' ' || *dp=='\t'){
                dp++;
            }

            bool    FmBin=false;    //書式指定：２進数
            bool    FmHex=false;    //書式指定：１６進数
            bool    FmDec=false;    //書式指定：１０進数
            bool    FmStr=false;    //書式指定：文字列桁数指定
            bool    FmNumbOn=false; //書式指定：桁数指定があるか否か
            int     FmNNumb=32;     //書式指定：数値桁数
            int     FmCNumb=1024;   //書式指定：文字桁数
            bool    ZeroExtent=false;   //上位０拡張
            if(*dp=='('){
                dp++;
                while(*dp==' ' || *dp=='\t'){
                    dp++;
                }
                if(*dp=='B' || *dp=='b'){
                    FmBin=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    if(*dp!=')'){
                        if(*dp=='0'){
                            ZeroExtent=true;
                            dp++;
                        }
                        dp=(QChar *)GetNumberOnly(dp,FmNNumb,8);
                        FmNumbOn=true;
                    }
                }
                else
                if(*dp=='H' || *dp=='h'){
                    FmHex=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    if(*dp!=')'){
                        if(*dp=='0'){
                            ZeroExtent=true;
                            dp++;
                        }
                        dp=(QChar *)GetNumberOnly(dp,FmNNumb,8);
                        FmNumbOn=true;
                    }
                }
                else
                if(*dp=='D' || *dp=='d'){
                    FmDec=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    if(*dp!=')'){
                        if(*dp=='0'){
                            ZeroExtent=true;
                            dp++;
                        }
                        dp=(QChar *)GetNumberOnly(dp,FmNNumb,8);
                        FmNumbOn=true;
                    }
                }
                else
                if(*dp=='C' || *dp=='c'){
                    FmStr=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    if(*dp=='0'){
                        ZeroExtent=true;
                        dp++;
                    }
                    dp=(QChar *)GetNumberOnly(dp,FmCNumb,10);
                    FmNumbOn=true;
                }

                if(dp==NULL){
                    return(false);
                }
                if(*dp!=')'){
                    return(false);
                }
                dp++;
            }
            if(FmNNumb>sizeof(int)*8){
                FmNNumb=sizeof(int)*8;
            }

            QChar    c=*dp;
			if(c=='l' || c=='L'){
	            dp++;
				c=*dp;
				dp++;
		        while(*dp==' ' || *dp=='\t'){
			        dp++;
                }
					
	            int N;
		        dp=(QChar *)GetNumberOnly(dp,N,8);
	            if(dp==NULL){
		            return(false);
                }
			    if(N<0 || N>MaxMomoryRegisterSize){
	                return(false);
                }

	            while(*dp==' ' || *dp=='\t'){
		            dp++;
                }
			    if(*dp!=']'){
				    return(false);
                }
	            dp++;
		        if(c=='B' || c=='b'
			    || c=='P' || c=='p'){
				    Operand  *r=NULL;
					if(c=='B' || c=='b'){
	                    r=SearchReg(seq ,&seq->LocalRegs.LocalBitOpe,N);
                    }
	                if(r!=NULL){
					    int d=r->GetNumeric();
		                if(d==0){
			                *sp='0';
                        }
				        else{
					        *sp='1';
                        }
						sp++;
	                    slen++;
		                if(slen>=sizeof(SBuff)){
			                return(false);
	                    }
                    }
		            else{
			            return(false);
				    }
                }
	            else
		        if(c=='W' || c=='w'
			    || c=='S' || c=='s'
				|| c=='F' || c=='f'){
	                Operand  *r=NULL;
		            if(c=='W' || c=='w'){
			            r=SearchReg(seq ,&seq->LocalRegs.LocalWordOpe,N);
                    }
	                else
		            if(c=='F' || c=='f'){
			            r=SearchReg(seq ,&seq->LocalRegs.LocalFloatOpe,N);
                    }
				    if(r!=NULL){
					    if(FmBin==true){
						    int d=r->GetNumeric();
							for(int i=FmNNumb-1;i>=0;i--){
								if((d&(0x1<<i))==0){
									*sp='0';
                                }
	                            else{
		                            *sp='1';
                                }
			                    sp++;
				                slen++;
					            if(slen>=sizeof(SBuff)){
						            return(false);
							    }
	                        }
                        }
		                else
			            if(FmHex==true){
				            int d=r->GetNumeric();
					        if(FmNumbOn==true){
						        for(int i=FmNNumb-1;i>=0;i--){
							        int k=(d>>(i<<4))&0x0F;
								    switch(k){
									    case 0: *sp='0';    break;
										case 1: *sp='1';    break;
	                                    case 2: *sp='2';    break;
		                                case 3: *sp='3';    break;
			                            case 4: *sp='4';    break;
				                        case 5: *sp='5';    break;
					                    case 6: *sp='6';    break;
						                case 7: *sp='7';    break;
							            case 8: *sp='8';    break;
								        case 9: *sp='9';    break;
									    case 10:*sp='A';    break;
										case 11:*sp='B';    break;
	                                    case 12:*sp='C';    break;
		                                case 13:*sp='D';    break;
			                            case 14:*sp='E';    break;
				                        case 15:*sp='F';    break;
					                    }

	                                sp++;
		                            slen++;
			                        if(slen>=sizeof(SBuff)){
				                        return(false);
					                }
						        }
                            }
							else{
								int i;
	                            for(i=sizeof(int)/16;i>=0;i--){
		                            int k=(d>>(i<<4))&0x0F;
			                        if(k!=0){
				                        break;
					                }
                                }
						        for(;i>=0;i--){
							        int k=(d>>(i<<4))&0x0F;
								    switch(k){
									    case 0: *sp='0';    break;
										case 1: *sp='1';    break;
	                                    case 2: *sp='2';    break;
		                                case 3: *sp='3';    break;
			                            case 4: *sp='4';    break;
				                        case 5: *sp='5';    break;
					                    case 6: *sp='6';    break;
						                case 7: *sp='7';    break;
							            case 8: *sp='8';    break;
								        case 9: *sp='9';    break;
									    case 10:*sp='A';    break;
										case 11:*sp='B';    break;
	                                    case 12:*sp='C';    break;
		                                case 13:*sp='D';    break;
			                            case 14:*sp='E';    break;
				                        case 15:*sp='F';    break;
					                    }

	                                sp++;
		                            slen++;
			                        if(slen>=sizeof(SBuff)){
				                        return(false);
					                }
						        }
							}
                        }
	                    else
		                if(FmDec==true){
			                if(c=='W' || c=='w'
				            || c=='S' || c=='s'){
					            int d=r->GetNumeric();
						        if(d<0){
							        *sp='-';
								    sp++;
									slen++;
	                                if(slen>=sizeof(SBuff)){
		                                return(false);
                                    }
			                        d=-d;
				                }
					            if(FmNumbOn==true){
						            for(int i=FmNNumb-1;i>=0;i--){
							            int pw=1;
								        for(int j=0;j<i;j++){
									        pw=pw*10;
										}
	                                    int k=(d/pw)%10;
		                                *sp=(char)('0'+k);
			                            sp++;
				                        slen++;
					                    if(slen>=sizeof(SBuff)){
						                    return(false);
							            }
								    }
                                }
	                            else{
		                            int i;
			                        for(i=10;i>=0;i--){
				                        int pw=1;
					                    for(int j=0;j<i;j++){
						                    pw=pw*10;
							            }
								        int k=(d/pw)%10;
									    if(k!=0){
										    break;
	                                    }
                                    }
		                            for(;i>=0;i--){
			                            int pw=1;
				                        for(int j=0;j<i;j++){
					                        pw=pw*10;
						                }
							            int k=(d/pw)%10;
								        *sp=(char)('0'+k);
									    sp++;
										slen++;
	                                    if(slen>=sizeof(SBuff)){
		                                    return(false);
			                            }
				                    }
					            }
                            }
						    else
							if(c=='F' || c=='f'){
								char    mbuff[50];
	                            sprintf(mbuff,"%lf",r->GetFloat());
		                        if(FmNumbOn==true){
			                        for(int i=0;i<FmNNumb;i++){
				                        *sp=mbuff[i];
					                    sp++;
						                slen++;
							            if(slen>=sizeof(SBuff)){
								            return(false);
									    }
	                                }
                                }
		                        else{
			                        for(int i=0;mbuff[i]!=0;i++){
				                        *sp=mbuff[i];
					                    sp++;
						                slen++;
							            if(slen>=sizeof(SBuff)){
								            return(false);
	                                    }
		                            }
			                    }
				            }
                        }
					    else{
						    if(c=='W' || c=='w'
							|| c=='S' || c=='s'){
								int d=r->GetNumeric();
	                            if(d<0){
		                            *sp='-';
			                        sp++;
				                    slen++;
					                if(slen>=sizeof(SBuff)){
						                return(false);
                                    }
							        d=-d;
								}
	                            int i;
		                        if(d>0){
			                        for(i=10;i>=0;i--){
				                        int pw=1;
					                    for(int j=0;j<i;j++){
						                    pw=pw*10;
							            }
								        int k=(d/pw)%10;
									    if(k!=0){
										    break;
	                                    }
                                    }
		                            for(;i>=0;i--){
			                            int pw=1;
				                        for(int j=0;j<i;j++){
					                        pw=pw*10;
						                }
							            int k=(d/pw)%10;
								        *sp=(char)('0'+k);
									    sp++;
	                                    slen++;
		                                if(slen>=sizeof(SBuff)){
			                                return(false);
				                        }
					                }
                                }
						        else{
							        *sp='0';
								    sp++;
									slen++;
	                                if(slen>=sizeof(SBuff)){
		                                return(false);
			                        }
				                }
                            }
					        else
						    if(c=='F' || c=='f'){
							    char    mbuff[50];
								sprintf(mbuff,"%lf",r->GetFloat());
	                            for(int i=0;mbuff[i]!=0;i++){
		                            *sp=mbuff[i];
			                        sp++;
				                    slen++;
					                if(slen>=sizeof(SBuff)){
						                return(false);
							        }
								}
	                        }
		                }
                    }
			        else{
				        return(false);
	                }
                }
		        else
			    if(c=='C' || c=='c'
				|| c=='Q' || c=='q'){
					Operand  *r=NULL;
	                if(c=='C' || c=='c'){
		                r=SearchReg(seq ,&seq->LocalRegs.LocalStringOpe,N);
                    }
	                if(r!=NULL){
		                char    *kp=(char *)r->GetString().data();
			            if(FmStr==true){
				            for(int i=0;i<FmCNumb && i<r->GetStringCount();i++,kp++){
					            *sp=*kp;
						        sp++;
							    slen++;
								if(slen>=sizeof(SBuff)){
									return(false);
	                            }
		                    }
                        }
			            else{
				            for(int i=0;i<r->GetStringCount();i++,kp++){
					            *sp=*kp;
						        sp++;
							    slen++;
								if(slen>=sizeof(SBuff)){
									return(false);
	                            }
		                    }
						}
                    }
				}
            }
			else{
	            dp++;
		        while(*dp==' ' || *dp=='\t'){
			        dp++;
                }
					
	            int N;
		        dp=(QChar *)GetNumberOnly(dp,N,8);
	            if(dp==NULL){
		            return(false);
                }
			    if(N<0 || N>MaxMomoryRegisterSize){
	                return(false);
                }

	            while(*dp==' ' || *dp=='\t'){
		            dp++;
                }
			    if(*dp!=']'){
				    return(false);
                }
	            dp++;
		        if(c=='B' || c=='b'
			    || c=='P' || c=='p'){
				    Operand  *r=NULL;
					if(c=='B' || c=='b'){
	                    r=SearchReg(seq ,&BitOpe,N);
                    }
		            else
			        if(c=='P' || c=='p'){
				        r=SearchReg(seq ,&SpecialBitOpe,N);
                    }
	                if(r!=NULL){
					    int d=r->GetNumeric();
		                if(d==0){
			                *sp='0';
                        }
				        else{
					        *sp='1';
                        }
						sp++;
	                    slen++;
		                if(slen>=sizeof(SBuff)){
			                return(false);
	                    }
                    }
		            else{
			            return(false);
				    }
                }
	            else
		        if(c=='W' || c=='w'
			    || c=='S' || c=='s'
				|| c=='F' || c=='f'){
	                Operand  *r=NULL;
		            if(c=='W' || c=='w'){
			            r=SearchReg(seq ,&WordOpe,N);
                    }
				    else
					if(c=='S' || c=='s'){
						r=SearchReg(seq ,&SpecialOpe,N);
                    }
	                else
		            if(c=='F' || c=='f'){
			            r=SearchReg(seq ,&FloatOpe,N);
                    }
				    if(r!=NULL){
					    if(FmBin==true){
						    int d=r->GetNumeric();
							for(int i=FmNNumb-1;i>=0;i--){
								if((d&(0x1<<i))==0){
									*sp='0';
                                }
	                            else{
		                            *sp='1';
                                }
			                    sp++;
				                slen++;
					            if(slen>=sizeof(SBuff))
						            return(false);
							    }
	                        }
		                else
			            if(FmHex==true){
				            int d=r->GetNumeric();
					        if(FmNumbOn==true){
						        for(int i=FmNNumb-1;i>=0;i--){
							        int k=(d>>(i<<4))&0x0F;
								    switch(k){
									    case 0: *sp='0';    break;
										case 1: *sp='1';    break;
	                                    case 2: *sp='2';    break;
		                                case 3: *sp='3';    break;
			                            case 4: *sp='4';    break;
				                        case 5: *sp='5';    break;
					                    case 6: *sp='6';    break;
						                case 7: *sp='7';    break;
							            case 8: *sp='8';    break;
								        case 9: *sp='9';    break;
									    case 10:*sp='A';    break;
										case 11:*sp='B';    break;
	                                    case 12:*sp='C';    break;
		                                case 13:*sp='D';    break;
			                            case 14:*sp='E';    break;
				                        case 15:*sp='F';    break;
					                    }

	                                sp++;
		                            slen++;
			                        if(slen>=sizeof(SBuff)){
				                        return(false);
                                    }
					            }
						    }
							else{
								int i;
	                            for(i=sizeof(int)/16;i>=0;i--){
		                            int k=(d>>(i<<4))&0x0F;
			                        if(k!=0){
				                        break;
                                    }
					            }
						        for(;i>=0;i--){
							        int k=(d>>(i<<4))&0x0F;
								    switch(k){
									    case 0: *sp='0';    break;
										case 1: *sp='1';    break;
	                                    case 2: *sp='2';    break;
		                                case 3: *sp='3';    break;
			                            case 4: *sp='4';    break;
				                        case 5: *sp='5';    break;
					                    case 6: *sp='6';    break;
						                case 7: *sp='7';    break;
							            case 8: *sp='8';    break;
								        case 9: *sp='9';    break;
									    case 10:*sp='A';    break;
										case 11:*sp='B';    break;
	                                    case 12:*sp='C';    break;
		                                case 13:*sp='D';    break;
			                            case 14:*sp='E';    break;
				                        case 15:*sp='F';    break;
					                    }

	                                sp++;
		                            slen++;
			                        if(slen>=sizeof(SBuff)){
				                        return(false);
                                    }
					            }
						    }
				        }
	                    else
		                if(FmDec==true){
			                if(c=='W' || c=='w'
				            || c=='S' || c=='s'){
					            int d=r->GetNumeric();
						        if(d<0){
							        *sp='-';
								    sp++;
									slen++;
	                                if(slen>=sizeof(SBuff)){
		                                return(false);
                                    }
			                        d=-d;
				                }
					            if(FmNumbOn==true){
						            for(int i=FmNNumb-1;i>=0;i--){
							            int pw=1;
								        for(int j=0;j<i;j++){
									        pw=pw*10;
										}
	                                    int k=(d/pw)%10;
		                                *sp=(char)('0'+k);
			                            sp++;
				                        slen++;
					                    if(slen>=sizeof(SBuff)){
						                    return(false);
                                        }
							        }
								}
	                            else{
		                            int i;
			                        for(i=10;i>=0;i--){
				                        int pw=1;
					                    for(int j=0;j<i;j++){
						                    pw=pw*10;
							            }
								        int k=(d/pw)%10;
									    if(k!=0){
										    break;
                                        }
	                                }
		                            for(;i>=0;i--){
			                            int pw=1;
				                        for(int j=0;j<i;j++){
					                        pw=pw*10;
						                }
							            int k=(d/pw)%10;
								        *sp=(char)('0'+k);
									    sp++;
										slen++;
	                                    if(slen>=sizeof(SBuff)){
		                                    return(false);
                                        }
			                        }
				                }
					        }
						    else
							if(c=='F' || c=='f'){
								char    mbuff[50];
	                            sprintf(mbuff,"%lf",r->GetFloat());
		                        if(FmNumbOn==true){
			                        for(int i=0;i<FmNNumb;i++){
				                        *sp=mbuff[i];
					                    sp++;
						                slen++;
							            if(slen>=sizeof(SBuff)){
								            return(false);
                                        }
									}
	                            }
		                        else{
			                        for(int i=0;mbuff[i]!=0;i++){
				                        *sp=mbuff[i];
					                    sp++;
						                slen++;
							            if(slen>=sizeof(SBuff)){
								            return(false);
                                        }
	                                }
		                        }
			                }
				        }
					    else{
						    if(c=='W' || c=='w'
							|| c=='S' || c=='s'){
								int d=r->GetNumeric();
	                            if(d<0){
		                            *sp='-';
			                        sp++;
				                    slen++;
					                if(slen>=sizeof(SBuff)){
						                return(false);
                                    }
							        d=-d;
								}
	                            int i;
		                        if(d>0){
			                        for(i=10;i>=0;i--){
				                        int pw=1;
					                    for(int j=0;j<i;j++){
						                    pw=pw*10;
							            }
								        int k=(d/pw)%10;
									    if(k!=0){
										    break;
                                        }
	                                }
		                            for(;i>=0;i--){
			                            int pw=1;
				                        for(int j=0;j<i;j++){
					                        pw=pw*10;
						                }
							            int k=(d/pw)%10;
								        *sp=(char)('0'+k);
									    sp++;
	                                    slen++;
		                                if(slen>=sizeof(SBuff)){
			                                return(false);
                                        }
				                    }
					            }
						        else{
							        *sp='0';
								    sp++;
									slen++;
	                                if(slen>=sizeof(SBuff)){
		                                return(false);
			                        }
				                }
                            }
					        else
						    if(c=='F' || c=='f'){
							    char    mbuff[50];
								sprintf(mbuff,"%lf",r->GetFloat());
	                            for(int i=0;mbuff[i]!=0;i++){
		                            *sp=mbuff[i];
			                        sp++;
				                    slen++;
					                if(slen>=sizeof(SBuff)){
						                return(false);
                                    }
							    }
					        }
	                    }
		            }
			        else{
				        return(false);
	                }
                }
		        else
			    if(c=='C' || c=='c'
				|| c=='Q' || c=='q'){
					Operand  *r=NULL;
	                if(c=='C' || c=='c'){
		                r=SearchReg(seq ,&StringOpe,N);
                    }
			        else
				    if(c=='Q' || c=='q'){
					    r=SearchReg(seq ,&SpecialStringOpe,N);
                    }
						
	                if(r!=NULL){
		                char    *kp=(char *)r->GetString().data();
			            if(FmStr==true){
				            for(int i=0;i<FmCNumb && i<r->GetStringCount();i++,kp++){
					            *sp=*kp;
						        sp++;
							    slen++;
								if(slen>=sizeof(SBuff)){
									return(false);
                                }
	                        }
		                }
			            else{
				            for(int i=0;i<r->GetStringCount();i++,kp++){
					            *sp=*kp;
						        sp++;
							    slen++;
								if(slen>=sizeof(SBuff)){
									return(false);
	                            }
		                    }
						}
                    }
                }
            }
        }
        else
        if(*dp=='[' && *(dp+1)=='['){
            dp+=2;
            *sp='[';
            sp++;
            slen++;
            if(slen>=sizeof(SBuff)){
                return(false);
            }
        }
        else{
            *sp=dp->toLatin1();
            dp++;
            sp++;
            slen++;
            if(slen>=sizeof(SBuff)){
                return(false);
            }
        }
    }
    *sp=0;
    src=SBuff;
    return(true);
}

bool    SeqControl::BScanExecute(Sequence *seq ,QString &src, QString &formatStr)
{
	char	formatStrBuff[1000];
	char	srcBuff[1000];

	QString2Char(formatStr,formatStrBuff ,sizeof(formatStrBuff));
	QString2Char(src,srcBuff ,sizeof(srcBuff));

    char    *dp=formatStrBuff;
    char    *sp=srcBuff;

    while(*dp!=0){
        if(*dp=='[' && *(dp+1)!='['){
            dp++;
            while(*dp==' ' || *dp=='\t'){
                dp++;
            }

            bool    FmBin=false;    //書式指定：２進数
            bool    FmHex=false;    //書式指定：１６進数
            bool    FmDec=false;    //書式指定：１０進数
            bool    FmStr=false;    //書式指定：文字列桁数指定
            int     FmNNumb=32;     //書式指定：数値桁数
            int     FmCNumb=1024;   //書式指定：文字桁数
            if(*dp=='('){
	            dp++;
                while(*dp==' ' || *dp=='\t'){
                    dp++;
                }
                if(*dp=='B' || *dp=='b'){
                    FmBin=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    if(*dp!=')'){
                        dp=GetNumberOnly(dp,FmNNumb,8);
                    }
                }
                else
                if(*dp=='H' || *dp=='h'){
                    FmHex=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    if(*dp!=')'){
                        dp=GetNumberOnly(dp,FmNNumb,8);
                    }
                }
                else
                if(*dp=='D' || *dp=='d'){
                    FmDec=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    if(*dp!=')'){
                        dp=GetNumberOnly(dp,FmNNumb,8);
                    }
                }
                else
                if(*dp=='C' || *dp=='c'){
                    FmStr=true;
                    dp++;
                    while(*dp==' ' || *dp=='\t'){
                        dp++;
                    }
                    dp=GetNumberOnly(dp,FmCNumb,10);
                }

                if(dp==NULL){
                    return(false);
                }
                if(*dp!=')'){
                    return(false);
                }
                dp++;
            }
            if(FmNNumb>sizeof(int)*8){
                FmNNumb=sizeof(int)*8;
            }

            char    c=*dp;
			if(c=='l' || c=='L'){
	            dp++;
				c=*dp;
				dp++;
		        while(*dp==' ' || *dp=='\t'){
			        dp++;
                }

	            int RegN;
		        dp=GetNumberOnly(dp,RegN,8);
			    if(dp==NULL){
				    return(false);
                }
	            if(RegN<0 || RegN>MaxMomoryRegisterSize){
		            return(false);
                }

	            while(*dp==' ' || *dp=='\t'){
		            dp++;
                }
			    if(*dp!=']'){
				    return(false);
                }
	            dp++;
		        if(c=='B' || c=='b'
			    || c=='P' || c=='p'){
				    int N;
	                sp=GetNumberOnly(sp ,N ,1);
		            if(sp==NULL){
			            return(false);
                    }

	                if(N!=1 && N!=0){
		                return(false);
                    }
						
	                Operand  *r=NULL;
		            if(c=='B' || c=='b'){
			            r=SearchReg(seq,&seq->LocalRegs.LocalBitOpe,RegN);
                    }
	                if(r!=NULL){
		                r->SetData(N);
			        }
                }
				if(c=='W' || c=='w'
	            || c=='S' || c=='s'){
		            int N;
			        sp=GetNumberOnlyBySourceNumb(sp ,N ,FmNNumb);
				    if(sp==NULL){
					    return(false);
                    }

					Operand  *r=NULL;
	                if(c=='W' || c=='w'){
		                r=SearchReg(seq,&seq->LocalRegs.LocalWordOpe,RegN);
                    }
	                if(r!=NULL){
		                r->SetData(N);
			        }
                }

	            else
		        if(c=='C' || c=='c'
			    || c=='Q' || c=='q'){
				    StringOperand  *r=NULL;
					if(c=='C' || c=='c'){
						r=(StringOperand  *)SearchReg(seq,&seq->LocalRegs.LocalStringOpe,RegN);
                    }
	                if(r!=NULL){
		                if(FmStr==true){
			                char    *rbuff=new char[FmCNumb+1];
				            strncpy(rbuff,sp,FmCNumb);
					        rbuff[FmCNumb]=0;
							QString	Q=QString(rbuff);
							r->SetData(Q);
	                        sp+=strlen(rbuff);
		                    delete  []rbuff;
			            }
				        else{
							QString	Q=QString(sp);
						    r->SetData(Q);
							sp+=strlen(sp);
                        }
                    }
                }
            }
			else{
	            dp++;
		        while(*dp==' ' || *dp=='\t'){
			        dp++;
                }

	            int RegN;
		        dp=GetNumberOnly(dp,RegN,8);
			    if(dp==NULL){
				    return(false);
                }
	            if(RegN<0 || RegN>MaxMomoryRegisterSize){
		            return(false);
                }

	            while(*dp==' ' || *dp=='\t'){
		            dp++;
                }
			    if(*dp!=']'){
				    return(false);
                }
	            dp++;
		        if(c=='B' || c=='b'
			    || c=='P' || c=='p'){
				    int N;
	                sp=GetNumberOnly(sp ,N ,1);
		            if(sp==NULL){
			            return(false);
                    }

	                if(N!=1 && N!=0){
		                return(false);
                    }
						
	                Operand  *r=NULL;
		            if(c=='B' || c=='b'){
			            r=SearchReg(seq,&BitOpe,RegN);
                    }
				    else
					if(c=='P' || c=='p'){
						r=SearchReg(seq,&SpecialBitOpe,RegN);
                    }
	                if(r!=NULL){
		                r->SetData(N);
			        }
                }
				if(c=='W' || c=='w'
	            || c=='S' || c=='s'){
		            int N;
			        sp=GetNumberOnlyBySourceNumb(sp ,N ,FmNNumb);
				    if(sp==NULL){
					    return(false);
                    }

					Operand  *r=NULL;
	                if(c=='W' || c=='w'){
		                r=SearchReg(seq,&WordOpe,RegN);
                    }
			        else
				    if(c=='S' || c=='s'){
					    r=SearchReg(seq,&SpecialOpe,RegN);
                    }
	                if(r!=NULL){
		                r->SetData(N);
			        }
                }

	            else
		        if(c=='C' || c=='c'
			    || c=='Q' || c=='q'){
				    StringOperand  *r=NULL;
					if(c=='C' || c=='c'){
						r=(StringOperand  *)SearchReg(seq,&StringOpe,RegN);
                    }
	                else
		            if(c=='Q' || c=='q'){
			            r=(StringOperand  *)SearchReg(seq,&SpecialStringOpe,RegN);
                    }
						
	                if(r!=NULL){
		                if(FmStr==true){
			                char    *rbuff=new char[FmCNumb+1];
				            strncpy(rbuff,sp,FmCNumb);
					        rbuff[FmCNumb]=0;
							QString	Q=QString(rbuff);
							r->SetData(Q);
	                        sp+=strlen(rbuff);
		                    delete  []rbuff;
			            }
				        else{
							QString	Q=QString(sp);
						    r->SetData(Q);
							sp+=strlen(sp);
					    }
                    }
                }
            }
        }
        else
        if(*dp=='[' && *(dp+1)=='['){
            dp+=2;
            if(*sp!='['){
                return(false);
            }
            sp++;
        }
        else
        if(*dp=='\x20'){
            if(*sp!='\x20' && *sp!='\t'){
                return(false);
            }
            sp++;
            while(*sp=='\x20' || *sp=='\t'){
                sp++;
            }
            dp++;
            }
        else
        if(*dp=='\\' && *(dp+1)=='t'){
            while(*sp=='\x20' || *sp=='\t'){
                sp++;
            }
            dp+=2;
            }
        else
        if(*dp=='\\' && *(dp+1)=='0'){
            if(*sp!=0){
                return(false);
            }
            sp++;
            dp+=2;
        }
        else
        if(*dp=='\\' && isxdigit(*(dp+1))!=0){
            if(isxdigit(*(dp+2))!=0){
                //int i1=SequenceStock::ToXDigit(*(dp+1));
				int i1=SequenceStock(this).ToXDigit(*(dp+1));
                //int i2=SequenceStock::ToXDigit(*(dp+2));
				int i2=SequenceStock(this).ToXDigit(*(dp+2));
                if(*sp!=(i1*16+i2)){
                    return(false);
                }
                sp++;
                dp+=3;
            }
            else{
                //int i1=SequenceStock::ToXDigit(*(dp+1));
				int i1=SequenceStock(this).ToXDigit(*(dp+1));
                if(*sp!=i1){
                    return(false);
                }
                sp++;
                dp+=2;
            }
        }
        else
        if(*dp=='\\' && *(dp+1)=='\\'){
            if(*sp!='\\'){
                return(false);
            }
            dp+=2;
        }
        else{
            if(*sp!=*dp){
                return(false);
            }
            dp++;
            sp++;
        }
    }
    return(true);
}


Operand *SeqControl::SearchReg(Sequence *seq ,const QString &regname)
{
    for(IOOperand       *c=IOOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(CommOperand     *c=CommOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(BitOperand      *c=BitOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(WordOperand     *c=WordOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(FloatOperand    *c=FloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(StringOperand   *c=StringOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(SpecialOperand  *c=SpecialOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(GroupOperand  *c=GroupOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(SpecialBitOperand  *c=SpecialBitOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(SpecialStringOperand  *c=SpecialStringOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(SpecialFloatOperand  *c=SpecialFloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
///    for(LanvarOperand   *c=LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){	//D-20051026
///        if(strcmp(c->GetName(),(char *)regname.data())==0)
///            return(c);
///        }
    for(FifoOperand   *c=FifoOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    for(DLLVarOperand *c=DLLVarOpe.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetName().compare(regname)==0){
            return(c);
        }
    }
    if(seq!=NULL){
        return(seq->SearchReg(regname));
    }
    return(NULL);
}

Operand *SeqControl::SearchReg(int OpeKindCode ,int OpeId)
{
    for(IOOperand       *c=IOOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(CommOperand     *c=CommOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(BitOperand      *c=BitOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(WordOperand     *c=WordOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(FloatOperand    *c=FloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(StringOperand   *c=StringOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(SpecialOperand  *c=SpecialOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(GroupOperand  *c=GroupOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(SpecialBitOperand  *c=SpecialBitOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(SpecialStringOperand  *c=SpecialStringOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(SpecialFloatOperand  *c=SpecialFloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
///    for(LanvarOperand   *c=LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){	//D-20051026
///        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId)
///            return(c);
///        }
    for(FifoOperand   *c=FifoOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    for(DLLVarOperand *c=DLLVarOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetKindCode()==OpeKindCode && c->GetID()==OpeId){
            return(c);
        }
    }
    return(NULL);
}


Operand *LocalReg::SearchReg(QString regname)
{
    for(LocalBitOperand   *c=LocalBitOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetName()==regname){
            return(c);
        }
    }
    for(LocalWordOperand   *c=LocalWordOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetName()==regname){
            return(c);
        }
    }
    for(LocalFloatOperand   *c=LocalFloatOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetName()==regname){
            return(c);
        }
    }
    for(LocalStringOperand   *c=LocalStringOpe.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->GetName()==regname){
            return(c);
        }
    }
    return(NULL);
}

bool    SeqControl::Initial(void)
{
    //if(LanVarCSection==NULL)
    //   LanVarCSection=new QMutex();
///    LanVarRData.RemoveAll();	//D-20051026
    for(CommOperand *p=CommOpe.GetFirst();p!=NULL;p=p->GetNext()){
        p->Initial();
    }
    return(true);
}

bool    SeqControl::NetInitial(void)
{
	return(true);
/*↓D-20051026------------------------------------------------------------------
    if(LanvarOpe.GetNumber()==0)
        return(false);
    if(ServerSock!=NULL){
        ServerSock->Close();
        delete  ServerSock;
        }
    ServerSock=new MTWSocket(Application->MainForm);
    ServerSock->Close();
    ServerSock->FlushTimeout=60;
    ServerSock->LineEcho=false;
    ServerSock->LineEdit=false;
    ServerSock->LineLimit=false;
    ServerSock->LineMode=false;
    ServerSock->LingerOnOff=wsLingerOn;
    ServerSock->LocalAddr="0.0.0.0";
    ServerSock->LocalPort=0;
    ServerSock->Name    ="SequenceServer";
    ServerSock->Port=LanvarPort;
    ServerSock->Addr  = "0.0.0.0";
    ServerSock->Proto  = "tcp";              // Protocol we wants to use
    ServerSock->OnSessionAvailable=SeqControlInstance.ServerSockSessionAvailable;
    ServerSock->Listen();
    return(true);
↑D-20051026------------------------------------------------------------------*/
}
/*↓D-20051026------------------------------------------------------------------
void  SeqControl::ServerSockSessionAvailable(
                              TObject *Sender, WORD Error)
{
    for(LanVarSocketList *s=LanVarSocket.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->IsConnected()==false)
            s->Connect();
        }

    LanVarSocketList    *p=new LanVarSocketList();
    p->CliSock=new MTWSocket(Application->MainForm);
    p->CliSock->LineMode =false;
    p->CliSock->OnDataAvailable=p->RReceiverDataAvailable;
    p->CliSock->OnSessionClosed=p->RReceiverSessionClosed;

    p->CliSock->HSocket  =ServerSock->Accept();
    p->BuiltInListen=true;

    LanVarSocket.AppendList(p);
}
↑D-20051026------------------------------------------------------------------*/

Operand *BitOperandPack::GetItemFromID(int id)
{
    for(BitOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}

Operand *WordOperandPack::GetItemFromID(int id)
{
    for(WordOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
Operand *FloatOperandPack::GetItemFromID(int id)
{
    for(FloatOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
Operand *StringOperandPack::GetItemFromID(int id)
{
    for(StringOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}

Operand *LocalBitOperandPack::GetItemFromID(int id)
{
    for(LocalBitOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}

Operand *LocalWordOperandPack::GetItemFromID(int id)
{
    for(LocalWordOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
Operand *LocalFloatOperandPack::GetItemFromID(int id)
{
    for(LocalFloatOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
Operand *LocalStringOperandPack::GetItemFromID(int id)
{
    for(LocalStringOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}

Operand *SpecialOperandPack::GetItemFromID(int id)
{
    for(SpecialOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
Operand *SpecialBitOperandPack::GetItemFromID(int id)
{
    for(SpecialBitOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
Operand *SpecialStringOperandPack::GetItemFromID(int id)
{
    for(SpecialStringOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
Operand *SpecialFloatOperandPack::GetItemFromID(int id)
{
    for(SpecialFloatOperand *d=GetFirst();d!=NULL;d=d->GetNext()){
        if(d->GetID()==id){
            return(d);
        }
    }
    return(NULL);
}
int     IOOperandPack::GetNumber(void)
{
    int N=0;
    for(IOOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     CommOperandPack::GetNumber(void)
{
    int N=0;
    for(CommOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     BitOperandPack::GetNumber(void)
{
    int N=0;
    for(BitOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     WordOperandPack::GetNumber(void)
{
    int N=0;
    for(WordOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     FloatOperandPack::GetNumber(void)
{
    int N=0;
    for(FloatOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     StringOperandPack::GetNumber(void)
{
    int N=0;
    for(StringOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     LocalBitOperandPack::GetNumber(void)
{
    int N=0;
    for(LocalBitOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     LocalWordOperandPack::GetNumber(void)
{
    int N=0;
    for(LocalWordOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     LocalFloatOperandPack::GetNumber(void)
{
    int N=0;
    for(LocalFloatOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     LocalStringOperandPack::GetNumber(void)
{
    int N=0;
    for(LocalStringOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     SpecialOperandPack::GetNumber(void)
{
    int N=0;
    for(SpecialOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     NumberOperandPack::GetNumber(void)
{
    int N=0;
    for(NumberOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     CharOperandPack::GetNumber(void)
{
    int N=0;
    for(CharOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     GroupOperandPack::GetNumber(void)
{
    int N=0;
    for(GroupOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     SpecialBitOperandPack::GetNumber(void)
{
    int N=0;
    for(SpecialBitOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     SpecialStringOperandPack::GetNumber(void)
{
    int N=0;
    for(SpecialStringOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
int     SpecialFloatOperandPack::GetNumber(void)
{
    int N=0;
    for(SpecialFloatOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
/*↓D-20051026------------------------------------------------------------------
int     LanvarOperandPack::GetNumber(void)
{
    int N=0;
    for(LanvarOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}
↑D-20051026------------------------------------------------------------------*/

int     FifoOperandPack::GetNumber(void)
{
    int N=0;
    for(FifoOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}

int     DLLVarOperandPack::GetNumber(void)
{
    int N=0;
    for(DLLVarOperand *d=GetFirst();d!=NULL;d=d->GetNext(),N++);
    return(N);
}


Operand *SeqControl::SearchReg(Sequence *seq ,OperandPackBase *base ,int id)
{
    return(base->GetItemFromID(id));
}


QString  SeqControl::GetTimingFileName(void)
{
    unsigned short  year;
    unsigned short  month;
    unsigned short  day;
    unsigned short  hour;
    unsigned short  min;
    unsigned short  sec;
    unsigned short  msec;

///    Now().DecodeDate(&year, &month, &day);	//D-20051026
	year=QDate::currentDate().year();
	month=QDate::currentDate().month();
	day=QDate::currentDate().day();
///    Now().DecodeTime(&hour, &min, &sec ,&msec);	//D-20051026
	hour=QTime::currentTime().hour();
	min=QTime::currentTime().minute();
	sec=QTime::currentTime().second();
	msec=QTime::currentTime().msec();

    QString  s=QString(year)  +QString("y")
                + QString(month) +QString("m")
                + QString(day)   +QString("d ")
                + QString(hour)  +QString("h")
                + QString(min)   +QString("m")
                + QString(sec)   +QString("s");

    if(TimingPath.length()!=0){
        if(*(TimingPath.data()+TimingPath.length()-1)=='\\'){
            return(TimingPath+QString("SeqTM ")+s+QString(".tmg"));
        }
        else{
            return(TimingPath+QString("/SeqTM ")+s+QString(".tmg"));
        }
    }
    else{
        return(QString("/SeqTM ")+s+QString(".tmg"));
    }
}


bool    SeqControl::WriteTimingFileTop(void)
{
	return(true);
}

bool    SeqLine::WriteBin(FILE *file)
{
    if(fwrite(&LNumber,sizeof(LNumber),1,file)!=1){
        return(false);
    }
    if(fwrite(&LCode  ,sizeof(LCode  ),1,file)!=1){
        return(false);
    }
    QString  E=eFlag.GetFlagString();
    if(WriteString(E,file)==false){
        return(false);
    }
    if(GetOpCount()>=1){
        int OpKindID=Op1->GetKindCode();
        if(fwrite(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID=Op1->GetID();
        if(fwrite(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
    }
    if(GetOpCount()>=2){
        int OpKindID=Op2->GetKindCode();
        if(fwrite(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID=Op2->GetID();
        if(fwrite(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
    }
    if(GetOpCount()>=3){
        int OpKindID=Op3->GetKindCode();
        if(fwrite(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID=Op3->GetID();
        if(fwrite(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
    }
    if(GetOpCount()>=4){
        int OpKindID=Op4->GetKindCode();
        if(fwrite(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID=Op4->GetID();
        if(fwrite(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
    }
    return(true);
}
bool    SeqLine::ReadBin(FILE *file)
{
    if(fread(&LNumber,sizeof(LNumber),1,file)!=1){
        return(false);
    }
    if(fread(&LCode  ,sizeof(LCode  ),1,file)!=1){
        return(false);
    }

    QString  E;
    if(ReadString(E,file)==false){
        return(false);
    }
    GetSeqControl()->SeqStock.GetFirst()->LoadFlag(&eFlag,(char *)E.data());
    if(GetOpCount()>=1){
        int OpKindID;
        if(fread(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID;
        if(fread(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
        Op1=GetSeqControl()->SearchReg(OpKindID ,OpID);
    }
    if(GetOpCount()>=2){
        int OpKindID;
        if(fread(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID;
        if(fread(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
        Op2=GetSeqControl()->SearchReg(OpKindID ,OpID);
    }
    if(GetOpCount()>=3){
        int OpKindID;
        if(fread(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID;
        if(fread(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
        Op3=GetSeqControl()->SearchReg(OpKindID ,OpID);
    }
    if(GetOpCount()>=4){
        int OpKindID;
        if(fread(&OpKindID,sizeof(OpKindID),1,file)!=1){
            return(false);
        }
        int OpID;
        if(fread(&OpID,sizeof(OpID),1,file)!=1){
            return(false);
        }
        Op4=GetSeqControl()->SearchReg(OpKindID ,OpID);
    }
    return(true);
}

SeqLine *SeqLine::Get(unsigned short OpID ,SeqControl *parent)
{
    SeqLine *ret;
    switch(OpID){
        case OpID_Let:
            ret=new LetSeq(parent);
            break;
        case OpID_LetB:
            ret=new LetBSeq(parent);
            break;
        case OpID_Add:
            ret=new AddSeq(parent);
            break;
        case OpID_Sub:
            ret=new SubSeq(parent);
            break;
        case OpID_And:
            ret=new AndSeq(parent);
            break;
        case OpID_Or:
            ret=new OrSeq(parent);
            break;
        case OpID_Xor:
            ret=new XorSeq(parent);
            break;
        case OpID_Not:
            ret=new NotSeq(parent);
            break;
        case OpID_Flush:
            ret=new FlushSeq(parent);
            break;
        case OpID_Alloc:
            ret=new AllocSeq(parent);
            break;
        case OpID_Ind:
            ret=new IndSeq(parent);
            break;
        case OpID_Bitload:
            ret=new BitloadSeq(parent);
            break;
        case OpID_Goto:
            ret=new GotoSeq(parent);
            break;
        case OpID_EqualGoto:
            ret=new EqualGotoSeq(parent);
            break;
        case OpID_NotEqualGoto:
            ret=new NotEqualGotoSeq(parent);
            break;
        case OpID_LargeGoto:
            ret=new LargeGotoSeq(parent);
            break;
        case OpID_GreaterGoto:
            ret=new GreaterGotoSeq(parent);
            break;
        case OpID_SmallGoto:
            ret=new SmallGotoSeq(parent);
            break;
        case OpID_LessGoto:
            ret=new LessGotoSeq(parent);
            break;
        case OpID_AndGoto:
            ret=new AndGotoSeq(parent);
            break;
        case OpID_OrGoto:
            ret=new OrGotoSeq(parent);
            break;
        case OpID_XorGoto:
            ret=new XorGotoSeq(parent);
            break;
        case OpID_Set:
            ret=new SetSeq(parent);
            break;
        case OpID_Reset:
            ret=new ResetSeq(parent);
            break;
        case OpID_Flag:
            ret=new FlagSeq(parent);
            break;
        case OpID_Wait:
            ret=new WaitSeq(parent);
            break;
        case OpID_CAnd:
            ret=new CAndSeq(parent);
            break;
        case OpID_COr:
            ret=new COrSeq(parent);
            break;
        case OpID_CXor:
            ret=new CXorSeq(parent);
            break;
        case OpID_Equal:
            ret=new EqualSeq(parent);
            break;
        case OpID_Zone:
            ret=new ZoneSeq(parent);
            break;
        case OpID_PartEq:
            ret=new PartEqSeq(parent);
            break;
        case OpID_Unequal:
            ret=new UnequalSeq(parent);
            break;
        case OpID_Greater:
            ret=new GreaterSeq(parent);
            break;
        case OpID_Large:
            ret=new LargeSeq(parent);
            break;
        case OpID_Less:
            ret=new LessSeq(parent);
            break;
        case OpID_Small:
            ret=new SmallSeq(parent);
            break;
        case OpID_MOut:
            ret=new MOutSeq(parent);
            break;
        case OpID_MYesNo:
            ret=new MYesNoSeq(parent);
            break;
        case OpID_Mult:
            ret=new MultSeq(parent);
            break;
        case OpID_Div:
            ret=new DivSeq(parent);
            break;
        case OpID_Mod:
            ret=new ModSeq(parent);
            break;
        case OpID_StrMove:
            ret=new StrMoveSeq(parent);
            break;
        case OpID_Lower:
            ret=new LowerSeq(parent);
            break;
        case OpID_Upper:
            ret=new UpperSeq(parent);
            break;
        case OpID_State:
            ret=new StateSeq(parent);
            break;
        case OpID_Return:
            ret=new ReturnSeq(parent);
            break;
        case OpID_TWSet:
            ret=new TWSetSeq(parent);
            break;
        case OpID_TWaitLess:
            ret=new TWaitLessSeq(parent);
            break;
        case OpID_TWaitGreater:
            ret=new TWaitGreaterSeq(parent);
            break;
        case OpID_FSet:
            ret=new FSetSeq(parent);
            break;
        case OpID_FReset:
            ret=new FResetSeq(parent);
            break;
        case OpID_RxTimeout:
            ret=new RxTimeoutSeq(parent);
            break;
        case OpID_StrLen:
            ret=new StrLenSeq(parent);
            break;
        case OpID_AddFile:
            ret=new AddFileSeq(parent);
            break;
        case OpID_OpenLFile:
            ret=new OpenLFileSeq(parent);
            break;
        case OpID_LoadFile:
            ret=new LoadFileSeq(parent);
            break;
        case OpID_CloseFile:
            ret=new CloseFileSeq(parent);
            break;
        case OpID_DeleteFile:
            ret=new DeleteFileSeq(parent);
            break;
        case OpID_BPrint:
            ret=new BPrintSeq(parent);
            break;
        case OpID_BScan:
            ret=new BScanSeq(parent);
            break;
        case OpID_SyncGet:
            ret=new SyncGetSeq(parent);
            break;
        case OpID_DLLCmd:
            ret=new DLLCmdSeq(parent);
            break;
        case OpID_ShowOn:
            ret=new ShowOnSeq(parent);
            break;
        case OpID_ShowOff:
            ret=new ShowOffSeq(parent);
            break;
        case OpID_Nop:
            ret=new NopSeq(parent);
            break;
        case OpID_MInput:
            ret=new MInputSeq(parent);
            break;
        case OpID_FloatNum:
            ret=new FloatNumSeq(parent);
            break;
        case OpID_Call:
            ret=new CallSeq(parent);
            break;
        case OpID_MessageColor:
            ret=new MessageColorSeq(parent);
            break;
		default:
			ret=NULL;
        }
    return(ret);
}

bool    Operand::SaveBinHeader(FILE *file)
{
    if(WriteString(Name,file)==false){
        return(false);
    }
    if(fwrite(&ID,sizeof(ID),1,file)!=1){
        return(false);
    }
    if(WriteString(Comment,file)==false){
        return(false);
    }
    return(true);
}
bool    Operand::LoadBinHeader(FILE *file)
{
    QString  tName;
    if(ReadString(tName,file)==false){
        return(false);
    }
    SetName(tName);
    if(fread(&ID,sizeof(ID),1,file)!=1){
        return(false);
    }
    if(ReadString(Comment,file)==false){
        return(false);
    }
    return(true);
}

bool    IOOperand::SaveBinHeader(FILE *file)
{
    if(Operand::SaveBinHeader(file)==false)
        return(false);
    if(fwrite(&BoardNumber,sizeof(BoardNumber),1,file)!=1)
        return(false);
    if(fwrite(&PortNumber,sizeof(PortNumber),1,file)!=1)
        return(false);
    if(fwrite(&BitNumber,sizeof(BitNumber),1,file)!=1)
        return(false);
    if(fwrite(&InMode,sizeof(InMode),1,file)!=1)
        return(false);
    return(true);
}

bool    IOOperand::LoadBinHeader(FILE *file)
{
    if(Operand::LoadBinHeader(file)==false)
        return(false);
    if(fread(&BoardNumber,sizeof(BoardNumber),1,file)!=1)
        return(false);
    if(fread(&PortNumber,sizeof(PortNumber),1,file)!=1)
        return(false);
    if(fread(&BitNumber,sizeof(BitNumber),1,file)!=1)
        return(false);
    if(fread(&InMode,sizeof(InMode),1,file)!=1)
        return(false);
    return(true);
}

bool    CommOperand::SaveBinHeader(FILE *file)
{
    if(Operand::SaveBinHeader(file)==false)
        return(false);

    if(fwrite(&CommPort,sizeof(CommPort),1,file)!=1)
        return(false);
    if(fwrite(&BPS,sizeof(BPS),1,file)!=1)
        return(false);
    if(fwrite(&Parity,sizeof(Parity),1,file)!=1)
        return(false);
    if(fwrite(&Stopbit,sizeof(Stopbit),1,file)!=1)
        return(false);
    if(fwrite(&Character,sizeof(Character),1,file)!=1)
        return(false);
    if(fwrite(&TermNumb,sizeof(TermNumb),1,file)!=1)
        return(false);
    if(fwrite(&IgnoreNumb,sizeof(TermNumb),1,file)!=1)
        return(false);
    for(int i=0;i<TermNumb;i++){
		if(TermChar[i]!=NULL){
			int	len=strlen(TermChar[i])+1;
		    if(fwrite(&len,sizeof(len),1,file)!=1)
				return(false);
			if(fwrite(TermChar[i],len,1,file)!=1)
				return(false);
		}
	}
    for(int i=0;i<IgnoreNumb;i++){
		if(IgnoreChar[i]!=NULL){
			int	len=strlen(IgnoreChar[i])+1;
		    if(fwrite(&len,sizeof(len),1,file)!=1)
				return(false);
			if(fwrite(IgnoreChar[i],len,1,file)!=1)
				return(false);
		}
	}
    return(true);
}
bool    CommOperand::LoadBinHeader(FILE *file)
{
    if(Operand::LoadBinHeader(file)==false)
        return(false);

    if(fread(&CommPort,sizeof(CommPort),1,file)!=1)
        return(false);
    if(fread(&BPS,sizeof(BPS),1,file)!=1)
        return(false);
    if(fread(&Parity,sizeof(Parity),1,file)!=1)
        return(false);
    if(fread(&Stopbit,sizeof(Stopbit),1,file)!=1)
        return(false);
    if(fread(&Character,sizeof(Character),1,file)!=1)
        return(false);
    if(fread(&TermNumb,sizeof(TermNumb),1,file)!=1)
        return(false);
    if(fread(&IgnoreNumb,sizeof(TermNumb),1,file)!=1)
        return(false);
    for(int i=0;i<TermNumb;i++){
		int	len=0;
	    if(fread(&len,sizeof(len),1,file)!=1)
		    return(false);
		if(TermChar[i]!=NULL)
			delete	[]TermChar[i];
		TermChar[i]=new char[len];
	    if(fread(TermChar[i],len,1,file)!=1)
		    return(false);
	}
    for(int i=0;i<IgnoreNumb;i++){
		int	len=0;
	    if(fread(&len,sizeof(len),1,file)!=1)
		    return(false);
		if(IgnoreChar[i]!=NULL)
			delete	[]IgnoreChar[i];
		IgnoreChar[i]=new char[len];
	    if(fread(IgnoreChar[i],len,1,file)!=1)
		    return(false);
	}
    return(true);
}



bool    NumberOperand::SaveBinHeader(FILE *file)
{
    if(Operand::SaveBinHeader(file)==false)
        return(false);
    if(fwrite(&Data,sizeof(Data),1,file)!=1)
        return(false);
    return(true);
}
bool    NumberOperand::LoadBinHeader(FILE *file)
{
    if(Operand::LoadBinHeader(file)==false)
        return(false);
    if(fread(&Data,sizeof(Data),1,file)!=1)
        return(false);
    return(true);
}

bool    CharOperand::SaveBinHeader(FILE *file)
{
    if(Operand::SaveBinHeader(file)==false){
        return(false);
    }
///    if(fwrite(&DataLen,sizeof(DataLen),1,file)!=1)
///        return(false);
	if(fwrite(&Data,Data.length(),1,file)!=1)
        return(false);
    return(true);
}
bool    CharOperand::LoadBinHeader(FILE *file)
{
    if(Operand::LoadBinHeader(file)==false){
        return(false);
    }
///    if(fread(&DataLen,sizeof(DataLen),1,file)!=1)
///        return(false);
///    if(Data!=NULL)
///        delete  []Data;
///    Data=new BYTE[DataLen];
	if(fread(&Data,Data.length(),1,file)!=1)
        return(false);
    return(true);
}
bool    GroupOperand::SaveBinHeader(FILE *file)
{
    if(Operand::SaveBinHeader(file)==false){
        return(false);
    }
    for(int i=0;i<GroupBitCount;i++){
        if(WriteString(EachBitName[i],file)==false){
            return(false);
        }
    }
    return(true);
}
bool    GroupOperand::LoadBinHeader(FILE *file)
{
    if(Operand::LoadBinHeader(file)==false){
        return(false);
    }
    for(int i=0;i<GroupBitCount;i++){
        if(ReadString(EachBitName[i],file)==false){
            return(false);
        }
    }
    return(true);
}

/*↓D-20051026------------------------------------------------------------------
bool    LanvarOperand::SaveBinHeader(FILE *file)
{
    if(Operand::SaveBinHeader(file)==false)
        return(false);
    int N=IP.GetNumber();
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    for(IPList *c=IP.GetFirst();c!=NULL;c=c->GetNext()){
        if(c->SaveBinHeader(file)==false)
            return(false);
        }
    return(true);
}
bool    LanvarOperand::LoadBinHeader(FILE *file)
{
    if(Operand::LoadBinHeader(file)==false)
        return(false);
    int N;
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    IP.RemoveAll();
    for(int i=0;i<N;i++){
        IPList *c=new IPList();
        if(c->LoadBinHeader(file)==false)
            return(false);
        IP.AppendList(c);
        }
    return(true);
}
↑D-20051026------------------------------------------------------------------*/

bool    DLLVarOperand::SaveBinHeader(FILE *file)
{
    if(Operand::SaveBinHeader(file)==false)
        return(false);
    if(WriteString(Interface->FileName,file)==false)
        return(false);
    return(true);
}
bool    DLLVarOperand::LoadBinHeader(FILE *file)
{
    if(Operand::LoadBinHeader(file)==false)
        return(false);
    if(ReadString(Interface->FileName,file)==false)
        return(false);
    return(true);
}

bool    SequenceStock::SaveBinHeader(FILE *file)
{
    if(WriteString(Name,file)==false)
        return(false);
    if(fwrite(&SLineNumb,sizeof(SLineNumb),1,file)!=1)
        return(false);
    if(fwrite(&stype,sizeof(stype),1,file)!=1)
        return(false);
    if(fwrite(&SCode,sizeof(SCode),1,file)!=1)
        return(false);

    for(int i=0;i<SLineNumb;i++){
        SeqLine *s=SLine[i];
        unsigned short  id=s->GetOpID();
        if(fwrite(&id  ,sizeof(id  ),1,file)!=1)
            return(false);
        if(s->WriteBin(file)==false)
            return(false);
        }
    return(true);
}

void    SequenceStock::SetName(QString &name)
{
    Name=name;
}

bool    SequenceStock::LoadBinHeader(FILE *file)
{
    QString  tName;
    if(ReadString(tName,file)==false)
        return(false);
    SetName(tName);
    if(fread(&SLineNumb,sizeof(SLineNumb),1,file)!=1)
        return(false);
    if(fread(&stype,sizeof(stype),1,file)!=1)
        return(false);
    if(fread(&SCode,sizeof(SCode),1,file)!=1)
        return(false);

    if(SLine!=NULL)
        delete  []SLine;
    SLine=new SeqLine *[SLineNumb];
    for(int i=0;i<SLineNumb;i++){
        unsigned short  id;
        if(fread(&id  ,sizeof(id  ),1,file)!=1)
            return(false);
        SeqLine *s=SeqLine::Get(id ,GetSeqControl());
        SLine[i]=s;
        if(s->ReadBin(file)==false)
            return(false);
        }
    return(true);
}

bool    SeqControl::SaveBinHeader(FILE *file)
{
    int N;

    N=IOOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(IOOperand *m=IOOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=CommOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(CommOperand *m=CommOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=BitOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(BitOperand *m=BitOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=WordOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(WordOperand *m=WordOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=FloatOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(FloatOperand *m=FloatOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=StringOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(StringOperand *m=StringOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=SpecialOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(SpecialOperand *m=SpecialOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=NumberOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(NumberOperand *m=NumberOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=CharOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(CharOperand *m=CharOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=GroupOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(GroupOperand *m=GroupOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=SpecialBitOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(SpecialBitOperand *m=SpecialBitOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=SpecialStringOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(SpecialStringOperand *m=SpecialStringOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=SpecialFloatOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(SpecialFloatOperand *m=SpecialFloatOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
/*↓D-20051026------------------------------------------------------------------
    N=LanvarOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(LanvarOperand *m=LanvarOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
↑D-20051026------------------------------------------------------------------*/
    N=FifoOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(FifoOperand *m=FifoOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    N=DLLVarOpe.GetNumber();
    if(fwrite(&N,sizeof(N),1,file)!=1)
        return(false);
    for(DLLVarOperand *m=DLLVarOpe.GetFirst();m!=NULL;m=m->GetNext()){
        if(m->SaveBinHeader(file)==false)
            return(false);
        }
    if(fwrite((void *)&SeqNumb,sizeof(SeqNumb),1,file)!=1)
        return(false);
    for(SequenceStock *s=SeqStock.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->SaveBinHeader(file)==false)
            return(false);
        }
    return(true);
}
bool    SeqControl::LoadBinHeader(FILE *file)
{
    int N;

    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    IOOpe.RemoveAll();
    for(int i=0;i<N;i++){
        IOOperand *m=new IOOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        IOOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    CommOpe.RemoveAll();
    for(int i=0;i<N;i++){
        CommOperand *m=new CommOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        CommOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    BitOpe.RemoveAll();
    for(int i=0;i<N;i++){
        BitOperand *m=new BitOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        BitOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    WordOpe.RemoveAll();
    for(int i=0;i<N;i++){
        WordOperand *m=new WordOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        WordOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    FloatOpe.RemoveAll();
    for(int i=0;i<N;i++){
        FloatOperand *m=new FloatOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        FloatOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    StringOpe.RemoveAll();
    for(int i=0;i<N;i++){
        StringOperand *m=new StringOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        StringOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    SpecialOpe.RemoveAll();
    for(int i=0;i<N;i++){
        SpecialOperand *m=new SpecialOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        SpecialOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    NumberOpe.RemoveAll();
    for(int i=0;i<N;i++){
        NumberOperand *m=new NumberOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        NumberOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    CharOpe.RemoveAll();
    for(int i=0;i<N;i++){
        CharOperand *m=new CharOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        CharOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    GroupOpe.RemoveAll();
    for(int i=0;i<N;i++){
        GroupOperand *m=new GroupOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        GroupOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    SpecialBitOpe.RemoveAll();
    for(int i=0;i<N;i++){
        SpecialBitOperand *m=new SpecialBitOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        SpecialBitOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    SpecialStringOpe.RemoveAll();
    for(int i=0;i<N;i++){
        SpecialStringOperand *m=new SpecialStringOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        SpecialStringOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    SpecialFloatOpe.RemoveAll();
    for(int i=0;i<N;i++){
        SpecialFloatOperand *m=new SpecialFloatOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        SpecialFloatOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
/*↓D-20051026------------------------------------------------------------------
    LanvarOpe.RemoveAll();
    for(int i=0;i<N;i++){
        LanvarOperand *m=new LanvarOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        LanvarOpe.AppendList(m);
        }
↑D-20051026------------------------------------------------------------------*/
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    FifoOpe.RemoveAll();
    for(int i=0;i<N;i++){
        FifoOperand *m=new FifoOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        FifoOpe.AppendList(m);
        }
    if(fread(&N,sizeof(N),1,file)!=1)
        return(false);
    DLLVarOpe.RemoveAll();
    for(int i=0;i<N;i++){
        DLLVarOperand *m=new DLLVarOperand(this);
        if(m->LoadBinHeader(file)==false)
            return(false);
        DLLVarOpe.AppendList(m);
        }

    if(fread((void *)&SeqNumb,sizeof(SeqNumb),1,file)!=1)
        return(false);
    for(SequenceStock *s=SeqStock.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->SaveBinHeader(file)==false)
            return(false);
        }
    return(true);
}

bool     Sequence::WriteHPush(int         d ,OpeChangeListBase::ForceChange c,Operand *O)
{
    TimingDataHeader.DataSize   = sizeof(TimingDataHeader)+sizeof(d);
    //VInt64  k=GetCPUClock();
    //TimingDataHeader.Clocks     =k;
    TimingDataHeader.TickCount  =ThreadSequence::GetNowMiliSec();
    TimingDataHeader.SeqCode    =GetSCode();
    TimingDataHeader.MLine      =NowLine;
    TimingDataHeader.OType      =O->GetKindCode();
    TimingDataHeader.ONumber    =O->GetID();
    TimingDataHeader.Flag       =eFlag.GetLatestFlag();
    TimingDataHeader.Cause      =(int)c;
    TimingDataHeader.DType      =1;
    TimingDataType=1;
    TimingDataI                 =d;
    TimingWriteMode             =true;

    return(true);
}

bool     Sequence::WriteHPush(double     d ,OpeChangeListBase::ForceChange c,Operand *O)
{
    TimingDataHeader.DataSize   = sizeof(TimingDataHeader)+sizeof(d);
    //VInt64  k=GetCPUClock();
    //TimingDataHeader.Clocks     =k;
    TimingDataHeader.TickCount  =ThreadSequence::GetNowMiliSec();
    TimingDataHeader.SeqCode    =GetSCode();
    TimingDataHeader.MLine      =NowLine;
    TimingDataHeader.OType      =O->GetKindCode();
    TimingDataHeader.ONumber    =O->GetID();
    TimingDataHeader.Flag       =eFlag.GetLatestFlag();
    TimingDataHeader.Cause      =(int)c;
    TimingDataHeader.DType      =1;
    TimingDataType=1;
    TimingDataF                 =d;
    TimingWriteMode             =true;

    return(true);
}
bool     Sequence::WriteHPush(QString &d ,OpeChangeListBase::ForceChange c,Operand *O)
{
    TimingDataHeader.DataSize   = sizeof(TimingDataHeader)+sizeof(d.length())+1;
    //VInt64  k=GetCPUClock();
    //TimingDataHeader.Clocks     =k;
    TimingDataHeader.TickCount  =ThreadSequence::GetNowMiliSec();
    TimingDataHeader.SeqCode    =GetSCode();
    TimingDataHeader.MLine      =NowLine;
    TimingDataHeader.OType      =O->GetKindCode();
    TimingDataHeader.ONumber    =O->GetID();
    TimingDataHeader.Flag       =eFlag.GetLatestFlag();
    TimingDataHeader.Cause      =(int)c;
    TimingDataHeader.DType      =2;
    TimingDataType=2;
    TimingDataS                 =d;
    TimingWriteMode             =true;
    return(true);
}
bool     Sequence::WriteHPush(BYTE *d,int len   ,OpeChangeListBase::ForceChange c,Operand *O)
{
    try{
        TimingDataHeader.DataSize   = sizeof(TimingDataHeader)+len;
        //VInt64  k=GetCPUClock();
        //TimingDataHeader.Clocks     =k;
        TimingDataHeader.TickCount  =ThreadSequence::GetNowMiliSec();
        TimingDataHeader.SeqCode    =GetSCode();
        TimingDataHeader.MLine      =NowLine;
        TimingDataHeader.OType      =O->GetKindCode();
        TimingDataHeader.ONumber    =O->GetID();
        TimingDataHeader.Flag       =eFlag.GetLatestFlag();
        TimingDataHeader.Cause      =(int)c;
        TimingDataHeader.DType      =3;
        TimingDataType=3;

        if(TimingDataB!=NULL && TimingDataBAllocedSize<len){
            delete  []TimingDataB;
            TimingDataB=NULL;
            }
        if(TimingDataB==NULL){
            TimingDataB                 =new BYTE[len];
            TimingDataBAllocedSize      =len;
            }
        if(d!=NULL)
            memcpy(TimingDataB,d,len);
        TimingDataLen               =len;
        TimingWriteMode             =true;

        return(true);
        }
    catch(...){
        return(false);
        }
}


bool        SeqControl::WriteTimingSeq(Sequence *s)
{
    if(WriteTimingFile!=NULL){
        if(s->WriteExecute(WriteTimingFile)==false){
            delete  WriteTimingFile;
            WriteTimingFile=NULL;
            return(false);
            }
        }
    return(true);
}

bool     Sequence::WriteExecute(QDataStream *f)
{
	if(f->writeRawData((char *)&TimingDataHeader,sizeof(TimingDataHeader))!=sizeof(TimingDataHeader))
        return(false);
    int len;
    switch(TimingDataType){
        case 1:
            if(f->writeRawData((char *)&TimingDataI,sizeof(TimingDataI))!=sizeof(TimingDataI))
                return(false);
            break;
        case 2:
            len=TimingDataS.length()+1;
            if(f->writeRawData((char *)TimingDataS.data(),len)!=len)
                return(false);
            break;
        case 3:
            if(f->writeRawData((char *)TimingDataB,TimingDataLen)!=TimingDataLen)
                return(false);
            break;
        }
    return(true);
}
ThreadSequence	*SeqControl::GetThread(void)
{
	return (ThreadSequence *)Parent;
}
QObject	*SeqControl::GetThreadParent(void)
{	
	return ((ThreadSequence *)Parent)->GetMainWindow();	
}

FlagExecuted::FlagExecuted(void)
{
    FlagDim     =NULL;
    AllocNumb   =0;
    NowWTop     =0;
    NeedWCount  =0;
}
FlagExecuted::~FlagExecuted(void)
{
    if(FlagDim!=NULL)
        delete  []FlagDim;
    FlagDim=NULL;
    AllocNumb=0;
}

void    FlagExecuted::AddFlag(bool flag)
{
    if(FlagDim==NULL)
        return;
    FlagDim[NowWTop]=flag;
    NowWTop++;
    if(NowWTop>=AllocNumb){
        NowWTop=NeedWCount;
        memmove(FlagDim,&FlagDim[AllocNumb-NowWTop],NeedWCount*sizeof(bool));
        }
}

void    FlagExecuted::SetFlag(bool flag)
{
    if(FlagDim==NULL)
        return;
    FlagDim[0]=flag;
    NowWTop=1;
}

bool    *FlagExecuted::GetTop(void)
{
    return(FlagDim);
}

int     FlagExecuted::GetEffectiveLen(void)
{
    return(NowWTop);
}

bool     FlagExecuted::GetLatestFlag(void)
{
    if(NowWTop==0)
        return(false);
    return(FlagDim[NowWTop-1]);
}

void    FlagExecuted::Alloc(SequenceStock *s)
{
    if(FlagDim!=NULL)
        delete  []FlagDim;
    AllocNumb=0;
    NeedWCount=0;
    for(int i=0;i<s->GetSLineNumb();i++){
        if(s->GetSLine(i)!=NULL){
            int x=s->GetSLine(i)->eFlag.GetLen();
            if(x>NeedWCount)
                NeedWCount=x;
            AllocNumb++;
            }
        }
    AllocNumb+=NeedWCount+1;
    FlagDim=new bool[AllocNumb];
    memset(FlagDim,true,AllocNumb*sizeof(bool));
    NowWTop=0;
}

FlagExecuted    &FlagExecuted::operator=(FlagExecuted &src)
{
	if( this == &src ){
		return *this;
	}

    if(FlagDim!=NULL)
        delete  []FlagDim;
    AllocNumb   = src.AllocNumb;
    NowWTop     = src.NowWTop;
    NeedWCount  = src.NeedWCount;

    FlagDim=new bool[AllocNumb];

    memcpy(FlagDim,src.FlagDim,AllocNumb*sizeof(bool));
    return(*this);
}

bool    SeqLine::ExecuteEOk(Sequence *Parent, FlagExecuted &eflag)
{
    if(GetFlagConnectedMode()==false){
        bool    *top=eflag.GetTop();
        int     Len =eflag.GetEffectiveLen();
        if(Parent!=NULL){
            Parent->LastExecuted=eFlag.Compare(top,Len);
            return(Parent->LastExecuted);
        }
    }
    else{
        if(Parent!=NULL){
            if(Parent->LastExecuted==true)
                return(true);
        }
    }
    return(false);
}


void    Sequence::RemoveBreakPoint(int n)
{
    memmove((void *)&(BreakPoint[n]),(void *)&(BreakPoint[n+1]),(MaxBreakPoint-n-1)*sizeof(int));
    BreakPointNumb--;
}


void    Sequence::AddBreakPoint(int n)
{
    BreakPoint[BreakPointNumb]=n;
    BreakPointNumb++;
    GoMode=false;
    StepBreakMode=false;
    StepBreak=false;
}

void    Sequence::GoFromStep(void)
{
    StopExecute=false;
    StepBreakMode=false;
    GoMode     =true;
}

void    Sequence::StepIt(void)
{
    IsDebugStopped=false;
    GoMode     =true;
    StepBreak=true;
    StepBreakMode=true;
    StepBreak=false;
    StopExecute=false;
}

void    Sequence::StopFromGo(void)
{
    IsDebugStopped=false;
    DebugMode=true;
    StopExecute=true;
}

void    Sequence::LoadFromStock(SequenceStock *base)
{
    SPoint=base;
    eFlag.Alloc(base);

    if(SLine!=NULL){
        for(int i=0;i<GetSLineNumb();i++){
            if(SLine[i]!=NULL)
                delete  SLine[i];
            }
        delete  []SLine;
        }
    SLine=new SeqLine*[GetSLineNumb()];
    for(int i=0;i<GetSLineNumb();i++){
        if(SPoint->SLine[i]!=NULL){
            SLine[i]=SPoint->SLine[i]->MakeDup(&LocalRegs);
            }
        else
            SLine[i]=NULL;
        }
    Clear();
    ClearBreak();
}

void    SeqControl::ClearCmdHistList(void)
{
    if(SeqControl::DLLSync!=NULL){
		SeqControl::DLLSync->lock();
        SeqControl::CmdList.RemoveAll();
		SeqControl::DLLSync->unlock();
        }
}


SeqControl::SeqControl(LayersBase *base) : ServiceForLayers(base)
{
	OutSequenceYesNoForm		=NULL;
	OutSequenceShowYesNoForm	=NULL;
	OutSequenceShowForm			=NULL;
	OutSequenceShowOKForm		=NULL;
	OutSequenceMessageForm		=NULL;
	OutSequenceInputForm		=NULL;

    PIO =new PIOClass(base,false);

	SeqNumb	=0;
	Parent	=NULL;

	ReqHalt=0;
	OnStepping=false;
	DoHalt=false;
	OnHalting=false;
	GlanceFreq=0;
	NowGlanceTime=0;

	LanVarCSection=NULL;	//D-20051026
	GetLanverReqMode=false;
	MessageCol=Qt::red;

	SeqTitle=/**/"";
	TimingPath=/**/"";
	WriteTimingFile=NULL;

	ReArrangehistSW=false;
	StepTime=20;
	LastOperationTime=0;	// 最後に操作、実行された時
													// 刻
	ErrorLine=/**/"";
	Started=false;

	StateOut=NULL;
///ServerSock=NULL;	//D-20051026
	LanvarPort=20031;
	XSeqLocalInit=NULL;

	SetDataSpecialOperand=NULL;
	GetDataSpecialOperand=NULL;

	SetDataSpecialBitOperand=NULL;
	GetDataSpecialBitOperand=NULL;

	SetDataSpecialStringOperand=NULL;
	GetDataSpecialStringOperand=NULL;

	SetDataSpecialFloatOperand=NULL;
	GetDataSpecialFloatOperand=NULL;

	S20Time=0;

	DLLDebugMode    =false;
	DLLSync        =NULL;
	StartTickCount  =0;
	StartTime       =0;
	LocalParamPointer	=NULL;
}
