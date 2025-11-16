#include "XMLExplorer.h"
#include "XRememberer.h"
#include "SettingParameterForm.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include <QMessageBox>

XMLExplorer::XMLExplorer(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	Server=NULL;

	ControlRememberer::SetDefaultFileName("XMLExplorerRememberer.dat");

	ui.lineEditIPAddress				->setText(ControlRememberer::GetString(ui.lineEditIPAddress			,"localhost"));
	ui.spinBoxPortNumber				->setValue(ControlRememberer::GetInt(ui.spinBoxPortNumber			,12345));
	ui.lineEditTableStr					->setText(ControlRememberer::GetString(ui.lineEditTableStr			,/**/""));
	ui.lineEditEnumTableFilter			->setText(ControlRememberer::GetString(ui.lineEditEnumTableFilter	,"*"));
	ui.textEditInsertXMLWhereStr		->setPlainText(ControlRememberer::GetString(ui.textEditInsertXMLWhereStr		,/**/""));
	ui.textEditInsertXMLStr				->setPlainText(ControlRememberer::GetString(ui.textEditInsertXMLStr				,/**/""));
	ui.textEditUpdateXMLStr				->setPlainText(ControlRememberer::GetString(ui.textEditUpdateXMLStr				,/**/""));
	ui.textEditInsUpdateAttrXMLStr		->setPlainText(ControlRememberer::GetString(ui.textEditInsUpdateAttrXMLStr		,/**/""));
	ui.textEditDeleteAttrXMLStr			->setPlainText(ControlRememberer::GetString(ui.textEditDeleteAttrXMLStr			,/**/""));
	ui.textEditSelectXMLOutputStr		->setPlainText(ControlRememberer::GetString(ui.textEditSelectXMLOutputStr		,/**/""));
	ui.textEditSelectXMLWhereStr		->setPlainText(ControlRememberer::GetString(ui.textEditSelectXMLWhereStr		,/**/""));
	ui.textEditSelectXMLOrderStr		->setPlainText(ControlRememberer::GetString(ui.textEditSelectXMLOrderStr		,/**/""));
	ui.textEditSelectFirstXMLOutputStr	->setPlainText(ControlRememberer::GetString(ui.textEditSelectFirstXMLOutputStr	,/**/""));
	ui.textEditSelectFirstXMLWhereStr	->setPlainText(ControlRememberer::GetString(ui.textEditSelectFirstXMLWhereStr	,/**/""));
	ui.textEditSelectFirstXMLOrderStr	->setPlainText(ControlRememberer::GetString(ui.textEditSelectFirstXMLOrderStr	,/**/""));
	ui.textEditSelectLastXMLOutputStr	->setPlainText(ControlRememberer::GetString(ui.textEditSelectLastXMLOutputStr	,/**/""));
	ui.textEditSelectLastXMLWhereStr	->setPlainText(ControlRememberer::GetString(ui.textEditSelectLastXMLWhereStr	,/**/""));
	ui.textEditSelectLastXMLOrderStr	->setPlainText(ControlRememberer::GetString(ui.textEditSelectLastXMLOrderStr	,/**/""));

	ui.textEditChildSelectXMLOutputStr		->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectXMLOutputStr		,/**/""));
	ui.textEditChildSelectXMLWhereStr		->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectXMLWhereStr		,/**/""));
	ui.textEditChildSelectXMLOrderStr		->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectXMLOrderStr		,/**/""));
	ui.textEditChildSelectFirstXMLOutputStr	->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectFirstXMLOutputStr	,/**/""));
	ui.textEditChildSelectFirstXMLWhereStr	->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectFirstXMLWhereStr	,/**/""));
	ui.textEditChildSelectFirstXMLOrderStr	->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectFirstXMLOrderStr	,/**/""));
	ui.textEditChildSelectLastXMLOutputStr	->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectLastXMLOutputStr	,/**/""));
	ui.textEditChildSelectLastXMLWhereStr	->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectLastXMLWhereStr	,/**/""));
	ui.textEditChildSelectLastXMLOrderStr	->setPlainText(ControlRememberer::GetString(ui.textEditChildSelectLastXMLOrderStr	,/**/""));
	
}

