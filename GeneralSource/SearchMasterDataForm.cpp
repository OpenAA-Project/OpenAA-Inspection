#include "RepairStationResource.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QHeaderView>

#include "SearchMasterDataForm.h"
#include "RepairBase.h"

#include "PasswordEventOperator.h"

SearchMasterDataForm::SearchMasterDataForm(RepairBase *ParentClass,const QStringList &trMFieldNames,const QStringList &twMFieldNames,QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	PasswordEventOperator *peo = new PasswordEventOperator(this);
	peo->addButton(ui.pbCancel);
	peo->addButton(ui.pbReadMasterData);
	peo->addButton(ui.pbSearchByMasterID);
	peo->addButton(ui.pbSearchByMasterName);

	setWindowTitle(LangSolver.GetString(SearchMasterDataForm_LS,LID_890)/*"?}?X?^?[???o?a?E"*/);

	PClass		=ParentClass;
	MTFieldNames=trMFieldNames;
	MFieldNames	=twMFieldNames;

	IDOrder		=_IDNormal;
	NameOrder	=_NameNormal;
	TimeOrder	=_TimeNormal;
	RemarkOrder	=_RemarkNormal;

	CategoryID		=-1;
	StartSearchID	=0;

	//?}?X?^?[?c???[?\?|
	ui.trMasterList->setColumnCount(MTFieldNames.count());
	ui.trMasterList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.trMasterList->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.trMasterList->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.trMasterList->setHeaderLabels(MTFieldNames);
	ui.trMasterList->header()->setSectionResizeMode(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_812)/*"FOLDERNAME"*/),QHeaderView::Stretch);
	ui.trMasterList->hideColumn(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_813)/*"CATEGORYID"*/));

	//?}?X?^?[?e?[?u???\?|
	ui.twMasterList->setColumnCount(MFieldNames.count());
	ui.twMasterList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui.twMasterList->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.twMasterList->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.twMasterList->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.twMasterList->setHorizontalHeaderLabels(MFieldNames);
	ui.twMasterList->horizontalHeader()->setSectionResizeMode(MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_814)/*"MASTERNAME"*/),QHeaderView::Stretch);
	ui.twMasterList->horizontalHeader()->setSectionResizeMode(MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_815)/*"REMARK"*/),QHeaderView::Stretch);

	connect(ui.trMasterList,					SIGNAL(currentItemChanged(QTreeWidgetItem *,QTreeWidgetItem *)),this,SLOT(MasterTreeRowChanged(QTreeWidgetItem *)));
	connect(ui.twMasterList->selectionModel(),	SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),				this,SLOT(MasterListRowChanged(QModelIndex)));
	connect(ui.pbSearchByMasterID,				SIGNAL(clicked()),												this,SLOT(pbSearchByMasterIDClicked()));
	connect(ui.pbSearchByMasterName,			SIGNAL(clicked()),												this,SLOT(pbSearchByMasterNameClicked()));
	connect(ui.pbReadMasterData,				SIGNAL(clicked()),												this,SLOT(pbReadMasterDataClicked()));
	connect(ui.pbCancel,						SIGNAL(clicked()),												this,SLOT(pbCancelClicked()));
	connect(ui.twMasterList->horizontalHeader(),SIGNAL(sectionClicked(int)),									this,SLOT(MasterListsectionClicked(int)));

	//?}?X?^?[?c???[?I?\?|
	ShowMasterTree();

	//???u?t?H?[?J?X?i?I?d?j?I?Y?e
	if(ui.trMasterList->topLevelItemCount()>0){
		ui.trMasterList->setCurrentItem(ui.trMasterList->topLevelItem(0));
		ui.trMasterList->setFocus();
	}
	ui.trMasterList->expandItem(ui.trMasterList->currentItem());
	if(ui.twMasterList->rowCount()>0){
		ui.twMasterList->selectRow(0);
	}
//	ui.twMasterList->setSortingEnabled(true);
//	ui.twMasterList->sortItems(0,Qt::AscendingOrder);
}

SearchMasterDataForm::~SearchMasterDataForm()
{
}

