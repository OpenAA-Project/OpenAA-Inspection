#include "SelectListDialog.h"
#include "ui_SelectListDialog.h"
#include "XDataInLayer.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XGeneralFunc.h"

SelectListDialog::SelectListDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectListDialog)
{
    ui->setupUi(this);

	ui->tableWidgetLight->setColumnWidth(0,44);
	ui->tableWidgetLight->setColumnWidth(1,190);
	ui->tableWidgetLight->setColumnWidth(2,190);

	LightID=-1;
	ShowLightList();
	
	InstallOperationLog(this);
}

SelectListDialog::~SelectListDialog()
{
    delete ui;
}


void	SelectListDialog::ShowLightList(void)
{
	LightListContainer.RemoveAll();
	QString	S=QString(/**/"SELECT LIGHTID,NAME,REMARK FROM LIGHT where MACHINEID=")
		+ QString::number(GetLayersBase()->GetMachineID())
		+ QString(" order by LIGHTID");
	QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
	while(query.next ()==true){
		int		LightID		=query.value(query.record().indexOf(/**/"LIGHTID"	)).toInt();
		QString	LightName	=query.value(query.record().indexOf(/**/"NAME"		)).toString();
		QString	LightRemark	=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
		LightList	*L=new LightList(LightID, LightName ,LightRemark);
		LightListContainer.AppendList(L);
	}

	ui->tableWidgetLight->setRowCount(LightListContainer.GetCount());
	int	Row=0;
	for(LightList *L=LightListContainer.GetFirst();L!=NULL;L=L->GetNext()){
		SetDataToTable(ui->tableWidgetLight ,0,Row,QString::number(L->ID));
		SetDataToTable(ui->tableWidgetLight ,1,Row,L->Name);
		SetDataToTable(ui->tableWidgetLight ,2,Row,L->Remark);
		Row++;
	}
}

void	SelectListDialog::Initial(int lightID)
{
	int	Row=0;
	for(LightList *L=LightListContainer.GetFirst();L!=NULL;L=L->GetNext()){
		if(L->ID==lightID){
			break;
		}
		Row++;
	}
	if(LightListContainer.GetCount()>Row){
		ui->tableWidgetLight->setCurrentCell(Row,0);
		QModelIndex	Index;
		on_tableWidgetLight_doubleClicked(Index);
	}
	LightID=lightID;
}

void SelectListDialog::on_tableWidgetLight_doubleClicked(const QModelIndex &index)
{
	on_tableWidgetLight_clicked(index);
	on_pushButtonSelect_clicked();
}

void SelectListDialog::on_pushButtonSelect_clicked()
{
	if(LightID>=0){
		done(true);
	}
}

void SelectListDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectListDialog::on_tableWidgetLight_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetLight->currentRow();
	if(Row<0)
		return;
	LightList	*L=LightListContainer.GetItem(Row);
	if(L==NULL)
		return;
	LightID=L->ID;
}
