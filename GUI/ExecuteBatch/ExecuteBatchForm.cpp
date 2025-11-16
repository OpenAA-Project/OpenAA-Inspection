#include "ExecuteBatchResource.h"
#include "ExecuteBatchForm.h"
#include "ui_ExecuteBatchForm.h"
#include "SetCommandDialog.h"
#include "ExecuteBatch.h"
#include "XGeneralFunc.h"

extern	const	char* sRoot;
extern	const	char* sName;

ExecuteBatchForm::ExecuteBatchForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent)
	,MClient(this)
    ,ui(new Ui::ExecuteBatchForm)
{
    ui->setupUi(this);
	CancelMode=false;
	ExecutingLine	=-1;
	LoadedNewBatch	=false;
	HMessage=NULL;
	MessagerIPAddress	=/**/"localhost";

	GetParamGUI()->SetParam(&MessagerIPAddress, sName,/**/"MessagerIPAddress"
							,LangSolver.GetString(ExecuteBatchForm_LS,LID_0)/*"Messager IP Address"*/		);
	connect(this,SIGNAL(SignalExecute()),this,SLOT(SlotExecute()),Qt::QueuedConnection);
	connect(&MClient,SIGNAL(SignalReceived()),this,SLOT(SlotReceived()));

}

ExecuteBatchForm::~ExecuteBatchForm()
{
	if(HMessage!=NULL)
		delete	HMessage;
	HMessage=NULL;

    delete ui;
}
void	ExecuteBatchForm::Prepare(void)
{
	MClient.Start();
	MClient.Initial(MessagerIPAddress);
}

void	ExecuteBatchForm::resizeEvent ( QResizeEvent * event )
{
	ui->frame->move(width()-ui->frame->width(),ui->frame->geometry().top());
	ui->tableWidget->resize(width()-ui->frame->width(),height());

	int	W=ui->tableWidget->width()-32;
	ui->tableWidget->setColumnWidth(0,2*W/20);
	ui->tableWidget->setColumnWidth(1,4*W/20);
	ui->tableWidget->setColumnWidth(2,5*W/20);
	ui->tableWidget->setColumnWidth(3,3*W/20);
	ui->tableWidget->setColumnWidth(4,3*W/20);
	ui->tableWidget->setColumnWidth(5,3*W/20);
}
void	ExecuteBatchForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdLoadBatchFile	*CmdLoadBatchFileVar=dynamic_cast<CmdLoadBatchFile *>(packet);
	if(CmdLoadBatchFileVar!=NULL){
		QFile	File(CmdLoadBatchFileVar->FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			BatchData.LoadText(&File);
			LoadedNewBatch=true;
			ShowList();	
		}
		else{
			BatchData.RemoveAll();
		}
		return;
	}
	CmdExecuteBatch	*CmdExecuteBatchVar=dynamic_cast<CmdExecuteBatch *>(packet);
	if(CmdExecuteBatchVar!=NULL){
		emit	SignalExecute();
		return;
	}
	CmdCheckExecuteStatus	*CmdCheckExecuteStatusVar=dynamic_cast<CmdCheckExecuteStatus *>(packet);
	if(CmdCheckExecuteStatusVar!=NULL){
		if(ExecutingLine==-1){
			CmdCheckExecuteStatusVar->Executing=false;
		}
		else{
			CmdCheckExecuteStatusVar->Executing=true;
			CmdCheckExecuteStatusVar->CurrentLine=ExecutingLine;
		}
		if(CancelMode==true || LoadedNewBatch==true){
			CmdCheckExecuteStatusVar->ExecutingWithStop=true;
		}
		else{
			CmdCheckExecuteStatusVar->ExecutingWithStop=false;
		}
		return;
	}
	CmdSetArgParameter	*CmdSetArgParameterVar=dynamic_cast<CmdSetArgParameter *>(packet);
	if(CmdSetArgParameterVar!=NULL){
		int	Row=0;
		for(BatchLine *L=BatchData.GetFirst();L!=NULL;L=L->GetNext()){
			if(L->DLLRoot==CmdSetArgParameterVar->DLLRoot
			&& L->DLLName==CmdSetArgParameterVar->DLLName
			&& L->CommandStr==CmdSetArgParameterVar->CommandStr){
				if(CmdSetArgParameterVar->Turn==-1 || CmdSetArgParameterVar->Turn==Row){
					for(int i=0;i<L->ArgValues.count();i++){
						if(L->ArgValues[i]==CmdSetArgParameterVar->ArgName){
							L->ArgValues[i]=CmdSetArgParameterVar->NewParam;
						}
					}
				}
				Row++;
			}
		}
		return;
	}
	CmdSetParameterInNumber	*CmdSetParameterInNumberVar=dynamic_cast<CmdSetParameterInNumber *>(packet);
	if(CmdSetParameterInNumberVar!=NULL){
		if(CmdSetParameterInNumberVar->ParamNumber<=BatchData.ParamFromArg.count()){
			BatchData.ParamFromArg[CmdSetParameterInNumberVar->ParamNumber]=CmdSetParameterInNumberVar->NewParam;
		}
		return;
	}
	CmdReplaceCommandParam	*CmdReplaceCommandParamVar=dynamic_cast<CmdReplaceCommandParam *>(packet);
	if(CmdReplaceCommandParamVar!=NULL){
		BatchData.ReplaceParam(CmdReplaceCommandParamVar->Keyword,CmdReplaceCommandParamVar->ReplacedStr);
		ShowList();
		return;
	}
}
void	ExecuteBatchForm::ShowList(void)
{
	ui->tableWidget->setRowCount(BatchData.GetCount());
	int	Row=0;
	for(BatchLine *L=BatchData.GetFirst();L!=NULL;L=L->GetNext(),Row++){
		::SetDataToTable(ui->tableWidget,0,Row ,L->DLLRoot);
		::SetDataToTable(ui->tableWidget,1,Row ,L->DLLName);
		::SetDataToTable(ui->tableWidget,2,Row ,L->CommandStr);
		if(L->ArgValues.count()>=1)
			::SetDataToTable(ui->tableWidget,3,Row ,L->ArgValues[0]);
		else
			::SetDataToTable(ui->tableWidget,3,Row ,/**/"");
		if(L->ArgValues.count()>=2)
			::SetDataToTable(ui->tableWidget,4,Row ,L->ArgValues[1]);
		else
			::SetDataToTable(ui->tableWidget,4,Row ,/**/"");
		if(L->ArgValues.count()>=3)
			::SetDataToTable(ui->tableWidget,5,Row ,L->ArgValues[2]);
		else
			::SetDataToTable(ui->tableWidget,5,Row ,/**/"");
	}
}

void ExecuteBatchForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	on_pushButtonModify_clicked();
}

void ExecuteBatchForm::on_pushButtonUp_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<1)
		return;
	BatchLine *L=BatchData[Row];
	if(L!=NULL){
		BatchData.RemoveList(L);
		BatchData.InsertList(Row-1,L);
		Row--;
		if(Row<0)
			Row=0;
		ui->tableWidget->setCurrentCell(Row,0);
	}
	ShowList();
}

void ExecuteBatchForm::on_pushButtonDown_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0 || Row>=(BatchData.GetCount()-1))
		return;
	BatchLine *L=BatchData[Row];
	if(L!=NULL){
		BatchData.RemoveList(L);
		BatchData.InsertList(Row+1,L);
		Row++;
		ui->tableWidget->setCurrentCell(Row,0);
	}
	ShowList();

}

void ExecuteBatchForm::on_pushButtonInsert_clicked()
{
	SetCommandDialog	D(GetLayersBase(),this);
	if(D.exec()==(int)true){
		BatchLine	*L=new BatchLine(&BatchData);
		*L=D.CurrentData;
		BatchData.AppendList(L);
		ShowList();
	}
}

void ExecuteBatchForm::on_pushButtonModify_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	BatchLine *L=BatchData[Row];
	SetCommandDialog	D(GetLayersBase(),this);
	D.Initial(*L);
	if(D.exec()==(int)true){
		*L=D.CurrentData;
		ShowList();
	}
}

void ExecuteBatchForm::on_pushButtonDelete_clicked()
{
	int	Row=ui->tableWidget->currentRow();
	if(Row<0)
		return;
	BatchLine *L=BatchData[Row];
	if(L!=NULL){
		BatchData.RemoveList(L);
		delete	L;
		ShowList();
	}
}

