#include "IntegrationInputLotResource.h"
#include "IntegrationInputLotForm.h"
#include "ui_IntegrationInputLotForm.h"
#include "swap.h"
#include<QFontInfo>
#include<QFontMetrics>
#include<QSqlQuery>
#include "XGeneralFunc.h"
#include "XLotInformation.h"
#include "XResult.h"
#include "XCriticalFunc.h"
#include "XDataInLayer.h"
#include "XResultDLLManager.h"
#include "XSequenceLocal.h"
#include "InputPanelDialog.h"
#include "XWriteResultThread.h"
#include "XEntryPoint.h"
extern	const	char	*sRoot;
extern	const	char	*sName;

IntegrationInputLotForm::IntegrationInputLotForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationInputLotForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	Registered	=false;
	LotNumber	=ui->lineEditLotNumber	->text();
	SubCode		=ui->lineEditSubCode	->text();

	ManualChangedLotID		=false;
	ManualChangedLotNumber	=false;
	ManualChangedSubCode	=false;
	EnableManualChanged		=true;
	Counter					=0;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationInputLotForm::~IntegrationInputLotForm()
{
    delete ui;
}

void	IntegrationInputLotForm::Prepare(void)
{
	ui->pushButtonTitleLotID		->setFont(TitleFont);
	ui->pushButtonTitleLotNumber	->setFont(TitleFont);
	ui->lineEditLotID		->setFont(CharFont);
	ui->lineEditLotNumber	->setFont(CharFont);
	ui->pushButtonTitleLotID		->setVisible(true);
	ui->pushButtonTitleLotNumber	->setVisible(true);
	ui->lineEditLotID		->setVisible(true);
	ui->lineEditLotNumber	->setVisible(true);

	ui->pushButtonTitleSubCode	->setFont(TitleFont);
	ui->lineEditSubCode			->setFont(CharFont);
	ui->pushButtonTitleSubCode	->setVisible(true);
	ui->lineEditLotNumber		->setVisible(true);

	ui->toolButtonGenerateLot	->setFont(ButtonFont);
	ui->toolButtonGenerateLot	->setText(ButtonText);

	ui->pushButtonTitleLotID	->setText(TitleLotID);
	ui->pushButtonTitleLotNumber->setText(TitleLotNumber);
	ui->pushButtonTitleSubCode	->setText(TitleSubCode);
}

void	IntegrationInputLotForm::ResizeAction()
{
	int	RowCount=3;
	QFontInfo	TitleFontInfo	(TitleFont);
	QFontInfo	DataFontInfo	(CharFont);
	int	YLen=max(TitleFontInfo.pixelSize(),DataFontInfo.pixelSize());
	if(height()>YLen*RowCount+6){
		YLen=(height()-6)/RowCount;
	}
	YLen+=2;
	int	TitleWidth=0;
	QFontMetrics	FontM(TitleFont);
	TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleLotNumber	).width()),ui->pushButtonTitleLotNumber	->width());
	TitleWidth=max(max(TitleWidth,FontM.boundingRect(TitleSubCode	).width()),ui->pushButtonTitleSubCode	->width());
	
	int	TopY=1;
	ui->pushButtonTitleLotID	->move(0,TopY);
	ui->lineEditLotID			->move(TitleWidth,TopY);
	ui->pushButtonTitleLotID	->resize(TitleWidth,YLen);
	ui->lineEditLotID			->resize(width()-TitleWidth-8-ui->toolButtonGenerateLot->width()-ui->pushButtonLotNumber->width(),YLen);
	ui->pushButtonLotID			->setGeometry(ui->lineEditLotID	->geometry().right(),TopY,ui->pushButtonLotID->width(),YLen);

	TopY+=YLen+2;
	ui->pushButtonTitleLotNumber->move(0,TopY);
	ui->lineEditLotNumber		->move(TitleWidth,TopY);
	ui->pushButtonTitleLotNumber->resize(TitleWidth,YLen);
	ui->lineEditLotNumber		->resize(width()-TitleWidth-8-ui->toolButtonGenerateLot->width()-ui->pushButtonLotNumber->width(),YLen);
	ui->pushButtonLotNumber		->setGeometry(ui->lineEditLotNumber	->geometry().right(),TopY,ui->pushButtonLotNumber->width(),YLen);

	TopY+=YLen+2;
	ui->pushButtonTitleSubCode	->move(0,TopY);
	ui->lineEditSubCode			->move(TitleWidth,TopY);
	ui->pushButtonTitleSubCode	->resize(TitleWidth,YLen);
	ui->lineEditSubCode			->resize(width()-TitleWidth-8-ui->toolButtonGenerateLot->width()-ui->pushButtonSubCode->width(),YLen);
	ui->pushButtonSubCode		->setGeometry(ui->lineEditSubCode	->geometry().right(),TopY,ui->pushButtonSubCode->width(),YLen);

	ui->toolButtonGenerateLot	->setGeometry(width()-ui->toolButtonGenerateLot->width()-5,10
											,ui->toolButtonGenerateLot->width(),height()-20);
}


