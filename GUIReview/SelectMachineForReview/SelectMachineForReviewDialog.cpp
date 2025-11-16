#include "SelectMachineForReviewResource.h"
#include "SelectMachineForReviewDialog.h"
#include "ui_SelectMachineForReviewDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XDatabaseLoader.h"
#include "XOutlineOffset.h"
#include "XFileRegistry.h"

#include "../XGUIReviewGlobal.h"
#include "XReviewCommon.h"
#include "ReviewStructurePacket.h"
#include "XReviewStructure.h"
#include "XReviewCommonPacket.h"

SelectMachineForReviewDialog::SelectMachineForReviewDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectMachineForReviewDialog)
{
    ui->setupUi(this);

	ui->tableWidgetFrontSide	->setColumnWidth (0, 30);
	ui->tableWidgetFrontSide	->setColumnWidth (1, 80);	
	ui->tableWidgetBackSide		->setColumnWidth (0, 30);
	ui->tableWidgetBackSide		->setColumnWidth (1, 80);	

	MFieldNames << tr(/**/"MACHINEID") << tr(/**/"NAME");
	ui->tableWidgetFrontSide->setColumnCount(MFieldNames.count());
	ui->tableWidgetFrontSide->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->tableWidgetFrontSide->setHorizontalHeaderLabels(MFieldNames);
	ui->tableWidgetFrontSide->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

	//MACHINEテーブル一覧の表示
	QSqlQuery FQuery(/**/"SELECT MACHINEID,NAME from MACHINE order by MACHINEID" ,GetLayersBase()->GetDatabase());
	int Row=0;
	int NumRowsAffected;
	while(FQuery.next()){
		if(Row==0){
			NumRowsAffected=FQuery.numRowsAffected();
			ui->tableWidgetFrontSide->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=FQuery.numRowsAffected();
			ui->tableWidgetFrontSide->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui->tableWidgetFrontSide->columnCount();Col++){
			ui->tableWidgetFrontSide->model()->setData(ui->tableWidgetFrontSide->model()->index(Row,Col),FQuery.value(FQuery.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}

	ui->tableWidgetBackSide->setColumnCount(MFieldNames.count());
	ui->tableWidgetBackSide->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->tableWidgetBackSide->setHorizontalHeaderLabels(MFieldNames);
	ui->tableWidgetBackSide->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);

	//MACHINEテーブル一覧の表示
	QSqlQuery BQuery(/**/"SELECT MACHINEID,NAME from MACHINE order by MACHINEID" ,GetLayersBase()->GetDatabase());
	Row=0;
	while(BQuery.next()){
		if(Row==0){
			NumRowsAffected=BQuery.numRowsAffected();
			ui->tableWidgetBackSide->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=BQuery.numRowsAffected();
			ui->tableWidgetBackSide->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui->tableWidgetBackSide->columnCount();Col++){
			ui->tableWidgetBackSide->model()->setData(ui->tableWidgetBackSide->model()->index(Row,Col),BQuery.value(BQuery.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}

	ReviewPIBase *RBase = GetReviewAlgorithm();
	CmdReqMasterDataInfo reqMInfo(GetLayersBase());
	RBase->TransmitDirectly(&reqMInfo);
	
	// 表側
	int MachineID = reqMInfo.FrontMasterDataInfo.MachineID;//m_FrontMachineID;

	// 裏側
	int rMachineID = reqMInfo.BackMasterDataInfo.MachineID;//m_BackMachineID;
}

SelectMachineForReviewDialog::~SelectMachineForReviewDialog()
{
    delete ui;
}

void SelectMachineForReviewDialog::on_tableWidgetFrontSide_clicked(const QModelIndex &index)
{

}

void SelectMachineForReviewDialog::on_pushButtonOK_clicked()
{
	int32 MachineIDFront=ui->tableWidgetFrontSide->item(ui->tableWidgetFrontSide->currentIndex().row(),MFieldNames.indexOf(/**/"MACHINEID"))->text().toInt();
	int32 MachineIDBack	=ui->tableWidgetBackSide ->item(ui->tableWidgetBackSide ->currentIndex().row(),MFieldNames.indexOf(/**/"MACHINEID"))->text().toInt();
	bool	Ret=false;

	ReviewPIBase *RBase = GetReviewAlgorithm();

	CmdSetMachineID cMachineID(GetLayersBase());
	cMachineID.MachineIDFront	=MachineIDFront;
	cMachineID.MachineIDBack	=MachineIDBack;
	RBase->TransmitDirectly(&cMachineID);

	accept();
}

void SelectMachineForReviewDialog::on_pushButtonCancel_clicked()
{
	reject();
}
