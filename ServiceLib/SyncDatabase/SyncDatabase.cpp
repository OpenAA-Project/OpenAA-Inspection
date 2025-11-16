#include "SyncDatabase.h"
#include "XGeneralFunc.h"

#include "XDataInLayer.h"
#include <QFile>
#include <QFileDialog>
#include <QSqlQuery>
#include "FormScanStrategy.h"
#include "FormCommSetting.h"
#include "XDatabase.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "EditPhaseForm.h"
#include "FormDirectionOnEachPage.h"
#include "EditGUILibResource.h"
#include "ShareMasterDataForm.h"
#include "AddExcludedFileDialog.h"

extern	int	LanguageCode;
extern	LangSolverNew	LangSolverGUILib;
extern	QString	LoadedFileName;
;

SyncDatabase::SyncDatabase(  LayersBase  *base
							,ParamGlobal *ParamCommData
							,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
	,ServiceForLayers(base)
	,SyncDB(base),ProcessDataBase(base,this,this)
{
	ui.setupUi(this);

	QString	Msg;
	GetLayersBase()->InitialDatabaseLoader(Msg);

	connect(this,SIGNAL(SignalSuccess(const QString &,const QString &,const QString &)),this,SLOT(SlotSuccess(const QString &,const QString &,const QString &)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalError  (const QString &,const QString &,const QString &)),this,SLOT(SlotError  (const QString &,const QString &,const QString &)),Qt::QueuedConnection);
	connect(this,SIGNAL(SignalProcessTable(const QString &)),this,SLOT(SlotProcessTable(const QString &)),Qt::QueuedConnection);

	ui.tableWidgetAction->setColumnWidth(0,140);
	ui.tableWidgetAction->setColumnWidth(1,70);
	ui.tableWidgetAction->setColumnWidth(2,100);
	ui.tableWidgetAction->setColumnWidth(3,350);
	ui.tableWidgetAction->setColumnWidth(4,80);

	STablePointer	=NULL;
	Step	=0;

	TM.setInterval(2000);
	TM.setSingleShot(false);
	connect(&TM,SIGNAL(timeout()),this,SLOT(SlotTimeOut()));

	QFile	SettingFile(LoadedFileName);
	if(SettingFile.open(QIODevice::ReadOnly)==true){
		if(Load(&SettingFile)==true){
			ui.lineEditSrcServer	->setText(SyncDB.DBSrc.IPAddress	);
			ui.spinBoxSrcPort	->setValue(SyncDB.DBSrc.Port			);
			ui.lineEditSrcFileName	->setText(SyncDB.DBSrc.FilePathName	);
			ui.lineEditSrcUserName	->setText(SyncDB.DBSrc.UserName		);
			ui.lineEditSrcPassword	->setText(SyncDB.DBSrc.Password		);

			ui.lineEditDstServer	->setText(SyncDB.DBDst.IPAddress	);
			ui.spinBoxDstPort		->setValue(SyncDB.DBDst.Port		);
			ui.lineEditDstFileName	->setText(SyncDB.DBDst.FilePathName	);
			ui.lineEditDstUserName	->setText(SyncDB.DBDst.UserName		);
			ui.lineEditDstPassword	->setText(SyncDB.DBDst.Password		);

			ui.listWidgetExcluded	->clear();
			ui.listWidgetExcluded	->addItems(ExcludedTables);

			ui.labelRegisteredFileName->setText(LoadedFileName);
			ui.toolButtonRun->setChecked(true);
			on_toolButtonRun_clicked();
		}
	}
}

SyncDatabase::~SyncDatabase()
{

}

void SyncDatabase::on_pushButtonRegister_clicked()
{
	SyncDB.DBSrc.IPAddress		=ui.lineEditSrcServer	->text();
	SyncDB.DBSrc.Port			=ui.spinBoxSrcPort	->value();
	SyncDB.DBSrc.FilePathName	=ui.lineEditSrcFileName	->text();
	SyncDB.DBSrc.UserName		=ui.lineEditSrcUserName	->text();
	SyncDB.DBSrc.Password		=ui.lineEditSrcPassword	->text();

	SyncDB.DBDst.IPAddress		=ui.lineEditDstServer	->text();
	SyncDB.DBDst.Port			=ui.spinBoxDstPort	->value();
	SyncDB.DBDst.FilePathName	=ui.lineEditDstFileName	->text();
	SyncDB.DBDst.UserName		=ui.lineEditDstUserName	->text();
	SyncDB.DBDst.Password		=ui.lineEditDstPassword	->text();

	QFile	SettingFile(LoadedFileName);
	if(SettingFile.open(QIODevice::WriteOnly)==true){
		if(Save(&SettingFile)==true){
			ui.labelRegisteredFileName->setText(LoadedFileName);
		}
	}
}

bool	SyncDatabase::Save(QIODevice *f)
{
	int32	Ver=2;
	if(::Save(f,Ver)==false)
		return false;
	if(SyncDB.Save(f)==false)
		return false;
	if(::Save(f,ExcludedTables)==false)
		return false;

	return true;
}

bool	SyncDatabase::Load(QIODevice *f)
{
	int32	Ver;
	if(::Load(f,Ver)==false)
		return false;
	if(SyncDB.Load(f)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,ExcludedTables)==false)
			return false;
	}
	return true;
}

