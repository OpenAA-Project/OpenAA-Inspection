#include "ShowResultMultiDeliveryResource.h"
#include "ShowResultMultiDeliveryForm.h"
#include "ui_ShowResultMultiDeliveryForm.h"
#include <QSqlQuery>
#include "XDataInLayer.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "ButtonSelectMultiDelivery.h"
#include "XResultDLLManager.h"
#include "XLotInformation.h"
#include "XCriticalFunc.h"
#include "ButtonAutoMode.h"
#include "ResultXMLMultiDelivery.h"
#include "swap.h"
#include "XSyncGUI.h"
#include "XWriteResultThread.h"
#include "XGeneralFunc.h"
#include <QMessageBox>

extern	char	*sRoot;
extern	char	*sName;

ShowResultMultiDeliveryForm::OperandUnit::OperandUnit(void)
{
	Number				=-1;
	iNGStockedCounter	=NULL;
	iReqChangeLot		=NULL;
	LotSubNumber		=0;
}
ShowResultMultiDeliveryForm::OperandUnit::~OperandUnit(void)
{
	if(iNGStockedCounter!=NULL){
		delete	iNGStockedCounter;
		iNGStockedCounter=NULL;
	}
	if(iReqChangeLot!=NULL){
		delete	iReqChangeLot;
		iReqChangeLot=NULL;
	}
}
void	ShowResultMultiDeliveryForm::OperandUnit::Initial(int _Number ,int SysNoNGStockedCounter,int SysNoReqChangeLot ,SeqControlParam	*Param)
{
	Number=_Number;
	iNGStockedCounter	=new SignalOperandInt(this,SysNoNGStockedCounter	,/**/"ShowResultMultiDelivery:iNGStockedCounter");
	iReqChangeLot		=new SignalOperandBit(this,SysNoReqChangeLot		,/**/"ShowResultMultiDelivery:iReqChangeLot");
	if(Param!=NULL){
		SeqErrorInfo	Error;
		if(Param->SetSpecialOperand(iNGStockedCounter	,&Error)==false){
			iNGStockedCounter->ShowErrorMessage(Error);
		}
		if(Param->SetSpecialOperand(iReqChangeLot		,&Error)==false){
			iReqChangeLot->ShowErrorMessage(Error);
		}
	}
}

