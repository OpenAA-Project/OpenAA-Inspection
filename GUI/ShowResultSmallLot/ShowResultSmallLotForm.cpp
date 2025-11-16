#include "ShowResultSmallLotFormResource.h"
#include <QSqlQuery>
#include "ShowResultSmallLotForm.h"
#include "ui_ShowResultSmallLotForm.h"
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "ButtonSelectSmallLot.h"
#include "XResultDLLManager.h"
#include "XResultXMLSmallLotCommon.h"
#include "XLotInformation.h"
#include "XCriticalFunc.h"
#include "ButtonAutoMode.h"
#include "XSyncGUI.h"
#include "XWriteResultThread.h"
#include "XGeneralFunc.h"
#include "XEntryPoint.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


ShowResultSmallLotForm::ShowResultSmallLotForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowResultSmallLotForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	iNGStockedCounter	=NULL;
	iReqChangeLot		=NULL;
	iMutex				=NULL;
	iAutoChangeLot		=NULL;
	NGCount			=0;
	LotSubNumber	=0;
	MaxAutoCount	=0;
	MaxSubNumber	=0;
	SyncMode		=false;
	ChangeToClear	=true;
	TransmitLotInfo	=false;
}

ShowResultSmallLotForm::~ShowResultSmallLotForm()
{
    delete ui;
}
	
void	ShowResultSmallLotForm::Prepare(void)
{
	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			iNGStockedCounter	=new SignalOperandInt(this,520,/**/"ShowResultSmallLot:iNGStockedCounter");
			iReqChangeLot		=new SignalOperandBit(this,521,/**/"ShowResultSmallLot:iReqChangeLot");
			iMutex				=new SignalOperandBit(this,522,/**/"ShowResultSmallLot:iMutex");
			iAutoChangeLot		=new SignalOperandBit(this,523,/**/"ShowResultSmallLot:iAutoChangeLot");
			
			connect(iNGStockedCounter	,SIGNAL(changed())	,this	,SLOT(OperandNGStocked())	,Qt::QueuedConnection);
			connect(iReqChangeLot		,SIGNAL(changed())	,this	,SLOT(OperandChangedLot())	,Qt::QueuedConnection);
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iNGStockedCounter	,&Error)==false){
				iNGStockedCounter->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iReqChangeLot		,&Error)==false){
				iReqChangeLot->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iMutex				,&Error)==false){
				iMutex->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iAutoChangeLot		,&Error)==false){
				iAutoChangeLot->ShowErrorMessage(Error);
			}
			iAutoChangeLot	->Set(false);
			iMutex			->Set(false);
		}
	}
}
void	ShowResultSmallLotForm::BuildForShow(void)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"SelectSmallLot" ,/**/"");
	if(GProp!=NULL){
		CmdReqLotInfo	LCmd(GetLayersBase());
		GProp->TransmitDirectly(&LCmd);

		QString	tmpLotID	=LCmd.LotID;
		QString	tmpLotName	=LCmd.LotName;
		QString	tmpRemark	=LCmd.Remark;
		int		IDNumber	=LCmd.IDNumber;

		QString	SubNMax= QString(/**/"SELECT MAX(SUBNUMBER) FROM INSPECTIONLOT WHERE MASTERCODE=")
						+QString::number(GetLayersBase()->GetMasterCode())
						+QString(/**/" and IDNUMBER=") + QString::number(IDNumber);
		QSqlQuery querySubNMax(SubNMax,GetLayersBase()->GetDatabase());
		LotSubNumber=0;
		if(querySubNMax.next ()==true){
			LotSubNumber=querySubNMax.value(0).toInt();
		}
		NGCount=0;
	}
	if(GetLayersBase()->GetLot(0)!=NULL){
		ui->lineEditLotID	->setText(GetLayersBase()->GetLot(0)->GetLotID());
		ui->lineEditLotName	->setText(GetLayersBase()->GetLot(0)->GetLotName());
		ui->lineEditSubLot	->setText(QString::number(LotSubNumber));
		ui->lineEditNGCount	->setText(QString::number(NGCount));
	}
}
void	ShowResultSmallLotForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqShowLot	*CmdReqShowLotVar=dynamic_cast<CmdReqShowLot *>(packet);
	if(CmdReqShowLotVar!=NULL){
		MaxAutoCount=0;
		QString	SGetMax=QString(/**/"SELECT MAX(LOTAUTOCOUNT) FROM INSPECTIONLOT WHERE MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode());
		QSqlQuery querySGetMax(SGetMax,GetLayersBase()->GetDatabase());
		if(querySGetMax.next ()==true){
			MaxAutoCount=querySGetMax.value(0).toInt();
		}

		QString	SubNMax= QString(/**/"SELECT MAX(SUBNUMBER) FROM INSPECTIONLOT WHERE MASTERCODE=")
						+QString::number(GetLayersBase()->GetMasterCode())
						+QString(/**/" and IDNUMBER=") + QString::number(CmdReqShowLotVar->IDNumber);
		QSqlQuery querySubNMax(SubNMax,GetLayersBase()->GetDatabase());
		MaxSubNumber=0;
		if(querySubNMax.next ()==true){
			MaxSubNumber=querySubNMax.value(0).toInt();
		}
		return;
	}
}