XMLExplorer::~XMLExplorer()
{
}

void	XMLExplorer::SlotDisconnectFromServer()
{
	ui.listWidgetOperationalHandleList->clear();
	for(XMLOperationHandle *r=Server->GetFirst();r!=NULL;r=r->GetNext()){
		ui.listWidgetOperationalHandleList->addItem(r->GetTableStr());
	}
}
void	XMLExplorer::closeEvent ( QCloseEvent * event )
{
	if(Server!=NULL){
		Server->Close();
	}
	event->accept();

	ControlRememberer::SetValue(ui.lineEditIPAddress				,ui.lineEditIPAddress->text());
	ControlRememberer::SetValue(ui.spinBoxPortNumber				,ui.spinBoxPortNumber->value());
	ControlRememberer::SetValue(ui.lineEditTableStr					,ui.lineEditTableStr->text());
	ControlRememberer::SetValue(ui.lineEditEnumTableFilter			,ui.lineEditEnumTableFilter->text());
	ControlRememberer::SetValue(ui.textEditInsertXMLWhereStr		,ui.textEditInsertXMLWhereStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditInsertXMLStr				,ui.textEditInsertXMLStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditUpdateXMLStr				,ui.textEditUpdateXMLStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditInsUpdateAttrXMLStr		,ui.textEditInsUpdateAttrXMLStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditDeleteAttrXMLStr			,ui.textEditDeleteAttrXMLStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectXMLOutputStr		,ui.textEditSelectXMLOutputStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectXMLWhereStr		,ui.textEditSelectXMLWhereStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectXMLOrderStr		,ui.textEditSelectXMLOrderStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectFirstXMLOutputStr	,ui.textEditSelectFirstXMLOutputStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectFirstXMLWhereStr	,ui.textEditSelectFirstXMLWhereStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectFirstXMLOrderStr	,ui.textEditSelectFirstXMLOrderStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectLastXMLOutputStr	,ui.textEditSelectLastXMLOutputStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectLastXMLWhereStr	,ui.textEditSelectLastXMLWhereStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditSelectLastXMLOrderStr	,ui.textEditSelectLastXMLOrderStr	->toPlainText());	

	ControlRememberer::SetValue(ui.textEditChildSelectXMLOutputStr		,ui.textEditChildSelectXMLOutputStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectXMLWhereStr		,ui.textEditChildSelectXMLWhereStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectXMLOrderStr		,ui.textEditChildSelectXMLOrderStr		->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectFirstXMLOutputStr	,ui.textEditChildSelectFirstXMLOutputStr->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectFirstXMLWhereStr	,ui.textEditChildSelectFirstXMLWhereStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectFirstXMLOrderStr	,ui.textEditChildSelectFirstXMLOrderStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectLastXMLOutputStr	,ui.textEditChildSelectLastXMLOutputStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectLastXMLWhereStr	,ui.textEditChildSelectLastXMLWhereStr	->toPlainText());	
	ControlRememberer::SetValue(ui.textEditChildSelectLastXMLOrderStr	,ui.textEditChildSelectLastXMLOrderStr	->toPlainText());	
}

void	XMLExplorer::SlotConnect()
{
	QString	IPAddress	=ui.lineEditIPAddress->text();
	int		PortNumber	=ui.spinBoxPortNumber->value();

	if(Server==NULL){
		Server=new XMLServerHandle(IPAddress,PortNumber,this);
		connect(Server,SIGNAL(SignalDisconnectFromServer()),this,SLOT(SlotDisconnectFromServer()),Qt::QueuedConnection);
		Server->SetParam(&EParam);
		EParam.LoadDefault(/**/"");
	}
	Server->Open();
}
void	XMLExplorer::SlotOpenXMLOperation()
{
	QString	TableStr=ui.lineEditTableStr->text();
	if(Server->OpenXMLOperation(TableStr)!=NULL){
		ui.listWidgetOperationalHandleList->clear();
		for(XMLOperationHandle *r=Server->GetFirst();r!=NULL;r=r->GetNext()){
			ui.listWidgetOperationalHandleList->addItem(r->GetTableStr());
		}
		ui.checkBoxResult->setChecked(true);
	}
	else{
		ui.checkBoxResult->setChecked(false);
	}
}

