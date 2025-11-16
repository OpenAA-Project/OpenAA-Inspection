#include <QFile>
#include <QFileInfo>
#include <QDir>
#include "XAlgorithmBase.h"
#include "XAlgorithmLibrary.h"
#include "XResultDLL.h"
#include "XGeneralFunc.h"
#include <QMessageBox>
#include "ResultKidaOutput.h"
#include "XLotInformation.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include "swap.h"
#include "XResult.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
//#include "XSequence.h"
#include "ThreadSequence.h"
#include "XPIOButton.h"
#include "XSequenceLocal.h"
#include "XMeasureLineMove.h"
#include "XCriticalFunc.h"
#include "XEntryPoint.h"

static	int64	LoopCounter;

static	void	LoopTimer(int64 count)
{
	for(int i=0;i<count;i++){
		LoopCounter++;
	}
}

OutThreadInResultKida::OutThreadInResultKida(ResultKidaOutput *p,QObject *parent)
	:ServiceForLayers(p->GetLayersBase()),Parent(p)
{
	Terminated	=false;
	LastPIOTimeOver	=false;
	RPoint = 0;
	WPoint = 0;
	StoredNumb	=0;
	ReqThreadOff=false;

	DWORD	t=::GetComputerMiliSec();
	LoopTimer(1000000000);
	DWORD	SpanMiliSec=::GetComputerMiliSec()-t;
	CouterPerMilisec=1000000000/SpanMiliSec;

	setPriority(QThread::HighPriority);
}

void	OutThreadInResultKida::run()
{
	while(Terminated==false
	&& GetLayersBase()->GetOnTerminating()==false){
		//if(EnableOut==true){
		//	Parent->PIOOff();
		//	EnableOut=false;
		//}
		//GSleep(10);
		if(ReqThreadOff==true){
			DWORD	t=::GetComputerMiliSec()-ReqOffTimeMiliSec;
			Parent->PIOOff(t);
			ReqThreadOff=false;
		}

		if(WPoint!=RPoint) {
			//GSleep(10);
			GSleep(10);
			//Parent->SetPIOCommand(false, false, false, false);
			MutexCommand.lock();
			RPoint++;
			if (RPoint >= sizeof(CommandStack) / sizeof(CommandStack[0])) {
				RPoint = 0;
			}
			MutexCommand.unlock();
		}
		if(Parent->IsPIOTimeOver()==true){
			if(LastPIOTimeOver==false){
				emit	SignalTimeOverOccurs();
				LastPIOTimeOver=true;
			}
		}
		else{
			LastPIOTimeOver=false;
		}

		GSleep(10);
	}
}
void	OutThreadInResultKida::WaitForMilisec(int msec)
{
	LoopTimer(CouterPerMilisec*msec);
}

void	OutThreadInResultKida::Push( int64 InspectionID
									,bool	OK
									,bool	NG
									,bool	SwordOK
									,bool	SwordNG)
{
	CommandStack[WPoint].OK = OK;
	CommandStack[WPoint].NG = NG;
	CommandStack[WPoint].SwordOK		= SwordOK;
	CommandStack[WPoint].SwordNG		= SwordNG;
	CommandStack[WPoint].InspectionID	=InspectionID;

	if(ReqThreadOff==true){
		while(ReqThreadOff==true){
			GSleep(10);
		}
		GSleep(10);
	}
	Parent->SetPIOCommand(CommandStack[WPoint].InspectionID
						 ,CommandStack[WPoint].OK
						 ,CommandStack[WPoint].NG
						 ,CommandStack[WPoint].SwordOK
						 ,CommandStack[WPoint].SwordNG);

	ReqOffTimeMiliSec=::GetComputerMiliSec();
	ReqThreadOff=true;
	//Parent->PIOOff();

	MutexCommand.lock();
	WPoint++;
	if(WPoint>=sizeof(CommandStack)/sizeof(CommandStack[0])){
		WPoint = 0;
	}
	StoredNumb++;
	MutexCommand.unlock();
}