void SearchMasterDataForm::MasterTreeRowChanged(QTreeWidgetItem *CIndex)
{
	//?}?X?^?[?e?[?u???E?f?[?^?d?Z?b?g
	disconnect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	ui.twMasterList->clearContents();
	ui.twMasterList->setRowCount(0);
	connect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	QSqlQuery query;
	if((CategoryID=CIndex->text(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_816)/*"CATEGORYID"*/)).toInt())==-1){
		query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA order by MASTERCODE");
	}
	else{
		query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID=? order by MASTERCODE");
		query.addBindValue(CategoryID);
	}
	query.exec();
	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui.twMasterList->columnCount();Col++){
			PClass->SetDataToTable(ui.twMasterList,Row,Col,query.value(query.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}
	if(ui.twMasterList->rowCount()>0){
		ui.twMasterList->selectRow(0);
	}
}

void SearchMasterDataForm::MasterListRowChanged(const QModelIndex &CIndex)
{
	ui.leMasterID		->setText(ui.twMasterList->item(CIndex.row(),MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_819)/*"MASTERCODE"*/))->text());
	ui.leMasterName		->setText(ui.twMasterList->item(CIndex.row(),MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_820)/*"MASTERNAME"*/))->text());
	ui.leMasterRemark	->setText(ui.twMasterList->item(CIndex.row(),MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_821)/*"REMARK"*/))->text());

	QSqlQuery query;
	query.prepare(LangSolver.GetString(SearchMasterDataForm_LS,LID_822)/*"select TOPVIEW from MASTERDATA where MASTERCODE=?"*/);
	query.addBindValue(ui.twMasterList->item(CIndex.row(),MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_823)/*"MASTERCODE"*/))->text());
	query.exec();
	if(query.next()==false){
		return;
	}

	//TOPVIEW?I?\?|
	if(!query.value(query.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_824)/*"TOPVIEW"*/)).isNull()){
//		QBuffer Buff(&query.value(query.record().indexOf("TOPVIEW")).toByteArray());
		QPixmap Pixmap;
		Pixmap.loadFromData(query.value(query.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_825)/*"TOPVIEW"*/)).toByteArray());
		ui.lbMasterImage->setPixmap(Pixmap);
	}
}

void SearchMasterDataForm::pbSearchByMasterIDClicked()
{
	//?}?X?^?[?e?[?u???E?f?[?^?d?Z?b?g
	disconnect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	ui.twMasterList->clearContents();
	ui.twMasterList->setRowCount(0);
	connect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	QSqlQuery query;
	if(CategoryID==-1){
		if(StartSearchName.isEmpty()==true){
			query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by MASTERCODE");
			StartSearchID=ui.sbSearchByMasterID->value();
			query.addBindValue(StartSearchID);
		}
		else{
			query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and MASTERNAME >= ? order by MASTERCODE");
			StartSearchID=ui.sbSearchByMasterID->value();
			query.addBindValue(StartSearchID);
			query.addBindValue(StartSearchName);
		}
	}
	else{
		if(StartSearchName.isEmpty()==true){
			query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and CATEGORYID = ? order by MASTERCODE");
			StartSearchID=ui.sbSearchByMasterID->value();
			query.addBindValue(StartSearchID);
			query.addBindValue(CategoryID);
		}
		else{
			query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and CATEGORYID = ? and MASTERNAME >= ? order by MASTERCODE");
			StartSearchID=ui.sbSearchByMasterID->value();
			query.addBindValue(StartSearchID);
			query.addBindValue(CategoryID);
			query.addBindValue(StartSearchName);
		}
	}
	query.exec();
	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui.twMasterList->columnCount();Col++){
			PClass->SetDataToTable(ui.twMasterList,Row,Col,query.value(query.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}
	if(ui.twMasterList->rowCount()>0){
		ui.twMasterList->selectRow(0);
	}
}

void SearchMasterDataForm::pbSearchByMasterNameClicked()
{
	//?}?X?^?[?e?[?u???E?f?[?^?d?Z?b?g
	disconnect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	ui.twMasterList->clearContents();
	ui.twMasterList->setRowCount(0);
	connect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	QSqlQuery query;
//	query.prepare("select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERNAME LIKE ? order by MASTERCODE");
//	QString StartSearchName;
//	StartSearchName="%" + ui.leSearchByMasterName->text() + "%";
	if(CategoryID==-1){
		query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERNAME >= ? and MASTERCODE >= ? order by MASTERNAME");
		StartSearchName=ui.leSearchByMasterName->text();
		query.addBindValue(StartSearchName);
		query.addBindValue(StartSearchID);
	}
	else{
		query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERNAME >= ? and CATEGORYID = ? and MASTERCODE >= ? order by MASTERNAME");
		StartSearchName=ui.leSearchByMasterName->text();
		query.addBindValue(StartSearchName);
		query.addBindValue(CategoryID);
		query.addBindValue(StartSearchID);
	}
	query.exec();
	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui.twMasterList->columnCount();Col++){
			PClass->SetDataToTable(ui.twMasterList,Row,Col,query.value(query.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}
	if(ui.twMasterList->rowCount()>0){
		ui.twMasterList->selectRow(0);
	}
}

void SearchMasterDataForm::pbReadMasterDataClicked()
{
	MasterCode=ui.twMasterList->item(ui.twMasterList->currentIndex().row(),MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_832)/*"MASTERCODE"*/))->text();

	accept();
}

