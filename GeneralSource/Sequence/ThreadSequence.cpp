/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\ThreadSequence.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/


/*----------------------------------------------------------------------------*/
//
//  概要
//
//  作成者
//
/*----------------------------------------------------------------------------*/

#include "XTypeDef.h"
#include<QFile>
#include<QMessageBox>
#include<QSerialPort>
#include "ThreadSequence.h"
#include "XSequence.h"
#include "XPIOButton.h"
#include "SimulateSequence.h"
#include "XCriticalFunc.h"
#include "swap.h"
#include "OutSequenceYesNo.h"
#include "OutSequenceShowYesNo.h"
#include "OutSequenceShow.h"
#include "OutSequenceShowOK.h"
#include "OutSequenceMessage.h"
#include "OutSequenceInput.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"

SeqErrorInfo::SeqErrorInfo(void)
{	
	Error=_SeqError_NoError;
}
SeqErrorInfo::SeqErrorInfo(const SeqErrorInfo &src)
{
	Error=src.Error;
	DupRegExplain=src.DupRegExplain;
}

SeqErrorInfo &SeqErrorInfo::operator=(const SeqErrorInfo &src)
{
	Error=src.Error;
	DupRegExplain=src.DupRegExplain;
	return *this;
}

CommWindow::CommWindow(int _ComNo ,LayersBase *base ,QWidget *mainW)
	:QWidget(mainW),ServiceForLayers(base),ComNo(_ComNo)
{
	ComPointer	=NULL;
	RxByte		=0;
	RPoint		=0;
	WPoint		=0;
	Ret=connect(this,SIGNAL(SignalOpenCommInThread(int ,int ,int ,int))
			,this,SLOT(SlotOpenCommInThread(int ,int ,int ,int))
			,Qt::QueuedConnection);
}

QSerialPort *CommWindow::OpenCommInThread(int Character ,int Parity ,int Stopbit ,int BPS)
{
	emit	SignalOpenCommInThread(Character ,Parity ,Stopbit ,BPS);

	while(ComPointer==NULL){
		GSleep(100);
	}
	return ComPointer;
}

void	CommWindow::SlotOpenCommInThread(int Character ,int Parity ,int Stopbit ,int BPS)
{
	if(ComPointer!=NULL && ComPointer->isOpen()==false){
		delete	ComPointer;
		ComPointer=NULL;
	}
    if(ComPointer==NULL){
		QString	portName;
        QSerialPort	*sio = new QSerialPort();
/*POSIX(Linux) CODE*/
#ifdef _TTY_POSIX_
       switch(CommPort){
           case 0:
               portName="/dev/ttyS0";
               break;
           case 1:
               portName="/dev/ttyS0";
               break;
           case 2:
               portName="/dev/ttyS1";
               break;
           case 3:
               portName="/dev/ttyS2";
               break;
           case 4:
               portName="/dev/ttyS3";
               break;
           case 5:
               portName="/dev/ttyS4";
               break;
           case 6:
               portName="/dev/ttyS5";
               break;
           case 7:
               portName="/dev/ttyS6";
               break;
           case 8:
               portName="/dev/ttyS7";
               break;
           case 9:
               portName="/dev/ttyS8";
               break;
           case 10:
               portName="/dev/ttyS9";
               break;
	}
/*MS WINDOWS CODE*/
#else
       switch(ComNo){
           case 0:
               portName="COM1";
               break;
           case 1:
               portName="COM1";
               break;
           case 2:
               portName="COM2";
               break;
           case 3:
               portName="COM3";
               break;
           case 4:
               portName="COM4";
               break;
           case 5:
               portName="COM5";
               break;
           case 6:
               portName="COM6";
               break;
           case 7:
               portName="COM7";
               break;
           case 8:
               portName="COM8";
               break;
           case 9:
               portName="COM9";
               break;
           case 10:
               portName="\\\\.\\COM10";
               break;
           case 11:
               portName="\\\\.\\COM11";
               break;
           case 12:
               portName="\\\\.\\COM12";
               break;
           case 13:
               portName="\\\\.\\COM13";
               break;
           case 14:
               portName="\\\\.\\COM14";
               break;
           case 15:
               portName="\\\\.\\COM15";
               break;
           case 16:
               portName="\\\\.\\COM16";
               break;
		}
#endif
		sio->setPortName(portName);

		switch(Character){
           case 5:
			sio->setDataBits(QSerialPort::Data5);
               break;
           case 6:
               sio->setDataBits(QSerialPort::Data6);
               break;
           case 7:
               sio->setDataBits(QSerialPort::Data7);
               break;
           case 8:
               sio->setDataBits(QSerialPort::Data8);
               break;
		}
		switch(Parity){
           case 0:
			sio->setParity(QSerialPort::NoParity);
               break;
           case 1:
               sio->setParity(QSerialPort::OddParity);
               break;
           case 2:
               sio->setParity(QSerialPort::EvenParity);
               break;
		}
		switch(Stopbit){
           case 1:
			sio->setStopBits(QSerialPort::OneStop);
               break;
           case 2:
               sio->setStopBits(QSerialPort::TwoStop);
               break;
           case 3:
               sio->setStopBits(QSerialPort::OneAndHalfStop);
               break;
		}
		sio->setBaudRate(BPS);

		sio->setFlowControl(QSerialPort::NoFlowControl);

		bool    Ret=false;
		if(sio->open(QIODevice::ReadWrite)==false){
			delete	sio;
			ComPointer=NULL;
		}
		else{
			Ret=connect(sio,SIGNAL(readyRead()),this,SLOT(SlotReadyRead()));
			ComPointer=sio;
		}
		RxByte=0;
		RPoint=0;
		WPoint=0;
	}
}