ResultKidaOutput::ResultKidaOutput(LayersBase *Base)
	:ResultDLLBaseRoot(Base)
{
	PIO			=NULL;
	OutputMode	=_FreeForResult;
	OutThreadInst=NULL;
	TimeOutBreak	=false;
	OutCount	=0;

	PIO_OK		=/**/"oOK";
	PIO_NG		=/**/"oNG";
	PIO_SwordOK	=/**/"oSwordOK";
	PIO_SwordNG	=/**/"oSwordNG";
	PIO_PCReady	=/**/"PCReady";
	PIO_IDBit0	=/**/"IDBit0";
	PIO_IDBit1	=/**/"IDBit1";
	PIO_IDBit2	=/**/"IDBit2";
	PIO_IDBit3	=/**/"IDBit3";
	PIO_TimeOverBit	=-1;
	MixModeBladeNG	=false;
	KeepONMilisec	=30;
	WaitingTime		=0;
	MinKeepONMilisec=20;

	ResultDLLBaseRoot::SetParam(&PIO_OK			, /**/"Data"	,/**/"PIO_OK"			,"PIO bit name for OK"		);
	ResultDLLBaseRoot::SetParam(&PIO_NG			, /**/"Data"	,/**/"PIO_NG"			,"PIO bit name for NG"		);
	ResultDLLBaseRoot::SetParam(&PIO_SwordOK	, /**/"Data"	,/**/"PIO_SwordOK"		,"PIO bit name for SwordOK"	);
	ResultDLLBaseRoot::SetParam(&PIO_SwordNG	, /**/"Data"	,/**/"PIO_SwordNG"		,"PIO bit name for SwordNG"	);
	ResultDLLBaseRoot::SetParam(&PIO_PCReady	, /**/"Data"	,/**/"PIO_PCReady"		,"PIO bit name for PCReady"	);
	ResultDLLBaseRoot::SetParam(&PIO_TimeOverBit, /**/"Data"	,/**/"PIO_TimeOverBit"	,"PIO bit number for TimeOver from PIO"	);
	ResultDLLBaseRoot::SetParam(&PIO_IDBit0		, /**/"Data"	,/**/"IDBit0"			,"PIO bit number for IDBit0"	);
	ResultDLLBaseRoot::SetParam(&PIO_IDBit1		, /**/"Data"	,/**/"IDBit1"			,"PIO bit number for IDBit1"	);
	ResultDLLBaseRoot::SetParam(&PIO_IDBit2		, /**/"Data"	,/**/"IDBit2"			,"PIO bit number for IDBit2"	);
	ResultDLLBaseRoot::SetParam(&PIO_IDBit3		, /**/"Data"	,/**/"IDBit3"			,"PIO bit number for IDBit3"	);
	ResultDLLBaseRoot::SetParam(&MixModeBladeNG	, /**/"Data"	,/**/"MixModeBladeNG"	,"Mix Sward signal with OK/NG"	);
	ResultDLLBaseRoot::SetParam(&KeepONMilisec	, /**/"Data"	,/**/"KeepONMilisec"	,"Keep ON time (milisec)"	);
	ResultDLLBaseRoot::SetParam(&WaitingTime	, /**/"Data"	,/**/"WaitingTime"		,"Time to wait output result (milisec)"	);
	ResultDLLBaseRoot::SetParam(&MinKeepONMilisec, /**/"Data"	,/**/"MinKeepONMilisec"	,"Minimum Keep ON time (milisec)"	);
}

ResultKidaOutput::~ResultKidaOutput(void)
{
	if(OutThreadInst!=NULL){
		OutThreadInst->Terminated=true;
		OutThreadInst->wait();
		OutThreadInst->deleteLater();
		OutThreadInst=NULL;
	}
}

void	ResultKidaOutput::Prepare(void)
{
	if(GetEntryPoint()!=NULL){
		if(GetEntryPoint()->GetThreadSequence()!=NULL){
			if(GetEntryPoint()->GetThreadSequence()->GetMainSeqControl()!=NULL){
				PIO=GetEntryPoint()->GetThreadSequence()->GetFirstPIO();
			}
		}
	}
	OutThreadInst=new OutThreadInResultKida(this,GetLayersBase()->GetMainWidget());
	connect(OutThreadInst,SIGNAL(SignalTimeOverOccurs()),this,SLOT(SlotTimeOverOccurs())
			,Qt::QueuedConnection);
	OutThreadInst->start();
}

struct	OkNGSword
{
	bool	OK;
	bool	OKSword;
};


