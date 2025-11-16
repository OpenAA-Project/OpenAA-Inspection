#include "EditGlobalOnMasterResource.h"
#include "EditParamDialog.h"
#include "ui_EditParamDialog.h"
#include "XParamGlobal.h"
#include "XDatabase.h"
#include "SelectMachineDialog.h"
#include "XDataInLayer.h"
#include <QSqlQuery>
#include <QString>
#include <QBuffer>
#include <QImage>
#include "SelectWorkerForm.h"
#include "XGeneralDialog.h"
#include "FormScanStrategy.h"
#include "FormCommSetting.h"

EditParamDialog::EditParamDialog(int _MasterCode ,LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
	,MasterParam(base)
	,MasterCommParam(base)
    ,ui(new Ui::EditParamDialog)
{
    ui->setupUi(this);
	MasterCode=_MasterCode;

	WTab=NULL;
	WStrategy=NULL;
	WCommSetting=NULL;

	SlaveParam=NULL;
	SlaveCommParam=NULL;
	LPageNumb=0;
	LastRow	=-1;

	QString	S=QString(/**/"SELECT MASTERNAME,MACHINEID,WORKERID,PAGENUMB from MASTERDATA where MASTERCODE=")+QString::number(MasterCode);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next()==true){
		ui->lineEditMasterCode->setText(QString::number(MasterCode));
		ui->lineEditMasterName->setText(query.value(query.record().indexOf(/**/"MACHINEID"	)).toString());
		ui->spinBoxMachineCode->setValue(query.value(query.record().indexOf(/**/"MACHINEID"	)).toInt());
		ui->spinBoxWorkerID	  ->setValue(query.value(query.record().indexOf(/**/"WORKERID"	)).toInt());
		LPageNumb=query.value(query.record().indexOf(/**/"PAGENUMB"	)).toInt();
		ui->listWidgetPage->clear();
		ui->listWidgetPage->addItem(/**/"MasterData");
		for(int page=0;page<LPageNumb;page++){
			ui->listWidgetPage->addItem(QString(/**/"Page ")+QString::number(page));
		}
	}
	LoadDataFromMaster(MasterCode);
}

EditParamDialog::~EditParamDialog()
{
	if(SlaveParam!=NULL){
		for(int i=0;i<LPageNumb;i++){
			if(SlaveParam[i]!=NULL){
				delete	SlaveParam[i];
			}
		}
		delete	[]SlaveParam;
	}
	if(SlaveCommParam!=NULL){
		for(int i=0;i<LPageNumb;i++){
			if(SlaveCommParam[i]!=NULL){
				delete	SlaveCommParam[i];
			}
		}
		delete	[]SlaveCommParam;
	}

    delete ui;
}