void SyncDatabase::on_pushButtonTestCOnnectionDst_clicked()
{

}

void SyncDatabase::on_toolButtonRun_clicked()
{
	if(ui.toolButtonRun->isChecked()==true){
		//ProcessDataBase.start();
		TM.start();
	}
	else{
		TM.stop();
	}
}
void SyncDatabase::on_pushButtonForceUpdate_clicked()
{
	SyncErrorContainer Errors;
	ForceUpdateInsert(Errors,"INSPECTLIB"		,"LASTUPDATED");
	ForceUpdateInsert(Errors,"LIBFOLDER"		,/**/"");
	ForceUpdateInsert(Errors,"MASTERDATA"		,"LASTEDITTIME");
	ForceUpdateInsert(Errors,"MASTERPAGE"		,/**/"");
	ForceUpdateInsert(Errors,"MASTERCATEGORY"	,/**/"");
	//ForceUpdateInsert(Errors,"INSPECTIONLOT"	,"LASTUPDATED");
	//ForceUpdateInsert(Errors,"LIGHT"			,"UPDATETIME");

	ProcessDataBase.Halt=none3;
}

ThreadProcessDatabase::ThreadProcessDatabase(LayersBase *base,SyncDatabase *pbase ,QObject *parent)
	:QThread(parent),ServiceForLayers(base)
{
	SBase=pbase;
	TerminationFlag	=false;
	Halt			=none3;
}

