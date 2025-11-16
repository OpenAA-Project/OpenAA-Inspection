#include "IntegratePlayer.h"
#include "XSequence.h"
#include "XExecuteIntegratePlayer.h"
#include "XCriticalFunc.h"

IntegratePlayer::IntegratePlayer(LayersBase *base,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(base),PIOServer(this)
{
	ui.setupUi(this);
	ShowIOFormInst	=NULL;
	OpenedPIO		=NULL;

	ONTop		=false;
	ONBottom	=false;

	TM.setInterval(10);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimerOut()),Qt::QueuedConnection);
	TM.start();
}

IntegratePlayer::~IntegratePlayer()
{
	if(OpenedPIO!=NULL){
		delete	OpenedPIO;
		OpenedPIO=NULL;
	}
}

void	IntegratePlayer::Initial(ExecuteIntegratePlayer	*ExeIns[16])
{
	PIOServer.Start(DefaultPIOPort);

	ParamGlobal	*P=GetParamGlobal();
	OpenedPIO=new PIOClass(GetLayersBase(),false);
	OpenedPIO->LoadDLL(P->IODLL_FileName,true);

	OpenedPIO->ReadDefFileOfBoardName(P->IODefine_FileName);
	QString	Something=P->IOSomething;
	OpenedPIO->Initialize(this,/**/"",false,Something);
	OpenedPIO->ReadDefFile(P->IODefine_FileName,false);

	OpenedPIO->SetBit(0,0,2,1);	//PC ready

	if(ExeIns[0]!=NULL){
		connect(ExeIns[0],SIGNAL(SignalOK()),this,SLOT(SlotTopOK()),Qt::QueuedConnection);
		connect(ExeIns[0],SIGNAL(SignalNG()),this,SLOT(SlotTopNG()),Qt::QueuedConnection);
	}
	if(ExeIns[1]!=NULL){
		connect(ExeIns[1],SIGNAL(SignalOK()),this,SLOT(SlotBottomOK()),Qt::QueuedConnection);
		connect(ExeIns[1],SIGNAL(SignalNG()),this,SLOT(SlotBottomNG()),Qt::QueuedConnection);
	}

}

void IntegratePlayer::on_pushButtonCheckIO_clicked()
{
	if(ShowIOFormInst==NULL){
		ShowIOFormInst=new ShowIOForm(this,NULL);
	}
	ShowIOFormInst->show();
}
void	IntegratePlayer::GetClientIDList(IntList &IDList)
{
	 PIOServer.GetClientIDList(IDList);
}
int	IntegratePlayer::GetNetworkPIOCount(void)
{
	return PIOServer.GetClientCount();
}

int	IntegratePlayer::GetIOInBitCount (int ID)
{
	return PIOServer.GetIOInBitCount (ID);
}
int	IntegratePlayer::GetIOOutBitCount(int ID)
{
	return PIOServer.GetIOOutBitCount (ID);
}
	
int		IntegratePlayer::GetPIOInBit(int PIOID ,int PortNo)
{
	BYTE data;
	if(PIOServer.InBit	(PIOID,PortNo,data)==false)
		return 0;
	return data;
}

void	IntegratePlayer::SetPIOOutBit(int PIOID ,int PortNo ,BYTE data)
{
	PIOServer.OutBit(PIOID,PortNo,data);
}

int		IntegratePlayer::GetPIOOutBit(int PIOID ,int PortNo)
{
	BYTE data;
	if(PIOServer.GetOutBit	(PIOID,PortNo,data)==false)
		return 0;
	return data;
}

QString	IntegratePlayer::GetPIOInBitName	(int PIOID ,int BitNo)
{
	return "";
}

QString	IntegratePlayer::GetPIOOutBitName(int PIOID ,int BitNo)
{
	return "";
}

void	IntegratePlayer::SetResult(bool OKMode,int UnitNo)
{
	IOMutex.lock();
	if(UnitNo==0){
		if(OKMode==false){
			OpenedPIO->SetBit(0,1,1,0);
			OpenedPIO->SetBit(0,1,0,1);
			TopLastTime=::GetComputerMiliSec();
		}
		else{
			OpenedPIO->SetBit(0,1,1,1);
			TopLastTime=::GetComputerMiliSec();
		}
		ONTop=true;
	}
	else{
		if(OKMode==false){
			OpenedPIO->SetBit(0,1,3,0);
			OpenedPIO->SetBit(0,1,2,1);
			BottomLastTime=::GetComputerMiliSec();
		}
		else{
			OpenedPIO->SetBit(0,1,3,1);
			BottomLastTime=::GetComputerMiliSec();
		}
		ONBottom=true;
	}
	IOMutex.unlock();
}
void	IntegratePlayer::SlotTopOK()
{
	ui.spinBoxTopOK->setValue(ui.spinBoxTopOK->value()+1);
}
void	IntegratePlayer::SlotTopNG()
{
	ui.spinBoxTopNG->setValue(ui.spinBoxTopNG->value()+1);
}
void	IntegratePlayer::SlotBottomOK()
{
	ui.spinBoxBottomOK->setValue(ui.spinBoxBottomOK->value()+1);
}
void	IntegratePlayer::SlotBottomNG()
{
	ui.spinBoxBottomNG->setValue(ui.spinBoxBottomNG->value()+1);
}

void	IntegratePlayer::SlotTimerOut()
{
	IOMutex.lock();
	if(ONTop==true){
		if(::GetComputerMiliSec()-TopLastTime>20){
			ONTop=false;
			OpenedPIO->SetBit(0,1,0,0);
			OpenedPIO->SetBit(0,1,1,0);
		}
	}
	if(ONBottom	==true){
		if(::GetComputerMiliSec()-BottomLastTime>20){
			ONBottom=false;
			OpenedPIO->SetBit(0,1,2,0);
			OpenedPIO->SetBit(0,1,3,0);
		}
	}
	IOMutex.unlock();
}