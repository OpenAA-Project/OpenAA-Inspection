#include "ManageMasterConnection.h"
#include "XFileRegistry.h"
#include <QSqlDatabase>
#include "XDataInExe.h"
#include "MasterCategoryForm.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "CreateNewRelation.h"
#include "Regulus64Version.h"
#include <QMessageBox>

static	int	CategoryID;


QSqlSelectMasterModel::QSqlSelectMasterModel(QObject * parent, const QSqlDatabase &db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<ManageMasterConnection *>(parent);
}
QString QSqlSelectMasterModel::selectStatement () const
{
	QString	ret;
	switch(ParentWindow->ListMode){
		case ManageMasterConnection::_IDNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+QString(/**/" ORDER BY MASTERCODE;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+QString(/**/" AND CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY MASTERCODE;");
			}
			break;
		case ManageMasterConnection::_IDReverse:
			if(ParentWindow->StartSearchID!=0){
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+QString(/**/" AND CATEGORYID=")
						+QString::number(CategoryID)
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
			}
			else{
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA ")
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA ")
						+QString(/**/" WHERE CATEGORYID=")
						+QString::number(CategoryID)
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
			}
			break;
		case ManageMasterConnection::_TimeNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA ORDER BY REGTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY REGTIME;");
			}
			break;
		case ManageMasterConnection::_TimeReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA ORDER BY REGTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY REGTIME DESC;");
			}
			break;
		case ManageMasterConnection::_NameNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")+QString(/**/" ORDER BY MASTERNAME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+QString(/**/" ORDER BY MASTERNAME;");
			}
			break;
		case ManageMasterConnection::_NameReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")+QString(/**/" ORDER BY MASTERNAME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+QString(/**/" ORDER BY MASTERNAME DESC;");
			}
			break;
	}
	return ret;
}

QSqlConnectionModel::QSqlConnectionModel(QObject * parent, const QSqlDatabase &db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<ManageMasterConnection *>(parent);
}
QString QSqlConnectionModel::selectStatement () const
{
	if(ParentWindow->RelationCode<0){
		return /**/"SELECT RELATIONCODE,REGTIME,RELATIONNAME FROM MASTERRELATION";
	}
	else{
		return QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNAME FROM MASTERRELATION WHERE RELATIONCODE=")
			+  QString::number(ParentWindow->RelationCode);
	}
}

QSqlContentModel::QSqlContentModel(QObject * parent, const QSqlDatabase &db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<ManageMasterConnection *>(parent);
}
QString QSqlContentModel::selectStatement () const
{
	return QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME FROM MASTERDATA WHERE RELATIONCODE=")
		+  QString::number(ParentWindow->RelationCode)
		+  QString(/**/" order by RELATIONID");
}

//===========================================================================================================

