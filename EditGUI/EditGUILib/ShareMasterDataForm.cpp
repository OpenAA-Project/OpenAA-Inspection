#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "ShareMasterDataForm.h"
#include "XShareMasterData.h"
#include "ui_ShareMasterDataForm.h"
#include "XDataInLayer.h"
#include "ShareMasterChangeMultiplyDialog.h"
#include "XGeneralFunc.h"

ShareMasterDataForm::ShareMasterDataForm(LayersBase *Base,QWidget *parent) :
    QWidget(parent),
	ServiceForLayers(Base),
    ui(new Ui::ShareMasterDataForm)
{
    ui->setupUi(this);

	IndexNumber=0;
	int	n=0;
	for(ShareMasterDestination *s=GetLayersBase()->GetDataOfShareMasterContainer()->GetFirst();s!=NULL;s=s->NPList<ShareMasterDestination>::GetNext()){
		ui->comboBoxMachineID->addItem(QString::number(s->DestinationMachineID));
		if(s->DestinationMachineID==GetLayersBase()->GetMachineID()){
			IndexNumber=n;
		}
		n++;
	}
	ui->comboBoxMachineID->setCurrentIndex(IndexNumber);
}

ShareMasterDataForm::~ShareMasterDataForm()
{
    delete ui;
}

void	ShareMasterDataForm::ShowGrid(void)
{
	int	R=ui->comboBoxMachineID->currentIndex();
	if(R<0)
		return;
	ShareMasterDestination	*SMDest=GetLayersBase()->GetDataOfShareMasterContainer()->GetItem(R);
	if(SMDest==NULL)
		return;
	int	RowCount=SMDest->GetCount();
	ui->tableWidget->setRowCount(RowCount);
	int	Row=0;
	for(ShareMasterFromSource *s=SMDest->NPListPackSaveLoad<ShareMasterFromSource>::GetFirst();s!=NULL;s=s->GetNext()){
		::SetDataToTable(ui->tableWidget,0,Row ,QString::number(s->SourceMachineID));
		::SetDataToTable(ui->tableWidget,1,Row ,QString::number(s->Dx));
		::SetDataToTable(ui->tableWidget,2,Row ,QString::number(s->Dy));
		::SetDataToTable(ui->tableWidget,3,Row ,QString::number(s->MultiplyLayer[0]));
		Row++;
	}
}

void	ShareMasterDataForm::GetFromWindow(int machineID)
{
	ShareMasterDestination	*SMDest=GetLayersBase()->GetDataOfShareMasterContainer()->FindDestination(machineID);
	if(SMDest==NULL)
		return;

	int	Row=0;
	for(ShareMasterFromSource *s=SMDest->NPListPackSaveLoad<ShareMasterFromSource>::GetFirst();s!=NULL;s=s->GetNext()){
		QString	IDStr=GetDataToTable(ui->tableWidget,0,Row);
		bool	ok;
		int	id=IDStr.toInt(&ok);
		if(ok==true){
			s->SourceMachineID=id;
		}
		QString	DxStr=GetDataToTable(ui->tableWidget,1,Row);
		int	dx=DxStr.toInt(&ok);
		if(ok==true){
			s->Dx=dx;
		}
		QString	DyStr=GetDataToTable(ui->tableWidget,2,Row);
		int	dy=DyStr.toInt(&ok);
		if(ok==true){
			s->Dy=dy;
		}
		Row++;
	}

}

void ShareMasterDataForm::on_tableWidget_doubleClicked(const QModelIndex &index)
{
	int	R=ui->comboBoxMachineID->currentIndex();
	if(R<0)
		return;
	ShareMasterDestination	*SMDest=GetLayersBase()->GetDataOfShareMasterContainer()->GetItem(R);
	if(SMDest==NULL)
		return;
	if(index.column()==3){
		int	Row=index.row();
		ShareMasterFromSource *s=SMDest->GetItem(Row);
		ShareMasterChangeMultiplyDialog	D(s->MultiplyLayer);
		if(D.exec()==(int)true){
			memcpy(s->MultiplyLayer,D.MultiplyLayer,sizeof(double)*256);
		}
	}
}

void ShareMasterDataForm::on_pushButtonOK_clicked()
{
	QFile	FShareMData(GetLayersBase()->GetUserPath()
						+GetSeparator()+GetParamGlobal()->FileNameOfShareMasterData);
	if(FShareMData.open(QIODevice::ReadOnly)==true){
		GetLayersBase()->GetDataOfShareMasterContainer()->Load(&FShareMData);
	}
}

void ShareMasterDataForm::on_comboBoxMachineID_currentIndexChanged(int index)
{
	GetFromWindow(IndexNumber);
	ShowGrid();
	int	R=ui->comboBoxMachineID->currentIndex();
	if(R<0)
		return;
	IndexNumber=R;
}

void ShareMasterDataForm::on_pushButtonAddDestination_clicked()
{

}

void ShareMasterDataForm::on_pushButtonDelDestination_clicked()
{

}