void	ThreadProcessDatabase::run(void)
{
	if(SBase->SyncDB.DBSrc.IsOpen()==false){
		if(SBase->SyncDB.DBSrc.Open()==false){
			return;
		}
	}
	if(SBase->SyncDB.DBDst.IsOpen()==false){
		if(SBase->SyncDB.DBDst.Open()==false){
			return;
		}
	}

	SBase->SyncDB.DBSrc.LoadAllData(SBase->SyncDB.DBSrc.AllOldDatas);

	while(TerminationFlag==false){
		SyncErrorContainer Errors;
		SBase->SyncDB.DBSrc.LoadAllData(SBase->SyncDB.DBSrc.CurrentDatas);
		for(XTable *s=SBase->SyncDB.DBSrc.TableList.GetFirst();s!=NULL;s=s->GetNext()){
			SBase->CompareUpdate(Errors,s->Name);
			if(Halt==true3){
				Halt=false3;
				while(Halt==false3){
					GSleep(100);
				}
			}
		}
		SBase->SyncDB.DBSrc.CopyToOld();

		if(Halt==true3){
			Halt=false3;
			while(Halt==false3){
				GSleep(100);
			}
		}
	}
}
void	SyncDatabase::SlotTimeOut()
{
	if(Step==0){
		if(SyncDB.DBSrc.IsOpen()==false){
			if(SyncDB.DBSrc.Open()==false){
				return;
			}
		}
		if(SyncDB.DBDst.IsOpen()==false){
			if(SyncDB.DBDst.Open()==false){
				return;
			}
		}
		Step=1;
	}
	else if(Step==1){
		SyncDB.DBSrc.LoadAllData(SyncDB.DBSrc.AllOldDatas);
		Step=2;
	}
	else if(Step==2){
		SyncDB.DBSrc.LoadAllData(SyncDB.DBSrc.CurrentDatas);
		Step=3;
	}
	else if(Step==3){
		STablePointer=SyncDB.DBSrc.TableList.GetFirst();
		Step=4;
	}
	else if(Step==4){
		if(STablePointer==NULL){
			Step=10;
		}
		else{
			CompareUpdate(CompErrors,STablePointer->Name);
			Step=5;
		}
	}
	else if(Step==5){
		STablePointer=STablePointer->GetNext();
		Step=4;
	}
	else if(Step==10){
		SyncDB.DBSrc.CopyToOld();
		Step=11;
	}
	else if(Step==11){
		CompErrors.RemoveAll();
		Step=2;
	}

	if(ui.progressBar->value()>=ui.progressBar->maximum()){
		ui.progressBar->setValue(0);
	}
	else{
		ui.progressBar->setValue(ui.progressBar->value()+1);
	}
}