void	IntegrationInputLotForm::RegisterLot(const QString &_LotID,const QString &_LotNumber,const QString &_LotSubcode)
{
	ui->lineEditLotID		->setText(_LotID);
	ui->lineEditLotNumber	->setText(_LotNumber);
	ui->lineEditSubCode		->setText(_LotSubcode);

	on_toolButtonGenerateLot_clicked();
}

void IntegrationInputLotForm::on_toolButtonGenerateLot_clicked()
{
	//if(GetLayersBase()->GetIntegrationBasePointer()->NowOnUsing()==false){
		SubCode	=ui->lineEditSubCode	->text();

		if(DefaultLotID.isEmpty()==false){
			LotID=ReplaceKeyword(DefaultLotID,UserLotID);
			ui->lineEditLotID	->setText(LotID);
		}
		else{
			LotID	=ui->lineEditLotID		->text();
		}

		if(DefaultLotNumber.isEmpty()==false){
			LotNumber=ReplaceKeyword(DefaultLotNumber,UserLotNumber);
			ui->lineEditLotNumber	->setText(LotNumber);
		}
		else{
			LotNumber=ui->lineEditLotNumber		->text();
		}

		if(DefaultSubCode.isEmpty()==false){
			SubCode=ReplaceKeyword(DefaultSubCode,UserSubCode);
			ui->lineEditSubCode	->setText(SubCode);
		}
		else{
			SubCode	=ui->lineEditSubCode		->text();
		}
		Counter++;

		if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
			XDateTime	GeneratedTime	=XDateTime::currentDateTime();
			int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
			for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
				IntegrationCmdInputLot	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				RCmd.LotID			=LotID;
				RCmd.LotName		=LotNumber;
				RCmd.SubCode		=SubCode;
				RCmd.GeneratedTime	=GeneratedTime;
				RCmd.SendReqAck(NULL,SlaveNo,0);
			}

			GSleep(200);
			bool	NowOnIdle;
			do{
				NowOnIdle=true;
				for(EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas.GetFirst();m!=NULL;m=m->GetNext()){
					int	SlaveNo=m->GetIntegrationSlaveNo();
					if(GetLayersBase()->GetIntegrationBasePointer()->CheckOnProcessing(SlaveNo)==false){
						NowOnIdle=false;
					}
				}
			}while(NowOnIdle==false);

			for(int SlaveNo=0;SlaveNo<N;SlaveNo++){
				IntegrationReqInputLot	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
				IntegrationAckInputLot	ACmd(GetLayersBase(),sRoot,sName,SlaveNo);
				if(RCmd.Send(SlaveNo,0,ACmd)==true){
					EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(SlaveNo);
					if(m!=NULL){
						LotList	*L=new LotList();
						L->LotName		=LotNumber;
						int		MasterID	=m->GetMasterCode();
						int		MachineID	=m->GetMachineCode();
						IntegrationSlave	*Slave=GetLayersBase()->GetIntegrationBasePointer()->GetParamIntegrationMaster()->Slaves[SlaveNo];
						if(Slave!=NULL){
							L->LotFileName	=Slave->SharedFolder
											+::GetSeparator()
											+QString::number(MachineID)
											+QString(/**/"-")
											+QString::number(MasterID)
											+::GetSeparator()
											+ACmd.LotID
											+QString(/**/"--")
											+ACmd.LotName
											+QString(/**/".rdt");
							L->GlobalID=0;
							m->AddCurrentLot(L);
							m->SetCurrentLot(L);
							EnableManualChanged=false;
							if(LotNumber.isEmpty()==true){
								ui->lineEditLotNumber	->setText(ACmd.LotName);
							}
							if(LotID.isEmpty()==true){
								ui->lineEditLotID		->setText(ACmd.LotID);
							}
							EnableManualChanged=true;

							L->LotID	=ACmd.LotID;
							L->LotName	=ACmd.LotName;
							L->Remark	=ACmd.LotRemark;
						}
					}
				}
			}
			Registered=true;
			CmdChangeLotID	ICmd;
			ICmd.LotID		=ui->lineEditLotID		->text();
			ICmd.LotName	=ui->lineEditLotNumber	->text();
			BroadcastSpecifiedDirectly(&ICmd);
		}
		GetLayersBase()->ClearSystemResult();
	//}
}

