#include "ExecutorOfPixListForm.h"
#include "ui_ExecutorOfPixListForm.h"
#include "XGeneralFunc.h"
#include <QFileInfo>
#include <QDir>
#include "LoadImageTargetButton.h"
#include "ButtonLoadBmpJpg.h"
#include "XCriticalFunc.h"
#include "XGeneralStocker.h"
#include "ShowMultiImage.h"
#include "XResult.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ExecutorOfPixListForm::ExecutorList	*ExecutorOfPixListForm::ExecutorListContainerClass::Find(const QString &foldername ,const QString &filename)
{
	for(ExecutorList *e=GetFirst();e!=NULL;e=e->GetNext()){
		if(e->FolderName==foldername && e->FileName==filename){
			return e;
		}
	}
	return NULL;
}
int	ExecutorOfPixListForm::ExecutorList::Compare(ExecutorList &src)
{
	QVariantList	iArgV;
	QVariantList	iRetV;
	iArgV.append(FileName);
	iArgV.append(src.FileName);
	if(Parent->GetLayersBase()->GetGeneralStocker()->GetData(/**/"CompareFileNameForSort",iRetV,iArgV)==true){
		if(iRetV.count()!=0){
			int	Ret=iRetV[0].toInt();
			return Ret;
		}
	}
	return 0;
}


ExecutorOfPixListForm::ExecutorOfPixListForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ExecutorOfPixListForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	PhaseToLoad	=-1;
	Canceled	=false;

	GetParamGUI()->SetParam(&DefaultFolders		, /**/"ExecutorOfPixList",/**/"DefaultFolders"	,/**/"Default folders"	);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ExecutorOfPixListForm::~ExecutorOfPixListForm()
{
    delete ui;
}

void	ExecutorOfPixListForm::Prepare(void)
{
	ui->tableWidget->setColumnWidth(0,(width()-32)*2/7);
	ui->tableWidget->setColumnWidth(1,(width()-32)*4/7);
	ui->tableWidget->setColumnWidth(2,(width()-32)*1/7);

//	QDir	CurrentDir=QDir::current();
//	ExecutorListContainer.RemoveAll();
//	for(int i=0;i<DefaultFolders.count();i++){
//		QString	foldername=DefaultFolders[i];
//		QDir	CD;
//		CD.setCurrent(foldername);
//		
//		QStringList nameFilters;
//		nameFilters<</**/"*.pix";
//		QStringList Files=CD.entryList (nameFilters, QDir::Files, QDir::Time );
//		for(int j=0;j<Files.count();j++){
//			QString	f=Files[j];
//			ExecutorListContainer.AppendList(new ExecutorList(this,foldername,f));
//		}
//	}
//	QString	path=CurrentDir.absolutePath();
//	QDir::setCurrent(path);

	ShowList();

	if(GetLayersBase()->GetGeneralStocker()->GetType(/**/"SearchFilter")==QVariant::Invalid){
		ui->toolButtonFilter->setVisible(false);
	}
}

void ExecutorOfPixListForm::ShowList(void)
{
	ui->tableWidget->setRowCount(ExecutorListContainer.GetCount());
	int	Row=0;
	int	OKCount=0;
	int	NGCount=0;
	for(ExecutorList *a=ExecutorListContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget ,0 ,Row ,a->FolderName);
		::SetDataToTable(ui->tableWidget ,1 ,Row ,a->FileName);
		QString	JudgeStr;
		if(a->Judge==true3){
			JudgeStr="OK";
			OKCount++;
		}
		else if(a->Judge==false3){
			JudgeStr="NG";
			NGCount++;
		}
		else
			JudgeStr="--";

		::SetDataToTable(ui->tableWidget ,2 ,Row ,JudgeStr);
	}
	ui->labelOKCount->setText(QString::number(OKCount));
	ui->labelNGCount->setText(QString::number(NGCount));
}