static	void Func(ResultInItemRoot *Item ,void *Something)
{
	struct	OkNGSword	*p=(struct	OkNGSword *)Something;
	if(Item->IsOk()==false){
		AlgorithmItemRoot	*r=Item->GetAlgorithmItem();
		if(r!=NULL){
			if(r->GetLibraryContainer()!=NULL
			&& r->GetLibraryContainer()->GetLibType()==DefLibTypeMeasureLineMove
			&& r->GetID()<100){
				p->OKSword=false;
			}
			else{
				p->OK=false;
			}
		}
	}
}
static	void FuncMixed(ResultInItemRoot *Item ,void *Something)
{
	struct	OkNGSword	*p=(struct	OkNGSword *)Something;
	if(Item->IsOk()==false){
		p->OK=false;
	}
}

void	ResultKidaOutput::SetPIO(const QString &BitName)
{
	PIO->SetBit(BitName,1);
	//GSleep(5);
	//BYTE	data;
	//if(PIO->GetEchobackBit(BitName,data)==true){
	//	if(data==0){
	//		PIO->SetBit(BitName,1);
	//		GSleep(10);
	//		if(PIO->GetEchobackBit(BitName,data)==true){
	//			if(data==0){
	//				Error++;
	//			}
	//		}
	//	}
	//}
}

void	ResultKidaOutput::SetPIOOff(const QString &BitName)
{
	PIO->SetBit(BitName,0);
	//GSleep(5);
	//BYTE	data;
	//if(PIO->GetEchobackBit(BitName,data)==true){
	//	if(data==0){
	//		PIO->SetBit(BitName,1);
	//		GSleep(10);
	//		if(PIO->GetEchobackBit(BitName,data)==true){
	//			if(data==0){
	//				Error++;
	//			}
	//		}
	//	}
	//}
}
ExeResult	ResultKidaOutput::ExecuteStartByInspection	(int ExeID,ResultInspection *Res)
{
	Res->SetPriorityCounter(1);
	return _ER_true;
}
bool	ResultKidaOutput::OutputResultDirectly(int mode ,ResultInspection &Res,GUIDirectMessage *packet)
{
	struct	OkNGSword	OkNGSwordData;

	if(GetLayersBase()->GetShadowLevel()!=0){
		return true;
	}

	if(GetLayersBase()->GetMasterCode()<0){
		SetPIO(PIO_NG);
		SetPIO(PIO_SwordNG);
		
		GSleep(KeepONMilisec);
		SetPIOOff(PIO_NG);
		SetPIOOff(PIO_SwordNG);
		return true;
	}
	bool	LOK = false;
	bool	LNG = false;
	bool	LSwordOK = false;
	bool	LSwordNG = false;

	if(OutputMode==_FreeForResult){
		OkNGSwordData.OK		=true;
		OkNGSwordData.OKSword	=true;
		if(MixModeBladeNG==false){
			Res.ExecuteInAllItems(*Func,&OkNGSwordData);
		}
		else{
			Res.ExecuteInAllItems(*FuncMixed,&OkNGSwordData);
		}
		ResultPkNgPacket	*ResultPkNgPacketVar=dynamic_cast<ResultPkNgPacket *>(packet);
		if(ResultPkNgPacketVar!=NULL){
			if(ResultPkNgPacketVar->Ok==true3)
				OkNGSwordData.OK=true;
			else
			if(ResultPkNgPacketVar->Ok==false3)
				OkNGSwordData.OK=false;
		}

		//GSleep(WaitingTime);
		if(PIO!=NULL){
			if(Res.GetTimeOutBreak()==true){
				if(PIO_SwordNG.isEmpty()==true){
					//SetPIO(PIO_NG);
					LNG = true;
				}
				else{
					//SetPIO(PIO_SwordNG);
					//SetPIO(PIO_NG);
					LSwordNG = true;
					LNG = true;
				}
			}
			else{
				if(OkNGSwordData.OK==true){
					LOK = true;
					//SetPIO(PIO_OK);
				}
				else{
					//SetPIO(PIO_NG);
					LNG = true;
				}
				if(OkNGSwordData.OKSword==true){
					//SetPIO(PIO_SwordOK);
					LSwordOK = true;
				}
				else{
					//SetPIO(PIO_SwordNG);
					LSwordNG = true;
				}
			}
		}
	}
	else
	if(OutputMode==_Abs_OK){
		//SetPIO(PIO_OK);
		//SetPIO(PIO_SwordOK);
		LOK = true;
		LSwordOK = true;
	}
	else
	if(OutputMode==_Abs_NG){
		//SetPIO(PIO_NG);
		//SetPIO(PIO_SwordOK);
		LNG = true;
		LSwordOK = true;
	}
	else
	if(OutputMode==_Abs_Blade){
		//SetPIO(PIO_OK);
		//SetPIO(PIO_SwordNG);
		LOK = true;
		LSwordNG = true;
	}
	
	/*
	GSleep(KeepONMilisec);
	SetPIOOff(PIO_OK);
	SetPIOOff(PIO_NG);
	SetPIOOff(PIO_SwordOK);
	SetPIOOff(PIO_SwordNG);
	GSleep(10);
	*/
	OutThreadInst->Push(Res.GetInspectionID(),LOK, LNG, LSwordOK, LSwordNG);

	if(TimeOutBreak==true){
		Res.SetTimeOutBreak(true);
		TimeOutBreak=false;
	}
	Res.SetPriorityCounter(0);

	return true;
}