void	XMLExplorer::SaveDefault(void)
{
	if(Server!=NULL){
		EParam.SaveDefault(/**/"");
	}
}


	
void	XMLExplorer::SlotDup()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	bool	Ret=Server->Dup(OpeHandle);
	if(Ret==true){
		ui.listWidgetOperationalHandleList->clear();
		for(XMLOperationHandle *r=Server->GetFirst();r!=NULL;r=r->GetNext()){
			ui.listWidgetOperationalHandleList->addItem(r->GetTableStr());
		}
	}
	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotCloseOperation()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	bool	Ret=OpeHandle->Close();
	delete	OpeHandle;
	if(Ret==true){
		ui.listWidgetOperationalHandleList->clear();
		for(XMLOperationHandle *r=Server->GetFirst();r!=NULL;r=r->GetNext()){
			ui.listWidgetOperationalHandleList->addItem(r->GetTableStr());
		}
	}
	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::SlotInsertXML()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	WhereStr	=ui.textEditInsertXMLWhereStr->toPlainText();
	QString	InsertedStr	=ui.textEditInsertXMLStr->toPlainText();
	bool	Ret=OpeHandle->InsertXML(WhereStr,InsertedStr);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotUpdateXML()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	UpdatedStr=ui.textEditUpdateXMLStr->toPlainText();
	bool	Ret=OpeHandle->UpdateXML(UpdatedStr);

	ui.checkBoxResult->setChecked(Ret);
}
void	XMLExplorer::slotDeleteXML()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	bool	Ret=OpeHandle->DeleteXML();

	ui.checkBoxResult->setChecked(Ret);
}
void	XMLExplorer::slotInsUpdateAttr()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	UpdatedStr=ui.textEditInsUpdateAttrXMLStr->toPlainText();
	bool	Ret=OpeHandle->InsUpdateAttr(UpdatedStr);

	ui.checkBoxResult->setChecked(Ret);
}
void	XMLExplorer::slotDeleteAttr()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	DeletedStr=ui.textEditDeleteAttrXMLStr->toPlainText();
	bool	Ret=OpeHandle->DeleteAttr(DeletedStr);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotSelect()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	OutputStr	=ui.textEditSelectXMLOutputStr->toPlainText();
	QString	SearchStr	=ui.textEditSelectXMLWhereStr->toPlainText();
	QString	OrderStr	=ui.textEditSelectXMLOrderStr->toPlainText();
	QStringList	ResultList;
	bool	Ret=OpeHandle->Select(OutputStr,SearchStr,OrderStr,ResultList);
	ui.listWidgetSelectXMLResultStr->clear();
	ui.listWidgetSelectXMLResultStr->addItems(ResultList);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotSelectFirst()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	OutputStr	=ui.textEditSelectFirstXMLOutputStr->toPlainText();
	QString	SearchStr	=ui.textEditSelectFirstXMLWhereStr->toPlainText();
	QString	OrderStr	=ui.textEditSelectFirstXMLOrderStr->toPlainText();
	QString	ResultStr;
	bool	Ret=OpeHandle->SelectFirst(OutputStr,SearchStr,OrderStr,ResultStr);
	ui.textEditSelectFirstXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}