void ExecutorOfPixListForm::ShowRow(int Row)
{
	ExecutorList *a=ExecutorListContainer[Row];
	::SetDataToTable(ui->tableWidget ,0 ,Row ,a->FolderName);
	::SetDataToTable(ui->tableWidget ,1 ,Row ,a->FileName);
	QString	JudgeStr;
	if(a->Judge==true3){
		JudgeStr="OK";
	}
	else if(a->Judge==false3){
		JudgeStr="NG";
	}
	else
		JudgeStr="--";

	::SetDataToTable(ui->tableWidget ,2 ,Row ,JudgeStr);

	int	OKCount=0;
	int	NGCount=0;
	for(ExecutorList *a=ExecutorListContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		if(a->Judge==true3){
			OKCount++;
		}
		else if(a->Judge==false3){
			NGCount++;
		}
	}
	ui->labelOKCount->setText(QString::number(OKCount));
	ui->labelNGCount->setText(QString::number(NGCount));
}

void	ExecutorOfPixListForm::ShowClearResult(int Row)
{
	::SetDataToTable(ui->tableWidget ,2 ,Row ,"--");
}

void ExecutorOfPixListForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidget	->currentRow();
	if(Row<0)
		return;
	ExecutorList *k=ExecutorListContainer[Row];
	QString	FileName=k->FolderName	+::GetSeparator()+k->FileName;
	LoadImageData(FileName);

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Panel",/**/"ShowMultiImage",/**/"");
	if(f!=NULL){
		int	PanelCount=0;
		{
			CmdReqPanelCount	RCmd(GetLayersBase());
			f->TransmitDirectly(&RCmd);
			PanelCount=RCmd.PanelCount;
		}
		{
			CmdLoadImages	RCmd(GetLayersBase());
			int	r=Row-PanelCount/2;
			if(r<0)
				r=0;
			for(int i=0;i<PanelCount;i++){
				int	Cr=r+i;
				if(Cr<ExecutorListContainer.GetCount()){
					ExecutorList *k=ExecutorListContainer[Cr];
					QString	FileName=k->FolderName	+::GetSeparator()+k->FileName;
					RCmd.FileNames.append(FileName);
				}
			}
			f->TransmitDirectly(&RCmd);
		}
	}

	BroadcastShowInEdit();
}

void ExecutorOfPixListForm::on_pushButtonExecute_clicked()
{
	IntList Rows;
	::GetSelectedRows(ui->tableWidget,Rows);
	if(Rows.GetCount()==0){
		int	Row=0;
		for(ExecutorList *a=ExecutorListContainer.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			Rows.Add(Row);
		}
	}
	GetLayersBase()->ShowProcessingForm("Processing again");
	GetLayersBase()->SetMaxProcessing(Rows.GetCount());
	Canceled=false;

	for(IntClass *a=Rows.GetFirst();a!=NULL;a=a->GetNext()){
		if(Canceled==true){
			break;
		}
		int	Row=a->GetValue();
		ShowClearResult(Row);
	}

	for(IntClass *a=Rows.GetFirst();a!=NULL;a=a->GetNext()){
		if(Canceled==true){
			break;
		}
		int	Row=a->GetValue();
		ExecutorList *k=ExecutorListContainer[Row];
		if(k!=NULL){
			QString	FileName=k->FolderName	+::GetSeparator()+k->FileName;
			LoadImageData(FileName);
			bool	Ret=ExecuteOne();
			if(Ret==true)
				k->Judge=true3;
			else
				k->Judge=false3;
		}
		ShowRow(Row);

		QCoreApplication::processEvents();

		GetLayersBase()->StepProcessing(-1);
	}
	GetLayersBase()->CloseProcessingForm ();
	ShowList();
}

void ExecutorOfPixListForm::on_pushButtonDeleteList_clicked()
{
	IntList Rows;
	::GetSelectedRows(ui->tableWidget,Rows);
	for(IntClass *p=Rows.GetLast();p!=NULL;p=p->GetPrev()){
		ExecutorList *k=ExecutorListContainer[p->GetValue()];
		ExecutorListContainer.RemoveList(k);
		delete	k;
	}
	ShowList();
}

