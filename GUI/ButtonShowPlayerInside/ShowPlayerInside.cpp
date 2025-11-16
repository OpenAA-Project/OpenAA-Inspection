#include "ButtonShowPlayerInsideResource.h"
#include "ShowPlayerInside.h"
#include "ui_ShowPlayerInside.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XResult.h"

ShowPlayerInside::ShowPlayerInside(LayersBase *base ,QWidget *parent) :
    QWidget(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::ShowPlayerInside)
{
    ui->setupUi(this);

	connect(&Timer,SIGNAL(timeout()),this,SLOT(TimeOut()));
	Timer.setInterval(200);
	Timer.setSingleShot(false);

	ui->tableWidgetReceivedFlag->setColumnCount(GetPageNumb()+1);
	QStringList	ReceivedFlagLabel;
	ReceivedFlagLabel.append(/**/"Executer");
	ui->tableWidgetReceivedFlag->setColumnWidth(0,32);
	for(int page=0;page<GetPageNumb();page++){
		ui->tableWidgetReceivedFlag->setColumnWidth(page+1,32);
		ReceivedFlagLabel.append(QString(/**/"Pg")+QString::number(page));
	}
	ui->tableWidgetReceivedFlag->setRowCount(GetParamGlobal()->NGCacheNumb);
}

ShowPlayerInside::~ShowPlayerInside()
{
    delete ui;
}

void	ShowPlayerInside::TimeOut()
{
	SetDataToTable(ui->tableWidgetLayersBase,0,0,QString::number(GetLayersBase()->GetCurrentStrategicNumber()));
	SetDataToTable(ui->tableWidgetLayersBase,0,1,QString::number(GetLayersBase()->GetCurrentStrategicNumberForSeq()));
	SetDataToTable(ui->tableWidgetLayersBase,0,2,QString::number(GetLayersBase()->GetCurrentStrategicNumberForCalc()));
	SetDataToTable(ui->tableWidgetLayersBase,0,3,QString::number(GetLayersBase()->GetCurrentInspectIDForDisplay()));
	SetDataToTable(ui->tableWidgetLayersBase,0,4,QString::number(GetLayersBase()->GetCurrentInspectIDForExecute()));

	SetDataToTable(ui->tableWidgetLayersBase,0,5,QString::number(GetLayersBase()->GetCurrentCalcPoint()));
	SetDataToTable(ui->tableWidgetLayersBase,0,6,QString::number(GetLayersBase()->GetCurrentDrawPoint()));
	SetDataToTable(ui->tableWidgetLayersBase,0,7,QString::number(GetLayersBase()->GetLastCurrentCalcPoint()));

	SetDataToTable(ui->tableWidgetLayersBase,0,8,QString::number(GetLayersBase()->GetCurrentPhase()));
	SetDataToTable(ui->tableWidgetLayersBase,0,9,QString::number(GetLayersBase()->GetCurrentInspectIDForExecute()));
	SetDataToTable(ui->tableWidgetLayersBase,0,9,QString::number(GetLayersBase()->GetCurrentInspectIDForDisplay()));

	SetDataToTable(ui->tableWidgetLayersBase,0,9,QString::number(GetLayersBase()->GetResultWrittenID()));
	SetDataToTable(ui->tableWidgetLayersBase,0,9,QString::number(GetLayersBase()->GetCurrentScanPhaseNumber()));

	IntList	CurrentStrategicQueue=GetLayersBase()->GetCurrentStrategicQueue();
	if(ui->listWidgetCurrentStrategicQueue->count()<CurrentStrategicQueue.GetCount()){
		for(int	n=ui->listWidgetCurrentStrategicQueue->count();n<CurrentStrategicQueue.GetCount();n++){
			ui->listWidgetCurrentStrategicQueue->addItem(/**/"");
		}
	}
	else if(ui->listWidgetCurrentStrategicQueue->count()>CurrentStrategicQueue.GetCount()){
		int	n=ui->listWidgetCurrentStrategicQueue->count();
		while(n>CurrentStrategicQueue.GetCount()){
			QListWidgetItem *a=ui->listWidgetCurrentStrategicQueue->item(n-1);
			ui->listWidgetCurrentStrategicQueue->removeItemWidget(a);
			n--;
		}
	}
	int	n=0;
	for(IntClass *c=CurrentStrategicQueue.GetFirst();c!=NULL;c=c->GetNext()){
		QListWidgetItem *a=ui->listWidgetCurrentStrategicQueue->item(n);
		a->setText(QString::number(c->GetValue()));
	}
	
	for(int e=0;e<GetParamGlobal()->NGCacheNumb;e++){
		DataInExecuter	*E=GetLayersBase()->GetExecuter(e);
		ReceivedResultCountsParam	*Ep=E->GetReceivedResultCounts();
		::SetDataToTable(ui->tableWidgetReceivedFlag ,0,e,E->GetExecutingStateString());
		for(int page=0;page<GetPageNumb();page++){
			::SetDataToTable(ui->tableWidgetReceivedFlag ,page+1,e,QString::number(Ep[page].Result));
		}
	}
}