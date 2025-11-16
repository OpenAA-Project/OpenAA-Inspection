#include "ButtonSelectDatabaseResource.h"
#include "EditDatabaseListForm.h"
#include "XGeneralFunc.h"
#include "XDatabase.h"

EditDatabaseListForm::EditDatabaseListForm(LayersBase *base, QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ui.tableWidget->setColumnWidth(0,50);
	ui.tableWidget->setColumnWidth(1,50);
	ui.tableWidget->setColumnWidth(2,50);
	ui.tableWidget->setColumnWidth(3,30);
	InstallOperationLog(this);
}

EditDatabaseListForm::~EditDatabaseListForm()
{

}

void	EditDatabaseListForm::ShowList(void)
{
	ui.tableWidget->setRowCount(DatabaseListData.GetNumber());
	int	Row=0;
	for(DatabaseList *c=DatabaseListData.GetFirst();c!=NULL;c=c->GetNext(),Row++){
		SetDataToTable(ui.tableWidget,0,Row ,c->Name);
		SetDataToTable(ui.tableWidget,1,Row ,c->IP);
		SetDataToTable(ui.tableWidget,2,Row ,c->FileName);
		SetDataToTable(ui.tableWidget,3,Row ,QString::number(c->PortNo));
	}
}


void EditDatabaseListForm::on_pushButtonNew_clicked()
{
	DatabaseList *c=new DatabaseList();
	DatabaseListData.AppendList(c);
	ShowList();
}

void EditDatabaseListForm::on_pushButtonMod_clicked()
{
	int	Row=ui.tableWidget->currentRow();
	if(Row<0){
		return;
	}
	DatabaseList *c=DatabaseListData.GetItem(Row);
	c->Name		=ui.lineEditName->text();
	c->IP		=ui.lineEditIP->text();
	c->FileName	=ui.lineEditFileName->text();
	c->PortNo	=ui.spinBoxPortNo->value();
	ShowList();

	QFile	FL(DatabaseListData.GetFileName());
	if(FL.open(QIODevice::WriteOnly)==true){
		DatabaseListData.Save(&FL);
	}

}

void EditDatabaseListForm::on_pushButtonDel_clicked()
{
	int	Row=ui.tableWidget->currentRow();
	if(Row<0){
		return;
	}
	DatabaseList *c=DatabaseListData.GetItem(Row);
	DatabaseListData.RemoveList(c);
	delete	c;

	ShowList();

	QFile	FL(DatabaseListData.GetFileName());
	if(FL.open(QIODevice::WriteOnly)==true){
		DatabaseListData.Save(&FL);
	}
}

void EditDatabaseListForm::on_pushButtonClose_clicked()
{
	done(0);
}