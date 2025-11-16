#include "EditGlobalOnMasterResource.h"
#include "EditGlobalOnMaster.h"
#include "XFileRegistry.h"
#include <QSqlDatabase>
#include <QHeaderView>

#include "XGUI.h"
#include <stdio.h>
#include "XDatabase.h"
#include "XGeneralDialog.h"
#include "hasplib.h"
#include "Regulus64Version.h"
#include "XParamGlobal.h"
#include "XDatabase.h"
#include "EditParamDialog.h"

LocalDatabaseBasicClass	*KDatabase;
static	int	CategoryID;

//===========================================================================

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<EditGlobalOnMaster *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
{
	QString	ret;

	switch(ParentWindow->ListMode){
		case EditGlobalOnMaster::_IDNormal:
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
		case EditGlobalOnMaster::_IDReverse:
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
		case EditGlobalOnMaster::_TimeNormal:
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
		case EditGlobalOnMaster::_TimeReverse:
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
		case EditGlobalOnMaster::_NameNormal:
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
		case EditGlobalOnMaster::_NameReverse:
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
		case EditGlobalOnMaster::_LastEditNormal:
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
		case EditGlobalOnMaster::_LastEditReverse:
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

EditGlobalOnMaster::EditGlobalOnMaster(ParamGlobal *GlobalParam ,LayersBase *Base ,QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags),ServiceForLayers(Base)
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
}

EditGlobalOnMaster::~EditGlobalOnMaster()
{

}

void EditGlobalOnMaster::on_pushButtonOpenDatabase_clicked()
{
	QString	Msg;

	if(KDatabase==NULL){
		GetLayersBase()->InitialDatabaseLoader(Msg);
	}

	if(KDatabase==NULL || KDatabase->IsExistDatabase()==false){
		LayersBase	*LBase=GetLayersBase();
		KDatabase=new LocalDatabaseBasicClass(LBase->GetDatabaseLoader(false)
											,ui.lineEditDBFileName	->text()
											,ui.lineEditHostName	->text()
											,ui.spinBoxPortNo		->value()
											,/**/"",0);
	
		if(KDatabase->IsExistDatabase()==false){
			return;
		}
		if(LBase->OpenDatabase(*KDatabase)==false){
			QMessageBox::critical(NULL
						, /**/"Error"
						, /**/"Could not open database"
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			return;
		}
		LBase->LoadLevelFolderContainerFromDB();
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

	GetLayersBase()->CloseInformed();
}

void	EditGlobalOnMaster::RefreshGrid(void)
{
	if(MListView!=NULL){
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

void	EditGlobalOnMaster::ShowListHeader(void)
{
	//QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	QSqlLoadMasterModel *MModel = (QSqlLoadMasterModel*)(MListView->model());
	QString	MasterCodeStr	=LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_0)/*"MasterCode"*/;
	QString	MachineNameStr	=LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_1)/*"MachineID"*/;
	QString	RegTimeStr		=LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_2)/*"RegTime"*/;
	QString	LastEditStr		=LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_3)/*"Last Edit"*/;
	QString	NameStr			=LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_4)/*"Name"*/;
	QString	RemarkStr		=LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_5)/*"Remark"*/;
	switch(ListMode){
		case  _IDNormal:
			MasterCodeStr=MasterCodeStr+LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_6)/*"Up"*/;
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_7)/*"MasterCode ->"*/);
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_8)/*"Down"*/;
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_9)/*"MasterCode <-"*/);
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_10)/*"Up"*/;
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_11)/*"RegTime ->"*/);
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_12)/*"Down"*/;
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_13)/*"RegTime <-"*/);
			break;
		case  _NameNormal:
			NameStr		=NameStr+LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_14)/*"Up"*/;
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_15)/*"MasterName ->"*/);
			break;
		case  _NameReverse:
			NameStr		=NameStr+LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_16)/*"Down"*/;
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_17)/*"MasterName <-"*/);
			break;
		case  _LastEditNormal:
			LastEditStr	=LastEditStr+QString(/**/"Up");
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_18)/*"LastEdit ->"*/);
			break;
		case  _LastEditReverse:
			LastEditStr	=LastEditStr+QString(/**/"Down");
			ui.lineEditState->setText(LangEPSolver.GetString(EditGlobalOnMaster_LS,LID_19)/*"LastEdit <-"*/);
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, MachineNameStr	,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, LastEditStr	,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(5, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
}

void	EditGlobalOnMaster::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}


void	EditGlobalOnMaster::SlotClicked(const QModelIndex &)
{
	SelectView();
}

void	EditGlobalOnMaster::SlotDoubleClicked(const QModelIndex &)
{
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();
		EditParamDialog		D(MasterCode,GetLayersBase());
		D.exec();
	}
}

void	EditGlobalOnMaster::SelectView(void)
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

void	EditGlobalOnMaster::MListSectionClicked ( int logicalIndex )
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

void EditGlobalOnMaster::on_pushButtonStartSearchByID_clicked()
{
	StartSearchID=ui.spinBoxSearchID->value();
	ListMode=_IDNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void EditGlobalOnMaster::on_pushButtonStartSearchByName_clicked()
{
	StartSearchName=ui.lineEditSearchName->text();
	ListMode=_NameNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void EditGlobalOnMaster::on_pushButtonClose_clicked()
{
	close();
}