void	SyncDatabase::ForceUpdateInsert(SyncErrorContainer &Errors ,const QString &TableName,const QString &LastUpdateStr)
{
	if(SyncDB.DBSrc.IsOpen()==false){
		if(SyncDB.DBSrc.Open()==false){
			return;
		}
	}
	if(SyncDB.DBDst.IsOpen()==false){
		if(SyncDB.DBDst.Open()==false){
			return;
		}
	}

	XTable *s1=SyncDB.DBSrc.Find(TableName);
	XTable *d1=SyncDB.DBDst.Find(TableName);

	XIndex	*Index=s1->GetUniqueIndex();
	if(Index==NULL)
		return;

	if(s1!=NULL && d1!=NULL){
		QSqlQuery	QuerySrc(QString("Select * from ")+s1->Name,SyncDB.DBSrc.DB->GetDatabase());
		if(QuerySrc.first()){
			do{
				QString	str= QString("Select * from ")+s1->Name +QString(" where ");

				QString	StrAnd=/**/"";
				QString	KeyStr;
				for(XFieldPointer *p=Index->KeyField.GetFirst();p!=NULL;p=p->GetNext()){
					KeyStr+=StrAnd;
					KeyStr+=p->Point->Name+QString("=")+QuerySrc.record().value(p->Point->Name).toString();
					StrAnd=" and ";
				}
				str+=KeyStr;
				str+=" ";
				QSqlQuery	QueryDst(str,SyncDB.DBDst.DB->GetDatabase());
				if(QueryDst.first()){
					if(LastUpdateStr.isNull()==false){
						QDateTime	dtS=QuerySrc.record().value(LastUpdateStr).toDateTime();
						QDateTime	dtD=QueryDst.record().value(LastUpdateStr).toDateTime();
						if(dtS>dtD){
							QString	UStr=QString("UPDATE ")+s1->Name +QString(" SET ");
							QString Comma=/**/"";
							for(XField *f=s1->FieldList.GetFirst();f!=NULL;f=f->GetNext()){
								UStr+=Comma;
								UStr+=f->Name + QString("=:")+f->Name;
								Comma=",";
							}
							UStr+=QString(" where ");

							Comma=/**/"";
							for(XFieldPointer *p=Index->KeyField.GetFirst();p!=NULL;p=p->GetNext()){
								UStr+=Comma;
								UStr+=p->Point->Name+QString("=")+QuerySrc.record().value(p->Point->Name).toString();
								Comma=" and ";
							}
							QSqlQuery	QueryUpdate(SyncDB.DBDst.DB->GetDatabase());
							QueryUpdate.prepare(UStr);
							int	k=0;
							for(XField *f=s1->FieldList.GetFirst();f!=NULL;f=f->GetNext(),k++){
								QueryUpdate.bindValue(k	, QuerySrc.record().value(f->Name));
							}
							if(QueryUpdate.exec()==true){
								emit	SignalSuccess(TableName ,KeyStr ,"Update");
							}
							else{
								Errors.AppendList(new SyncDBError(TableName,KeyStr,"Update error"));
							}
						}
					}
					/*
					else{
						QString	UStr=QString("UPDATE ")+s1->Name +QString(" SET ");
						QString Comma="";
						for(XField *f=s1->FieldList.GetFirst();f!=NULL;f=f->GetNext()){
							UStr+=Comma;
							UStr+=f->Name + QString("=:")+f->Name;
							Comma=",";
						}
						UStr+=QString(" where ");

						Comma="";
						for(XFieldPointer *p=Index->KeyField.GetFirst();p!=NULL;p=p->GetNext()){
							UStr+=Comma;
							UStr+=p->Point->Name+QString("=")+QuerySrc.record().value(p->Point->Name).toString();
							Comma=" and ";
						}
						QSqlQuery	QueryUpdate(SyncDB.DBDst.DB->GetDatabase());
						QueryUpdate.prepare(UStr);
						int	k=0;
						for(XField *f=s1->FieldList.GetFirst();f!=NULL;f=f->GetNext(),k++){
							QueryUpdate.bindValue(k	, QuerySrc.record().value(f->Name));
						}
						if(QueryUpdate.exec()==false){
						}
					}
					*/
				}
				else{
					QSqlQuery queryInsrt(SyncDB.DBDst.DB->GetDatabase());
					QString	IStr=QString("INSERT INTO ")+s1->Name +QString("(");
					QString Comma=/**/"";
					for(XField *f=s1->FieldList.GetFirst();f!=NULL;f=f->GetNext()){
						IStr+=Comma;
						IStr+=f->Name;
						Comma=",";
					}
					IStr+=QString(") VALUES(");
					
					Comma=/**/"";
					for(XField *f=s1->FieldList.GetFirst();f!=NULL;f=f->GetNext()){
						IStr+=Comma;
						IStr+=QString(":")+f->Name;
						Comma=",";
					}
					IStr+=QString(");");
		
					queryInsrt.prepare(IStr);
					int	k=0;
					for(XField *f=s1->FieldList.GetFirst();f!=NULL;f=f->GetNext(),k++){
						queryInsrt.bindValue(k	, QuerySrc.record().value(f->Name));
					}
					if(queryInsrt.exec()==true){
						emit	SignalSuccess(TableName ,KeyStr ,"Insert");
					}
					else{
						Errors.AppendList(new SyncDBError(TableName,KeyStr,"Insert error"));
					}
				}
			}while(QuerySrc.next()==true);
		}
	}
	emit	SignalProcessTable(TableName);
}


