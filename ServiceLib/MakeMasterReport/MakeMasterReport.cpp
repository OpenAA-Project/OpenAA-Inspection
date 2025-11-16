#include "MakeMasterReport.h"
#include "XFileRegistry.h"
#include <QSqlDatabase>

#include "XGUI.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "hasplib.h"
#include "Regulus64Version.h"
#include "XParamGlobal.h"
#include "XDatabase.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "XGeneralFunc.h"
#include "ShowExecutingDialog.h"
#include "Regulus64System.h"

LocalDatabaseBasicClass	*KDatabase;
static	int	CategoryID;

//===========================================================================
class	QSqlLoadMasterModel : public QSqlTableModel
{
	MakeMasterReport	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;

};

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<MakeMasterReport *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
{
	QString	ret;

	switch(ParentWindow->ListMode){
		case MakeMasterReport::_IDNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+QString(/**/" ORDER BY MASTERCODE;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+QString(/**/" AND CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY MASTERCODE;");
			}
			break;
		case MakeMasterReport::_IDReverse:
			if(ParentWindow->StartSearchID!=0){
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERCODE")
						+QString(/**/",MACHINEID")
						+QString(/**/",REGTIME")
						+QString(/**/",LASTEDITTIME")
						+QString(/**/",MASTERNAME")
						+QString(/**/",REMARK")
						+QString(/**/" FROM MASTERDATA WHERE MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERCODE")
						+QString(/**/",MACHINEID")
						+QString(/**/",REGTIME")
						+QString(/**/",LASTEDITTIME")
						+QString(/**/",MASTERNAME")
						+QString(/**/",REMARK")
						+QString(/**/" FROM MASTERDATA WHERE MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+QString(/**/" AND CATEGORYID=")
						+QString::number(CategoryID)
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
			}
			else{
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERCODE")
						+QString(/**/",MACHINEID")
						+QString(/**/",REGTIME")
						+QString(/**/",LASTEDITTIME")
						+QString(/**/",MASTERNAME")
						+QString(/**/",REMARK")
						+QString(/**/" FROM MASTERDATA")
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERCODE")
						+QString(/**/",MACHINEID")
						+QString(/**/",REGTIME")
						+QString(/**/",LASTEDITTIME")
						+QString(/**/",MASTERNAME")
						+QString(/**/",REMARK")
						+QString(/**/" FROM MASTERDATA")
						+QString(/**/" WHERE CATEGORYID=")
						+QString::number(CategoryID)
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
			}
			break;
		case MakeMasterReport::_TimeNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA")
					+QString(/**/" ORDER BY REGTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY REGTIME;");
			}
			break;
		case MakeMasterReport::_TimeReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA")
					+QString(/**/" ORDER BY REGTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY REGTIME DESC;");
			}
			break;
		case MakeMasterReport::_NameNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+QString(/**/" ORDER BY MASTERNAME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+QString(/**/" ORDER BY MASTERNAME;");
			}
			break;
		case MakeMasterReport::_NameReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+QString(/**/" ORDER BY MASTERNAME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+QString(/**/" ORDER BY MASTERNAME DESC;");
			}
			break;
		case MakeMasterReport::_LastEditNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA")
					+QString(/**/" ORDER BY LASTEDITTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY LASTEDITTIME;");
			}
			break;
		case MakeMasterReport::_LastEditReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA")
					+QString(/**/" ORDER BY LASTEDITTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE")
					+QString(/**/",MACHINEID")
					+QString(/**/",REGTIME")
					+QString(/**/",LASTEDITTIME")
					+QString(/**/",MASTERNAME")
					+QString(/**/",REMARK")
					+QString(/**/" FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY LASTEDITTIME DESC;");
			}
			break;
	}
	return ret;
}

//===========================================================================