ManageMasterConnection::ManageMasterConnection(LayersBase *Base ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(Base)
{
	ui.setupUi(this);

	CurrentMasterCode	=-1;
	RelationCode		=-1;
	StartSearchID		=0;

	MasterCategory=new MasterCategoryForm(GetLayersBase(),ui.frameCategory);
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	QSqlSelectMasterModel *MModel = new QSqlSelectMasterModel(this,*GetLayersBase()->GetDataBase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	ui.tableView->setModel(MModel);
	ui.tableView->setColumnWidth (0, 120);
	ui.tableView->setColumnWidth (1, 150);
	ui.tableView->setColumnWidth (2, 300);
	ui.tableView->setColumnWidth (3, 250);
	ui.tableView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->show();
	
	ShowListHeader();

	CModel = new QSqlConnectionModel(this,*GetLayersBase()->GetDataBase());
	CModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	CModel->select();
	CModel->removeColumn(0); // don't show the ID
	ui.tableViewConnection->setModel(CModel);
	ui.tableViewConnection->setColumnWidth (0, 50);
	ui.tableViewConnection->setColumnWidth (1, 80);
	ui.tableViewConnection->setColumnWidth (2, 140);
	ui.tableViewConnection->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableViewConnection->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableViewConnection->show();
	CModel->setHeaderData(0, Qt::Horizontal, "ID"	,Qt::DisplayRole);
	CModel->setHeaderData(1, Qt::Horizontal, "Time"	,Qt::DisplayRole);
	CModel->setHeaderData(2, Qt::Horizontal, "Name"	,Qt::DisplayRole);

	QSqlContentModel *SModel = new QSqlContentModel(this,*GetLayersBase()->GetDataBase());
	SModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	SModel->select();
	SModel->removeColumn(0); // don't show the ID
	ui.tableViewContents->setModel(SModel);
	ui.tableViewContents->setColumnWidth (0, 50);
	ui.tableViewContents->setColumnWidth (1, 80);
	ui.tableViewContents->setColumnWidth (2, 140);
	ui.tableViewContents->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableViewContents->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableViewContents->show();
	SModel->setHeaderData(0, Qt::Horizontal, "ID"	,Qt::DisplayRole);
	SModel->setHeaderData(1, Qt::Horizontal, "Time"	,Qt::DisplayRole);
	SModel->setHeaderData(2, Qt::Horizontal, "Name"	,Qt::DisplayRole);

	ui.lineEditHost			->setText(GetParamGlobal()->LocalDatabase_HostName);
	ui.lineEditDatabaseFile	->setText(GetParamGlobal()->LocalDatabase_FileName);
}

ManageMasterConnection::~ManageMasterConnection()
{

}


void ManageMasterConnection::on_pushButtonClose_clicked()
{
	close();
}
void	ManageMasterConnection::ShowListHeader(void)
{
	QSqlSelectMasterModel *MModel = new QSqlSelectMasterModel(this,*GetLayersBase()->GetDataBase());
	QString	MasterCodeStr	=tr("MasterCode");
	QString	RegTimeStr		=tr("RegTime");
	QString	NameStr			=tr("Name");
	QString	RemarkStr		=tr("Remark");
	switch(ListMode){
		case  _IDNormal:
			MasterCodeStr=MasterCodeStr+QString("Up");
			//ui.lineEditState->setText("MasterCode ->");
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+QString("Down");
			//ui.lineEditState->setText("MasterCode <-");
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+QString("Up");
			//ui.lineEditState->setText("RegTime ->");
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+QString("Down");
			//ui.lineEditState->setText("RegTime <-");
			break;
		case  _NameNormal:
			NameStr		=NameStr+QString("Up");
			//ui.lineEditState->setText("MasterName ->");
			break;
		case  _NameReverse:
			NameStr		=NameStr+QString("Down");
			//ui.lineEditState->setText("MasterName <-");
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
}


void	ManageMasterConnection::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlSelectMasterModel	*M=dynamic_cast<QSqlSelectMasterModel *>(ui.tableView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}

void	ManageMasterConnection::SelectView(void)
{
	QModelIndex Index=ui.tableView->currentIndex();

	QSqlSelectMasterModel	*M=dynamic_cast<QSqlSelectMasterModel	 *>(ui.tableView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		CurrentMasterCode=M->data(RIndex).toInt();
		ui.EditMasterCode->setText(QString::number(CurrentMasterCode));
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(CurrentMasterCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		if(query.next ()==false)
			return;

		QString	MasterName	=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
		QString	Remark		=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
		QByteArray	TopVArray=query.value(query.record().indexOf(/**/"TOPVIEW"	)).toByteArray();
		ui.EditMasterName->setText(MasterName);
		ui.EditRemark	 ->setText(Remark);
		QPixmap		TopView;
		TopView.loadFromData(TopVArray,/**/"PNG");
		ui.labelTopView->setPixmap(TopView);

		QString	E=QString(/**/"SELECT RELATIONCODE FROM MASTERDATA WHERE MASTERCODE=")+QString::number(CurrentMasterCode);
		QSqlQuery queryE(E ,GetLayersBase()->GetDatabase());
		if(queryE.next ()==false)
			return;
		if(queryE.value(queryE.record().indexOf(/**/"RELATIONCODE")).isNull()==false){
			RelationCode=queryE.value(queryE.record().indexOf(/**/"RELATIONCODE")).toInt();
		}
		else{
			RelationCode=-1;
		}
		CModel->select();
	}
}


void ManageMasterConnection::on_tableView_clicked(const QModelIndex &)
{
	SelectView();

	QSqlContentModel	*L=dynamic_cast<QSqlContentModel *>(ui.tableViewContents->model());
	L->select();
	ui.tableViewContents->show();
}

void ManageMasterConnection::on_tableViewConnection_clicked(const QModelIndex &)
{
	QModelIndex Index=ui.tableViewConnection->currentIndex();

	QSqlConnectionModel	*M=dynamic_cast<QSqlConnectionModel	 *>(ui.tableViewConnection->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		RelationCode=M->data(RIndex).toInt();
				
		QSqlContentModel	*L=dynamic_cast<QSqlContentModel *>(ui.tableViewContents->model());
		L->select();
		ui.tableViewContents->show();
	}
}

void ManageMasterConnection::on_tableViewConnection_doubleClicked(QModelIndex)
{
	on_pushButtonDeleteConnection_clicked();
}

void ManageMasterConnection::on_tableViewContents_doubleClicked(QModelIndex)
{
	QModelIndex Index=ui.tableViewContents->currentIndex();

	QSqlContentModel	*M=dynamic_cast<QSqlContentModel *>(ui.tableViewContents->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	iMasterCode=M->data(RIndex).toInt();

		if(QMessageBox::question(NULL,"Alarm"
			, "Pull out from connection?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
			QSqlQuery queryUpdate(*GetLayersBase()->GetDataBase());
			queryUpdate.prepare("UPDATE MASTERDATA "
								"SET RELATIONCODE=-1"
								", RELATIONID=0 "
								"WHERE MASTERCODE=:MASTERCODE;");

			queryUpdate.bindValue(0, iMasterCode);
			queryUpdate.exec();
		}
		QSqlContentModel	*L=dynamic_cast<QSqlContentModel *>(ui.tableViewContents->model());
		L->select();
		ui.tableViewContents->show();
	}
}

void ManageMasterConnection::on_pushButtonCreateNew_clicked()
{
	CreateNewRelation	D;
	if(D.exec()==(int)true){
		QString	S=QString("SELECT max(RELATIONCODE) FROM MASTERRELATION");
		QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
		int	RetRelationCode=1;
		if(query.next()==true){
			RetRelationCode=query.value(0).toInt()+1;
		}

		QSqlQuery queryInsrt(*GetLayersBase()->GetDataBase());
		queryInsrt.prepare("INSERT INTO MASTERRELATION(RELATIONCODE,REGTIME,RELATIONNAME,REMARK,VERSION,RELATIONTYPE) "
			"VALUES(:RELATIONCODE,:REGTIME,:RELATIONNAME,:REMARK,:VERSION,:RELATIONTYPE);");
		queryInsrt.bindValue(0	, RetRelationCode);
		queryInsrt.bindValue(1	, XDateTime::currentDateTime().GetQDateTime());
		queryInsrt.bindValue(2	, D.Name);
		queryInsrt.bindValue(3	, D.Remark);
		queryInsrt.bindValue(4	, (int)RegulusVersion);
		queryInsrt.bindValue(5	, D.RelationType);

		if(queryInsrt.exec()==false){
			QMessageBox Q("error"
					, "Not created new MasterRelation record", QMessageBox::Critical
					, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
		}
		RelationCode=-1;
		QSqlConnectionModel	*M=dynamic_cast<QSqlConnectionModel *>(ui.tableViewConnection->model());
		M->select();
		ui.tableViewConnection->show();

		QSqlContentModel	*L=dynamic_cast<QSqlContentModel *>(ui.tableViewContents->model());
		L->select();
		ui.tableViewContents->show();
	}
}

void ManageMasterConnection::on_pushButtonDeleteConnection_clicked()
{
	if(QMessageBox::question(NULL,"Alarm"
		, "Delete OK?",QMessageBox::Yes,QMessageBox::No)==QMessageBox::Yes){
		QSqlQuery queryDelete(*GetLayersBase()->GetDataBase());
		QString	S=QString("DELETE FROM MASTERRELATION "
							"WHERE RELATIONCODE=")+QString::number(RelationCode);
		queryDelete.prepare(S);
		queryDelete.exec();

		if(RelationCode>0){
			QSqlQuery queryUpdate(*GetLayersBase()->GetDataBase());
			queryUpdate.prepare("UPDATE MASTERDATA "
								"SET RELATIONCODE=-1"
								", RELATIONID=0 "
								"WHERE RELATIONCODE=:RELATIONCODE;");

			queryUpdate.bindValue(0, RelationCode);
			queryUpdate.exec();
		}
		RelationCode=-1;
		QSqlConnectionModel	*M=dynamic_cast<QSqlConnectionModel *>(ui.tableViewConnection->model());
		M->select();
		ui.tableViewConnection->show();

		QSqlContentModel	*L=dynamic_cast<QSqlContentModel *>(ui.tableViewContents->model());
		L->select();
		ui.tableViewContents->show();
	}
}

void ManageMasterConnection::on_pushButtonAddMaster_clicked()
{
	if(RelationCode>0 && CurrentMasterCode>0){
		QString	S=QString(/**/"SELECT MACHINEID FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(CurrentMasterCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		if(query.next ()==false)
			return;

		int	MachineID	=query.value(query.record().indexOf(/**/"MACHINEID")).toInt();

		QSqlQuery queryUpdate(*GetLayersBase()->GetDataBase());
		queryUpdate.prepare("UPDATE MASTERDATA "
							"SET RELATIONCODE=:RELATIONCODE"
							", RELATIONID=:RELATIONID "
							"WHERE MASTERCODE=:MASTERCODE");
		queryUpdate.bindValue(0, RelationCode);
		queryUpdate.bindValue(1, MachineID);
		queryUpdate.bindValue(2, CurrentMasterCode);
		queryUpdate.exec();
	
		QSqlContentModel	*L=dynamic_cast<QSqlContentModel *>(ui.tableViewContents->model());
		L->select();
		ui.tableViewContents->show();
	}
}