ShowResultMultiDeliveryForm::ShowResultMultiDeliveryForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ShowResultMultiDeliveryForm)
{
    ui->setupUi(this);

	OperandDeliver		=NULL;
	iMutex				=NULL;
	iAutoChangeLot		=NULL;
	SyncMode		=false;
	ChangeToClear	=true;
	
	SysNoNGStockedCounter	=460;
	SysNoReqChangeLot		=480;
	AllocatedCount			=0;
	ResultDelivery		=NULL;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ShowResultMultiDeliveryForm::~ShowResultMultiDeliveryForm()
{
    delete ui;
}
	
void	ShowResultMultiDeliveryForm::Prepare(void)
{
	ResultDelivery=NULL;
	ResultDLLBaseClass		*RDLL=GetLayersBase()->GetResultDLLBase();
	if(RDLL!=NULL){
		ResultDLL	*R=RDLL->GetResultDLL(/**/"Result",/**/"ResultXMLMultiDelivery");
		if(R!=NULL){
			ResultDelivery=dynamic_cast<ResultXMLMultiDelivery *>(R->GetDLLPoint());
		}
	}

	if(OperandDeliver!=NULL)
		delete	[]OperandDeliver;
	OperandDeliver=NULL;

	if(ResultDelivery!=NULL
	&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
	&& GetLayersBase()->GetShadowLevel()==0){
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(Param!=NULL){
			AllocatedCount=ResultDelivery->GetDeliveryCount();
			int	iAllocatedCount=max(GetParamGlobal()->MaxLotDeliveryCount,AllocatedCount);
			OperandDeliver=new OperandUnit[iAllocatedCount];
			for(int i=0;i<iAllocatedCount;i++){
				OperandDeliver[i].Initial(i,SysNoNGStockedCounter+i,SysNoReqChangeLot+i,Param);
				connect(OperandDeliver[i].iNGStockedCounter	,SIGNAL(changed(int))	,this	,SLOT(OperandNGStocked(int))	,Qt::QueuedConnection);
				connect(OperandDeliver[i].iReqChangeLot		,SIGNAL(changed(int))	,this	,SLOT(OperandChangedLot(int))	,Qt::QueuedConnection);
			}

			iMutex				=new SignalOperandBit(this,552,/**/"ShowResultMultiDelivery:iMutex");
			iAutoChangeLot		=new SignalOperandBit(this,553,/**/"ShowResultMultiDelivery:iAutoChangeLot");
			SeqErrorInfo	Error;
			if(Param->SetSpecialOperand(iMutex			,&Error)==false){
				iMutex->ShowErrorMessage(Error);
			}
			if(Param->SetSpecialOperand(iAutoChangeLot	,&Error)==false){
				iAutoChangeLot->ShowErrorMessage(Error);
			}
			iAutoChangeLot	->Set(false);
			iMutex			->Set(false);
		}
	}
	ShowHeader();
}

void	ShowResultMultiDeliveryForm::ResizeAction()
{
	ui->tableWidget->resize(width(),ui->tableWidget->height());
	if(AllocatedCount>0){
		int	WLen=(width()-ui->tableWidget->verticalHeader()->width())/AllocatedCount-2;
		for(int i=0;i<AllocatedCount;i++){
			ui->tableWidget->setColumnWidth(i,WLen);
		}
	}
}

void	ShowResultMultiDeliveryForm::ShowHeader(void)
{
	if(ResultDelivery!=NULL){
		ui->tableWidget->setColumnCount(AllocatedCount);
		QStringList	HeaderList;
		for(int i=0;i<AllocatedCount;i++){
			HeaderList.append(ResultDelivery->GetDeliveryInfoList(i));
		}
		ui->tableWidget->setHorizontalHeaderLabels(HeaderList);
	}
}

void	ShowResultMultiDeliveryForm::BuildForShow(void)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"SelectMultiDelivery" ,/**/"");
	if(ResultDelivery!=NULL && GProp!=NULL){
		CmdReqLotInfo	LCmd(GetLayersBase());
		GProp->TransmitDirectly(&LCmd);

		QString	tmpLotID	=LCmd.LotID;
		QString	tmpLotName	=LCmd.LotName;
		QString	tmpRemark	=LCmd.Remark;

		if(tmpLotID.isEmpty()==false){
			for(int n=0;n<AllocatedCount;n++){
				QString	SubNMax= QString(/**/"SELECT MAX(SUBNUMBER) FROM INSPECTIONLOT WHERE MASTERCODE=")
								+QString::number(GetLayersBase()->GetMasterCode())
								+QString(/**/" and IDNAME=\'") + tmpLotID +QString(/**/"\'")
								+QString(/**/" and DeliveryNo=") + QString::number(n);
				QSqlQuery querySubNMax(SubNMax,GetLayersBase()->GetDatabase());
				OperandDeliver[n].LotSubNumber=0;
				if(querySubNMax.next ()==true){
					OperandDeliver[n].LotSubNumber=querySubNMax.value(0).toInt();
				}
				OperandDeliver[n].StackCount=0;
				::SetDataToTable(ui->tableWidget,n ,0 ,QString::number(OperandDeliver[n].LotSubNumber),Qt::ItemIsEditable | Qt::ItemIsEnabled);
				::SetDataToTable(ui->tableWidget,n ,1 ,MakeDeliveryLot(tmpLotID		,n,OperandDeliver[n].LotSubNumber));
				::SetDataToTable(ui->tableWidget,n ,2 ,MakeDeliveryLot(tmpLotName	,n,OperandDeliver[n].LotSubNumber));
				::SetDataToTable(ui->tableWidget,n ,3 ,QString::number(OperandDeliver[n].StackCount));
			}
		}
		else{
			for(int n=0;n<AllocatedCount;n++){
				::SetDataToTable(ui->tableWidget,n ,0 ,/**/"");
				::SetDataToTable(ui->tableWidget,n ,1 ,/**/"");
				::SetDataToTable(ui->tableWidget,n ,2 ,/**/"");
				::SetDataToTable(ui->tableWidget,n ,3 ,/**/"");
			}
		}
	}
}
void	ShowResultMultiDeliveryForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqShowLot	*CmdReqShowLotVar=dynamic_cast<CmdReqShowLot *>(packet);
	if(CmdReqShowLotVar!=NULL){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"SelectMultiDelivery" ,/**/"");
		if(GProp!=NULL){
			CmdReqLotInfo	LCmd(GetLayersBase());
			GProp->TransmitDirectly(&LCmd);

			QString	tmpLotID	=LCmd.LotID;
			QString	tmpLotName	=LCmd.LotName;
			QString	tmpRemark	=LCmd.Remark;
			if(tmpLotID.isEmpty()==false){
				for(int n=0;n<AllocatedCount;n++){
					QString	SubNMax= QString(/**/"SELECT MAX(SUBNUMBER) FROM INSPECTIONLOT WHERE MASTERCODE=")
									+QString::number(GetLayersBase()->GetMasterCode())
									+QString(/**/" and IDNAME=\'") + tmpLotID +QString(/**/"\'")
									+QString(/**/" and DeliveryNo=") + QString::number(n);
					QSqlQuery querySubNMax(SubNMax,GetLayersBase()->GetDatabase());
					if(querySubNMax.next ()==true){
						if(OperandDeliver[n].LotSubNumber!=querySubNMax.value(0).toInt()){
							OperandDeliver[n].StackCount=0;
							OperandDeliver[n].LotSubNumber=querySubNMax.value(0).toInt();
						}
					}
		
					::SetDataToTable(ui->tableWidget,n ,0 ,QString::number(OperandDeliver[n].LotSubNumber),Qt::ItemIsEditable | Qt::ItemIsEnabled);
					::SetDataToTable(ui->tableWidget,n ,1 ,MakeDeliveryLot(tmpLotID		,n,OperandDeliver[n].LotSubNumber));
					::SetDataToTable(ui->tableWidget,n ,2 ,MakeDeliveryLot(tmpLotName	,n,OperandDeliver[n].LotSubNumber));
					::SetDataToTable(ui->tableWidget,n ,3 ,QString::number(OperandDeliver[n].StackCount));
				}
			}
			else{
				for(int n=0;n<AllocatedCount;n++){
					::SetDataToTable(ui->tableWidget,n ,0 ,QString::number(OperandDeliver[n].LotSubNumber),Qt::ItemIsEditable | Qt::ItemIsEnabled);
					::SetDataToTable(ui->tableWidget,n ,1 ,/**/" --");
					::SetDataToTable(ui->tableWidget,n ,2 ,/**/" --");
					::SetDataToTable(ui->tableWidget,n ,3 ,QString::number(OperandDeliver[n].StackCount));
				}
			}
		}
		return;
	}
	CmdReqLotSubNumber	*CmdReqLotSubNumberVar=dynamic_cast<CmdReqLotSubNumber *>(packet);
	if(CmdReqLotSubNumberVar!=NULL){
		for(int n=0;n<AllocatedCount;n++){
			CmdReqLotSubNumberVar->LotSubNumbers.Add(OperandDeliver[n].LotSubNumber);
		}
		return;
	}
}

