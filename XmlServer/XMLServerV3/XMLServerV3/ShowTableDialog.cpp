#include "ShowTableDialog.h"
#include "ui_ShowTableDialog.h"
#include "XCommandServer.h"
#include "XMLServerV3.h"
#include "XMLConstruction.h"

ShowTableDialog::ShowTableDialog(XMLElementRoot *s ,XMLServerComm *ServerCommDataParent ,QWidget *parent) :
    QDialog(parent)
	,ServerCommData(ServerCommDataParent)
	,SRoot(s)
    ,ui(new Ui::ShowTableDialog)
{
    ui->setupUi(this);

	ui->lineEditTableName	->setText(SRoot->GetTableName());

	ui->listWidgetSharedClients	->clear();
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*SData=ServerCommData->GetSClient(i);
		if(SData!=NULL){
			if(SData->IsDealingTable(s->GetTableName())==true){
				ui->listWidgetSharedClients	->addItem(SData->GetPeerIPAddress());
			}
		}
	}
}

ShowTableDialog::~ShowTableDialog()
{
    delete ui;
}

void ShowTableDialog::on_pushButtonSave_clicked()
{
	SRoot->TableReadLock();
	SRoot->SaveFile();
	SRoot->TableUnLock();
}

void ShowTableDialog::on_pushButtonRemove_clicked()
{
	for(int i=0;i<MaxCommLeafNumb;i++){
		SClient	*SData=ServerCommData->GetSClient(i);
		if(SData!=NULL){
			if(SData->IsDealingTable(SRoot->GetTableName())==true){
				SData->RemoveClientOperation(SRoot->GetTableName());
			}
		}
	}
	ServerCommData->SaveAndRemove(SRoot->GetTableName());
}

void ShowTableDialog::on_pushButtonClose_clicked()
{
	close();
}