void	CommWindow::SlotReadyRead()
{
	if(ComPointer!=NULL){
		RxLock.lock();
		int	Len=sizeof(RxBuff)-WPoint;
		int	N1=ComPointer->read(&RxBuff[WPoint],Len);
		WPoint+=N1;
		RxByte+=N1;
		if(WPoint>=sizeof(RxBuff)){
			WPoint=0;
			Len=sizeof(RxBuff)-WPoint;
			int	N2=ComPointer->read(RxBuff,Len);
			WPoint=N2;
			RxByte+=N2;
		}
		RxLock.unlock();
	}
}
	
int		CommWindow::CommBytesAvailable(void)
{
	return RxByte;
}
	
int		CommWindow::CommReadByte(char *Buff ,int MaxLen)
{
	RxLock.lock();
	int	N=min(RxByte,MaxLen,(int)sizeof(RxBuff));
	if(N>0){
		if((RPoint+N)<sizeof(RxBuff)){
			memcpy(Buff,&RxBuff[RPoint],N);
			RPoint+=N;
			
		}
		else{
			int	N1=sizeof(RxBuff)-RPoint;
			memcpy(Buff,&RxBuff[RPoint],N1);
			int	N2=N-N1;
			if(N2>0){
				memcpy(&Buff[N1],RxBuff,N2);
				RPoint=N2;
			}
		}
		RxByte-=N;
	}
	RxLock.unlock();
	return N;
}

/*----------------------------------------------------------------------------*/
//
//  1.日本語名
//
//  2.パラメタ説明
//    CreateSuspended
//
//  3.概要
//
//  4.機能説明
//
//  5.戻り値
//
//  6.備考
//
/*----------------------------------------------------------------------------*/

//bool    ThreadSequence::AliveMode;
//ThreadSequence	*ThreadSequence::InstSeq=NULL;