void ExecuteBatchForm::on_pushButtonExecuteAll_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;

	LoadedNewBatch=false;
	ShowList();
	CancelMode=false;
	ui->pushButtonExecuteAll->setEnabled(false);
	ui->pushButtonExecuteOne->setEnabled(false);
	ExecutingLine=0;
	if(HMessage!=NULL)
		HMessage->close();
	for(BatchLine *L=BatchData.GetFirst();L!=NULL;L=L->GetNext(),ExecutingLine++){
		ui->tableWidget->setCurrentCell(ExecutingLine,0);
		bool ExeReturn=L->ExecuteLine(GetLayersBase());
		for(int i=0;i<10;i++){
			QCoreApplication::processEvents();
		}
		if(CancelMode==true){
			break;
		}
		if(LoadedNewBatch==true){
			LoadedNewBatch=false;
			break;
		}
		if(GetLayersBase()->GetOnTerminating()==true){
			ReEntrant=false;
			return;
		}
	}
	ui->pushButtonExecuteAll->setEnabled(true);
	ui->pushButtonExecuteOne->setEnabled(true);
	ExecutingLine=-1;

	ReEntrant=false;
}

void	ExecuteBatchForm::Sleep(int MiliSec)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;

	QElapsedTimer	Tm;
	Tm.start();
	while(!Tm.hasExpired(MiliSec)){
		QCoreApplication::processEvents();

		if(CancelMode==true){
			break;
		}
		if(LoadedNewBatch==true){
			LoadedNewBatch=false;
			break;
		}
		if(GetLayersBase()->GetOnTerminating()==true){
			ReEntrant=false;
			return;
		}
	}

	ReEntrant=false;
}
void	ExecuteBatchForm::ShowMessage(const QString &Message)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	ReEntrant=true;
	if(HMessage==NULL){
		HMessage=new MessageForm(GetLayersBase());
	}
	HMessage->SetMessage(Message);
	HMessage->show();

	MClient.Send(2,0,Message);

	ReEntrant=false;
}
void	ExecuteBatchForm::CloseMessage(void)
{
	if(HMessage!=NULL){
		HMessage->close();
	}
	MClient.Send(3,0,/**/"");
}

void ExecuteBatchForm::SlotExecute(void)
{
	on_pushButtonExecuteAll_clicked();
}

void ExecuteBatchForm::on_pushButtonExecuteOne_clicked()
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true){
		return;
	}
	LoadedNewBatch=false;
	ShowList();
	ReEntrant=true;
	CancelMode=false;
	ui->pushButtonExecuteAll->setEnabled(false);
	ui->pushButtonExecuteOne->setEnabled(false);
	int	Row=ui->tableWidget->currentRow();
	if(Row<0){
		ReEntrant=false;
		return;
	}
	if(Row==0){
		if(HMessage!=NULL)
			HMessage->close();
	}
	BatchLine *L=BatchData[Row];
	if(L!=NULL){
		ExecutingLine=Row;
		bool ExeReturn=L->ExecuteLine(GetLayersBase());
		ExecutingLine=-1;
	}
	ui->pushButtonExecuteAll->setEnabled(true);
	ui->pushButtonExecuteOne->setEnabled(true);
	ReEntrant=false;
}

void ExecuteBatchForm::on_pushButtonStop_clicked()
{
	CancelMode=true;
}

void ExecuteBatchForm::on_pushButtonLoad_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL
												,LangSolver.GetString(ExecuteBatchForm_LS,LID_1)/*"Load batch file"*/ 
												, /**/"" 
												, QString(/**/"Bat file(*.bdt);;All file(*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			BatchData.LoadText(&File);
			ShowList();
		}
	}
}

void ExecuteBatchForm::on_pushButtonSave_clicked()
{
	QString	FileName=QFileDialog::getSaveFileName(NULL
												,LangSolver.GetString(ExecuteBatchForm_LS,LID_2)/*"Save batch file"*/ 
												, /**/"" 
												, QString(/**/"Bat file(*.bdt);;All file(*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			BatchData.SaveText(&File);
		}
	}
}

void ExecuteBatchForm::on_pushButtonAppend_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(NULL
												,LangSolver.GetString(ExecuteBatchForm_LS,LID_3)/*"Append batch file"*/ 
												, /**/"" 
												, QString(/**/"Bat file(*.bdt);;All file(*.*)"));
	if(FileName.isEmpty()==false){
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			BatchData.AppendText(&File);
			ShowList();
		}
	}
}

void	ExecuteBatchForm::SlotReceived()
{
	QBuffer	Buff(&MClient.ReceivedData);
	Buff.open(QIODevice::ReadOnly);
	int32	Cmd;

	if(::Load(&Buff,Cmd)==false)
		return;
	if(Cmd==10){
	}
}
