#include "ButtonSelectSmallLotResource.h"
#include "SelectSmallLotForm.h"
#include "ui_SelectSmallLotForm.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"
#include "XGUIFormBase.h"
#include "XDateTime.h"
#include "ButtonSelectSmallLot.h"

SelectSmallLotForm::SelectSmallLotForm(bool ShowMode ,LayersBase *pbase ,QWidget *parent, QWidget *parentGUI) :
    QDialog(parent)
 	,ServiceForLayers(pbase)
	,ui(new Ui::SelectSmallLotForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	//LangCGSolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
	//LangCGSolver.SetUI(this);

	ParentGUI=dynamic_cast<GUIFormBase*>(parentGUI);

	RetCmd=0;
	RetMode=false;
	ui->tableWidgetLot->setColumnWidth ( 0, 120);
	ui->tableWidgetLot->setColumnWidth ( 1, 120);
	ui->tableWidgetLot->setColumnWidth ( 2, 80);
	ui->tableWidgetLot->setColumnWidth ( 3, 120);
	
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(SelectSmallLotForm_LS,LID_11)/*"Select lot information"*/,false);
	QString	SCount=QString(/**/"SELECT count(*) FROM INSPECTIONLOT WHERE (SUBNUMBER=0 or SUBNUMBER=1) and MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode());
	QSqlQuery querySCount(SCount ,GetLayersBase()->GetDatabase());
	int	RowCount=0;
	if(querySCount.next ()==true){
		RowCount=querySCount.value(0).toInt();
		ui->tableWidgetLot->setRowCount(RowCount);
	}	
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(SelectSmallLotForm_LS,LID_12)/*"Select and show lot information"*/,false,RowCount);

	if(ShowMode==true){
		QString	S=QString(/**/"SELECT * FROM INSPECTIONLOT WHERE (SUBNUMBER=0 or SUBNUMBER=1) and MASTERCODE=")
				+QString::number(GetLayersBase()->GetMasterCode())
				+QString(/**/" order by LASTUPDATED DESC");
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		int	L=0;
		if(query.next ()==true){
			do{
				if(L>=((ButtonSelectSmallLot *)ParentGUI)->MaxLines){
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

	ui->pushButtonIncrement	->setVisible(false);
	ui->ButtonSelect		->setVisible(false);

	InstallOperationLog(this);
}

SelectSmallLotForm::~SelectSmallLotForm()
{
    delete ui;
}

void SelectSmallLotForm::closeEvent ( QCloseEvent * event )
{
	QWidget::closeEvent (event);
	deleteLater ();
}

void SelectSmallLotForm::on_ButtonCreate_clicked()
{
	SelectedLotID		=ui->EditID		->text();
	SelectedLotName		=ui->EditName	->text();

	if(SelectedLotID.isEmpty()==false && SelectedLotName.isEmpty()==true){
		SelectedLotName=SelectedLotID;
		ui->EditName->setText(SelectedLotName);
	}

	SelectedRemark		=ui->EditRemark	->text();

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(SelectSmallLotForm_LS,LID_13)/*"Create new lot"*/,false);
	if(ExecuteCreateNew()==false){
		GetLayersBase()->CloseProcessingForm();
		return;
	}
	GetLayersBase()->CloseProcessingForm();

	RetCmd=1;
	RetMode=true;
	close();
}
bool SelectSmallLotForm::ExecuteCreateNew(void)
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

void SelectSmallLotForm::on_ButtonSelect_clicked()
{
	if(SelectLotAction()==true){
		RetCmd=2;
		RetMode=true;
		close();
	}
}

void	SelectSmallLotForm::TxSync(QBuffer &Buff)
{
	ParentGUI->TxSync(Buff.buffer());
}

void SelectSmallLotForm::on_ButtonCancel_clicked()
{
	RetMode=false;
	close();
}

void SelectSmallLotForm::on_tableWidgetLot_clicked(const QModelIndex &index)
{
	SelectLotAction();
}
bool SelectSmallLotForm::SelectLotAction(void)
{
	QModelIndex Index=ui->tableWidgetLot->currentIndex();
	int	R=Index.row();
	if(R<0){
		return false;
	}
	IntClass	*c=LotAutoCounts.GetItem(R);
	if(c==NULL){
		return false;
	}
	int	LotAutoCount=c->GetValue();
	QString	S=QString(/**/"SELECT * FROM INSPECTIONLOT WHERE MASTERCODE=")
			+QString::number(GetLayersBase()->GetMasterCode())
			+QString(/**/" and LOTAUTOCOUNT=")
			+QString::number(LotAutoCount);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next ()==true){
		SelectedLotAutoCount=query.value(query.record().indexOf(/**/"LOTAUTOCOUNT"	)).toInt();
		SelectedLotID		=query.value(query.record().indexOf(/**/"IDName"		)).toString();
		SelectedLotName		=query.value(query.record().indexOf(/**/"LOTNAME"		)).toString();
		SelectedLastUpdated	=query.value(query.record().indexOf(/**/"LASTUPDATED"	)).toDateTime();
		SelectedRemark		=query.value(query.record().indexOf(/**/"REMARK"		)).toString();
		SelectedIDNumber	=query.value(query.record().indexOf(/**/"IDNUMBER"		)).toInt();
		ui->EditID			->setText(SelectedLotID);
		ui->EditName		->setText(SelectedLotName);
		ui->EditRemark		->setText(SelectedRemark);

		return true;
	}
	return false;
}
bool	SelectSmallLotForm::RxSync(QByteArray &f)
{
	QBuffer	Buff(&f);
	Buff.open(QIODevice::ReadWrite);
	bool	ret=RxSync(Buff);
	return ret;
}

bool	SelectSmallLotForm::RxSync(QIODevice &Buff)
{
	int	Cmd;
	::Load(&Buff,Cmd);
	if(Cmd==1){
		::Load(&Buff,SelectedLotID);
		::Load(&Buff,SelectedLotName);
		::Load(&Buff,SelectedRemark);
		if(ExecuteCreateNew()==false){
			return false;
		}
		return true;
	}
	else if(Cmd==2){
		::Load(&Buff,SelectedLotID);
		::Load(&Buff,SelectedLotName);
		::Load(&Buff,SelectedRemark);
		try{
			QString	S=QString(/**/"SELECT * FROM INSPECTIONLOT where (SUBNUMBER=0 or SUBNUMBER=1) and MASTERCODE=")
					+QString::number(GetLayersBase()->GetMasterCode())
					+QString(/**/" and IDNAME=\'")
					+SelectedLotID
					+QString(/**/"\'");
			QSqlQuery query(S ,GetLayersBase()->GetDatabase());
			if(query.next ()==true){
				SelectedLotAutoCount=query.value(query.record().indexOf(/**/"LOTAUTOCOUNT"	)).toInt();
				SelectedLotID		=query.value(query.record().indexOf(/**/"IDName"		)).toString();
				SelectedLotName		=query.value(query.record().indexOf(/**/"LOTNAME"		)).toString();
				SelectedLastUpdated	=query.value(query.record().indexOf(/**/"LASTUPDATED"	)).toDateTime();
				SelectedRemark		=query.value(query.record().indexOf(/**/"REMARK"		)).toString();
				SelectedIDNumber	=query.value(query.record().indexOf(/**/"IDNUMBER"		)).toInt();
				return true;
			}
		}
		catch(...)
		{
			return false;
		}
	}
	return false;
}

void SelectSmallLotForm::on_pushButtonIncrement_clicked()
{

}