void	ShowResultSmallLotForm::GetMenuInfo(MenuInfoContainer &Info)
{
}

void	ShowResultSmallLotForm::ExecuteMenu(int ID)
{
}


void	ShowResultSmallLotForm::SetLotToSystem(int iLotAutoCount
					,const QString &iLotID
					,const QString &iLotName
					,int LotCountNumber)
{
}

void	ShowResultSmallLotForm::OperandNGStocked()
{
	if(iNGStockedCounter!=NULL){
		//int	N=iNGStockedCounter->Get();
		NGCount++;
		ui->lineEditNGCount->setText(QString::number(NGCount));
		iNGStockedCounter->Set(NGCount);
	}
}

void	ShowResultSmallLotForm::OperandChangedLot()
{
	if(iReqChangeLot!=NULL){
		//if(iReqChangeLot->Get()==true){
			if(NGCount!=0){
				NGCount=0;
				if(iAutoChangeLot!=NULL){
					iAutoChangeLot->Set(true);
				}
				iReqChangeLot->Set(false);
				ChangeLotAction();
			}
			else{
				iReqChangeLot->Set(false);
			}
		//}
	}
}

bool	ShowResultSmallLotForm::UpdateSubNumber(int MaxAutoCount , int LotSubNumber)
{
	QSqlQuery queryUpdate(*GetLayersBase()->GetDataBase());
	QString	S=QString(	"UPDATE INSPECTIONLOT "
						"SET SUBNUMBER=:SUBNUMBER "
						" WHERE LOTAUTOCOUNT=")
			+ QString::number(MaxAutoCount);
	queryUpdate.prepare(S);
	queryUpdate.bindValue(0	, LotSubNumber);
	
	bool	ret=queryUpdate.exec();
	return ret;
}