bool	SyncDatabase::CompareUpdate(SyncErrorContainer &Errors ,const QString &TableName)
{
	XTableWithData	*SNew=SyncDB.DBSrc.FindWithCurrentData(TableName);
	XTableWithData	*SOld=SyncDB.DBSrc.FindWithAllOldData(TableName);
	XTable			*D=SyncDB.DBDst.Find(TableName);
	XIndex	*Index=SNew->PointTable->GetUniqueIndex();
	if(Index==NULL)
		return false;
	for(int i=0;i<ExcludedTables.count();i++){
		if(ExcludedTables[i]==TableName){
			return false;
		}
	}

	if(SNew!=NULL && SOld!=NULL && D!=NULL){
		for(XRecordWithData *rnew=SNew->RecordDatas.GetFirst();rnew!=NULL;rnew=rnew->GetNext()){
			XRecordWithData *rold=SOld->FindWithKey(rnew,*Index);
			if(rold==NULL){
				QSqlQuery queryInsrt(SyncDB.DBDst.DB->GetDatabase());
				QString	IStr=QString("INSERT INTO ")+D->Name +QString("(");
				QString Comma=/**/"";
				for(XFieldWithData *f=rnew->FieldDatas.GetFirst();f!=NULL;f=f->GetNext()){
					IStr+=Comma;
					IStr+=f->PointField->Name;
					Comma=",";
				}
				IStr+=QString(") VALUES(");
					
				Comma=/**/"";
				for(XFieldWithData *f=rnew->FieldDatas.GetFirst();f!=NULL;f=f->GetNext()){
					IStr+=Comma;
					IStr+=QString(":")+f->PointField->Name;
					Comma=",";
				}
				IStr+=QString(");");
		
				queryInsrt.prepare(IStr);
				int	k=0;
				for(XFieldWithData *f=rnew->FieldDatas.GetFirst();f!=NULL;f=f->GetNext(),k++){
					queryInsrt.bindValue(k	, f->GetData());
				}
				Comma=/**/"";
				QString	KeyStr;
				for(XFieldPointer *p=Index->KeyField.GetFirst();p!=NULL;p=p->GetNext()){
					KeyStr+=Comma;
							
					XFieldWithData	*fa=rnew->FindField(p->Point->Name);
					if(fa==NULL){
						return false;
					}
					KeyStr+=p->Point->Name+QString("=")+fa->GetData().toString();
					Comma=" and ";
				}
				if(queryInsrt.exec()==true){
					emit	SignalSuccess(TableName ,KeyStr ,"Insert");
				}
				else{
					Errors.AppendList(new SyncDBError(TableName,KeyStr,"Insert error"));
				}
			}
			else if(*rnew!=*rold){
				QString	UStr=QString("UPDATE ")+D->Name +QString(" SET ");
				QString Comma=/**/"";
				for(XFieldWithData *f=rnew->FieldDatas.GetFirst();f!=NULL;f=f->GetNext()){
					UStr+=Comma;
					UStr+=f->PointField->Name + QString("=:")+f->PointField->Name;
					Comma=",";
				}
				UStr+=QString(" where ");

				Comma=/**/"";
				QString	KeyStr;
				for(XFieldPointer *p=Index->KeyField.GetFirst();p!=NULL;p=p->GetNext()){
					KeyStr+=Comma;
						
					XFieldWithData	*fa=rnew->FindField(p->Point->Name);
					if(fa==NULL){
						return false;
					}
					KeyStr+=p->Point->Name+QString("=")+fa->GetData().toString();
					Comma=" and ";
				}
				UStr+=KeyStr;
				UStr+=" ";

				QSqlQuery	QueryUpdate(SyncDB.DBDst.DB->GetDatabase());
				QueryUpdate.prepare(UStr);
				int	k=0;
				for(XFieldWithData *f=rnew->FieldDatas.GetFirst();f!=NULL;f=f->GetNext(),k++){
					QueryUpdate.bindValue(k	, f->GetData());
				}
				if(QueryUpdate.exec()==true){
					emit	SignalSuccess(TableName ,KeyStr ,"Update");
				}
				else{
					Errors.AppendList(new SyncDBError(TableName,KeyStr,"Update error"));
				}
			}
		}
		for(XRecordWithData *rold=SOld->RecordDatas.GetFirst();rold!=NULL;rold=rold->GetNext()){
			XRecordWithData *rnew=SOld->FindWithKey(rold,*Index);
			if(rnew==NULL){
				QString	UStr=QString("DELETE from ")+D->Name;
				UStr+=QString(" where ");

				QString	Comma=/**/"";
				QString	KeyStr;
				for(XFieldPointer *p=Index->KeyField.GetFirst();p!=NULL;p=p->GetNext()){
					KeyStr+=Comma;
						
					XFieldWithData	*fa=rnew->FindField(p->Point->Name);
					if(fa==NULL){
						return false;
					}
					KeyStr+=p->Point->Name+QString("=")+fa->GetData().toString();
					Comma=" and ";
				}
				UStr+=KeyStr;
				UStr+=" ";

				QSqlQuery queryDelete(SyncDB.DBDst.DB->GetDatabase());
				queryDelete.prepare(UStr);
				if(queryDelete.exec()==true){
					emit	SignalSuccess(TableName ,KeyStr ,"Delete");
				}
				else{
					Errors.AppendList(new SyncDBError(TableName,KeyStr,"Delete error"));
				}
			}
		}
	}
	emit	SignalProcessTable(TableName);
	return true;
}