void	ShowResultMultiDeliveryForm::GetMenuInfo(MenuInfoContainer &Info)
{
}

void	ShowResultMultiDeliveryForm::ExecuteMenu(int ID)
{
}

void	ShowResultMultiDeliveryForm::OperandNGStocked(int n)
{
	n-=SysNoNGStockedCounter;
	if(0<=n && n<AllocatedCount && OperandDeliver[n].iNGStockedCounter!=NULL){
		if(OperandDeliver[n].iNGStockedCounter->Get()>0){
			OperandDeliver[n].StackCount++;
			SetDataToTable(ui->tableWidget,n,3,QString::number(OperandDeliver[n].StackCount));
			OperandDeliver[n].iNGStockedCounter->Set(OperandDeliver[n].StackCount);

			if(ResultDelivery!=NULL){
				GetLayersBase()->GetResultThread()->SetDeliveredInfo(ResultDelivery->GetDeliveryInfoList(n));
			}
			if(OperandDeliver[n].iNGStockedCounter!=NULL){
				OperandDeliver[n].iNGStockedCounter->Set(0);
			}
		}
	}
}

void	ShowResultMultiDeliveryForm::OperandChangedLot(int n)
{
	n-=SysNoReqChangeLot;
	if(0<=n && n<AllocatedCount && OperandDeliver[n].iReqChangeLot!=NULL){
		//if(iReqChangeLot->Get()==true){
			if(OperandDeliver[n].StackCount!=0){
				OperandDeliver[n].StackCount=0;
				if(iAutoChangeLot!=NULL){
					iAutoChangeLot->Set(true);
				}
				OperandDeliver[n].iReqChangeLot->Set(false);
				ChangeLotAction(n);
			}
		//}
	}
}