void	ShowResultSmallLotForm::ChangeLotAction(void)
{
	if(iMutex!=NULL){
		iMutex->Set(true);
	}
	ResultDLLBaseRoot	*RL=NULL;
	ResultDLLBaseClass		*RDLL=GetLayersBase()->GetResultDLLBase();
	if(RDLL!=NULL){
		ResultDLL	*R=RDLL->GetResultDLL(/**/"Result",/**/"XMLSmallLot");
		if(R!=NULL){
			RL=R->GetDLLPoint();
		}
	}

	NGCount=0;

	MaxAutoCount++;
	QString	tmpLotID;
	QString	tmpLotName;
	QString	tmpRemark;
	int		IDNumber;

	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"SelectSmallLot" ,/**/"");
	if(GProp!=NULL){
		CmdReqLotInfo	LCmd(GetLayersBase());
		GProp->TransmitDirectly(&LCmd);

		tmpLotID	=LCmd.LotID;
		tmpLotName	=LCmd.LotName;
		tmpRemark	=LCmd.Remark;
		IDNumber	=LCmd.IDNumber;
	}

	MaxSubNumber++;
	LotSubNumber	=MaxSubNumber;

	tmpLotName	=tmpLotName+QString(/**/"-")+QString::number(LotSubNumber);
	tmpLotID	=tmpLotID+QString(/**/"-")+QString::number(LotSubNumber);

	GetLayersBase()->GetLot(0)->ReserveChangeLot(MaxAutoCount
										,tmpLotID
										,tmpLotName
										,tmpRemark);

	ui->lineEditLotID	->setText(tmpLotID);
	ui->lineEditLotName	->setText(tmpLotName);
	ui->lineEditSubLot	->setText(QString::number(LotSubNumber));
	ui->lineEditNGCount	->setText(QString::number(NGCount));

	if(iMutex!=NULL){
		iMutex->Set(false);
	}

	UpdateSubNumber(MaxAutoCount , LotSubNumber);

	if(SyncMode==false && TransmitLotInfo==true){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int32	Cmd=2;
			::Save(&Buff,Cmd);
			::Save(&Buff,LotSubNumber);
			::Save(&Buff,NGCount);
			::Save(&Buff,tmpLotName);
			::Save(&Buff,tmpLotID);
			::Save(&Buff,tmpRemark);
			TxSync(Buff.buffer());
		}
	}
}

//============================================================================================

void ShowResultSmallLotForm::on_pushButtonChange_clicked()
{
	NGCount=0;

	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int32	Cmd=1;
			::Save(&Buff,Cmd);
			::Save(&Buff,ChangeToClear);
			TxSync(Buff.buffer());
		}
	}

	if(ChangeToClear==true){
		bool	AutoModeOn=false;
		GUIFormBase	*AGProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"AutoMode",/**/"");
		if(AGProp!=NULL){
			CmdLockAutoMode	LockCmd(GetLayersBase());
			LockCmd.Enabled=false;
			AGProp->TransmitDirectly(&LockCmd);

			CmdGetStateOnAutoMode	RqCmd(GetLayersBase());
			AGProp->TransmitDirectly(&RqCmd);
			AutoModeOn	=RqCmd.AutoModeOn;

			CmdSetStateOnAutoMode	AmCmd(GetLayersBase());
			AmCmd.AutoModeOn=false;
			AGProp->TransmitDirectly(&AmCmd);
		}
		//GSleep(1000);
		for(time_t t=time(NULL);time(NULL)-t<3;){
			QApplication::processEvents();
		}		

		GetLayersBase()->ClearInspectID();
		GetLayersBase()->RemoveStockedResult();

		int64 InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
		XDateTime	CurrentInspectTime	=XDateTime::currentDateTime();
	 	GetLayersBase()->SetStartInspectTime(CurrentInspectTime);
		GetLayersBase()->SetInspectionTimeMilisec(::GetComputerMiliSec());

		GetLayersBase()->SetCurrentInspectID(InspectionID);

		GetLayersBase()->SetForceChangedInspectID();
		GetLayersBase()->GetResultHistryData()->Reset();

		BroadcastDirectly(_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());

		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
			if(Param!=NULL){
				Param->InspectionID=InspectionID;
			}
		}
		int		RPoint[3];
		RPoint[0]=0;
		RPoint[1]=0;
		RPoint[2]=0;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat()==ExecuteInspectBase::_AutoCaptureInspect){
				RPoint[0]=1;
			}
		}
		GetLayersBase()->SetCalcPoint(RPoint);

		for(int page=0;page<GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdChangeLot	RCmd(GetLayersBase(),sRoot,sName ,GlobalPage);
			RCmd.CurrentInspectTime	=CurrentInspectTime;
			RCmd.SendOnly(NULL,GlobalPage,0);
		}

		if(iAutoChangeLot!=NULL){
			iAutoChangeLot->Set(true);
		}
		iReqChangeLot->Set(false);
		ChangeLotAction();


		XDateTime	NowR=GetLayersBase()->GetStartInspectTime();
		ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
		if(Res!=NULL){
			Res->SetStartTimeForInspect(NowR);
		}
					
		ResultInspection	*NRes=GetLayersBase()->GetNextResultForCalc();
		if(NRes!=NULL){
			NRes->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());
		}

		GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
		GetLayersBase()->ClearCurrentStrategicNumberForCalc();

		for(time_t t=time(NULL);time(NULL)-t<3;){
			QApplication::processEvents();
		}
		if(AGProp!=NULL){
			CmdSetStateOnAutoMode	AmCmd(GetLayersBase());
			AmCmd.AutoModeOn=AutoModeOn;
			AGProp->TransmitDirectly(&AmCmd);

			CmdLockAutoMode	LockCmd(GetLayersBase());
			LockCmd.Enabled=true;
			AGProp->TransmitDirectly(&LockCmd);
		}
	}
}