void	SyncDatabase::SlotSuccess(const QString &TableName ,const QString &IDCode ,const QString &Message)
{
	while(ui.tableWidgetAction->rowCount()>1000){
		ui.tableWidgetAction->removeRow(0);
	}
	int	row=ui.tableWidgetAction->rowCount();
	ui.tableWidgetAction->setRowCount(ui.tableWidgetAction->rowCount()+1);

	::SetDataToTable(ui.tableWidgetAction ,0,row,QDateTime::currentDateTime().toString("yy/MM/dd HH:mm:ss"));
	::SetDataToTable(ui.tableWidgetAction ,1,row,"Success");
	::SetDataToTable(ui.tableWidgetAction ,2,row,TableName);
	::SetDataToTable(ui.tableWidgetAction ,3,row,IDCode);
	::SetDataToTable(ui.tableWidgetAction ,4,row,Message);
}

void	SyncDatabase::SlotError  (const QString &TableName ,const QString &IDCode ,const QString &Message)
{
	while(ui.tableWidgetAction->rowCount()>1000){
		ui.tableWidgetAction->removeRow(0);
	}
	int	row=ui.tableWidgetAction->rowCount();
	ui.tableWidgetAction->setRowCount(ui.tableWidgetAction->rowCount()+1);

	::SetDataToTable(ui.tableWidgetAction ,0,row,QDateTime::currentDateTime().toString("yy/MM/dd HH:mm:ss"));
	::SetDataToTable(ui.tableWidgetAction ,1,row,"Error");
	::SetDataToTable(ui.tableWidgetAction ,2,row,TableName);
	::SetDataToTable(ui.tableWidgetAction ,3,row,IDCode);
	::SetDataToTable(ui.tableWidgetAction ,4,row,Message);
}

void	SyncDatabase::SlotProcessTable(const QString &TableName)
{
	for(int i=0;i<TableList.count();i++){
		if(TableList[i]==TableName){
			return;
		}
	}
	TableList.append(TableName);
	ui.listWidgetSourceTable->addItem(TableName);
}
void SyncDatabase::on_pushButtonAddExcluded_clicked()
{
	AddExcludedFileDialog	D;
	if(D.exec()==true){
		ExcludedTables.append(D.TableName);
		ui.listWidgetExcluded	->clear();
		ui.listWidgetExcluded	->addItems(ExcludedTables);
	}
}

void SyncDatabase::on_pushButtonDelExcluded_clicked()
{
	int	Row=ui.listWidgetExcluded->currentRow();
	if(Row<0)
		return;
	ExcludedTables.removeAt(Row);

	ui.listWidgetExcluded	->clear();
	ui.listWidgetExcluded	->addItems(ExcludedTables);
}