bool ExecutorOfPixListForm::LoadImageData(const QString &FileName)
{
	QFileInfo	Info(FileName);
	if(Info.suffix().toUpper()==QString(/**/"PIX")){
		int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
		if(PhaseToLoad==-1){
			bool	Ret=false;
			for(int phase=0;phase<GetPhaseNumb();phase++){
				GetLayersBase()->SetCurrentPhase(phase);
				CmdReqLoadImage	Cmd(GetLayersBase());
				Cmd.FileName=FileName;
				GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"LoadImageTargetButton",/**/"");
				if(f!=NULL){
					f->TransmitDirectly(&Cmd);
					Ret=Cmd.Success;
				}
			}
			GetLayersBase()->SetCurrentPhase(CurrentPhase);
			BroadcastShowInEdit();
			return Ret;
		}
		else if(0<=PhaseToLoad && PhaseToLoad<GetPhaseNumb()){
			GetLayersBase()->SetCurrentPhase(PhaseToLoad);
			CmdReqLoadImage	Cmd(GetLayersBase());
			Cmd.FileName=FileName;
			GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Inspection",/**/"LoadImageTargetButton",/**/"");
			if(f!=NULL){
				f->TransmitDirectly(&Cmd);
				GetLayersBase()->SetCurrentPhase(CurrentPhase);
				BroadcastShowInEdit();
				return Cmd.Success;
			}
		}

	}
	else{
		int	CurrentPhase=GetLayersBase()->GetCurrentPhase();
		if(PhaseToLoad==-1){
			bool	Ret=false;
			for(int phase=0;phase<GetPhaseNumb();phase++){
				GetLayersBase()->SetCurrentPhase(phase);
				CmdLoadBmpJpgPacketTarget	Cmd(GetLayersBase());
				Cmd.FileName=FileName;
				GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonLoadBmpJpg",/**/"");
				if(f!=NULL){
					f->TransmitDirectly(&Cmd);
					Ret=Cmd.Success;
				}
			}
			GetLayersBase()->SetCurrentPhase(CurrentPhase);
			BroadcastShowInEdit();
			return Ret;
		}
		else if(0<=PhaseToLoad && PhaseToLoad<GetPhaseNumb()){
			GetLayersBase()->SetCurrentPhase(PhaseToLoad);
			CmdLoadBmpJpgPacketTarget	Cmd(GetLayersBase());
			Cmd.FileName=FileName;
			GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ButtonLoadBmpJpg",/**/"");
			if(f!=NULL){
				f->TransmitDirectly(&Cmd);
				GetLayersBase()->SetCurrentPhase(CurrentPhase);
				BroadcastShowInEdit();
				return Cmd.Success;
			}
		}
	}
	return false;
}
void ExecutorOfPixListForm::on_pushButtonAddFolder_clicked()
{
	QString foldername=QFileDialog::getExistingDirectory ( NULL
									, "Folder for PIX"
									, QString());
	if(foldername.isEmpty()==false){
		QDir	CurrentDir=QDir::current();
		QDir	CD;
		CD.setCurrent(foldername);
		
		QStringList nameFilters;
		nameFilters<</**/"*.pix";
		QStringList Files=CD.entryList (nameFilters, QDir::Files, QDir::Time );
		for(int j=0;j<Files.count();j++){
			QString	f=Files[j];
			ExecutorList	*k=new ExecutorList(this,foldername,f);
			if(ExecutorListContainer.Find(foldername,f)==NULL){
				ExecutorListContainer.AppendList(k);
			}
			else{
				delete	k;
			}
		}
		QString	path=CurrentDir.absolutePath();
		QDir::setCurrent(path);

		ShowList();
	}
}

void ExecutorOfPixListForm::on_pushButtonUpdate_clicked()
{
	ExecutorListContainer.RemoveAll();

	QVariantList	ArgV;
	QVariantList	RetV;
	QStringList		SearchedFilters;
	GetLayersBase()->GetGeneralStocker()->GetData(/**/"SearchFilter",RetV,ArgV);
	if(RetV.count()>0){
		for(int i=0;i<RetV.count();i++){
			SearchedFilters.append(RetV[i].toString());
		}
	}
	if(SearchedFilters.count()==0){
		SearchedFilters.append(/**/"*.pix");
		SearchedFilters.append(/**/"*.jpg");
		SearchedFilters.append(/**/"*.png");
		SearchedFilters.append(/**/"*.bmp");
	}

	GetLayersBase()->ShowProcessingForm ("リスト更新中" ,false ,DefaultFolders.count());

	for(int i=0;i<DefaultFolders.count();i++){
		QString	foldername=DefaultFolders[i];
		QDir	CD;
		CD.setCurrent(foldername);
		
		QStringList nameFilters;
		nameFilters=SearchedFilters;
		QStringList Files=CD.entryList (nameFilters, QDir::Files, QDir::Time );
		for(int j=0;j<Files.count();j++){
			QString	f=Files[j];
			QVariantList	iArgV;
			QVariantList	iRetV;
			iArgV.append(f);
			if(GetLayersBase()->GetGeneralStocker()->GetData(/**/"IsMatched",iRetV,iArgV)==true){
				if(iRetV.count()!=0){
					if(iRetV[0].toBool()==true){
						ExecutorListContainer.AppendList(new ExecutorList(this,foldername,f));
					}
				}
			}
			else{
				ExecutorListContainer.AppendList(new ExecutorList(this,foldername,f));
			}
		}
		GetLayersBase()->StepProcessing(-1);
	}
	if(GetLayersBase()->GetGeneralStocker()->GetType(/**/"CompareFileNameForSort")!=QVariant::Invalid){
		ExecutorListContainer.Sort();
	}
	ShowList();
	GetLayersBase()->CloseProcessingForm();
}