void SearchMasterDataForm::pbCancelClicked()
{
	reject();
}

void SearchMasterDataForm::MasterListsectionClicked(int logicalIndex)
{
	QSqlQuery query;
	if(logicalIndex==MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_833)/*"MASTERCODE"*/)){
		if(IDOrder==_IDNormal){
			IDOrder=_IDReverse;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by MASTERCODE DESC");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and MASTERNAME >= ? order by MASTERCODE DESC");
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and CATEGORYID = ? order by MASTERCODE DESC");
					query.addBindValue(StartSearchID);
					query.addBindValue(CategoryID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and CATEGORYID = ? and MASTERNAME >= ? order by MASTERCODE DESC");
					query.addBindValue(StartSearchID);
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchName);
				}
			}
		}
		else if(IDOrder==_IDReverse){
			IDOrder=_IDNormal;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by MASTERCODE");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and MASTERNAME >= ? order by MASTERCODE");
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and CATEGORYID = ? order by MASTERCODE");
					query.addBindValue(StartSearchID);
					query.addBindValue(CategoryID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and CATEGORYID = ? and MASTERNAME >= ? order by MASTERCODE");
					query.addBindValue(StartSearchID);
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchName);
				}
			}
		}
	}
	else if(logicalIndex==MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_842)/*"MASTERNAME"*/)){
		if(NameOrder==_NameNormal){
			NameOrder=_NameReverse;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by MASTERNAME DESC");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERNAME >= ? and MASTERCODE >= ? order by MASTERNAME DESC");
					query.addBindValue(StartSearchName);
					query.addBindValue(StartSearchID);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? order by MASTERNAME DESC");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERNAME >= ? and CATEGORYID = ? and MASTERCODE >= ? order by MASTERNAME DESC");
					query.addBindValue(StartSearchName);
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
			}
		}
		else if(NameOrder==_NameReverse){
			NameOrder=_NameNormal;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by MASTERNAME");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERNAME >= ? and MASTERCODE >= ? order by MASTERNAME");
					query.addBindValue(StartSearchName);
					query.addBindValue(StartSearchID);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? order by MASTERNAME");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERNAME >= ? and CATEGORYID = ? and MASTERCODE >= ? order by MASTERNAME");
					query.addBindValue(StartSearchName);
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
			}
		}
	}
	else if(logicalIndex==MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_851)/*"REGTIME"*/)){
		if(TimeOrder==_TimeNormal){
			TimeOrder=_TimeReverse;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by REGTIME DESC");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and MASTERNAME >= ? order by REGTIME DESC");
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? order by REGTIME DESC");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? and MASTERNAME >= ? order by REGTIME DESC");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
		}
		else if(TimeOrder==_TimeReverse){
			TimeOrder=_TimeNormal;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by REGTIME");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and MASTERNAME >= ? order by REGTIME");
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? order by REGTIME");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? and MASTERNAME >= ? order by REGTIME");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
		}
	}
	else if(logicalIndex==MFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_860)/*"REMARK"*/)){
		if(RemarkOrder==_RemarkNormal){
			RemarkOrder=_RemarkReverse;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by REMARK DESC");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and MASTERNAME >= ? order by REMARK DESC");
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? order by REMARK DESC");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? and MASTERNAME >= ? order by REMARK DESC");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
		}
		else if(RemarkOrder==_RemarkReverse){
			RemarkOrder=_RemarkNormal;
			if(CategoryID==-1){
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? order by REMARK");
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where MASTERCODE >= ? and MASTERNAME >= ? order by REMARK");
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
			else{
				if(StartSearchName.isEmpty()==true){
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? order by REMARK");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
				}
				else{
					query.prepare(/**/"select MASTERCODE,MASTERNAME,REGTIME,REMARK,MACHINEID from MASTERDATA where CATEGORYID = ? and MASTERCODE >= ? and MASTERNAME >= ? order by REMARK");
					query.addBindValue(CategoryID);
					query.addBindValue(StartSearchID);
					query.addBindValue(StartSearchName);
				}
			}
		}
	}
	else{
		return;
	}

	//?}?X?^?[?e?[?u???E?f?[?^?d?Z?b?g
	disconnect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));
	ui.twMasterList->clearContents();
	ui.twMasterList->setRowCount(0);
	connect(ui.twMasterList->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(MasterListRowChanged(QModelIndex)));

	query.exec();

	int Row=0;
	int NumRowsAffected;
	while(query.next()){
		if(Row==0){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		if(Row>=NumRowsAffected){
			NumRowsAffected=query.numRowsAffected();
			ui.twMasterList->setRowCount(NumRowsAffected);
		}
		for(int Col=0;Col<ui.twMasterList->columnCount();Col++){
			PClass->SetDataToTable(ui.twMasterList,Row,Col,query.value(query.record().indexOf(MFieldNames.at(Col))));
		}
		Row++;
	}
	if(ui.twMasterList->rowCount()>0){
		ui.twMasterList->selectRow(0);
	}
}