void	IntegrationInputLotForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdClearMasterData					*CmdClearMasterDataVar				=dynamic_cast<CmdClearMasterData *>(v);
	LoadMasterSpecifiedBroadcaster		*LoadMasterSpecifiedBroadcasterVar	=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	CreateNewMasterSpecifiedBroadcaster	*CreatedMasterSpecifiedBroadcasterVar=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(CmdClearMasterDataVar!=NULL
	|| LoadMasterSpecifiedBroadcasterVar!=NULL
	|| CreatedMasterSpecifiedBroadcasterVar!=NULL){
		ui->lineEditLotID		->setText(/**/"");
		ui->lineEditLotNumber	->setText(/**/"");
		ui->lineEditSubCode		->setText(/**/"");
		UserLotID		=/**/"";
		UserLotNumber	=/**/"";
		UserSubCode		=/**/"";

		Counter=0;
		Registered=false;
		return;
	}
}
void	IntegrationInputLotForm::StartLot(void)
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->GetMaster(0);
		if(m!=NULL){
			for(LotList *L=m->GetLotFirst();L!=NULL;L=L->GetNext()){
				if(L->GlobalID==GetLayersBase()->GetIntegrationBasePointer()->CurrentLotGlobalID){
					ui->lineEditLotID		->setText(/**/L->LotID);
					ui->lineEditLotNumber	->setText(/**/L->LotName);
					ui->lineEditSubCode		->setText(/**/L->Remark);
					break;
				}
			}
		}
	}
}

//================================================================================================
IntegrationCmdInputLot::IntegrationCmdInputLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationCmdInputLot::Load(QIODevice *f)
{
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	if(::Load(f,SubCode)==false)
		return false;
	if(::Load(f,GeneratedTime)==false)
		return false;
	return true;
}
bool	IntegrationCmdInputLot::Save(QIODevice *f)
{
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	if(::Save(f,SubCode)==false)
		return false;
	if(::Save(f,GeneratedTime)==false)
		return false;
	return true;
}