MakeMasterReport::MakeMasterReport(ParamGlobal *_GlobalParam ,LayersBase *Base ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(Base)
	,GlobalParam(_GlobalParam)
{
	ui.setupUi(this);

	ui.lineEditHostName		->setText	(GlobalParam->LocalDatabase_HostName);
	ui.spinBoxPortNo		->setValue	(GlobalParam->LocalDatabase_Port);
	ui.lineEditDBFileName	->setText	(GlobalParam->LocalDatabase_FileName);

	ui.frameMasterData->setEnabled(false);

	MListView=NULL;
	ListMode=_NameNormal;
	StartSearchID=0;
	SelectedMasterCode	=-1;

	CategoryID=-1;
	//MasterCategory=new MasterCategoryForm(GetLayersBase(),ui->frameCategory);
	QGridLayout *glayout = new QGridLayout;
	MasterCategory = new MasterCategoryForm(GetLayersBase(), NULL);
	glayout->addWidget(MasterCategory, 0, 0);
	ui.frameCategory->setLayout(glayout);
	
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	ui.tableWidgetAlgorithm->setColumnWidth(0,80);
	ui.tableWidgetAlgorithm->setColumnWidth(1,120);
	ui.tableWidgetAlgorithm->setColumnWidth(2,200);
}

MakeMasterReport::~MakeMasterReport()
{

}

void MakeMasterReport::on_pushButtonOpenDatabase_clicked()
{
	QString	Msg;

	if(KDatabase==NULL){
		GetLayersBase()->InitialDatabaseLoader(Msg);
	}

	if(KDatabase==NULL || KDatabase->IsExistDatabase()==false){

		KDatabase=new LocalDatabaseBasicClass(GetLayersBase()->GetDatabaseLoader()
											,ui.lineEditDBFileName	->text()
											,ui.lineEditHostName	->text()
											,ui.spinBoxPortNo		->value()
											,/**/"",0);
	
		if(KDatabase->IsExistDatabase()==false){
			return;
		}
		if(GetLayersBase()->OpenDatabase(*KDatabase)==false){
			QMessageBox::critical(NULL
						, "Error"
						, "Could not open database"
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			return;
		}
		GetLayersBase()->LoadLevelFolderContainerFromDB();
	}
	ui.frameDatabase	->setEnabled(false);
	ui.frameMasterData	->setEnabled(true);

	MasterCategory->ShowAllNodes();

	QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	//MListView = new QTableView(ui->frameGrid);
	MListView = new QTableView(NULL);
	MListView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	MListView->horizontalHeader()->setStretchLastSection(true);
	QGridLayout *glayout = new QGridLayout;
	glayout->addWidget(MListView);
	ui.frameGrid->setLayout(glayout);
	MListView->setModel(MModel);
	MListView->setObjectName(/**/"MListView");
	MListView->move(0,0);
	MListView->resize(ui.frameGrid->width(),ui.frameGrid->height());
	MListView->setColumnWidth (0, 90);
	MListView->setColumnWidth (1, 100);
	MListView->setColumnWidth (2, 120);
	MListView->setColumnWidth (3, 120);
	MListView->setColumnWidth (4, 220);
	MListView->setColumnWidth (5, 160);
	MListView->setSelectionMode(QAbstractItemView::SingleSelection);
	MListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	MListView->setObjectName(/**/"SelectMasterDataListView");
	MListView->show();
	connect(MListView ,SIGNAL(clicked		(const QModelIndex &)),this,SLOT(SlotClicked(const QModelIndex &)));
	connect(MListView ,SIGNAL(doubleClicked	(const QModelIndex &)),this,SLOT(SlotDoubleClicked(const QModelIndex &)));
	
	ShowListHeader();
	connect(MListView->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));


	RootNameListContainer	AlgorithmRootNameList;
	QStringList	AlgorithmPathList;
	AlgorithmPathList<<DefAlgorithmPath;
	AlgorithmPathList<<DefRegulusWorldAlgorithmPath;
	GetLayersBase()->InitialAlgorithm(AlgorithmRootNameList,AlgorithmPathList,true);
	//GetLayersBase()->InitialAllocExecuterDim();
	//GetLayersBase()->InitialResult();

	ui.tableWidgetAlgorithm->setRowCount(GetLayersBase()->GetAlgoDLLContPointer()->GetCount());
	int	Row=0;
	for(AlgorithmDLLList *L=GetLayersBase()->GetAlgoDLLContPointer()->GetFirst();L!=NULL;L=L->GetNext(),Row++){
		QString Root ,Name;
		L->GetName(Root ,Name);
		::SetDataToTable(ui.tableWidgetAlgorithm ,0,Row ,Root);
		::SetDataToTable(ui.tableWidgetAlgorithm ,1,Row ,Name);
		const	QString	s=L->GetExplain();
		if(s.isEmpty()==false){
			::SetDataToTable(ui.tableWidgetAlgorithm ,2,Row ,s);
		}
		else{
			::SetDataToTable(ui.tableWidgetAlgorithm ,2,Row ,/**/"");
		}
	}
	GetLayersBase()->CloseInformed();
	GetLayersBase()->InitialAlgorithmLibrary();
}

void	MakeMasterReport::RefreshGrid(void)
{
	if(MListView!=NULL){
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

void	MakeMasterReport::ShowListHeader(void)
{
	//QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	QSqlLoadMasterModel *MModel = (QSqlLoadMasterModel*)(MListView->model());
	QString	MasterCodeStr	=tr("MasterCode");
	QString	MachineNameStr	=tr("MachineID");
	QString	RegTimeStr		=tr("RegTime");
	QString	LastEditStr		=tr("Last Edit");
	QString	NameStr			=tr("Name");
	QString	RemarkStr		=tr("Remark");
	switch(ListMode){
		case  _IDNormal:
			MasterCodeStr=MasterCodeStr+QString("Up");
			ui.lineEditState->setText("MasterCode ->");
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+QString("Down");
			ui.lineEditState->setText("MasterCode <-");
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+QString("Up");
			ui.lineEditState->setText("RegTime ->");
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+QString("Down");
			ui.lineEditState->setText("RegTime <-");
			break;
		case  _NameNormal:
			NameStr		=NameStr+QString("Up");
			ui.lineEditState->setText("MasterName ->");
			break;
		case  _NameReverse:
			NameStr		=NameStr+QString("Down");
			ui.lineEditState->setText("MasterName <-");
			break;
		case  _LastEditNormal:
			LastEditStr	=LastEditStr+QString(/**/"Up");
			ui.lineEditState->setText("LastEdit ->");
			break;
		case  _LastEditReverse:
			LastEditStr	=LastEditStr+QString(/**/"Down");
			ui.lineEditState->setText("LastEdit <-");
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, MachineNameStr	,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, LastEditStr	,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(5, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
}

void	MakeMasterReport::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}


void	MakeMasterReport::SlotClicked(const QModelIndex &)
{
	SelectView();
}

void	MakeMasterReport::SlotDoubleClicked(const QModelIndex &)
{
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();
		
		ShowExecutingDialog	D(MasterCode,GlobalParam,GetLayersBase());
		D.exec();
	}
}



void	MakeMasterReport::SelectView(void)
{
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(MasterCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		if(query.next ()==false)
			return;

		QByteArray	TopVArray=query.value(query.record().indexOf(/**/"TOPVIEW"	)).toByteArray();
		QPixmap		TopView;
		TopView.loadFromData(TopVArray,/**/"PNG");
		ui.labelTopView->setPixmap(TopView);
	}
}

void	MakeMasterReport::MListSectionClicked ( int logicalIndex )
{
	switch(logicalIndex){
		case 0:
			if(ListMode==_IDNormal)
				ListMode=_IDReverse;
			else if(ListMode==_IDReverse)
				ListMode=_IDNormal;
			else
				ListMode=_IDNormal;
			break;
		case 2:
			if(ListMode==_TimeNormal)
				ListMode=_TimeReverse;
			else if(ListMode==_TimeReverse)
				ListMode=_TimeNormal;
			else
				ListMode=_TimeNormal;
			break;
		case 3:
			if(ListMode==_LastEditNormal)
				ListMode=_LastEditReverse;
			else if(ListMode==_LastEditReverse)
				ListMode=_LastEditNormal;
			else
				ListMode=_LastEditNormal;
			break;
		case 4:
			if(ListMode==_NameNormal)
				ListMode=_NameReverse;
			else if(ListMode==_NameReverse)
				ListMode=_NameNormal;
			else
				ListMode=_NameNormal;
			break;
	}
	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void MakeMasterReport::on_pushButtonStartSearchByID_clicked()
{
	StartSearchID=ui.spinBoxSearchID->value();
	ListMode=_IDNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void MakeMasterReport::on_pushButtonStartSearchByName_clicked()
{
	StartSearchName=ui.lineEditSearchName->text();
	ListMode=_NameNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void MakeMasterReport::on_pushButtonClose_clicked()
{
	close();
}

void MakeMasterReport::on_pushButtonSelect_clicked()
{
	QModelIndex	Dummy;
	SlotDoubleClicked(Dummy);
}