int SearchMasterDataForm::ShowMasterTree(bool UpdatesEnabled)
{
	disconnect(ui.trMasterList,	SIGNAL(currentItemChanged(QTreeWidgetItem *,QTreeWidgetItem *)),this,SLOT(MasterTreeRowChanged(QTreeWidgetItem *)));
	ui.trMasterList->clear();
	connect(ui.trMasterList,	SIGNAL(currentItemChanged(QTreeWidgetItem *,QTreeWidgetItem *)),this,SLOT(MasterTreeRowChanged(QTreeWidgetItem *)));
	ui.trMasterList->setUpdatesEnabled(UpdatesEnabled);

	QSqlQuery MainQuery(LangSolver.GetString(SearchMasterDataForm_LS,LID_869)/*"select FOLDERNAME,REMARK,CATEGORYID from MASTERCATEGORY where PARENTID=0 order by CATEGORYID"*/);
	int Row=0;
	QTreeWidgetItem *RootItem;
	RootItem=new QTreeWidgetItem();
	RootItem->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_870)/*"FOLDERNAME"*/),LangSolver.GetString(SearchMasterDataForm_LS,LID_871)/*"Root"*/);
	RootItem->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_872)/*"CATEGORYID"*/),QString::number(-1));
	ui.trMasterList->addTopLevelItem(RootItem);
	while(MainQuery.next()){
		QTreeWidgetItem *Item=new QTreeWidgetItem();
		Item->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_873)/*"FOLDERNAME"*/),MainQuery.value(MainQuery.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_874)/*"FOLDERNAME"*/)).toString());
		Item->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_875)/*"REMARK"*/),MainQuery.value(MainQuery.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_876)/*"REMARK"*/)).toString());
		Item->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_877)/*"CATEGORYID"*/),MainQuery.value(MainQuery.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_878)/*"CATEGORYID"*/)).toString());
		RootItem->addChild(Item);
		AddChildTree(Item,&MainQuery.value(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_879)/*"CATEGORYID"*/)));
		Row++;
	}
	return Row;
}

void SearchMasterDataForm::AddChildTree(QTreeWidgetItem *ParentItem,QVariant *value)
{
	QSqlQuery SubQuery;
	SubQuery.prepare(LangSolver.GetString(SearchMasterDataForm_LS,LID_880)/*"select FOLDERNAME,REMARK,CATEGORYID from MASTERCATEGORY where PARENTID=? order by CATEGORYID"*/);
	SubQuery.addBindValue(*value);
	SubQuery.exec();
	while(SubQuery.next()){
		QTreeWidgetItem *item=new QTreeWidgetItem();
		item->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_881)/*"FOLDERNAME"*/),SubQuery.value(SubQuery.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_882)/*"FOLDERNAME"*/)).toString());
		item->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_883)/*"REMARK"*/),SubQuery.value(SubQuery.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_884)/*"REMARK"*/)).toString());
		item->setText(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_885)/*"CATEGORYID"*/),SubQuery.value(SubQuery.record().indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_886)/*"CATEGORYID"*/)).toString());
		ParentItem->addChild(item);
		AddChildTree(item,&SubQuery.value(MTFieldNames.indexOf(LangSolver.GetString(SearchMasterDataForm_LS,LID_887)/*"CATEGORYID"*/)));
	}
}