void	ResultKidaOutput::PIOOff(DWORD PassedMilisec)
{
	if(KeepONMilisec>PassedMilisec){
		int	d=KeepONMilisec-PassedMilisec;
		if(d<MinKeepONMilisec){
			d=MinKeepONMilisec;
		}
		GSleep(d);
		//OutThreadInst->WaitForMilisec(d);
	}
	for(int i=0;i<3;i++){
		SetPIOOff(PIO_OK);
		SetPIOOff(PIO_NG);
		SetPIOOff(PIO_SwordOK);
		SetPIOOff(PIO_SwordNG);
	}
	GSleep(10);
}
bool	ResultKidaOutput::IsPIOTimeOver(void)
{
	if(PIO_TimeOverBit>=0){
		if(PIO->GetBit(0,PIO_TimeOverBit>>3,PIO_TimeOverBit&0x07)!=0){
			return true;
		}
	}
	return false;
}
void	ResultKidaOutput::SlotTimeOverOccurs()
{
	TimeOutBreak=true;
}

void	ResultKidaOutput::SetPIOCommand(int64 InspectionID
										,bool Ok, bool Ng, bool SwordOk, bool SwordNg)
{
	for(int i=0;i<3;i++){
		if((InspectionID&0x01)!=0)
			SetPIO(PIO_IDBit0);
		else
			SetPIOOff(PIO_IDBit0);

		if((InspectionID&0x02)!=0)
			SetPIO(PIO_IDBit1);
		else
			SetPIOOff(PIO_IDBit1);

		if((InspectionID&0x04)!=0)
			SetPIO(PIO_IDBit2);
		else
			SetPIOOff(PIO_IDBit2);

		if((InspectionID&0x08)!=0)
			SetPIO(PIO_IDBit3);
		else
			SetPIOOff(PIO_IDBit3);

		QThread::usleep(100);
		if(Ok==true)
			SetPIO(PIO_OK);
		else
			SetPIOOff(PIO_OK);

		if (Ng == true)
			SetPIO(PIO_NG);
		else
			SetPIOOff(PIO_NG);

		if (SwordOk == true)
			SetPIO(PIO_SwordOK);
		else
			SetPIOOff(PIO_SwordOK);

		if (SwordNg == true)
			SetPIO(PIO_SwordNG);
		else
			SetPIOOff(PIO_SwordNG);
	}
	OutCount++;
}

bool	ResultKidaOutput::IsPIO_NG(void)
{
	if(PIO!=NULL){
		BYTE data;
		if(PIO->GetEchobackBit(PIO_NG,data)==true)
			return (data==0)?false:true;
	}
	return false;
}
void	ResultKidaOutput::TransmitDirectly(GUIDirectMessage *packet)
{
	IntegrationSetControlOutput	*IntegrationSetControlOutputVar=dynamic_cast<IntegrationSetControlOutput *>(packet);
	if(IntegrationSetControlOutputVar!=NULL){
		OutputMode=IntegrationSetControlOutputVar->ControlMode;
		return;
	}
}