void	XMLExplorer::slotSelectLast()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	OutputStr	=ui.textEditSelectLastXMLOutputStr->toPlainText();
	QString	SearchStr	=ui.textEditSelectLastXMLWhereStr->toPlainText();
	QString	OrderStr	=ui.textEditSelectLastXMLOrderStr->toPlainText();
	QString	ResultStr;
	bool	Ret=OpeHandle->SelectLast(OutputStr,SearchStr,OrderStr,ResultStr);
	ui.textEditSelectLastXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotSelectNext()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	ResultStr;
	bool	Ret=OpeHandle->SelectNext(ResultStr);
	ui.textEditSelectNextXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotSelectPrev()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	ResultStr;
	bool	Ret=OpeHandle->SelectPrev(ResultStr);
	ui.textEditSelectPrevXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}
void	XMLExplorer::slotChildSelect()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	OutputStr	=ui.textEditChildSelectXMLOutputStr->toPlainText();
	QString	SearchStr	=ui.textEditChildSelectXMLWhereStr->toPlainText();
	QString	OrderStr	=ui.textEditChildSelectXMLOrderStr->toPlainText();
	QStringList	ResultList;
	bool	Ret=OpeHandle->ChildSelect(OutputStr,SearchStr,OrderStr,ResultList);
	ui.listWidgetChildSelectXMLResultStr->clear();
	ui.listWidgetChildSelectXMLResultStr->addItems(ResultList);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotChildSelectFirst()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	OutputStr	=ui.textEditChildSelectFirstXMLOutputStr->toPlainText();
	QString	SearchStr	=ui.textEditChildSelectFirstXMLWhereStr->toPlainText();
	QString	OrderStr	=ui.textEditChildSelectFirstXMLOrderStr->toPlainText();
	QString	ResultStr;
	bool	Ret=OpeHandle->ChildSelectFirst(OutputStr,SearchStr,OrderStr,ResultStr);
	ui.textEditChildSelectFirstXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}


void	XMLExplorer::slotChildSelectLast()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	OutputStr	=ui.textEditChildSelectLastXMLOutputStr->toPlainText();
	QString	SearchStr	=ui.textEditChildSelectLastXMLWhereStr->toPlainText();
	QString	OrderStr	=ui.textEditChildSelectLastXMLOrderStr->toPlainText();
	QString	ResultStr;
	bool	Ret=OpeHandle->ChildSelectLast(OutputStr,SearchStr,OrderStr,ResultStr);
	ui.textEditChildSelectLastXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotChildSelectNext()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	ResultStr;
	bool	Ret=OpeHandle->ChildSelectNext(ResultStr);
	ui.textEditChildSelectNextXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotChildSelectPrev()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	QString	ResultStr;
	bool	Ret=OpeHandle->ChildSelectPrev(ResultStr);
	ui.textEditChildSelectPrevXMLResultStr->setPlainText(ResultStr);

	ui.checkBoxResult->setChecked(Ret);
}

void	XMLExplorer::slotEnumTable()
{
	if(Server!=NULL){
		QString	Filter=ui.lineEditEnumTableFilter->text();
		bool	Ret=Server->EnumTables(Filter,EnumResultList);
		ui.listWidgetTableList->clear();
		ui.listWidgetTableList->addItems(EnumResultList);

		ui.checkBoxResult->setChecked(Ret);
	}
}

void XMLExplorer::on_pushButtonCopyPointer_clicked()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];
	bool	Ret=OpeHandle->XML_CopyPointerFromChild();

	ui.checkBoxResult->setChecked(Ret);
}

void XMLExplorer::on_listWidgetTableList_doubleClicked(const QModelIndex &index)
{
	int	R=ui.listWidgetTableList->currentRow();
	if(R>=0){
		QString	s=EnumResultList[R];
		ui.lineEditTableStr->setText(s);
	}
}

void XMLExplorer::on_pushButtonSetting_clicked()
{
	if(Server!=NULL){
		SettingParameterForm	D(this);
		D.exec();
	}
}