ThreadSequence::ThreadSequence(LayersBase *base ,QWidget *mainW)
    : QThread(),ThreadSequenceAbstract(base)
{
	MainW	=mainW;
	MainSeqControl	=new SeqControl(base);
	Terminated=false;
    MainSeqControl->Parent=this;
    AliveMode	=false;

	for(int i=0;i<sizeof(CommWindowDim)/sizeof(CommWindowDim[0]);i++){
		CommWindowDim[i]=new CommWindow(i,base ,mainW);
	}

	connect(this,SIGNAL(SignalMessage(int)),mainW,SLOT(MessageOutFunc(int)),Qt::QueuedConnection);
}
ThreadSequence::~ThreadSequence(void)
{
	delete	MainSeqControl;
	MainSeqControl=NULL;

	for(int i=0;i<sizeof(CommWindowDim)/sizeof(CommWindowDim[0]);i++){
		if(CommWindowDim[i]!=NULL){
			CommWindowDim[i]->close();
			CommWindowDim[i]->deleteLater();
			CommWindowDim[i]=NULL;
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

void	ThreadSequence::SetFunction( SeqLocalParam *param
									,void (*XSeqLocalInit)(SeqLocalParam *param ,SeqControl *seqControl)
									,void (*SetDataSpecialOperand)(SeqLocalParam *param ,int ID, int d)
									,int  (*GetDataSpecialOperand)(SeqLocalParam *param ,int ID)
									,void (*SetDataSpecialBitOperand)(SeqLocalParam *param ,int ID, bool d)
									,bool (*GetDataSpecialBitOperand)(SeqLocalParam *param ,int ID)
									,void (*SetDataSpecialStringOperand)(SeqLocalParam *param ,int ID, QString d)
									,QString(*GetDataSpecialStringOperand)(SeqLocalParam *param ,int ID)
									,void (*SetDataSpecialFloatOperand)(SeqLocalParam *param ,int ID, double d)
									,double  (*GetDataSpecialFloatOperand)(SeqLocalParam *param ,int ID)
									)
{
	MainSeqControl->LocalParamPointer			=param;
	MainSeqControl->XSeqLocalInit				=XSeqLocalInit;

	MainSeqControl->SetDataSpecialOperand		=SetDataSpecialOperand;
	MainSeqControl->GetDataSpecialOperand		=GetDataSpecialOperand;

	MainSeqControl->SetDataSpecialBitOperand	=SetDataSpecialBitOperand;
	MainSeqControl->GetDataSpecialBitOperand	=GetDataSpecialBitOperand;

	MainSeqControl->SetDataSpecialStringOperand	=SetDataSpecialStringOperand;
    MainSeqControl->GetDataSpecialStringOperand	=GetDataSpecialStringOperand;

	MainSeqControl->SetDataSpecialFloatOperand	=SetDataSpecialFloatOperand;
    MainSeqControl->GetDataSpecialFloatOperand	=GetDataSpecialFloatOperand;
}

bool	ThreadSequence::LoadStartSequenceFile(QWidget *mainW ,const QString &FileName 
															,const QString &IODLLFileName
															,const QString &IODefFileName 
															,QString &ErrorLine
															,QString Something
															,bool InitialOutput
															)
{
	if(MainW==NULL && mainW!=NULL){
		MainW=mainW;
	}
	QDir::setCurrent(MainSeqControl->GetLayersBase()->GetUserPath());

	if(IODLLFileName.isEmpty()==false && MainSeqControl->PIO!=NULL){
		MainSeqControl->PIO->ReadDefFileOfBoardName(IODefFileName);
		MainSeqControl->PIO->Initialize(mainW,IODLLFileName,InitialOutput,Something);
		MainSeqControl->PIO->ReadDefFile(IODefFileName);
	}

	QFile	File(FileName);
	if(File.open(QIODevice::ReadOnly | QIODevice::Text)==true){
		#ifdef _MSC_VER
		if(_CrtCheckMemory()==false){
			return(false);
		}
		#endif
        if(MainSeqControl->Load(File)==false){
			ErrorLine=MainSeqControl->ErrorLine;
			return(false);
            }

		MainSeqControl->Start();
		return(true);
        }
	return(false);
}

QSerialPort *ThreadSequence::OpenCommInThread(int ComNo,int Character ,int Parity ,int Stopbit ,int BPS)
{
	if(ComNo<sizeof(CommWindowDim)/sizeof(CommWindowDim[0])){
		return CommWindowDim[ComNo]->OpenCommInThread(Character ,Parity ,Stopbit ,BPS);
	}
	return NULL;
}
	
int		ThreadSequence::CommBytesAvailable(int ComNo)
{
	if(ComNo<sizeof(CommWindowDim)/sizeof(CommWindowDim[0])){
		return CommWindowDim[ComNo]->CommBytesAvailable();
	}
	return 0;
}

int		ThreadSequence::CommReadByte(int ComNo ,char *Buff ,int MaxLen)
{
	if(ComNo<sizeof(CommWindowDim)/sizeof(CommWindowDim[0])){
		return CommWindowDim[ComNo]->CommReadByte(Buff ,MaxLen);
	}
	return 0;
}

void ThreadSequence::run()
{
    // TODO : スレッドとして実行したいコードをここに記述 */
    //Priority=tpHighest;
    MainSeqControl->Initial();
    MainSeqControl->OnStepping=false;
    AliveMode=true;
    bool    ExecutedBegin;
    do{
        ExecutedBegin=false;
        if(MainSeqControl->DoHalt==true){
            while(MainSeqControl->DoHalt==true){
                msleep(10);
				if(Terminated==true){
                    goto    EndSeq;
				}
                MainSeqControl->OnHalting=true;
			}
            MainSeqControl->OnHalting=false;
		}
        BeforeActionOnExecute();
        //MainSeqControl->ProcessLanvar();
        for(Sequence *s=MainSeqControl->Seq.GetFirst();s!=NULL;s=s->GetNext()){
            if(s->GetSType()==SequenceStock::_Begin
            && s->IsAliveExecuting()==true){
                s->StepExecute();
                ExecutedBegin=true;
                }
            }
        MainSeqControl->NowGlanceTime++;
		if(Terminated==true){
            goto    EndSeq;
		}
		/*
        if(MainSeqControl->GetLanverReqMode==true){
            for(LanvarOperand *c=MainSeqControl->LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                c->GetString();
                }
            MainSeqControl->GetLanverReqMode=false;
            }
		*/
        for(FifoOperand *c=MainSeqControl->FifoOpe.GetFirst();c!=NULL;c=c->GetNext()){
            c->GetStackedListInner();
            }

        AfterActionOnExecute();
        }while(ExecutedBegin==true);

    while(Terminated==false){
        if(MainSeqControl->DoHalt==true){
            while(MainSeqControl->DoHalt==true){
                msleep(10);
				if(Terminated==true){
                    goto    EndSeq;
				}
                MainSeqControl->OnHalting=true;
                }
            MainSeqControl->OnHalting=false;
            }
        BeforeActionOnExecute();

        int         ReqChangeRegID;
        int         ReqChangeData;
        Sequence    *ReqChangeShowOnSeq;
        int         ReqChangeRegKindCode;
        if(ReqWRegChange.Pop(ReqChangeRegID,ReqChangeData,&ReqChangeShowOnSeq,ReqChangeRegKindCode)==true){
            MainSeqControl->SetWReg(ReqChangeShowOnSeq,ReqChangeRegKindCode,ReqChangeRegID,ReqChangeData);
            }

        //MainSeqControl->ProcessLanvar();
        MainSeqControl->OnStepping=true;
        MainSeqControl->StepExecute();
        MainSeqControl->OnStepping=false;

        bool    ImmidiateEnabled=false;
        for(Sequence *s=MainSeqControl->Seq.GetFirst();s!=NULL;s=s->GetNext()){
            if(s->GetSType()==SequenceStock::_Immidiate){
                ImmidiateEnabled=true;
                break;
                }
            }
        if(ImmidiateEnabled==true){
            for(Sequence *s=MainSeqControl->Seq.GetFirst();s!=NULL;s=s->GetNext()){
                if(s->GetSType()==SequenceStock::_Immidiate){
                    s->StepExecute();
                    }
                }
            //MainSeqControl->ProcessLanvar();
            MainSeqControl->StepExecute();
            }
        else{
			if(MainSeqControl->StepTime>=10){
                msleep(MainSeqControl->StepTime);
			}
            else{
				if(MainSeqControl->StepTime==0){
                    MainSeqControl->StepTime=1;
				}
                int m=10/MainSeqControl->StepTime;
                //MainSeqControl->ProcessLanvar();
                for(int i=1;i<m;i++){
                    MainSeqControl->StepExecute();
                    }
                msleep(10);
                }
            }
		/*
        if(MainSeqControl->GetLanverReqMode==true){
            for(LanvarOperand *c=MainSeqControl->LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                c->GetString();
                }
            MainSeqControl->GetLanverReqMode=false;
            }
		*/
        for(FifoOperand *c=MainSeqControl->FifoOpe.GetFirst();c!=NULL;c=c->GetNext()){
            c->GetStackedListInner();
            }

        AfterActionOnExecute();
        MainSeqControl->NowGlanceTime++;
        }
    EndSeq:;

    bool    ExecutedEnd;
    do{
        ExecutedEnd=false;
        if(MainSeqControl->DoHalt==true){
            while(MainSeqControl->DoHalt==true){
                msleep(10);
                if(Terminated==true){
                    AliveMode=false;
                    return;
                    }
                MainSeqControl->OnHalting=true;
                }
            MainSeqControl->OnHalting=false;
            }
        BeforeActionOnExecute();
        //MainSeqControl->ProcessLanvar();
        for(Sequence *s=MainSeqControl->Seq.GetFirst();s!=NULL;s=s->GetNext()){
            if(s->GetSType()==SequenceStock::_End
            && s->IsAliveExecuting()==true){
                s->StepExecute();
                ExecutedEnd=true;
                }
            }
        MainSeqControl->NowGlanceTime++;
		/*
        if(MainSeqControl->GetLanverReqMode==true){
            for(LanvarOperand *c=MainSeqControl->LanvarOpe.GetFirst();c!=NULL;c=c->GetNext()){
                c->GetString();
                }
            MainSeqControl->GetLanverReqMode=false;
            }
		*/
        for(FifoOperand *c=MainSeqControl->FifoOpe.GetFirst();c!=NULL;c=c->GetNext()){
            c->GetStackedListInner();
            }

        AfterActionOnExecute();
        for(Sequence *s=MainSeqControl->Seq.GetFirst();s!=NULL;s=s->GetNext()){
            if(s->GetSType()==SequenceStock::_End
            && s->IsAliveExecuting()==true){
                if(s->IsAliveExecuting()==false){
                    AliveMode=false;
                    return;
                    }
                }
            }
        }while(ExecutedEnd==true);
    AliveMode=false;
	MainSeqControl->Release();
}
void	ThreadSequence::MSleep(int milisec)
{
	msleep(milisec);
}

int		ThreadSequence::GetNowMiliSec(void)
{
	return(GetComputerMiliSec());
}

QString	ThreadSequence::GetTitle(void)
{
	if(MainSeqControl!=NULL){
		return MainSeqControl->SeqTitle;
	}
	return /**/"";
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

void ThreadSequence::MessageOut(const QString &s)
{
    Msg=s;
	emit SignalMessage(0);	
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

bool ThreadSequence::MessageYesNoOut(const QString &s)
{
    Msg=s;
	emit SignalMessage(1);	
    return(true);
}

bool ThreadSequence::MessageInputOut(const QString &defaultStr ,const QString &msg)
{
    Msg=msg;
    DefaultString=defaultStr;
	emit SignalMessage(2);	
    
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
void ThreadSequence::MessageOutFunc(void)
{
	MainSeqControl->OutSequenceMessageForm->ShowMessage(Msg);
    MainSeqControl->OutSequenceMessageForm->show();
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
void ThreadSequence::MessageYesNoOutFunc(void)
{
	MainSeqControl->OutSequenceYesNoForm->SeqParent=this;
    MainSeqControl->OutSequenceYesNoForm->ShowMessage(Msg);
    MainSeqControl->OutSequenceYesNoForm->show();

	if(MainSeqControl->OutSequenceYesNoForm->OKMode==true){
        Result=true;
	}
	else{
        Result=false;
	}
}

void ThreadSequence::MessageInputOutFunc(void)
{
	MainSeqControl->OutSequenceInputForm->SeqParent=this;
	MainSeqControl->OutSequenceInputForm->ShowMessage(Msg ,DefaultString);
    MainSeqControl->OutSequenceInputForm->show();

	if(MainSeqControl->OutSequenceInputForm->OKMode==true){
        Result=true;
	}
	else{
        Result=false;
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

void ThreadSequence::MessageShowOn(const QString &s  ,int _PageCode,int _WRegID ,Sequence *seq ,int _RegKind)
{
    ShowingMsg  =s;
    PageCode    =_PageCode;
    WRegID      =_WRegID;
    ShowOnSeq   =seq;
    RegKindCode =_RegKind;
	emit SignalMessage(3);	   
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
void ThreadSequence::MessageShowOnFunc(void)
{
    if(PageCode<=0){
		MainSeqControl->OutSequenceShowForm->SeqParent=this;
	    MainSeqControl->OutSequenceShowForm->ShowMessage(ShowingMsg);
        MainSeqControl->OutSequenceShowForm->WRegID=-1;
		MainSeqControl->OutSequenceShowForm->show();
        }
    else
    if(PageCode==1){
		MainSeqControl->OutSequenceShowOKForm->SeqParent=this;
	    MainSeqControl->OutSequenceShowOKForm->ShowMessage(ShowingMsg);
        MainSeqControl->OutSequenceShowOKForm->WRegID     =WRegID;
        MainSeqControl->OutSequenceShowOKForm->ShowOnSeq  =ShowOnSeq;
        MainSeqControl->OutSequenceShowOKForm->RegKindCode=RegKindCode;
		MainSeqControl->OutSequenceShowOKForm->show();
        }
    else
    if(PageCode==2){
		MainSeqControl->OutSequenceShowYesNoForm->SeqParent=this;
	    MainSeqControl->OutSequenceShowYesNoForm->ShowMessage(ShowingMsg);
        MainSeqControl->OutSequenceShowYesNoForm->WRegID     =WRegID;
        MainSeqControl->OutSequenceShowYesNoForm->ShowOnSeq  =ShowOnSeq;
        MainSeqControl->OutSequenceShowYesNoForm->RegKindCode=RegKindCode;
		MainSeqControl->OutSequenceShowYesNoForm->show();
        }
}

void	ThreadSequence::LoopOnIdle(void)
{
	GetMainSeqControl()->LoopOnIdle();
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

void ThreadSequence::MessageShowOff(void)
{
	emit SignalMessage(4);    
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
void ThreadSequence::MessageShowOffFunc(void)
{
	MainSeqControl->OutSequenceYesNoForm		->close();
	MainSeqControl->OutSequenceShowYesNoForm	->close();
	MainSeqControl->OutSequenceShowForm			->close();
	MainSeqControl->OutSequenceShowOKForm		->close();
	MainSeqControl->OutSequenceInputForm		->close();
}

void	ThreadSequence::MessageOutExec(int N)
{
	switch(N){
		case 0:	
			MessageOutFunc();
			break;
		case 1:
			MessageYesNoOutFunc();
			break;
		case 2:
			MessageInputOutFunc();
			break;
		case 3:
			MessageShowOnFunc();
			break;
		case 4:
			MessageShowOffFunc();
			break;
	}
}

QWidget	*ThreadSequence::ShowSimulateSequence(QWidget *parent)
{
	SimulateSequence	*D=new SimulateSequence(MainSeqControl ,parent);
	D->show();
	return D;
}

PIOClass	*ThreadSequence::FindPIO(const QString &PIOName)
{
	if(MainSeqControl!=NULL){
		return MainSeqControl->FindPIO(PIOName);
	}
	return NULL;
}
PIOClass	*ThreadSequence::GetFirstPIO(void)
{
	if(MainSeqControl!=NULL){
		return MainSeqControl->GetFirstPIO();
	}
	return NULL;
}

NReqIntLeaf::NReqIntLeaf(void)
{
    Data=0;
}

NReqIntLeaf::~NReqIntLeaf(void)
{
}

void    NReqIntLeaf::SetData(int regcode ,int data ,Sequence *seq , int regkind)
{
    RegID       =regcode;
    Data        =data;
    ShowOnSeq   =seq;
    RegKindCode =regkind;
}



void    FifoReqIntPacket::Push(int regcode ,int data ,Sequence *seq , int regkind)
{
    NReqIntLeaf   *a=new NReqIntLeaf();
    a->SetData(regcode ,data ,seq,regkind);
	CSection.lock();
    LData.AppendList(a);
	CSection.unlock();
}

bool     FifoReqIntPacket::Pop(int &regcode ,int &data ,Sequence **seq , int &regkind)
{
    CSection.lock();
    NReqIntLeaf   *a=LData.GetFirst();
    if(a!=NULL){
        LData.RemoveList(a);
        regcode =a->RegID;
        data    =a->Data;
        *seq    =a->ShowOnSeq;
        regkind =a->RegKindCode;
		CSection.unlock();
        delete  a;
        return(true);
        }
	CSection.unlock();
    return(false);
}

//================================================================================================
void	SignalOperandInt::SetData(int data)
{
	Data=data;
	emit	changed();
	emit	changed(GetID());
}
int		SignalOperandInt::GetData(void)
{
	emit	loaded();
	emit	loaded(GetID());
	return Data;
}

void	SignalOperandString::SetData(const QString &data)
{
	Data=data;
	emit	changed();
	emit	changed(GetID());
}
QString		SignalOperandString::GetData(void)
{
	emit	loaded();
	emit	loaded(GetID());
	return Data;
}

void	SignalOperandBit::SetData(bool data)
{
	Data=data;
	emit	changed();
	emit	changed(GetID());
}
bool	SignalOperandBit::GetData(void)
{
	emit	loaded();
	emit	loaded(GetID());
	return Data;
}

void	SignalOperandFloat::SetData(double data)
{
	Data=data;
	emit	changed();
	emit	changed(GetID());
}
double	SignalOperandFloat::GetData(void)
{
	emit	loaded();
	emit	loaded(GetID());
	return Data;
}
//================================================================================================
SeqLocalParam::SeqLocalParam(LayersBase	*base)
	:ServiceForLayers(base)
{
	IntDimPoint		=NULL;
	BitDimPoint		=NULL;
	StringDimPoint	=NULL;
	FloatDimPoint		=NULL;
	MaxCodeInt		=0;
	MaxCodeBit		=0;
	MaxCodeString	=0;
}
SeqLocalParam::~SeqLocalParam(void)
{
	SpecialOperandListIntData	.RemoveAll();
	SpecialOperandListBitData	.RemoveAll();
	SpecialOperandListStringData.RemoveAll();
	SpecialOperandListFloatData	.RemoveAll();

	if(IntDimPoint!=NULL){
		delete	[]IntDimPoint;
	}
	IntDimPoint=NULL;

	if(BitDimPoint!=NULL){
		delete	[]BitDimPoint;
	}
	BitDimPoint=NULL;

	if(StringDimPoint!=NULL){
		delete	[]StringDimPoint;
	}
	StringDimPoint=NULL;

	if(FloatDimPoint!=NULL){
		delete	[]FloatDimPoint;
	}
	FloatDimPoint=NULL;
}

void	SeqLocalParam::SetSpecialOperand(volatile int *data ,int Default,int code ,const char *explain ,SpecialOperandRW RWMode)
{
	if(data!=NULL){
		*data=Default;
	}
	SpecialOperandListIntData.AppendList(new SpecialOperandListInt(data ,code ,explain ,RWMode));
}
void	SeqLocalParam::SetSpecialOperand(volatile bool *data ,bool Default,int code ,const char *explain ,SpecialOperandRW RWMode)
{
	if(data!=NULL){
		*data=Default;
	}
	SpecialOperandListBitData.AppendList(new SpecialOperandListBit(data ,code ,explain ,RWMode));
}
void	SeqLocalParam::SetSpecialOperand(volatile QString *data ,const char *Default,int code ,const char *explain ,SpecialOperandRW RWMode)
{
	if(data!=NULL){
		*((QString *)data)=QString(Default);
	}
	SpecialOperandListStringData.AppendList(new SpecialOperandListString(data ,code ,explain ,RWMode));
}
void	SeqLocalParam::SetSpecialOperand(volatile double *data ,double Default,int code ,const char *explain ,SpecialOperandRW RWMode)
{
	if(data!=NULL){
		*data=Default;
	}
	SpecialOperandListFloatData.AppendList(new SpecialOperandListFloat(data ,code ,explain ,RWMode));
}


bool	SeqLocalParam::SetSpecialOperand(SignalOperandInt *Ope,SeqErrorInfo *Error,bool EnableDup)
{
	if(EnableDup==false){
		IdentifiedClass	*SelfClass=Ope->GetIdentifiedClass();
		const std::type_info	&SelfClassInfo = typeid(*SelfClass);
		for(SignalOperandBase *s=SpecialSignalOperandInt.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetID()==Ope->GetID()){
				IdentifiedClass	*c=s->GetIdentifiedClass();
				const std::type_info	&CInfo = typeid(*c);
				if(Error!=NULL && SelfClassInfo!=CInfo){
					Error->Error		=_SeqError_DuplicateID;
					Error->DupRegExplain=s->GetExplain();
					return false;
				}
			}
		}
	}
	if(Error!=NULL){
		Error->Error=_SeqError_NoError;
	}
	SpecialSignalOperandInt.AppendList(Ope);
	return true;
}

bool	SeqLocalParam::SetSpecialOperand(SignalOperandBit *Ope,SeqErrorInfo *Error,bool EnableDup)
{
	if(EnableDup==false){
		IdentifiedClass	*SelfClass=Ope->GetIdentifiedClass();
		const std::type_info	&SelfClassInfo = typeid(*SelfClass);
		for(SignalOperandBase *s=SpecialSignalOperandBit.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetID()==Ope->GetID()){
				IdentifiedClass	*c=s->GetIdentifiedClass();
				const std::type_info	&CInfo = typeid(*c);
				if(Error!=NULL && SelfClassInfo!=CInfo){
					Error->Error		=_SeqError_DuplicateID;
					Error->DupRegExplain=s->GetExplain();
					return false;
				}
			}
		}
	}
	if(Error!=NULL){
		Error->Error=_SeqError_NoError;
	}
	SpecialSignalOperandBit.AppendList(Ope);
	return true;
}

bool	SeqLocalParam::SetSpecialOperand(SignalOperandString *Ope,SeqErrorInfo *Error,bool EnableDup)
{
	if(EnableDup==false){
		IdentifiedClass	*SelfClass=Ope->GetIdentifiedClass();
		const std::type_info	&SelfClassInfo = typeid(*SelfClass);
		for(SignalOperandBase *s=SpecialSignalOperandString.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetID()==Ope->GetID()){
				IdentifiedClass	*c=s->GetIdentifiedClass();
				const std::type_info	&CInfo = typeid(*c);
				if(Error!=NULL && SelfClassInfo!=CInfo){
					Error->Error		=_SeqError_DuplicateID;
					Error->DupRegExplain=s->GetExplain();
					return false;
				}
			}
		}
	}
	if(Error!=NULL){
		Error->Error=_SeqError_NoError;
	}
	SpecialSignalOperandString.AppendList(Ope);
	return true;
}

bool	SeqLocalParam::SetSpecialOperand(SignalOperandFloat *Ope,SeqErrorInfo *Error,bool EnableDup)
{
	if(EnableDup==false){
		IdentifiedClass	*SelfClass=Ope->GetIdentifiedClass();
		const std::type_info	&SelfClassInfo = typeid(*SelfClass);
		for(SignalOperandBase *s=SpecialSignalOperandFloat.GetFirst();s!=NULL;s=s->GetNext()){
			if(s->GetID()==Ope->GetID()){
				IdentifiedClass	*c=s->GetIdentifiedClass();
				const std::type_info	&CInfo = typeid(*c);
				if(Error!=NULL && SelfClassInfo!=CInfo){
					Error->Error		=_SeqError_DuplicateID;
					Error->DupRegExplain=s->GetExplain();
					return false;
				}
			}
		}
	}
	if(Error!=NULL){
		Error->Error=_SeqError_NoError;
	}
	SpecialSignalOperandFloat.AppendList(Ope);
	return true;
}

void	SeqLocalParam::XSeqLocalInit(SeqControl *seqControl)
{
	seqControl->LocalParamPointer=this;
	MaxCodeInt=0;
	for(SpecialOperandListInt *c=SpecialOperandListIntData.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialOperand(c->Code);
		if(MaxCodeInt<c->Code){
			MaxCodeInt=c->Code;
		}
	}
	for(SignalOperandBase *c=SpecialSignalOperandInt.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialOperand(c->GetID());
		if(MaxCodeInt<c->GetID()){
			MaxCodeInt=c->GetID();
		}
	}

	MaxCodeInt++;
	if(IntDimPoint!=NULL){
		delete	[]IntDimPoint;
	}
	IntDimPoint=new SpecialOperandListInt*[MaxCodeInt];
	for(int i=0;i<MaxCodeInt;i++){
		IntDimPoint[i]=NULL;
	}
	for(SpecialOperandListInt *c=SpecialOperandListIntData.GetFirst();c!=NULL;c=c->GetNext()){
		IntDimPoint[c->Code]=c;
	}

	MaxCodeBit=0;
	for(SpecialOperandListBit *c=SpecialOperandListBitData.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialBitOperand(c->Code);
		if(MaxCodeBit<c->Code){
			MaxCodeBit=c->Code;
		}
	}
	for(SignalOperandBase *c=SpecialSignalOperandBit.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialBitOperand(c->GetID());
		if(MaxCodeBit<c->GetID()){
			MaxCodeBit=c->GetID();
		}
	}
	MaxCodeBit++;
	if(BitDimPoint!=NULL){
		delete	[]BitDimPoint;
	}
	BitDimPoint=new SpecialOperandListBit*[MaxCodeBit];
	for(int i=0;i<MaxCodeBit;i++){
		BitDimPoint[i]=NULL;
	}
	for(SpecialOperandListBit *c=SpecialOperandListBitData.GetFirst();c!=NULL;c=c->GetNext()){
		BitDimPoint[c->Code]=c;
	}

	MaxCodeString=0;
	for(SpecialOperandListString *c=SpecialOperandListStringData.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialStringOperand(c->Code);
		if(MaxCodeString<c->Code){
			MaxCodeString=c->Code;
		}
	}
	for(SignalOperandBase *c=SpecialSignalOperandString.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialStringOperand(c->GetID());
		if(MaxCodeString<c->GetID()){
			MaxCodeString=c->GetID();
		}
	}
	MaxCodeString++;
	if(StringDimPoint!=NULL){
		delete	[]StringDimPoint;
	}
	StringDimPoint=new SpecialOperandListString*[MaxCodeString];
	for(int i=0;i<MaxCodeString;i++){
		StringDimPoint[i]=NULL;
	}
	for(SpecialOperandListString *c=SpecialOperandListStringData.GetFirst();c!=NULL;c=c->GetNext()){
		StringDimPoint[c->Code]=c;
	}

	MaxCodeFloat=0;
	for(SpecialOperandListFloat *c=SpecialOperandListFloatData.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialFloatOperand(c->Code);
		if(MaxCodeFloat<c->Code){
			MaxCodeFloat=c->Code;
		}
	}
	for(SignalOperandBase *c=SpecialSignalOperandFloat.GetFirst();c!=NULL;c=c->GetNext()){
		seqControl->AddSpecialFloatOperand(c->GetID());
		if(MaxCodeFloat<c->GetID()){
			MaxCodeFloat=c->GetID();
		}
	}
	MaxCodeFloat++;
	if(FloatDimPoint!=NULL){
		delete	[]FloatDimPoint;
	}
	FloatDimPoint=new SpecialOperandListFloat*[MaxCodeFloat];
	for(int i=0;i<MaxCodeFloat;i++){
		FloatDimPoint[i]=NULL;
	}
	for(SpecialOperandListFloat *c=SpecialOperandListFloatData.GetFirst();c!=NULL;c=c->GetNext()){
		FloatDimPoint[c->Code]=c;
	}
}
void	SeqLocalParam::SetDataSpecialOperand(int ID, int d)
{
	if(0<=ID && ID<MaxCodeInt){
		if(IntDimPoint[ID]!=NULL){
			if(IntDimPoint[ID]->Data!=NULL && (IntDimPoint[ID]->RWMode==_WriteOnly || IntDimPoint[ID]->RWMode==_ReadWrite)){
				*IntDimPoint[ID]->Data=d;
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandInt.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandInt	*k=dynamic_cast<SignalOperandInt*>(a);
			if(k!=NULL){
				k->SetData(d);
			}
		}
	}
}
int		SeqLocalParam::GetDataSpecialOperand(int ID)	const	
{
	if(0<=ID && ID<MaxCodeInt){
		if(IntDimPoint[ID]!=NULL){
			if(IntDimPoint[ID]->Data!=NULL && (IntDimPoint[ID]->RWMode==_ReadOnly || IntDimPoint[ID]->RWMode==_ReadWrite)){
				return(*IntDimPoint[ID]->Data);
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandInt.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandInt	*k=dynamic_cast<SignalOperandInt*>(a);
			if(k!=NULL){
				return k->GetData();
			}
		}
	}
	return(0);
}
void	SeqLocalParam::SetDataSpecialBitOperand(int ID, bool d)
{
	if(0<=ID && ID<MaxCodeBit){
		if(BitDimPoint[ID]!=NULL){
			if(BitDimPoint[ID]->Data!=NULL && (BitDimPoint[ID]->RWMode==_WriteOnly || BitDimPoint[ID]->RWMode==_ReadWrite)){
				if(d==true){
					*BitDimPoint[ID]->Data=true;
				}
				else{
					*BitDimPoint[ID]->Data=false;
				}
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandBit.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandBit	*k=dynamic_cast<SignalOperandBit*>(a);
			if(k!=NULL){
				k->SetData(d);
			}
		}
	}
}
bool	SeqLocalParam::GetDataSpecialBitOperand(int ID)	const
{
	if(0<=ID && ID<MaxCodeBit){
		if(BitDimPoint[ID]!=NULL){
			if(BitDimPoint[ID]->Data!=NULL && (BitDimPoint[ID]->RWMode==_ReadOnly || BitDimPoint[ID]->RWMode==_ReadWrite)){
				if(*BitDimPoint[ID]->Data==true){
					return(true);
				}
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandBit.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandBit	*k=dynamic_cast<SignalOperandBit*>(a);
			if(k!=NULL){
				return k->GetData();
			}
		}
	}
	return(false);
}
void	SeqLocalParam::SetDataSpecialStringOperand(int ID, QString d)
{
	if(0<=ID && ID<MaxCodeString){
		if(StringDimPoint[ID]!=NULL){
			if(StringDimPoint[ID]->Data!=NULL && (StringDimPoint[ID]->RWMode==_WriteOnly || StringDimPoint[ID]->RWMode==_ReadWrite)){
				*((QString *)StringDimPoint[ID]->Data)=d;
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandString.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandString	*k=dynamic_cast<SignalOperandString*>(a);
			if(k!=NULL){
				k->SetData(d);
			}
		}
	}
}
QString SeqLocalParam::GetDataSpecialStringOperand(int ID)	const
{
	if(0<=ID && ID<MaxCodeString){
		if(StringDimPoint[ID]!=NULL){
			if(StringDimPoint[ID]->Data!=NULL && (StringDimPoint[ID]->RWMode==_ReadOnly || StringDimPoint[ID]->RWMode==_ReadWrite)){
				return(QString(*((QString *)StringDimPoint[ID]->Data)));
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandString.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandString	*k=dynamic_cast<SignalOperandString*>(a);
			if(k!=NULL){
				return k->GetData();
			}
		}
	}
	return(QString(/**/""));
}

void	SeqLocalParam::SetDataSpecialFloatOperand(int ID, double d)
{
	if(0<=ID && ID<MaxCodeFloat){
		if(FloatDimPoint[ID]!=NULL){
			if(FloatDimPoint[ID]->Data!=NULL && (FloatDimPoint[ID]->RWMode==_WriteOnly || FloatDimPoint[ID]->RWMode==_ReadWrite)){
				if(d==(double)true){
					*FloatDimPoint[ID]->Data=(double)true;
				}
				else{
					*FloatDimPoint[ID]->Data=(double)false;
				}
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandFloat.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandFloat	*k=dynamic_cast<SignalOperandFloat*>(a);
			if(k!=NULL){
				k->SetData(d);
			}
		}
	}
}
double	SeqLocalParam::GetDataSpecialFloatOperand(int ID)	const
{
	if(0<=ID && ID<MaxCodeFloat){
		if(FloatDimPoint[ID]!=NULL){
			if(FloatDimPoint[ID]->Data!=NULL && (FloatDimPoint[ID]->RWMode==_ReadOnly || FloatDimPoint[ID]->RWMode==_ReadWrite)){
				if(*FloatDimPoint[ID]->Data==true){
					return(true);
				}
			}
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandFloat.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandFloat	*k=dynamic_cast<SignalOperandFloat*>(a);
			if(k!=NULL){
				return k->GetData();
			}
		}
	}
	return(false);
}

QString SeqLocalParam::GetExplainSpecialOperand(int ID)	const
{
	if(0<=ID && ID<MaxCodeInt){
		if(IntDimPoint[ID]!=NULL){
			return IntDimPoint[ID]->Explain;
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandInt.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandInt	*k=dynamic_cast<SignalOperandInt*>(a);
			if(k!=NULL){
				return k->GetExplain();
			}
		}
	}

	return(QString(/**/""));
}

QString SeqLocalParam::GetExplainSpecialBitOperand(int ID)	const
{
	if(0<=ID && ID<MaxCodeBit){
		if(BitDimPoint[ID]!=NULL){
			return BitDimPoint[ID]->Explain;
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandBit.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandBit	*k=dynamic_cast<SignalOperandBit*>(a);
			if(k!=NULL){
				return k->GetExplain();
			}
		}
	}
	return(QString(/**/""));
}

QString SeqLocalParam::GetExplainSpecialStringOperand(int ID)	const
{
	if(0<=ID && ID<MaxCodeString){
		if(StringDimPoint[ID]!=NULL){
			return StringDimPoint[ID]->Explain;
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandString.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandString	*k=dynamic_cast<SignalOperandString*>(a);
			if(k!=NULL){
				return k->GetExplain();
			}
		}
	}
	return(QString(/**/""));
}

QString SeqLocalParam::GetExplainSpecialFloatOperand(int ID)	const
{
	if(0<=ID && ID<MaxCodeFloat){
		if(FloatDimPoint[ID]!=NULL){
			return FloatDimPoint[ID]->Explain;
		}
	}
	for(SignalOperandBase *a=SpecialSignalOperandFloat.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetID()==ID){
			SignalOperandFloat	*k=dynamic_cast<SignalOperandFloat*>(a);
			if(k!=NULL){
				return k->GetExplain();
			}
		}
	}
	return(QString(/**/""));
}