void	ShowResultSmallLotForm::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	int32	Cmd;

	::Load(&Buff,Cmd);
	if(Cmd==1){
		::Load(&Buff,ChangeToClear);

		SyncMode=true;
		on_pushButtonChange_clicked();
		SyncMode=false;
	}
	else if(Cmd==2){
		QString	tmpLotID;
		QString	tmpLotName;
		QString	tmpRemark;

		::Load(&Buff,LotSubNumber);
		::Load(&Buff,NGCount);
		::Load(&Buff,tmpLotName);
		::Load(&Buff,tmpLotID);
		::Load(&Buff,tmpRemark);
		NGCount=0;
		MaxAutoCount++;

		GetLayersBase()->GetLot(0)->ReserveChangeLot(MaxAutoCount
											,tmpLotID
											,tmpLotName
											,tmpRemark);

		ui->lineEditLotID	->setText(tmpLotID);
		ui->lineEditLotName	->setText(tmpLotName);
		ui->lineEditSubLot	->setText(QString::number(LotSubNumber));
		ui->lineEditNGCount	->setText(QString::number(NGCount));
		UpdateSubNumber(MaxAutoCount , LotSubNumber);
	}
}

//==============================================================================================

GUICmdChangeLot::GUICmdChangeLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
	:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdChangeLot::Load(QIODevice *f)
{
	if(::Load(f,CurrentInspectTime)==false)
		return false;
	return true;
}

bool	GUICmdChangeLot::Save(QIODevice *f)
{
	if(::Save(f,CurrentInspectTime)==false)
		return false;
	return true;
}

void	GUICmdChangeLot::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
			int		RPoint[3];
			RPoint[0]=0;
			RPoint[1]=0;
			RPoint[2]=0;
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat()==ExecuteInspectBase::_AutoCaptureInspect){
					RPoint[0]=1;
				}
			}
			GetLayersBase()->SetCalcPoint(RPoint);

			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ChangeLot();
			}
			GetLayersBase()->SetStartInspectTime(CurrentInspectTime);
			ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
			if(Res!=NULL){
				Res->SetStartTimeForInspect(CurrentInspectTime);
			}
		
			ResultInspection	*NRes=GetLayersBase()->GetNextResultForCalc();
			if(NRes!=NULL){
				NRes->SetStartTimeForInspect(CurrentInspectTime);
			}
		}
		for(int i=0;i<3;i++){
			int	N=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==0){
				break;
			}
			GSleep(2000);
			int	M=GetLayersBase()->GetResultThread()->GetStockedCount();
			if(N==M){
				break;
			}
		}
		GetLayersBase()->GetResultThread()->SetCastAll();
		GetLayersBase()->GetResultThread()->WaitForFinishingCast();
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ClearCameraBuffer();
		}
	}
	SendAck(localPage);
}