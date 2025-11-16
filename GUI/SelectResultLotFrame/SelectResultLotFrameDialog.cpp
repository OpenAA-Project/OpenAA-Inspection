#include "SelectResultLotFrameDialog.h"
#include "ButtonToSelectResultLotFrameForm.h"
#include "ui_SelectResultLotFrameDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"
#include "XGUIFormBase.h"
#include "XDateTime.h"
#include "XSyncGUI.h"
#include <QMessageBox>

SelectResultLotFrameDialog::SelectResultLotFrameDialog(bool ShowMode ,LayersBase *Base ,QWidget *parent, QWidget *parentGUI) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::SelectResultLotFrameDialog)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	ParentGUI=dynamic_cast<GUIFormBase*>(parentGUI);

	RetMode=false;
	ui->tableWidgetLot->setColumnWidth ( 0, 120);
	ui->tableWidgetLot->setColumnWidth ( 1, 120);
	ui->tableWidgetLot->setColumnWidth ( 2, 80);
	ui->tableWidgetLot->setColumnWidth ( 3, 120);
	
	GetLayersBase()->ShowProcessingForm("Select lot information",false);
	QString	SCount=QString(/**/"SELECT count(*) FROM INSPECTIONLOT WHERE (SUBNUMBER=0 or SUBNUMBER=1) and MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode());
	QSqlQuery querySCount(SCount ,GetLayersBase()->GetDatabase());
	int	RowCount=0;
	if(querySCount.next ()==true){
		RowCount=querySCount.value(0).toInt();
		ui->tableWidgetLot->setRowCount(RowCount);
	}	
	GetLayersBase()->ShowProcessingForm("Select and show lot information",false,RowCount);

	if(ShowMode==true){
		QString	S=QString(/**/"SELECT * FROM INSPECTIONLOT WHERE (SUBNUMBER=0 or SUBNUMBER=1) and MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode())
				+QString(/**/" order by LASTUPDATED DESC");
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		int	L=0;
		if(query.next ()==true){
			do{
				if(L>=((ButtonToSelectResultLotFrameForm *)ParentGUI)->MaxLines){
					break;
				}
				int			LotAutoCount=query.value(query.record().indexOf(/**/"LOTAUTOCOUNT"	)).toInt();
				QString		IDName		=query.value(query.record().indexOf(/**/"IDNAME"		)).toString();
				QString		LotName		=query.value(query.record().indexOf(/**/"LOTNAME"		)).toString();
				XDateTime	LastUpdated	=query.value(query.record().indexOf(/**/"LASTUPDATED"	)).toDateTime();
				QString		Remark		=query.value(query.record().indexOf(/**/"REMARK"		)).toString();
				LotAutoCounts.Add(LotAutoCount);
		        SetDataToTable(ui->tableWidgetLot,0,L,IDName);
		        SetDataToTable(ui->tableWidgetLot,1,L,LotName);
				SetDataToTable(ui->tableWidgetLot,2,L,LastUpdated.toString(/**/"yy/MM/dd hh:mm:ss"));
				SetDataToTable(ui->tableWidgetLot,3,L,Remark);
				L++;
				GetLayersBase()->StepProcessing(-1);
			}while(query.next ()==true);
		}
	}
	GetLayersBase()->CloseProcessingForm();

	ui->tableWidgetGroup->setColumnWidth ( 0, 150);	
	ui->tableWidgetGroup->setColumnWidth ( 1, 400);	
	ui->tableWidgetGroup->setRowCount(((ButtonToSelectResultLotFrameForm *)ParentGUI)->GroupList.GetCount());
	int	Row=0;
	for(IntClass *c=((ButtonToSelectResultLotFrameForm *)ParentGUI)->GroupList.GetFirst();c!=NULL;c=c->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetGroup,0,Row,QString::number(c->GetValue()));
	}
	InstallOperationLog(this);
}

SelectResultLotFrameDialog::~SelectResultLotFrameDialog()
{
    delete ui;
}