void XMLExplorer::on_pushButtonExecuteDeleteMultiXML_clicked()
{
	int	Row=ui.listWidgetOperationalHandleList->currentRow();
	if(Row<0){
		ui.checkBoxResult->setChecked(false);
		return;
	}
	XMLOperationHandle *OpeHandle=(*Server)[Row];

	QString	SearchStr	=ui.textEditDeleteXMLWhereStr->toPlainText();
	
	bool	Ret=OpeHandle->DeleteXML(SearchStr);
	ui.checkBoxResult->setChecked(Ret);
}

void XMLExplorer::on_pushButtonBackup_clicked()
{
	if(Server!=NULL){
		QString FileName=QFileDialog::getSaveFileName ( 0, QString("Backup"), QString()
												, "BackupFile (*.xmlbkp);;All Files (*.*)");
		if(FileName.isEmpty()==false){
			QFile	WFile(FileName);
			if(WFile.open(QIODevice::WriteOnly)==false){
				QMessageBox::warning (NULL, "Error"
									,QString("Can not open file : ")+FileName);
				return;
			}
			IntList	Rows;
			GetSelectedRows(ui.listWidgetTableList,Rows);

			int32	N=Rows.GetCount();
			if(::Save(&WFile,N)==false)
				return;

			for(IntClass *d=Rows.GetFirst();d!=NULL;d=d->GetNext()){
				QString	TableStr=EnumResultList[d->GetValue()];
				QByteArray AllData;
				bool	Ret=Server->GetTableAllData	(TableStr,AllData);
				if(Ret==false){
					QMessageBox::warning (NULL, "Error"
										,QString("GetTableAllData : ")+TableStr);
					return;
				}
				if(::Save(&WFile,TableStr)==false)
					return;
				if(::Save(&WFile,AllData)==false)
					return;
			}
			QMessageBox::information (NULL, "Success"
										,QString("Backed up successfully : ")+FileName);
		}
	}
}

void XMLExplorer::on_pushButtonRestore_clicked()
{
	if(Server!=NULL){
		QString FileName=QFileDialog::getOpenFileName( 0, QString("Restore"), QString()
												, "BackupFile (*.xmlbkp);;All Files (*.*)");
		if(FileName.isEmpty()==false){
			QFile	RFile(FileName);
			if(RFile.open(QIODevice::ReadOnly)==false){
				QMessageBox::warning (NULL, "Error"
									,QString("Can not open file : ")+FileName);
				return;
			}

			int32	N;
			if(::Load(&RFile,N)==false){
				return;
			}
			for(int i=0;i<N;i++){
				QString	TableStr;
				QByteArray AllData;
				if(::Load(&RFile,TableStr)==false){
					QMessageBox::warning (NULL, "Error"
										,QString("Can not read data from file: ")+FileName);
					return;
				}
				if(::Load(&RFile,AllData)==false){
					QMessageBox::warning (NULL, "Error"
										,QString("Can not read data from file: ")+FileName);
					return;
				}
				bool	Ret=Server->ReplaceTableAllData	(TableStr,AllData);
				if(Ret==false){
					QMessageBox::warning (NULL, "Error"
										,QString("ReplaceTableAllData: ")+TableStr);
					return;
				}
			}
			slotEnumTable();

			QMessageBox::information (NULL, "Success"
										,QString("Restored successfully : ")+FileName);
		}
	}
}

void XMLExplorer::on_pushButtonRemove_clicked()
{
	if(QMessageBox::question ( NULL, "Alarm", "Remove tables? "
							, QMessageBox::Yes | QMessageBox::No
							, QMessageBox::No)==QMessageBox::Yes){
		if(Server!=NULL){
			IntList	Rows;
			GetSelectedRows(ui.listWidgetTableList,Rows);

			for(IntClass *d=Rows.GetFirst();d!=NULL;d=d->GetNext()){
				QString	TableStr=EnumResultList[d->GetValue()];
				if(Server->DeleteTable(TableStr)==false){
					QMessageBox::warning (NULL, "Error"
										,QString("DeleteTable: ")+TableStr);
					return;
				}
			}
			slotEnumTable();

			QMessageBox::information (NULL, "Success"
										,QString("Remove tables successfully"));
		}
	}

}
