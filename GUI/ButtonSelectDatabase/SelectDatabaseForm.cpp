#include "ButtonSelectDatabaseResource.h"
#include "SelectDatabaseForm.h"
#include "XGeneralFunc.h"
#include "EditDatabaseListForm.h"
#include "XDatabase.h"
#include "XDatabaseLoader.h"
#include "XDataInLayer.h"


SelectDatabaseForm::SelectDatabaseForm(LayersBase *Base,QWidget *parent)
	: QDialog(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);

	LoadData();
	ShowList();
	InstallOperationLog(this);
}

SelectDatabaseForm::~SelectDatabaseForm()
{
}

void	SelectDatabaseForm::LoadData(void)
{
	QFile	FL(DatabaseListData.GetFileName());

	if(FL.open(QIODevice::ReadOnly)==true){
		DatabaseListData.Load(&FL);
	}
}

void	SelectDatabaseForm::ShowList(void)
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


void SelectDatabaseForm::on_tableWidget_doubleClicked(QModelIndex)
{
	on_pushButtonOk_clicked();
}

void SelectDatabaseForm::on_pushButtonOk_clicked()
{
	int	Row=ui.tableWidget->currentRow();
	if(Row<0){
		return;
	}
	DatabaseList *L=DatabaseListData.GetItem(Row);
	LocalDatabaseBasicClass	KDatabase(GetLayersBase()->GetDatabaseLoader()
		,L->FileName
		,L->IP
		,L->PortNo
		,/**/"",0);
	if(GetLayersBase()->CloseDatabase()==false){
		QMessageBox Q( LangSolver.GetString(SelectDatabaseForm_LS,LID_2)/*"Error"*/
					, LangSolver.GetString(SelectDatabaseForm_LS,LID_3)/*"Could not close database"*/
					, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return;
	}
	if(GetLayersBase()->OpenDatabase(KDatabase)==false){
		QMessageBox Q( LangSolver.GetString(SelectDatabaseForm_LS,LID_4)/*"Error"*/
					, LangSolver.GetString(SelectDatabaseForm_LS,LID_5)/*"Could not open database"*/
					, QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		Q.exec();
		return;
	}
	GetLayersBase()->LoadLevelFolderContainerFromDB();
	
	done(true);
}

void SelectDatabaseForm::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectDatabaseForm::on_pushButtonEdit_clicked()
{
	EditDatabaseListForm	D(GetLayersBase(),this);
	D.DatabaseListData=DatabaseListData;
	D.ShowList();
	D.exec();
	LoadData();
	ShowList();
}