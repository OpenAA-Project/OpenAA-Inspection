#include "PanelMaxStockForm.h"
#include "ui_PanelMaxStockForm.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"

#include "XResult.h"
#include "XResultDLLManager.h"
#include <QMessageBox>
#include "XEntryPoint.h"

PanelMaxStockForm::StockLine::StockLine(PanelMaxStockForm *parent,int row)
{
	setParent(parent);

	Row=row;
	StockName	.setParent(this);
	StockValue	.setParent(this);

	move(4,30*row);
	resize(169,30);
	StockName.setFrameShape ( QFrame::Panel );
	StockName.setFrameShadow ( QFrame::Sunken );
	StockName.move(0,0);
	StockName.resize(100,28);
	StockName.setText(parent->StockStringList[row]);
	StockName.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	StockValue.move(104,0);
	StockValue.resize(64,28);
}

PanelMaxStockForm::PanelMaxStockForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base ,parent),
    ui(new Ui::PanelMaxStockForm)
{
    ui->setupUi(this);

	CurrentMaxStock	=NULL;
	iRegMaxStock	=NULL;
	TopRegNumber	=460;
	StockLineData	=NULL;
	StockStringListCount	=0;
}

PanelMaxStockForm::~PanelMaxStockForm()
{
	int	N=StockStringList.count();
	for(int row=0;row<N;row++){
		delete	iRegMaxStock[row];
		delete	StockLineData[row];
	}
	delete	[]iRegMaxStock;
	delete	[]StockLineData;
    delete ui;
}

void	PanelMaxStockForm::Prepare(void)
{
	StockStringListCount=StockStringList.count();
	if(StockStringListCount>0){
		SeqControlParam	*Param=NULL;
		if(GetLayersBase()!=NULL 
		&& GetLayersBase()->GetEntryPoint()!=NULL 
		&& GetLayersBase()->GetEntryPoint()->GetExecuteInspect()!=NULL
		&& GetLayersBase()->GetShadowLevel()==0){
			Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		}
		iRegMaxStock=new SignalOperandInt *[StockStringListCount];
		StockLineData	=new StockLine*[StockStringListCount];

		for(int row=0;row<StockStringListCount;row++){
			if(Param!=NULL){
				iRegMaxStock[row]	=new SignalOperandInt(this,TopRegNumber+row,QString(/**/"PanelMaxStock:iRegMaxStock")+QString::number(row));
				SeqErrorInfo	Error;
				if(Param->SetSpecialOperand(iRegMaxStock[row],&Error)==false){
					iRegMaxStock[row]->ShowErrorMessage(Error);
				}
				connect(iRegMaxStock[row]	,SIGNAL(changed())	,this	,SLOT(OperandChanged())	,Qt::QueuedConnection);
			}
			else{
				iRegMaxStock[row]=NULL;
			}
			StockLineData[row]=new StockLine(this,row);
			StockLineData[row]->show();
		}
		int	YLen=30*StockStringListCount;
		if(YLen<ui->pushButtonSet->height())
			YLen=ui->pushButtonSet->height();
		resize(170+ui->pushButtonSet->width(),YLen);
		ui->pushButtonSet->move(170,height()/2-ui->pushButtonSet->height()/2);

	}
}
void	PanelMaxStockForm::BuildForShow(void)
{
	QVariant	data;
	if(GetLayersBase()->LoadMasterFieldData(/**/"MAXSTOCK", data)==true){
		QByteArray	A=data.toByteArray();
		IntList	IList;
		QBuffer	Buff(&A);
		Buff.open(QIODevice::ReadOnly);
		IList.Load(&Buff);

		for(int i=0;i<StockStringListCount;i++){
			int	d=IList[i];
			if(iRegMaxStock!=NULL && iRegMaxStock[i]!=NULL){
				iRegMaxStock[i]->Set(d);
			}
			StockLineData[i]->StockValue.setValue(d);
		}
	}
}
void	PanelMaxStockForm::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CreateNewMasterSpecifiedBroadcaster	*C=dynamic_cast<CreateNewMasterSpecifiedBroadcaster *>(v);
	if(C!=NULL){
		on_pushButtonSet_clicked();
	}
}
void PanelMaxStockForm::on_pushButtonSet_clicked()
{
	IntList	IList;
	for(int i=0;i<StockStringListCount;i++){
		int	d=StockLineData[i]->StockValue.value();
		IList.Add(d);
		if(iRegMaxStock!=NULL && iRegMaxStock[i]!=NULL){
			iRegMaxStock[i]->Set(d);
		}
	}

	QBuffer	Buff;
	Buff.open(QIODevice::WriteOnly);
	IList.Save(&Buff);
	QVariant	data(Buff.buffer());
	if(GetLayersBase()->AddMasterFieldData(/**/"MAXSTOCK", data)==false){
		QMessageBox::warning ( NULL, "Error"
									, "Can't set MAXSTOCK in MasterData"
									, QMessageBox::Ok);
	}

	GetParamGUI()->SaveDefault(GetLayersBase()->GetUserPath());
}
void	PanelMaxStockForm::OperandChanged()
{
	for(int i=0;i<StockStringListCount;i++){
		if(iRegMaxStock!=NULL && iRegMaxStock[i]!=NULL){
			int	d=iRegMaxStock[i]->Get();
			StockLineData[i]->StockValue.setValue(d);
		}
	}
}