bool	ShowResultMultiDeliveryForm::ChangeLotAction(int DeliveryNo)
{
	if(iMutex!=NULL){
		iMutex->Set(true);
	}

	OperandDeliver[DeliveryNo].StackCount=0;


	QString	tmpLotID;
	QString	tmpLotName;
	QString	tmpRemark;
	int		IDNumber;

	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Button" ,/**/"SelectMultiDelivery" ,/**/"");
	if(GProp!=NULL){
		CmdReqLotInfo	LCmd(GetLayersBase());
		GProp->TransmitDirectly(&LCmd);

		tmpLotID	=LCmd.LotID;
		tmpLotName	=LCmd.LotName;
		tmpRemark	=LCmd.Remark;
	}
		
	ResultXMLMultiDelivery	*RL=NULL;
	ResultDLLBaseClass		*RDLL=GetLayersBase()->GetResultDLLBase();
	if(RDLL!=NULL){
		ResultDLL	*R=RDLL->GetResultDLL(/**/"Result",/**/"ResultXMLMultiDelivery");
		if(R!=NULL){
			RL=dynamic_cast<ResultXMLMultiDelivery *>(R->GetDLLPoint());
		}
	}
	if(RL==NULL){
		QMessageBox::warning(NULL
						,LangSolver.GetString(ShowResultMultiDeliveryForm_LS,LID_0)/*"Error"*/
						,LangSolver.GetString(ShowResultMultiDeliveryForm_LS,LID_1)/*"ResultXMLMultiDelivery.dll is not loaded"*/);
		return false;
	}
	OperandDeliver[DeliveryNo].LotSubNumber++;
	int		LotSubNumber=OperandDeliver[DeliveryNo].LotSubNumber;
	QString	DeliveryStr=RL->GetDeliveryInfoList(DeliveryNo);
	QString	rtmpLotName	=tmpLotName	+QString(/**/"-")+DeliveryStr+QString(/**/"-")+QString::number(LotSubNumber);
	QString	rtmpLotID	=tmpLotID	 +QString(/**/"-")+DeliveryStr+QString(/**/"-")+QString::number(LotSubNumber);


	int	MaxAutoCount=0;
	try{
		QString	SGetMax=QString(/**/"SELECT MAX(LOTAUTOCOUNT) FROM INSPECTIONLOT WHERE MASTERCODE=")
					+QString::number(GetLayersBase()->GetMasterCode());
		QSqlQuery querySGetMax(SGetMax,GetLayersBase()->GetDatabase());
		if(querySGetMax.next ()==true){
			MaxAutoCount=querySGetMax.value(0).toInt();
		}
		MaxAutoCount++;

		QSqlQuery queryInsrt(GetLayersBase()->GetDatabase());
		queryInsrt.prepare(QString(/**/"INSERT INTO INSPECTIONLOT(LOTAUTOCOUNT,MASTERCODE,LASTUPDATED,IDNAME,LOTNAME,REMARK,DeliveryNo,SUBNUMBER) ")
			+QString(/**/"VALUES(:LOTAUTOCOUNT,:MASTERCODE,:LASTUPDATED,:IDNAME,:LOTNAME,:REMARK,:DeliveryNo,:SUBNUMBER);"));
		queryInsrt.bindValue(0	, MaxAutoCount);
		queryInsrt.bindValue(1	, GetLayersBase()->GetMasterCode());
		queryInsrt.bindValue(2	, QDateTime::currentDateTime());
		queryInsrt.bindValue(3	, rtmpLotID);
		queryInsrt.bindValue(4	, rtmpLotName);
		queryInsrt.bindValue(5	, tmpRemark);
		queryInsrt.bindValue(6	, DeliveryNo);
		queryInsrt.bindValue(7	, OperandDeliver[DeliveryNo].LotSubNumber);
		
		if(queryInsrt.exec()==false){
			return false;
		}
	}
	catch(...){
		return false;
	}

	GetLayersBase()->GetLot(DeliveryNo)->ReserveChangeLot(MaxAutoCount
														,rtmpLotID
														,rtmpLotName
														,tmpRemark);

	::SetDataToTable(ui->tableWidget,DeliveryNo ,0 ,QString::number(OperandDeliver[DeliveryNo].LotSubNumber),Qt::ItemIsEditable | Qt::ItemIsEnabled);
	::SetDataToTable(ui->tableWidget,DeliveryNo ,1 ,MakeDeliveryLot(tmpLotID	,DeliveryNo,OperandDeliver[DeliveryNo].LotSubNumber));
	::SetDataToTable(ui->tableWidget,DeliveryNo ,2 ,MakeDeliveryLot(tmpLotName	,DeliveryNo,OperandDeliver[DeliveryNo].LotSubNumber));
	::SetDataToTable(ui->tableWidget,DeliveryNo ,3 ,QString::number(OperandDeliver[DeliveryNo].StackCount));

	if(iMutex!=NULL){
		iMutex->Set(false);
	}
	return true;
}

void ShowResultMultiDeliveryForm::on_pushButtonSet_clicked()
{
	if(SyncMode==false){
		if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
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
	}
	for(int DeliveryNo=0;DeliveryNo<AllocatedCount;DeliveryNo++){
		QString	str=::GetDataToTable(ui->tableWidget ,DeliveryNo ,0);
		bool	ok;
		int	LotSubNumber=str.toInt(&ok);
		if(ok==false)
			continue;
		if(OperandDeliver[DeliveryNo].LotSubNumber!=LotSubNumber){
		}
	}
}



void	ShowResultMultiDeliveryForm::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);

	::Load(&Buff,ChangeToClear);

	SyncMode=true;
	on_pushButtonSet_clicked();
	SyncMode=false;
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