void	IntegrationCmdInputLot::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	//IntegrationAckInputLot	*SendBack=GetSendBackIntegration(IntegrationAckInputLot,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	if(ExecuteCreateNew()==true){
		SetLotToSystem(LotAutoCount,LotID,LotName,SubCode);
	}
	//SendBack->LotID		=GetLayersBase()->GetLot(0)->GetLotID();
	//SendBack->LotName	=GetLayersBase()->GetLot(0)->GetLotName();
	//SendBack->LotRemark	=GetLayersBase()->GetLot(0)->GetRemark();
	//
	//SendBack->Send(this ,slaveNo,0);
	//CloseSendBackIntegration(SendBack);
	SendAck(slaveNo);
}
bool IntegrationCmdInputLot::ExecuteCreateNew(void)
{
	QString	SGetMax=QString(/**/"SELECT MAX(LOTAUTOCOUNT) FROM INSPECTIONLOT WHERE MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode());
	QSqlQuery querySGetMax(SGetMax,GetLayersBase()->GetDatabase());
	int	MaxAutoCount=0;
	if(querySGetMax.next ()==true){
		MaxAutoCount=querySGetMax.value(0).toInt();
	}
	MaxAutoCount++;
	LotAutoCount=MaxAutoCount;
	if(LotID.isEmpty()==true && LotName.isEmpty()==true){
		LotID	=GeneratedTime.toString(/**/"yyyy-MM-dd");
		LotName	=GeneratedTime.toString(/**/"hh-mm-ss");
	}
	else if(LotID.isEmpty()==false && LotName.isEmpty()==true){
		LotName	=GeneratedTime.toString(/**/"yyyy-MM-dd--hh-mm-ss");
	}
	else if(LotID.isEmpty()==true && LotName.isEmpty()==false){
		LotID	=GeneratedTime.toString(/**/"yyyy-MM-dd--hh-mm-ss");
	}

	//LotName	=LotNumber;

	try{
		QSqlQuery queryInsrt(GetLayersBase()->GetDatabase());
		queryInsrt.prepare(QString(/**/"INSERT INTO INSPECTIONLOT(LOTAUTOCOUNT,MASTERCODE,LASTUPDATED,IDNAME,LOTNAME,REMARK) ")
			+QString(/**/"VALUES(:LOTAUTOCOUNT,:MASTERCODE,:LASTUPDATED,:IDNAME,:LOTNAME,:REMARK);"));
		queryInsrt.bindValue(0	, LotAutoCount);
		queryInsrt.bindValue(1	, GetLayersBase()->GetMasterCode());
		queryInsrt.bindValue(2	, GeneratedTime.GetQDateTime());
		queryInsrt.bindValue(3	, LotID);
		queryInsrt.bindValue(4	, LotName);
		queryInsrt.bindValue(5	, SubCode);

		if(queryInsrt.exec()==false){
			return false;
		}
	}
	catch(...){
		return false;
	}
	return true;
}

void IntegrationCmdInputLot::SetLotToSystem(int iLotAutoCount
											,const QString &iLotID
											,const QString &iLotName
											,const QString &iLotRemark)
{
//	GetLayersBase()->RemoveStockedResult();

	GetLayersBase()->ClearInspectID();

	GetLayersBase()->GetLot(0)->SetLotAutoCount	(iLotAutoCount);
	GetLayersBase()->GetLot(0)->SetLotID		(iLotID);
	GetLayersBase()->GetLot(0)->SetLotName		(iLotName);
	GetLayersBase()->GetLot(0)->SetRemark		(iLotRemark);

	GetLayersBase()->GetLotBase()->SetLotID		(iLotID);
	GetLayersBase()->GetLotBase()->SetLotName	(iLotName);
	GetLayersBase()->GetLotBase()->SetLotRemark	(iLotRemark);
	
	GetLayersBase()->RemoveStockedResult();

	int64 InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
 	GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
	GetLayersBase()->SetInspectionTimeMilisec(GetComputerMiliSec());

	//if(LoadLastID==true){
	//	if(GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode(),iLotID,InspectionID)==true)
	//		InspectionID++;
	//}
	GetLayersBase()->SetCurrentInspectID(InspectionID);

	GetLayersBase()->SetForceChangedInspectID();
	GetLayersBase()->GetResultHistryData()->Reset();

	GUIFormBase	*f=GetLayersBase()->FindByName(sRoot,sName,/**/"");
	if(f!=NULL){
		f->BroadcastDirectly(GUIFormBase::_BC_BuildForShow ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	}

	//?!?n????CID?iS102?j?E?a????CID?d?Z?b?g??E?e
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

	if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->ChangeLot();
	}
	XDateTime	NowR=GetLayersBase()->GetStartInspectTime();
	ResultInspection	*Res=GetLayersBase()->GetCurrentResultForCalc();
	if(Res!=NULL){
		Res->SetStartTimeForInspect(NowR);
	}
					
	ResultInspection	*NRes=GetLayersBase()->GetNextResultForCalc();
	if(NRes!=NULL){
		NRes->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());
	}

	for(int page=0;page<GetPageNumb();page++){
		GUICmdSelectLot	RCmd(GetLayersBase(),sRoot,sName ,page);
		RCmd.LotAutoCount	=iLotAutoCount;
		RCmd.LotID			=iLotID;
		RCmd.LotName		=iLotName;
		RCmd.CurrentInspectTime=NowR;
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
			RCmd.AMode			=GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetAutoRepeat();
		}
		RCmd.Send(NULL,page,0);
	}
	//GetLayersBase()->ShowProcessingForm("Output lot to change");
	GetLayersBase()->GetResultDLLBase()->OutputInLotChangedCommon();
	GetLayersBase()->ClearCurrentStrategicNumberForCalc();
	//GetLayersBase()->CloseProcessingForm();
}