bool	ExecutorOfPixListForm::ExecuteOne(void)
{
	IntList PhaseCodes;
	GetLayersBase()->GetCurrentPhaseFromScanPhase(PhaseCodes);

	//Canceled=false;
	int	CurrentPhase=0;
	if(PhaseCodes.GetCount()>0)
		CurrentPhase=PhaseCodes[0];
	else
		CurrentPhase=GetLayersBase()->GetCurrentPhase();

	GetLayersBase()->ClearAllAckFlag();

	bool	Ok=true;

	if(GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetPageNumb();page++){
			GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
			GUIAckPushed	PushAnswer	 (GetLayersBase(),sRoot,sName);
			PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
			PushRequester.IsExecInitialAfterEdit=false;
			PushRequester.MaxInspectMilisec		=99999999;
			if(PushRequester.Send(GetLayersBase()->GetGlobalPageFromLocal(page),0,PushAnswer)==true){
				if(PushAnswer.Ok==false)
					Ok=false;
			}
		}
		GetLayersBase()->WaitAllAcknowledged(60*20);
	}
	else{
		GUICmdPushed	PushRequester(GetLayersBase(),sRoot,sName);
		GUIAckPushed	PushAnswer	 (GetLayersBase(),sRoot,sName);
		PushRequester.InspectionID=GetLayersBase()->GetCurrentInspectIDForExecute();
		PushRequester.IsExecInitialAfterEdit=false;
		PushRequester.MaxInspectMilisec		=99999999;
		if(PushRequester.Send(GetLayersBase()->GetGlobalPageFromLocal(0),0,PushAnswer)==true){
			if(PushAnswer.Ok==false)
				Ok=false;
		}

		GetLayersBase()->SetShouldWriteResult(false);

		GetLayersBase()->SetShouldWriteResult(true);
	}
	GetLayersBase()->SetCurrentInspectID(GetLayersBase()->GetCurrentInspectIDForExecute());

	GetLayersBase()->SetCurrentPhase(CurrentPhase);
	return Ok;
}

void	ExecutorOfPixListForm::ResizeAction()
{
	ui->tableWidget	->move(0,0);
	ui->tableWidget	->resize(width(),height()-ui->frame->height());
	ui->frame->move(0,height()-ui->frame->height());
	ui->frame->resize(width(),ui->frame->height());

	
	::SetColumnWidthInTable(ui->tableWidget ,0, 40);
	::SetColumnWidthInTable(ui->tableWidget ,1, 45);
	::SetColumnWidthInTable(ui->tableWidget ,2, 15);
}

void ExecutorOfPixListForm::on_tableWidget_itemSelectionChanged()
{

}

void ExecutorOfPixListForm::on_pushButtonAll_clicked()
{
	IntList Rows;
	GetSelectedRows(ui->tableWidget ,Rows);
	if(Rows.GetCount()==ExecutorListContainer.GetCount()){
		ui->tableWidget->clearSelection();
	}
	else{
		ui->tableWidget->selectAll();
	}
}

void ExecutorOfPixListForm::on_toolButtonCancel_clicked()
{
	Canceled=true;
}

void ExecutorOfPixListForm::on_toolButtonFilter_clicked()
{
	if(GetLayersBase()->GetGeneralStocker()->ShowDialog(/**/"SearchFilter",NULL)==true){
		on_pushButtonUpdate_clicked();
	}
}