bool EditParamDialog::LoadDataFromMaster(int masterCode)
{
	QString	S=QString(/**/"SELECT SETTINGDATA,PAGENUMB from MASTERDATA where MASTERCODE=")+QString::number(masterCode);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next()==true){
		QByteArray	Sd=query.value(query.record().indexOf(/**/"SETTINGDATA")).toByteArray();
		QBuffer	SettingBuff;
		SettingBuff.setData(Sd);
	
		SettingBuff.open(QIODevice::ReadOnly);
		if(MasterParam.LoadParam(&SettingBuff)==false){
			QMessageBox::critical(NULL
						, /**/"Error"
						, /**/"Could not load MasterParam"
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			//return false;
		}
		if(MasterCommParam.LoadParam(&SettingBuff)==false){
			QMessageBox::critical(NULL
						, /**/"Error"
						, /**/"Could not load MasterCommParam"
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			//return false;
		}

		SlaveParam	=new ParamGlobal*[LPageNumb];
		for(int i=0;i<LPageNumb;i++){
			SlaveParam[i]=new ParamGlobal(GetLayersBase());
		}
		SlaveCommParam	=new ParamComm*[LPageNumb];
		for(int i=0;i<LPageNumb;i++){
			SlaveCommParam[i]=new ParamComm(GetLayersBase());
		}

		for(int page=0;page<LPageNumb;page++){
			if(SlaveParam[page]==NULL){
				SlaveParam[page]=new ParamGlobal(GetLayersBase());
			}
			QString	LS=QString(/**/"SELECT SETTINGDATA from MASTERPAGE where MASTERCODE=")+QString::number(masterCode)
						+QString(/**/"and PAGECODE=")+QString::number(page);
			QSqlQuery LQuery(LS ,GetLayersBase()->GetDatabase());
			if(LQuery.next()==true){
				QByteArray	LSd=LQuery.value(query.record().indexOf(/**/"SETTINGDATA")).toByteArray();
				QBuffer	LSettingBuff;
				LSettingBuff.setData(LSd);

				LSettingBuff.open(QIODevice::ReadOnly);
				if(SlaveParam[page]->LoadParam(&LSettingBuff)==false){
					QMessageBox::critical(NULL
						, /**/"Error"
						, /**/"Could not load SlaveParam"
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
					return false;
				}
				if(SlaveCommParam[page]->LoadParam(&LSettingBuff)==false){
					QMessageBox::critical(NULL
						, /**/"Error"
						, /**/"Could not load SlaveCommParam"
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

void EditParamDialog::on_pushButtonSelectMachine_clicked()
{
	IntList MachineList;
	QSqlQuery query(/**/"SELECT MACHINEID from MACHINE order by MACHINEID" ,GetLayersBase()->GetDatabase());
	while(query.next()){
		MachineList.Add(query.value(query.record().indexOf(/**/"MACHINEID"	)).toInt());
	}

	SelectMachineDialog	D(GetLayersBase(),MachineList,NULL);
	if(D.exec()==(int)true){
		ui->spinBoxMachineCode->setValue(D.SelectedMachineID);
	}
}

void EditParamDialog::on_pushButtonSelectWorker_clicked()
{
	SelectWorkerForm	*D=new SelectWorkerForm(GetLayersBase(),NULL);
	D->SelectWorkerID	=ui->spinBoxWorkerID->value();
	GeneralDialog	G(GetLayersBase(),D,NULL);
	G.exec();
	ui->spinBoxWorkerID->setValue(D->SelectWorkerID);
}

void EditParamDialog::on_listWidgetPage_clicked(const QModelIndex &index)
{
	if(LastRow==0){
		if(WTab!=NULL){
			WTab->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			WStrategy->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			WStrategy->close();
			WStrategy->deleteLater();
		}
		WStrategy=NULL;
		MasterParam.CopyStrategyFrom(*GetLayersBase()->GetParamGlobal());
	}
	else if(LastRow>0){
		if(WTab!=NULL){
			WTab->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			WStrategy->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			WStrategy->close();
			WStrategy->deleteLater();
		}
		WStrategy=NULL;
		SlaveParam[LastRow-1]->CopyStrategyFrom(*GetLayersBase()->GetParamGlobal());
	}

	int	Row=ui->listWidgetPage->currentRow();
	if(Row==0){
		GetLayersBase()->GetParamGlobal()->CopyFrom(MasterParam);
		GetLayersBase()->GetParamComm()	 ->CopyFrom(MasterCommParam);

		if(WTab!=NULL){
			WTab->close();
			WTab->deleteLater();
		}
		if(WStrategy!=NULL){
			WStrategy->close();
			WStrategy->deleteLater();
		}
		if(WCommSetting!=NULL){
			WCommSetting->close();
			WCommSetting->deleteLater();
		}
		WTab=NULL;
		WStrategy=NULL;
		WCommSetting=NULL;


		WTab=new WEditParameterTab(&MasterParam ,-1,ui->framePanel);
		WTab->Initial(-1,15);
		WTab->ShowToWindow();
		WTab->show();
		
		WStrategy=new FormScanStrategy(GetLayersBase(),ui->frameFormStrategy);
		WStrategy->ShowToWindow();
		WStrategy->show();
		
		WCommSetting	=new FormCommSetting(GetLayersBase(),&MasterCommParam,ui->frameFormComm);
		WCommSetting->Show();	
		WCommSetting->show();
		
	}
	else if(Row>0){
		int	Page=Row-1;
		if(Page<0 || Page>=LPageNumb){
			return;
		}
		GetLayersBase()->GetParamGlobal()->CopyFrom(*SlaveParam[Page]);
		GetLayersBase()->GetParamComm()	 ->CopyFrom(*SlaveCommParam[Page]);

		if(WTab!=NULL){
			WTab->close();
			WTab->deleteLater();
		}
		if(WStrategy!=NULL){
			WStrategy->close();
			WStrategy->deleteLater();
		}
		if(WCommSetting!=NULL){
			WCommSetting->close();
			WCommSetting->deleteLater();
		}

		WTab=new WEditParameterTab(SlaveParam[Page] ,-1,ui->framePanel);
		WTab->Initial(-1,15);
		WTab->ShowToWindow();
		WTab->show();

		WStrategy=new FormScanStrategy(GetLayersBase(),ui->frameFormStrategy);
		WStrategy->ShowToWindow();
		WStrategy->show();

		WCommSetting	=new FormCommSetting(GetLayersBase(),SlaveCommParam[Page],ui->frameFormComm);
		WCommSetting->Show();
		WCommSetting->show();
	}
	LastRow=Row;
}

void EditParamDialog::on_pushButtonUpdate_clicked()
{
	if(LastRow==0){
		if(WTab!=NULL){
			WTab->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			WStrategy->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			delete	WStrategy;
		}
		WStrategy=NULL;
		MasterParam.CopyStrategyFrom(*GetLayersBase()->GetParamGlobal());
	}
	else if(LastRow>0){
		if(WTab!=NULL){
			WTab->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			WStrategy->LoadFromWindow();
		}
		if(WStrategy!=NULL){
			delete	WStrategy;
		}
		WStrategy=NULL;
		SlaveParam[LastRow-1]->CopyStrategyFrom(*GetLayersBase()->GetParamGlobal());
	}

	QBuffer SettingBuff;
	SettingBuff.open(QIODevice::ReadWrite);
	MasterParam.SaveParam(&SettingBuff);
	MasterCommParam.SaveParam(&SettingBuff);

	QSqlQuery query(GetLayersBase()->GetDatabase());
	query.prepare(/**/"UPDATE MASTERDATA "
				 /**/"SET MACHINEID=:MACHINEID"
				 /**/", WORKERID=:WORKERID"
				 /**/",SETTINGDATA=:SETTINGDATA "
				 /**/"WHERE MASTERCODE=:IN_MASTERCODE;");

	query.bindValue(0	, ui->spinBoxMachineCode->value());
	query.bindValue(1	, ui->spinBoxWorkerID	->value());
	query.bindValue(2	, SettingBuff.buffer());
	query.bindValue(3	, MasterCode);
	if(query.exec()==true){
		if(SlaveParam!=NULL && SlaveCommParam!=NULL){
			for(int page=0;page<LPageNumb;page++){
				QBuffer LSettingBuff;
				LSettingBuff.open(QIODevice::ReadWrite);
				SlaveParam[page]->SaveParam(&LSettingBuff);
				SlaveCommParam[page]->SaveParam(&LSettingBuff);

				QSqlQuery LQuery(GetLayersBase()->GetDatabase());
				query.prepare(/**/"UPDATE MASTERPAGE "
							 /**/"SET SETTINGDATA=:SETTINGDATA "
							 /**/"WHERE MASTERCODE=:IN_MASTERCODE and PAGECODE=:IN_PAGECODE;");

				query.bindValue(0	, LSettingBuff.buffer());
				query.bindValue(1	, MasterCode);
				query.bindValue(2	, page);
				if(query.exec()==false){
					return;
				}
			}
		}
		close();
	}
}

void EditParamDialog::on_pushButtonCancel_clicked()
{
	close();
}