void SelectResultLotFrameDialog::on_ButtonCreate_clicked()
{
	SelectedLotID		=ui->EditID		->text();
	SelectedLotName		=ui->EditName	->text();

	if(SelectedLotID.isEmpty()==false && SelectedLotName.isEmpty()==true){
		SelectedLotName=SelectedLotID;
		ui->EditName->setText(SelectedLotName);
	}

	SelectedRemark		=ui->EditRemark	->text();

	GetLayersBase()->ShowProcessingForm("Create new lot",false);
	if(ExecuteCreateNew()==false){
		GetLayersBase()->CloseProcessingForm();
		return;
	}
	GetLayersBase()->CloseProcessingForm();

	if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
		if(QMessageBox::question(NULL
									,"Synchronized"
									,"Synchronize other ?"
									,QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
			QBuffer	Buff;
			Buff.open(QIODevice::ReadWrite);
			int	Cmd=1;
			::Save(&Buff,Cmd);
			::Save(&Buff,SelectedLotID);
			::Save(&Buff,SelectedLotName);
			::Save(&Buff,SelectedRemark);

			if(ParentGUI!=NULL){
				TxSync(Buff);
			}
		}
	}

	RetMode=true;
	close();
}
bool SelectResultLotFrameDialog::ExecuteCreateNew(void)
{
	QString	SGetMax=QString(/**/"SELECT MAX(LOTAUTOCOUNT) FROM INSPECTIONLOT WHERE MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode());
	QSqlQuery querySGetMax(SGetMax,GetLayersBase()->GetDatabase());
	int	MaxAutoCount=0;
	if(querySGetMax.next ()==true){
		MaxAutoCount=querySGetMax.value(0).toInt();
	}
	MaxAutoCount++;
	SelectedLotAutoCount=MaxAutoCount;
	SelectedLastUpdated	=XDateTime::currentDateTime();
	if(SelectedLotID.isEmpty()==true){
		SelectedLotID=SelectedLastUpdated.toString(/**/"yyyy-MM-dd--hh-mm-ss");
	}
	if(SelectedLotName.isEmpty()==true){
		SelectedLotName=SelectedLotID;
	}

	QString	IDGetMax=QString(/**/"SELECT MAX(IDNUMBER) FROM INSPECTIONLOT WHERE MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode());
	QSqlQuery queryIDGetMax(IDGetMax,GetLayersBase()->GetDatabase());
	int	MaxIDNumber=0;
	if(queryIDGetMax.next ()==true){
		MaxIDNumber=queryIDGetMax.value(0).toInt();
	}
	SelectedIDNumber	=MaxIDNumber+1;
	try{
		QSqlQuery queryInsrt(GetLayersBase()->GetDatabase());
		queryInsrt.prepare(QString(/**/"INSERT INTO INSPECTIONLOT(LOTAUTOCOUNT,MASTERCODE,LASTUPDATED,IDNAME,LOTNAME,REMARK,IDNUMBER,SUBNUMBER) ")
			+QString(/**/"VALUES(:LOTAUTOCOUNT,:MASTERCODE,:LASTUPDATED,:IDNAME,:LOTNAME,:REMARK,:IDNUMBER,:SUBNUMBER);"));
		queryInsrt.bindValue(0	, SelectedLotAutoCount);
		queryInsrt.bindValue(1	, GetLayersBase()->GetMasterCode());
		queryInsrt.bindValue(2	, SelectedLastUpdated.GetQDateTime());
		queryInsrt.bindValue(3	, SelectedLotID);
		queryInsrt.bindValue(4	, SelectedLotName);
		queryInsrt.bindValue(5	, SelectedRemark);
		queryInsrt.bindValue(6	, SelectedIDNumber);
		queryInsrt.bindValue(7	, (int)1);

		if(queryInsrt.exec()==false){
			return false;
		}
	}
	catch(...){
		return false;
	}
	return true;
}
void SelectResultLotFrameDialog::on_ButtonCancel_clicked()
{

}

bool	SelectResultLotFrameDialog::RxSync(QByteArray &f)
{
	return true;
}
bool	SelectResultLotFrameDialog::RxSync(QIODevice &Buff)
{
	return true;
}

void	SelectResultLotFrameDialog::TxSync(QBuffer &f)
{
}