//===========================================================================================

GUICmdPushed::GUICmdPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	InspectionID=0;
	IsExecInitialAfterEdit=true;
}

bool	GUICmdPushed::Load(QIODevice *f)
{
	if(::Load(f,InspectionID)==false)
		return false;
	if(::Load(f,IsExecInitialAfterEdit)==false)
		return false;
	if(::Load(f,MaxInspectMilisec)==false)
		return false;
	return true;
}
bool	GUICmdPushed::Save(QIODevice *f)
{
	if(::Save(f,InspectionID)==false)
		return false;
	if(::Save(f,IsExecInitialAfterEdit)==false)
		return false;
	if(::Save(f,MaxInspectMilisec)==false)
		return false;
	return true;
}

void	GUICmdPushed::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIAckPushed	*SendBack=GetSendBack(GUIAckPushed,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	if(localPage==0){
		if(GetParamGlobal()->AllocRawTargetBuffForNGImage==true){
			for(int page=0;page<GetPageNumb();page++){
				for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
					GetLayersBase()->GetPageData(page)->GetLayerData(Layer)->RestoreTargetImageFromRaw();
				}
			}
		}

		GetLayersBase()->SetCurrentInspectID(InspectionID);
		int32	TmpMaxInspectMilisec	=GetParamGlobal()->MaxInspectMilisec;
		GetParamGlobal()->MaxInspectMilisec	=MaxInspectMilisec;

		GetLayersBase()->AddMaxProcessing(localPage,7);
		int	TempStrategy=GetParamGlobal()->GetMaxScanStrategy();
		GetParamGlobal()->SetMaxScanStrategy(1);

		int	CPoint[6];
		GetLayersBase()->GetCalcPoint(CPoint);
		CPoint[1]=CPoint[0];
		int	CurrentCalcPoint=CPoint[0];
		CurrentCalcPoint--;
		if(CurrentCalcPoint<0)
			CurrentCalcPoint=GetParamGlobal()->NGCacheNumb-1;
		if(GetLayersBase()->GetExecuter(CurrentCalcPoint)->GetState()==DataInExecuter::FinExecuteStartByInspection
		|| GetLayersBase()->GetExecuter(CurrentCalcPoint)->GetState()==DataInExecuter::FinExecuteStartByScanOnly){
			GetLayersBase()->DecPoint();
			CPoint[1]--;
			if(CPoint[1]<0)
				CPoint[1]=GetParamGlobal()->NGCacheNumb-1;
		}

		GetLayersBase()->PushExecuterState();
		GetLayersBase()->StepProcessing(localPage);
		if(IsExecInitialAfterEdit==true){
			ExecuteInitialAfterEditInfo DummyEInfo;
			GetLayersBase()->ExecuteInitialAfterEdit(DummyEInfo);
		}
		XDateTime	SaveTm=GetLayersBase()->GetStartInspectTime();
		DWORD		SaveRm=GetLayersBase()->GetStartInspectionTimeMilisec();

		GetLayersBase()->SetStartInspectTime(XDateTime::currentDateTime());
		GetLayersBase()->SetStartInspectionTimeMilisec(GetComputerMiliSec());

//		GetLayersBase()->SetForceChangedInspectID();
//		XDateTime	NowD=GetLayersBase()->GetStartInspectionTime();
//		GetLayersBase()->GetLogicDLLBase()->SetStartTimeForInspection(NowD);


		GetLayersBase()->StepProcessing(localPage);
		GetLayersBase()->ExecuteStartByInspection	(false);
		ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
		if(CurrentResult!=NULL){
			CurrentResult->SetStartTimeForInspect(GetLayersBase()->GetStartInspectTime());

			DWORD	C=GetComputerMiliSec();
			DWORD	Cn;

			ListPhasePageLayerPack	CapturedList;
			GetLayersBase()->MakeCapturedAllList(CapturedList);

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteCaptured		(CapturedList,false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteCaptured=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecutePreAlignment		(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePreAlignment=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteAlignment			(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteAlignment=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecutePreProcessing		(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePreProcessing=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteProcessing			(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteProcessing=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->ExecuteProcessingRevived	(false);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecuteProcessingRevived=Cn-C;
			C=Cn;

			GetLayersBase()->StepProcessing(localPage);
			GetLayersBase()->SetShouldWriteResult(false);
			GetLayersBase()->ExecutePostProcessing		(false);		
			GetLayersBase()->SetShouldWriteResult(true);
			Cn=GetComputerMiliSec();
			CurrentResult->ExecTime.TM_ExecutePostProcessing=Cn-C;
			C=Cn;

			GetParamGlobal()->SetMaxScanStrategy(TempStrategy);

			int	NGCount=CurrentResult->GetNGCount();
			SendBack->Ok		=(NGCount==0)?true:false;
			SendBack->NGCount	=CurrentResult->GetNGCount();

			GetLayersBase()->SendAckToMaster(localPage);

			CmdInspectionAgainReplied	PacketReplied(GetLayersBase(),QString(sRoot),QString(sName));
			PacketReplied.Result		=CmdInspectionAgainReplied::_OK;
			PacketReplied.NGCounts		=CurrentResult->GetNGCount();
			PacketReplied.TimeOutBreak	=CurrentResult->GetTimeOutBreak()	;
			PacketReplied.MaxErrorBreak	=CurrentResult->GetMaxErrorBreak()	;
			DataInExecuter	*Re			=GetLayersBase()->GetExecuter(CurrentResult);
			PacketReplied.ExecuterID	=Re->GetID();
			if(GetParamComm()->Mastered==true){
				for(int page=0;page<GetPageNumb();page++){
					Re->SetResultReceivedFlag(page,PacketReplied.NGCounts,PacketReplied.TimeOutBreak,PacketReplied.MaxErrorBreak);
				}
			}
			else{
				Re->SetResultReceivedFlag(localPage,PacketReplied.NGCounts,PacketReplied.TimeOutBreak,PacketReplied.MaxErrorBreak);
			}
		}



		GetLayersBase()->PopExecuterState();
		GetLayersBase()->SetCalcPoint(CPoint);
		GetLayersBase()->SetStartInspectTime(SaveTm);
		GetLayersBase()->SetStartInspectionTimeMilisec(SaveRm);
		GetParamGlobal()->MaxInspectMilisec=TmpMaxInspectMilisec;
	}
	else{
		ResultInspection	*CurrentResult=GetLayersBase()->GetCurrentResultForCalc();
		if(CurrentResult!=NULL){
			DataInExecuter	*Re		=GetLayersBase()->GetExecuter(CurrentResult);
			Re->SetResultReceivedFlag(localPage,0,false,false);
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

CmdInspectionAgainReplied::CmdInspectionAgainReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	CmdInspectionAgainReplied::Load(QIODevice *f)
{
	BYTE	ResultData;
	if(::Load(f,ResultData)==false)
		return false;
	Result=(__Result)ResultData;
	if(::Load(f,NGCounts)==false)
		return false;
	if(::Load(f,TimeOutBreak)==false)
		return false;
	if(::Load(f,MaxErrorBreak)==false)
		return false;
	if(::Load(f,ExecuterID)==false)
		return false;
	return true;
}
bool	CmdInspectionAgainReplied::Save(QIODevice *f)
{
	BYTE	ResultData=(BYTE)Result;
	if(::Save(f,ResultData)==false)
		return false;
	if(::Save(f,NGCounts)==false)
		return false;
	if(::Save(f,TimeOutBreak)==false)
		return false;
	if(::Save(f,MaxErrorBreak)==false)
		return false;
	if(::Save(f,ExecuterID)==false)
		return false;
	return true;
}

void	CmdInspectionAgainReplied::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	LayersBase	*L=GetLayersBase();
	DataInExecuter	*Re=GetLayersBase()->GetExecuter(ExecuterID);
	Re->SetResultReceivedFlag(localPage,NGCounts,TimeOutBreak,MaxErrorBreak);

	SendAck(localPage);
}

GUIAckPushed::GUIAckPushed(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	Ok		=false;
	NGCount	=0;
}
bool	GUIAckPushed::Load(QIODevice *f)
{
	if(::Load(f,Ok)==false)
		return false;
	if(::Load(f,NGCount)==false)
		return false;
	return true;
}
bool	GUIAckPushed::Save(QIODevice *f)
{
	if(::Save(f,Ok)==false)
		return false;
	if(::Save(f,NGCount)==false)
		return false;
	return true;
}