void IntegrationInputLotForm::on_pushButtonLotNumber_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditLotNumber->text());
	if(D.exec()==(bool)true){
		ui->lineEditLotNumber->setText(D.GetResult());
		ManualChangedLotID		=true;
	}
}

void IntegrationInputLotForm::on_pushButtonSubCode_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditSubCode->text());
	if(D.exec()==(bool)true){
		ui->lineEditSubCode->setText(D.GetResult());
		ManualChangedLotNumber	=true;
	}
}

void IntegrationInputLotForm::on_pushButtonLotID_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditLotID->text());
	if(D.exec()==(bool)true){
		ui->lineEditLotID->setText(D.GetResult());
		ManualChangedSubCode	=true;
	}

}

void IntegrationInputLotForm::on_lineEditLotID_textChanged(const QString &arg1)
{
	if(EnableManualChanged==true){
		ManualChangedLotID		=true;
	}
}

void IntegrationInputLotForm::on_lineEditLotNumber_textChanged(const QString &arg1)
{
	if(EnableManualChanged==true){
		ManualChangedLotNumber	=true;
	}
}

void IntegrationInputLotForm::on_lineEditSubCode_textChanged(const QString &arg1)
{
	if(EnableManualChanged==true){
		ManualChangedSubCode	=true;
	}
}

void IntegrationInputLotForm::on_pushButtonTitleLotID_clicked()
{
	InputPanelDialog	D(-1 ,UserLotID);
	if(D.exec()==(bool)true){
		UserLotID=D.GetResult();
		Counter=0;
	}
}

void IntegrationInputLotForm::on_pushButtonTitleLotNumber_clicked()
{
	InputPanelDialog	D(-1 ,UserLotNumber);
	if(D.exec()==(bool)true){
		UserLotNumber=D.GetResult();
		Counter=0;
	}
}

void IntegrationInputLotForm::on_pushButtonSubCode_2_clicked()
{
	InputPanelDialog	D(-1 ,UserSubCode);
	if(D.exec()==(bool)true){
		UserSubCode=D.GetResult();
	}
}

//========================================================================================
QString	IntegrationInputLotForm::ReplaceKeyword(const QString &src ,const QString &UserStr)
{
	IntegrationBase	*B=GetLayersBase()->GetIntegrationBasePointer();
	QString	s=src;
	bool	Changed;
	do{
		Changed=false;
		int	k1=s.indexOf(/**/"##");
		if(0<=k1){
			int	k2=s.indexOf(/**/"##",k1+2);
			if(2<=k2){
				QString Key=s.mid(k1+2,k2-k1-2);
				QString	L1=s.mid(0,k1);
				QString	L2=s.mid(k2+2);
				Key=Key.toUpper();
				if(Key==QString(/**/"++").toUpper()){
					s=L1+QString::number(Counter+1)+L2;
					Changed=true;
				}
				else if(Key==QString(/**/"User").toUpper()){
					s=L1+UserStr+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Alpha").toUpper()){
					s=L1+QString((char)('A'+Counter))+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"MasterID").toUpper()){
					if(B!=NULL){
						QString		RetRelationNumber;
						QString		RetRelationName;
						QString		RetRemark;
						int			RetRelationType;
						QByteArray	CommonData;
						int32		ThresholdLevelID;

						if(B->GetInformation(RetRelationNumber
											,RetRelationName
											,RetRemark
											,RetRelationType
											,CommonData
											,ThresholdLevelID)==true){
							s=L1+RetRelationNumber+L2;
							Changed=true;
						}
					}
				}
				else
				if(Key==QString(/**/"MasterName").toUpper()){
					if(B!=NULL){
						QString		RetRelationNumber;
						QString		RetRelationName;
						QString		RetRemark;
						int			RetRelationType;
						QByteArray	CommonData;
						int32		ThresholdLevelID;

						if(B->GetInformation(RetRelationNumber
											,RetRelationName
											,RetRemark
											,RetRelationType
											,CommonData
											,ThresholdLevelID)==true){
							s=L1+RetRelationName+L2;
							Changed=true;
						}
					}
				}
				else
				if(Key==QString(/**/"MasterRemark").toUpper()){
					if(B!=NULL){
						QString		RetRelationNumber;
						QString		RetRelationName;
						QString		RetRemark;
						int			RetRelationType;
						QByteArray	CommonData;
						int32		ThresholdLevelID;

						if(B->GetInformation(RetRelationNumber
											,RetRelationName
											,RetRemark
											,RetRelationType
											,CommonData
											,ThresholdLevelID)==true){
							s=L1+RetRemark+L2;
							Changed=true;
						}
					}
				}
				else
				if(Key==QString(/**/"Year").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.date().year())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Month").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.date().month())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Day").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.date().day())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Date").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+d.date().toString(/**/"yyyy-MM-dd")+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Hour").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.time().hour())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Minute").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.time().minute())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Second").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+QString::number(d.time().second())+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"Time").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+d.time().toString(/**/"hh-mm-ss")+L2;
					Changed=true;
				}
				else
				if(Key==QString(/**/"DateTime").toUpper()){
					QDateTime	d=QDateTime::currentDateTime();
					s=L1+d.toString(/**/"yyyy-MM-dd-hh-mm-ss")+L2;
					Changed=true;
				}
			}
		}
	}while(Changed==true);

	return s;
}
//========================================================================================
IntegrationReqInputLot::IntegrationReqInputLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

void	IntegrationReqInputLot::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	IntegrationAckInputLot	*SendBack=GetSendBackIntegration(IntegrationAckInputLot,GetLayersBase(),EmitterRoot,EmitterName ,slaveNo);

	SendBack->LotID		=GetLayersBase()->GetLot(0)->GetLotID();
	SendBack->LotName	=GetLayersBase()->GetLot(0)->GetLotName();
	SendBack->LotRemark	=GetLayersBase()->GetLot(0)->GetRemark();
	
	SendBack->Send(this ,slaveNo,0);
	CloseSendBackIntegration(SendBack);
}

IntegrationAckInputLot::IntegrationAckInputLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}

bool	IntegrationAckInputLot::Load(QIODevice *f)
{
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	if(::Load(f,LotRemark)==false)
		return false;
	return true;
}
bool	IntegrationAckInputLot::Save(QIODevice *f)
{
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	if(::Save(f,LotRemark)==false)
		return false;
	return true;
}

GUICmdSelectLot::GUICmdSelectLot(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	AMode=ExecuteInspectBase::_NoAutoRepeat;
}

bool	GUICmdSelectLot::Load(QIODevice *f)
{
	if(::Load(f,LotAutoCount)==false)
		return false;
	if(::Load(f,LotID)==false)
		return false;
	if(::Load(f,LotName)==false)
		return false;
	if(::Load(f,CurrentInspectTime)==false)
		return false;
	if(f->read((char *)&AMode,sizeof(AMode))!=sizeof(AMode))
		return false;
	return true;
}
bool	GUICmdSelectLot::Save(QIODevice *f)
{
	if(::Save(f,LotAutoCount)==false)
		return false;
	if(::Save(f,LotID)==false)
		return false;
	if(::Save(f,LotName)==false)
		return false;
	if(::Save(f,CurrentInspectTime)==false)
		return false;
	if(f->write((const char *)&AMode,sizeof(AMode))!=sizeof(AMode))
		return false;
	return true;
}
void	GUICmdSelectLot::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if(localPage==0){
		if(GetLayersBase()->GetEntryPoint()->IsMasterPC()==false){
			GetLayersBase()->GetLot(0)->SetLotAutoCount	(LotAutoCount);
			GetLayersBase()->GetLot(0)->SetLotID		(LotID);
			GetLayersBase()->GetLot(0)->SetLotName		(LotName);

			int64	InspectionID;
			GetLayersBase()->GetResultDLLBase()->GetLastInspectionID(GetLayersBase()->GetMasterCode()
																	,LotID
																	,InspectionID);
			int		RPoint[3];
			RPoint[0]=0;
			RPoint[1]=0;
			RPoint[2]=0;
			if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL){
				if(AMode==ExecuteInspectBase::_AutoCaptureInspect){
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
		GetLayersBase()->GetResultThread()->ClearAllErrorGroup();
		GetLayersBase()->ClearExecuterState();
		GetLayersBase()->ClearSystemResult();
	}
}
