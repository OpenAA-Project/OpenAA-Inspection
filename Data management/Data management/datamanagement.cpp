/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Data management\Data management\datamanagement.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "datamanagementResource.h"
#include "datamanagement.h"
#include "setting.h"
#include "progressbar.h"
#include "restorepath.h"
#include <QtSql>
#include <QtGui>
#include <QFileDialog>
#include <QPixmap>
#include "connection.h"
#include "swap.h"

extern QStringList MPathList;
extern bool quit;


Datamanagement::Datamanagement(QWidget *parent, Qt::WindowFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);
	ui.pbInsert->setVisible(false);

	QSqlDatabase::database().transaction();

	Pdialog = new Progressbar();
	MasterUI	*pMasterUI		= new MasterUI (this);
	MachineUI	*pMacUI			= new MachineUI(this);
	WorkerUI	*pWorkUI		= new WorkerUI (this);
	LibUI		*pLibUI			= new LibUI	   (this);
	RelationUI	*pRelationUI	= new RelationUI(this);
	UIList << pRelationUI << pMasterUI << pMacUI << pWorkUI << pLibUI;
	Gui = UIList.at(0);
}

Datamanagement::~Datamanagement()
{
	QSqlDatabase::database().commit();
	delete Pdialog;
	qDeleteAll(UIList);
}
void Datamanagement::on_pbInsert_clicked()
{
	if(QMessageBox::information(this, /**/"Insert",LangSolver.GetString(datamanagement_LS,LID_6)/*"Insert OK?"*/,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
		return;
	Gui->Insert();
}

void Datamanagement::on_pbUpdate_clicked()
{
	if(QMessageBox::information(this,/**/"UpDate",LangSolver.GetString(datamanagement_LS,LID_7)/*"UpDate OK?"*/,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
		return;
	Gui->Update();
}

void Datamanagement::on_pbDelete_clicked()
{
	 Gui->Delete();
}

void Datamanagement::on_pbBackup_clicked()
{
	 Gui->Backup();
}
void Datamanagement::on_pbRestore_clicked()
{
	 Gui->Restore();
}
void Datamanagement::on_pbSET_clicked()
{
	quit=false;
	Setting *dialog=new Setting;
	dialog->show();
	dialog->exec();
	if(quit==false){
		close();
	}
}
void Datamanagement::on_pbEND_clicked()
{
	quit=true;
	close();
}
void Datamanagement::saveRelatedMastercode(QIODevice &file,QString &MasterCode){
	UIList[3]->saveRelatedMastercode(file,MasterCode);
}
void Datamanagement::loadRelatedMastercode(QIODevice &file){
	UIList[3]->loadRelatedMastercode(file);
}
void Datamanagement::on_tabWidget_currentChanged(int index)
{
	Gui = UIList.at(index);
	Gui->changeUI();
}
//====================================================
UIBase::UIBase(Datamanagement *parent){
	this->parent = parent;
	this->ui	 = parent->getUI();
}
bool UIBase::message(const QString &type){
	if(type==/**/"DELETE"){
		if(QMessageBox::information(0,/**/"Delete",LangSolver.GetString(datamanagement_LS,LID_8)/*"Delete OK?"*/,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
			return false;
	}else if(type==/**/"FolderDelete"){
		if(QMessageBox::information(0,/**/"FolderDelete",LangSolver.GetString(datamanagement_LS,LID_9)/*"Do you want to delete all data in this folder?"*/,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
			return false;
	}else if(type==/**/"NOSELE"){
		QMessageBox::information(0, /**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_10)/*"Data Not Select"*/);
		return false;
	}else if(type==/**/"MACHINEID"){
		QMessageBox::warning(0,/**/"Warning",LangSolver.GetString(datamanagement_LS,LID_11)/*"The MACHINEID has already existed."*/,QMessageBox::Close);
		return false;
	}else if(type==/**/"WORKERID"){
		QMessageBox::warning(0,/**/"Warning",LangSolver.GetString(datamanagement_LS,LID_12)/*"The WORKERID has already existed."*/,QMessageBox::Close);
		return false;
	}else if(type==/**/"MachineDelete"){
		QMessageBox::warning(0,/**/"Warning",LangSolver.GetString(datamanagement_LS,LID_13)/*"The MACHINEID don't exist."*/,QMessageBox::Close);
		return false;
	}else if(type==/**/"WorkerDelete"){
		QMessageBox::warning(0,/**/"Warning",LangSolver.GetString(datamanagement_LS,LID_14)/*"The WORKERID don't exist."*/,QMessageBox::Close);
		return false;
	}
	return true;
}
//----------------------------------------------------

QSqlRelationModel::QSqlRelationModel(QObject * parent)
:QSqlTableModel(parent)
{
	ParentWindow	=dynamic_cast<RelationUI *>(parent);
}
QString QSqlRelationModel::selectStatement () const
{
	QString	ret;

	if(ParentWindow->OrderMode==0){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
				+QString(/**/" ORDER BY RELATIONCODE;");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
				+QString(/**/" ORDER BY RELATIONCODE DESC;");
		}
	}
	else
	if(ParentWindow->OrderMode==1){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
				+QString(/**/" ORDER BY REGTIME;");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
				+QString(/**/" ORDER BY REGTIME DESC;");
		}
	}
	else
	if(ParentWindow->OrderMode==2){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNUMBER");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNUMBER DESC");
		}
	}
	else
	if(ParentWindow->OrderMode==3){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNAME");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNAME DESC");
		}
	}
	else
	if(ParentWindow->OrderMode==4){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
				+QString(/**/" ORDER BY REMARK;");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
				+QString(/**/" ORDER BY REMARK DESC;");
		}
	}

	return ret;
}

RelationUI::RelationUI(Datamanagement *parent) : UIBase(parent)
{
	Master		= new MasterData(parent);
	Page		= new MasterPage(parent);
	Image		= new MasterImage(parent);

	OrderMode=0;
	AcsendantOrder=true;


	QSqlRelationModel *MModel = new QSqlRelationModel(this);
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	ui->tableView->setModel(MModel);
	ui->tableView->setColumnWidth (0, 90);
	ui->tableView->setColumnWidth (1, 120);
	ui->tableView->setColumnWidth (2, 200);
	ui->tableView->setColumnWidth (3, 200);	

	QString	MasterCodeStr	=tr("MasterCode");
	QString	RegTimeStr		=tr("RegTime");
	QString	NumberStr		=tr("Number");
	QString	NameStr			=tr("Name");
	QString	RemarkStr		=tr("Remark");

	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, NumberStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);

	connect(ui->tableView->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	ResultRelationCode=-1;
}
void	RelationUI::view()
{
}
void	RelationUI::clear()
{
}
void	RelationUI::changeUI()
{
}
void	RelationUI::Update()
{
	QSqlQuery queryUpdate;
	QString	QStr="UPDATE MASTERRELATION "
				 "SET RELATIONNAME=:IN_RELATIONNAME"
				 ",RELATIONNUMBER=:IN_RELATIONNUMBER"
				 ",REMARK=:IN_REMARK";
	QStr=QStr + " where RELATIONCODE=:IN_RELATIONCODE;";

	queryUpdate.prepare(QStr);
	queryUpdate.bindValue(0	, ui->leRELATIONNAME->text());
	queryUpdate.bindValue(1	, ui->leRELATIONNUMBER->text());
	queryUpdate.bindValue(2	, ui->leREMARK->text());
	queryUpdate.bindValue(3	, ResultRelationCode);
		
	queryUpdate.exec();

	QSqlRelationModel	*M=dynamic_cast<QSqlRelationModel	 *>(ui->tableView->model());
	if(M!=NULL){
		M->select();
	}
}
void	RelationUI::Delete()
{
	QSqlQuery queryDelete;
	queryDelete.prepare("DELETE FROM MASTERRELATION WHERE RELATIONCODE=:IN_RELATIONCODE");
	queryDelete.bindValue(0	, ResultRelationCode);
	if(queryDelete.exec()==true){
		QString	S=QString(/**/"SELECT MASTERCODE FROM MASTERDATA WHERE RELATIONCODE=")+QString::number(ResultRelationCode);
		QSqlQuery query(S);
		IntList	MasterCodeList;
		while(query.next()==true){
			int		MasterCode	=query.value(query.record().indexOf(/**/"MASTERCODE")).toInt();
			MasterCodeList.Add(MasterCode);
		}
		for(IntClass *c=MasterCodeList.GetFirst();c!=NULL;c=c->GetNext()){
			QString	MasterCode=QString::number(c->GetValue());
			Image ->Delete(MasterCode);
			Master->Delete(MasterCode);
			Page  ->Delete(MasterCode);
		}
	}
	QSqlRelationModel	*M=dynamic_cast<QSqlRelationModel	 *>(ui->tableView->model());
	if(M!=NULL){
		M->select();
	}
}
void	RelationUI::Backup()
{
}
void	RelationUI::Restore()
{
}
void Datamanagement::on_tableView_clicked(const QModelIndex &index)
{
	QModelIndex Index=ui.tableView->currentIndex();

	QSqlRelationModel	*M=dynamic_cast<QSqlRelationModel	 *>(ui.tableView->model());
	if(M!=NULL){
		QList<QPixmap *>	QPixmapDim;
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	RelationCode=M->data(RIndex).toInt();
		((RelationUI *)Gui)->ResultRelationCode=RelationCode;

		QString	Str=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
					+QString(/**/" WHERE RELATIONCODE=")
					+QString::number(RelationCode);
		QSqlQuery queryStr(Str);
		if(queryStr.next()==true){
			QString	RelationName	=queryStr.value(queryStr.record().indexOf(/**/"RELATIONNAME")).toString();
			QString	RelationNumber	=queryStr.value(queryStr.record().indexOf(/**/"RELATIONNUMBER")).toString();
			QString	Remark			=queryStr.value(queryStr.record().indexOf(/**/"REMARK"	)).toString();
			ui.leRELATIONCODE	->setText(QString::number(RelationCode));
			ui.leRELATIONNAME	->setText(RelationName);
			ui.leRELATIONNUMBER->setText(RelationNumber);
			ui.leREMARK		->setText(Remark);
		}
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE RELATIONCODE=")
			+QString::number(RelationCode);
		QSqlQuery query(S);
		while(query.next()==true){

			QString	MasterName	=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
			QString	Remark		=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
			QByteArray	TopVArray=query.value(query.record().indexOf(/**/"TOPVIEW"	)).toByteArray();

			QPixmap		*TopView=new QPixmap;
			TopView->loadFromData(TopVArray,/**/"PNG");
			QPixmapDim.append(TopView);
		}
		int	N=QPixmapDim.count();
		if(N>0){
			LabelDim.clear();
			int	W=ui.frameView->width()/N;
			int	H=ui.frameView->height();
			for(int i=0;i<N;i++){
				QLabel	*L=new QLabel(ui.frameView);
				L->setParent(ui.frameView);
				L->setGeometry(W*i,0,W,H);
				QPixmap		*TopView=QPixmapDim.at(i);
				int	PW=TopView->width();
				int	PH=TopView->height();
				L->setPixmap(*TopView);
				L->show();
				L->update();
				LabelDim.append(L);
			}
		}
	}
}

void	RelationUI::MListSectionClicked ( int logicalIndex )
{
	if(OrderMode==logicalIndex){
		AcsendantOrder=!AcsendantOrder;
	}
	else{
		OrderMode=logicalIndex;
		AcsendantOrder=true;
	}
	QSqlRelationModel	*M=dynamic_cast<QSqlRelationModel	 *>(ui->tableView->model());
	if(M!=NULL)
		M->select();
}
//----------------------------------------------------
MasterUI::MasterUI(Datamanagement *parent) : UIBase(parent){
	Master		= new MasterData(parent);
	Page		= new MasterPage(parent);
	Image		= new MasterImage(parent);
	Category	= new MasterCategory(parent);
	MasterModel = new QSqlQueryModel(parent);
	MasterJudge = 0;
//MasterTree表示
	QStringList MTFieldNames;
	MTFieldNames << /**/"FOLDERNAME" << /**/"REMARK" << /**/"CATEGORYID";
	ui->trMasterList->setColumnCount(MTFieldNames.count());
	ui->trMasterList->setHeaderLabels(MTFieldNames);
	ui->trMasterList->header()->resizeSection(0,135);
	ui->trMasterList->header()->resizeSection(1,50);
	ui->trMasterList->hideColumn(2);
//MASTERDATA
	ui->combMASTERSel_1->clear();
	ui->combMASTERSel_1->addItem(LangSolver.GetString(datamanagement_LS,LID_0)/*"MASTERCODE"*/);
	ui->combMASTERSel_1->addItem(LangSolver.GetString(datamanagement_LS,LID_1)/*"MASTERNAME"*/);
	ui->combMASTERSel_1->addItem(LangSolver.GetString(datamanagement_LS,LID_2)/*"REGTIME"*/);
	ui->dataMASTER_1->setDate(QDate::currentDate());
	ui->combMASTERSel_11->clear();
	ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_3)/*"Large"*/);
	ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_4)/*"Same"*/);
	ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_5)/*"Small"*/);
	ui->dataMASTER_1	->setVisible(false);
	ui->combMASTERSel_11->setVisible(true);

	resizeHeader();

	connect(ui->trMasterList->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),this, SLOT(Tree_rowChanged(QModelIndex)));
	connect(ui->MASTERView	->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),this, SLOT(rowMoved  (QModelIndex, QModelIndex)));
	connect(ui->pbMASTERSELECT				  , SIGNAL(clicked())							   ,this, SLOT(on_pbMASTERSELECT_clicked()));
	connect(ui->combMASTERSel_1				  , SIGNAL(currentIndexChanged(int))			   ,this, SLOT(on_combMASTERSel_1_currentIndexChanged(int)));
	connect(ui->trMasterList				  , SIGNAL(itemPressed(QTreeWidgetItem *,int))	   ,this, SLOT(on_trMasterList_itemClicked(QTreeWidgetItem *,int)));
	connect(ui->MASTERView					  , SIGNAL(itemPressed(QTableWidgetItem *))		   ,this, SLOT(on_MASTERView_itemClicked(QTableWidgetItem *)));
	showTree();
}
void MasterUI::view(){
	QTreeWidgetItem *p = ui->trMasterList->currentItem();
	if(p==NULL)
		return resizeHeader();
	QString FolderID = p->text(2);
	if(FolderID.isEmpty())
		return ;
	QString SELECT;
	if(FolderID==/**/"-1"){
		SELECT=/**/"WHERE MASTERDATA.CATEGORYID<='0' or MASTERDATA.CATEGORYID IS NULL ";
	}else{
		SELECT=/**/"WHERE MASTERDATA.CATEGORYID="+ FolderID;
	}
	QString ORDER=/**/"ORDER BY MASTERDATA.MASTERCODE";
	view(SELECT,ORDER);
}

void MasterUI::view(QString &SELECT,QString &ORDER){
	Master->Select(MasterModel, SELECT, ORDER);
	ui->MASTERView->clear();
	while (MasterModel->canFetchMore()){ // 256行以上読み込むために必要
		MasterModel->fetchMore();
	}
	int Row=MasterModel->rowCount();
	int Column=MasterModel->columnCount();
	ui->MASTERView->setRowCount(Row);
	ui->MASTERView->setColumnCount(Column);
	QStringList Header;
	for(int i=0; i<Column; i++ )
		Header.append(MasterModel->headerData(i, Qt::Horizontal).toString());
	ui->MASTERView->setHorizontalHeaderLabels(Header);
	for(int iR=0; iR<Row; iR++){
		for(int iC=0; iC<Column; iC++){
			QTableWidgetItem *item = new QTableWidgetItem(MasterModel->data(MasterModel->index(iR,iC)).toString());
			ui->MASTERView->setItem(iR, iC,item);
		}
	}
	clear();
	resizeHeader();
}
void MasterUI::clear(){
	int i=0;
	for(QLineEdit *p = getLineEdit(i);p!=NULL;p = getLineEdit(i)){
		p->clear();
		i++;
	}
	QPixmap Pixmap;
	ui->label->setPixmap(Pixmap);
}
void MasterUI::changeUI(){
	ui->pbInsert->setVisible(false);
	ui->pbUpdate->setVisible(true);
}
void MasterUI::resizeHeader(){
	ui->MASTERView->horizontalHeader()->resizeSection (0,40) ;//MASTERCODE
	ui->MASTERView->horizontalHeader()->resizeSection (1,110);//MASTERNAME
	ui->MASTERView->horizontalHeader()->resizeSection (2,50) ;//MACHINEID
	ui->MASTERView->horizontalHeader()->resizeSection (3,170);//REGTIME
	ui->MASTERView->horizontalHeader()->resizeSection (4,60) ;//REMARK
	ui->MASTERView->horizontalHeader()->resizeSection (5,170);//LASTEDITTIME
	ui->MASTERView->horizontalHeader()->resizeSection (6,70) ;//WORKERID
	ui->MASTERView->horizontalHeader()->resizeSection (7,60) ;//VERSION
	ui->MASTERView->horizontalHeader()->resizeSection (8,80) ;//CATEGORYID
	ui->MASTERView->horizontalHeader()->resizeSection (9,80) ;//DOTPERLINE
	ui->MASTERView->horizontalHeader()->resizeSection (10,70);//MAXLINE
	ui->MASTERView->horizontalHeader()->resizeSection (11,70);//PAGENUMB
	ui->MASTERView->horizontalHeader()->resizeSection (12,80);//LAYYERNUMB
	ui->MASTERView->horizontalHeader()->resizeSection (13,80);//PHASENUMB
	ui->MASTERView->horizontalHeader()->resizeSection (14,80);//MASTERTYPE
}
void MasterUI::showTree(){
	//Root階層のフォルダー表示
	disconnect(ui->trMasterList->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(Tree_rowChanged(QModelIndex)));
	ui->trMasterList->clear();
	connect(ui->trMasterList->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(Tree_rowChanged(QModelIndex)));
	//TreeWidget最初のフォルダー表示
	QTreeWidgetItem *RootItem=new QTreeWidgetItem();
	RootItem->setText(0,tr(/**/"Root"));
	RootItem->setText(1,/**/"");
	RootItem->setText(2,QString::number(-1));
	ui->trMasterList->addTopLevelItem(RootItem);
//以下のフォルダー表示
	QString QueryData=/**/"SELECT FOLDERNAME, REMARK, CATEGORYID FROM MASTERCATEGORY WHERE PARENTID=0 ORDER BY CATEGORYID";
	addChildTree(QueryData, RootItem);
}
void MasterUI::addChildTree(QString &QueryData, QTreeWidgetItem *ParentItem)
{
	//Root下階層のフォルダー表示
	int Cnt=0;
	QSqlQuery Query(QueryData);
	while (Query.next()) {
		if(Cnt==0)
			Cnt = Query.numRowsAffected();//Select数
		QTreeWidgetItem *item=new QTreeWidgetItem();
		QString Parent=Query.value(2).toString();
		if(Parent.isEmpty()==true)
			break;
		item->setText(0, Query.value(0).toString());
		item->setText(1, Query.value(1).toString());
		item->setText(2, Parent);
		ParentItem->addChild(item);
		QString Select=/**/"SELECT FOLDERNAME,REMARK,CATEGORYID FROM MASTERCATEGORY WHERE PARENTID="
					+ Parent
					+ /**/"ORDER BY CATEGORYID";
		addChildTree(Select, item);
	}
}
void MasterUI::setData(QStringList &DataList){
	for(int i=0;i<5;i++){
		DataList.append(getLineEdit(i)->text());
	}
}
QLineEdit *MasterUI::getLineEdit(int i){
	switch(i){
	case  0: return ui->leMASTERCODE;
	case  1: return ui->leMASTERMACHINEID;
	case  2: return ui->leMASTERWORKERID;
	case  3: return ui->leMASTERNAME;
	case  4: return ui->leMASTERREMARK;
//---------------------------------------
	case  5: return ui->leMASTERREG;
	case  6: return ui->leMASTERLAST;
	case  7: return ui->leMASTERVer;
	case  8: return ui->leMASTERCAT;
	case  9: return ui->leMASTEDOT;
	case 10: return ui->leMASTERLINE;
	case 11: return ui->leMASTERPAGE;
	case 12: return ui->leMASTERLAY;
	case 13: return ui->leMASTERPHASE;
	case 14: return ui->leMASTERTYPE;
	}
	return NULL;
}
bool MasterUI::isEmpty(QStringList &DataList)
{
	if (ui->MASTERView->currentIndex().row()==-1 || DataList[0].isEmpty()==true){
		message(QString(/**/"NOSELE"));
		return false;
	}
	if(DataList[1].isEmpty()){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_15)/*"MachineID is NULL"*/);
		return false;
	}
	if(DataList[2]==/**/"..." || DataList[1].isEmpty()){
		QMessageBox::information(0, /**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_16)/*"WORKERID is NULL"*/);
		return false;
	}
	return true;
}
void MasterUI::on_pbMASTERSELECT_clicked()
{
	if(ui->combMASTERSel_1->currentIndex()!=2 && ui->leMASTERSel_1->text().isEmpty())
		return;
	QString SELECT,ORDER;
	select(SELECT,ORDER);
	view(SELECT,ORDER);
}	
void MasterUI::select(QString &SELECT,QString &ORDER){
	int INDEX =ui->combMASTERSel_1 ->currentIndex();//0:MASTERCODE 1:MASTERNAME 2:REGTIME
	int JOUKEN=ui->combMASTERSel_11->currentIndex();

	QString Data=ui->leMASTERSel_1->text();
	QString Order;
	if (ui->checkbMASTERSort->isChecked()==true){
		Order=/**/" DESC";
	}else{
		Order=/**/" ASC";
	}
	QString sFlag;
	QString sSort;
	if (INDEX==0){
		sSort=/**/"MASTERCODE";
		if (Data.isEmpty()==true ){
			SELECT=/**/"";
		}else{
			switch (JOUKEN){
				case 0:
					sFlag=/**/" >= ";
					break;
				case 1:
					sFlag= /**/" = ";
					break;
				case 2:
					sFlag=/**/" <=";
					break;
			}
			SELECT=/**/" WHERE " + sSort + sFlag + Data ;
		}
	}else if(INDEX==1){
		sSort=/**/"MASTERNAME";
		if (Data==/**/"ANY"){
			SELECT=/**/"";
		}else{
			switch (JOUKEN){
				case 0:
					sFlag=/**/"%'";
					break;
				case 1:
					sFlag=/**/"'";
					break;
			}
			SELECT=/**/" WHERE " + sSort + /**/" LIKE '" + Data + sFlag;
		}
	}else if(INDEX==2){
		sSort=/**/"REGTIME";
		switch (JOUKEN){
			case 0:
				sFlag=/**/" <= ";
				break;
			case 1:
				sFlag=/**/" = ";
				break;
			case 2:
				sFlag=/**/" >= ";
				break;
		}
		SELECT=/**/" WHERE CAST(REGTIME AS DATE)"+ sFlag +/**/"CAST('" +
					QString().setNum(ui->dataMASTER_1->date().year()) + /**/"-" +
					QString().setNum(ui->dataMASTER_1->date().month()) + /**/"-" +
					QString().setNum(ui->dataMASTER_1->date().day()) + /**/"' AS DATE)";
	}
	ORDER=/**/"ORDER BY " + sSort + Order;
}
void MasterUI::Update(){
	QStringList DataList;
	setData(DataList);
	if(isEmpty(DataList)==false)
		return;
	Master->Update(DataList);
	view();
	// Pdialog->close();
}
void MasterUI::Delete(){
	if(MasterJudge==1){
		if (message(QString( /**/"FolderDelete"))==false)
			return;
		QList<QTreeWidgetItem*> items = ui->trMasterList->selectedItems();
		for(int i=0;i<items.count();i++){
			QTreeWidgetItem* item = items.at(i);
			QString CATEGORYID = item->text(2);
			if(CATEGORYID.isEmpty())
				continue;
			Master->ALLDelete(CATEGORYID);

		}
		showTree();
		ui->MASTERView->clear();
		ui->MASTERView->setRowCount(0);
		QStringList Header;
		int	Column=MasterModel->columnCount();
		for(int cc=0; cc<Column; cc++){
			Header.append(MasterModel->headerData(cc, Qt::Horizontal).toString());
		}
		ui->MASTERView->setHorizontalHeaderLabels(Header);
		clear();
		return;
	}
	if(MasterJudge==2){
		if(message(QString(/**/"DELETE"))==false)
			return;
		QList<QTableWidgetItem*> items = ui->MASTERView->selectedItems();

		QList<int> selectedRows;
		for(int i=0; i<items.count(); i++){
			const int r = items.at(i)->row();
			if(selectedRows.contains(r)==false){
				selectedRows << r;
			}
		}

		for(int i=0;i<selectedRows.count();i++){
			QString MasterCode = ui->MASTERView->item(selectedRows[i], 0)->text();
			Image ->Delete(MasterCode);
			Master->Delete(MasterCode);
			Page  ->Delete(MasterCode);
			//Image ->Delete(items.at(i)->text());
			//Master->Delete(items.at(i)->text());
			//Page  ->Delete(items.at(i)->text());
		}
		view();
		return;
	}
	message(QString(/**/"NOSELE"));
	return;
}
void MasterUI::Backup(){
//データの取得
	QString MASTERCODE=ui->leMASTERCODE->text();
	if(MASTERCODE.isEmpty()==true){
		message(QString(/**/"NOSELE"));
		return ;
	}
	QString CATEGORYID;
#if 1 // 20100310
	bool Ret = disconnect(ui->trMasterList->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(Tree_rowChanged(QModelIndex)));
	QTreeWidgetItem* qtwi = CheckTrMasterList(ui->trMasterList->topLevelItem(0), 0, ui->leMASTERCAT->text());

	if (NULL != qtwi)
		CATEGORYID = qtwi->text(2);

	connect(ui->trMasterList->selectionModel(), SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(Tree_rowChanged(QModelIndex)));

	if (/**/"" == CATEGORYID)
		CATEGORYID = /**/"-1";
#endif

	if(CATEGORYID.isEmpty()==true)
		return;
	QString	FileName=QFileDialog::getSaveFileName( 0, /**/"Create MasterDataBackupFile",  /**/"",(/**/" (*.MasB)"));
	if(FileName.isEmpty()==true)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::WriteOnly)==false)
		return;
//バックアップの後削除するか
	bool Delete=true;
	if(QMessageBox::information(0, /**/"Delete",LangSolver.GetString(datamanagement_LS,LID_25)/*"Do you want to delete this MasterData after you create the Backupfile?"*/,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No)
		Delete=false;
	//parent->Pdialog->show();
//フィールド名の取得
	QString Target=/**/"MASTERDATA";
	Master->FieldSave(file, Target);
	Target=/**/"MASTERPAGE";
	Master->FieldSave(file, Target);
	Target=/**/"MASTERCATEGORY";
	Master->FieldSave(file, Target);
	::Save(&file, MASTERCODE);
	::Save(&file, CATEGORYID);
//親階層の取得
	Category->ParentSave(file, CATEGORYID);
//Dataの取得
	Master	->Save(file, MASTERCODE);
	Page	->Save(file, MASTERCODE);
	Category->Save(file, CATEGORYID);
	//parent->Pdialog->P.progressBar->setValue(50);
	Image	->Save(file, MASTERCODE);
	//parent->Pdialog->P.progressBar->setValue(100);
	parent->saveRelatedMastercode(file,MASTERCODE); //RELATEDMASTERCODEの追加に伴い
	parent->Pdialog->close();

	if(Delete==false)
		return;
	Image ->Delete(MASTERCODE);
	Master->Delete(MASTERCODE);
	Page  ->Delete(MASTERCODE);
	showTree();
	ui->MASTERView->clear();
	ui->MASTERView->setRowCount(0);
	QStringList Header;
	int	Column=MasterModel->columnCount();
	for(int cc=0; cc<Column; cc++)
		Header.append(MasterModel->headerData(cc, Qt::Horizontal).toString());
	ui->MASTERView->setHorizontalHeaderLabels(Header);
	clear();
}
void MasterUI::Restore(){
	QStringList BMasterList,BPageList,BCategoryList,MasterList,PageList,CategoryList;
	QString Mins,Pins,Cins;

	QString	FileName=QFileDialog::getOpenFileName( 0, /**/"Restore MasterDataBackupFile",  /**/"",(/**/" (*.MasB)"));
	if(FileName.isEmpty()==true)
		return;
	RestorePath *dialog=new RestorePath(MPathList);
	if(dialog->exec()==0)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::ReadOnly)==false)
		return;
//Backupフィールド名の取得
	Master->FieldLoad(file, BMasterList);
	Master->FieldLoad(file, BPageList);
	Master->FieldLoad(file, BCategoryList);

//現状のテーブルのフィールド取得
	QString Target=/**/"MASTERDATA";
	Master->FieldGet(Target, MasterList);
	Master->RestoreField(BMasterList, MasterList, Target, Mins);
	Target=/**/"MASTERPAGE";
	Master->FieldGet(Target, PageList);
	Master->RestoreField(BPageList, PageList, Target, Pins);
	Target=/**/"MASTERCATEGORY";
	Master->FieldGet(Target, CategoryList);
	Master->RestoreField(BCategoryList, CategoryList, Target, Cins);

	QString MASTERCODE;
	QString MCode;
	if(::Load(&file, MASTERCODE)==false)
		return ;
	MCode=MASTERCODE;
	QSqlQuery Query(/**/"SELECT MASTERCODE FROM MASTERDATA WHERE MASTERCODE="+ MASTERCODE);
	if(Query.next()==true){//既に存在している場合
		if(QMessageBox::information(0, LangSolver.GetString(datamanagement_LS,LID_26)/*"Data has already existed"*/,LangSolver.GetString(datamanagement_LS,LID_27)/*"Save New:Yes  UpDate:No"*/,QMessageBox::Yes,QMessageBox::No)==QMessageBox::No){
			//上書きの場合
			Image->Delete(MASTERCODE);
			Master->Delete(MASTERCODE);
			Page->Delete(MASTERCODE);
			MCode=MASTERCODE;
		}else{
			//MasterCodeを新規で割り当て新規保存の場合
			QSqlQuery MAXQuery(/**/"SELECT MAX(MASTERCODE) FROM MASTERDATA");
			if (MAXQuery.next())
				MCode = QString::number(MAXQuery.value(0).toInt()+1);
		}
	}

	QString CATEGORYID;
	if(::Load(&file, CATEGORYID)==false){
		// Pdialog->close();
		return;
	}
	//親階層の取得
	Category->ParentLoad(file, BCategoryList, CategoryList, Cins);
	Master->Load(file, BMasterList, MasterList, Mins, MCode);

	Page	->Load(file, BPageList, PageList, Pins, MCode);
	Category->Load(file, BCategoryList, CategoryList, Cins);
	Image	->Load(file, MCode);
	showTree();
	clear();
	ui->MASTERView->clear();
	ui->MASTERView->setRowCount(0);
	ui->MASTERView->setColumnCount(0);
	parent->loadRelatedMastercode(file); //RELATEDMASTERCODEの追加に伴い
}
QTreeWidgetItem* MasterUI::CheckTrMasterList(QTreeWidgetItem* item, int col, QString data)
{
	if(item->text(col) == data)
		return item;
	for(int i=0;i<item->childCount();i++){
		QTreeWidgetItem *itemChild=item->child(i);
		if(CheckTrMasterList(itemChild,col,data)!=NULL)
			return itemChild;
	}
	return NULL;
}
void MasterUI::rowMoved(QModelIndex INDEX, QModelIndex INDEX2){
	//Tree対表示
	if (INDEX.row()==-1)
		return clear();
////////
	ui->leMASTERCODE		->setText(MasterModel->data(MasterModel->index(INDEX.row(),0)).toString());//ID
	ui->leMASTERNAME		->setText(MasterModel->data(MasterModel->index(INDEX.row(),1)).toString());//NAME
	ui->leMASTERMACHINEID	->setText(MasterModel->data(MasterModel->index(INDEX.row(),2)).toString());//MACID
	ui->leMASTERREG			->setText(MasterModel->data(MasterModel->index(INDEX.row(),3)).toString());//REG
	ui->leMASTERREMARK		->setText(MasterModel->data(MasterModel->index(INDEX.row(),4)).toString());//REMARK
	ui->leMASTERLAST		->setText(MasterModel->data(MasterModel->index(INDEX.row(),5)).toString());//LASTDATETIME
	ui->leMASTERWORKERID	->setText(MasterModel->data(MasterModel->index(INDEX.row(),6)).toString());//WORKERID
	ui->leMASTERVer			->setText(MasterModel->data(MasterModel->index(INDEX.row(),7)).toString());//VERSION
	ui->leMASTERCAT			->setText(MasterModel->data(MasterModel->index(INDEX.row(),8)).toString());//CATEGORY
	ui->leMASTEDOT			->setText(MasterModel->data(MasterModel->index(INDEX.row(),9)).toString());//DOTPERLINE
	ui->leMASTERLINE		->setText(MasterModel->data(MasterModel->index(INDEX.row(),10)).toString());//MAXLINES
	ui->leMASTERPAGE		->setText(MasterModel->data(MasterModel->index(INDEX.row(),11)).toString());//PAGENUMB
	ui->leMASTERLAY			->setText(MasterModel->data(MasterModel->index(INDEX.row(),12)).toString());//LAYERNUMB
	ui->leMASTERPHASE		->setText(MasterModel->data(MasterModel->index(INDEX.row(),13)).toString());//PHASENUMB
	ui->leMASTERTYPE		->setText(MasterModel->data(MasterModel->index(INDEX.row(),14)).toString());//MASTERTYPE
/////////
	QPixmap pixmap;
	int MasterID=ui->leMASTERCODE->text().toInt();
	QSqlQuery Buffquery;
	Buffquery.prepare(/**/"SELECT TOPVIEW FROM MASTERDATA WHERE MASTERCODE=?");
	Buffquery.addBindValue(MasterID);
	Buffquery.exec();
	if(Buffquery.next()==false || Buffquery.value(0).toByteArray().isNull()==true) {
		ui->label->setPixmap(pixmap);
		return;
	}
	QByteArray Buff=Buffquery.value(Buffquery.record().indexOf(/**/"TOPVIEW")).toByteArray();
	QBuffer Buffer (&Buff);
	if (Buffer.open(QIODevice::ReadOnly)==true){
		pixmap.loadFromData(Buffquery.value(0).toByteArray());
		Buffer.close();
	}
	ui->label->setPixmap(pixmap.scaled(ui->label->size(),Qt::IgnoreAspectRatio));
}
void MasterUI::Tree_rowChanged(QModelIndex INDEX){
	view();

	ui->combMASTERSel_1 ->setCurrentIndex(0);
	ui->combMASTERSel_11->setCurrentIndex(0);

	ui->leMASTERSel_1->setVisible(true);
	ui->dataMASTER_1 ->setVisible(false);
}
void MasterUI::on_combMASTERSel_1_currentIndexChanged(int index)
{//CombBox検索条件表示
	ui->leMASTERSel_1	->setVisible(true);
	ui->dataMASTER_1	->setVisible(false);
	ui->combMASTERSel_11->setVisible(true);
	if	(index== 0){//MASTERCORDE
		ui->combMASTERSel_11->clear();
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_31)/*"Large"*/);
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_32)/*"Same"*/);
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_33)/*"Small"*/);
	}else if  (index== 1){//MASTERNAME
		ui->combMASTERSel_11->clear();
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_34)/*"contains"*/);
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_35)/*"Same"*/);
	}else if (index== 2){
		ui->leMASTERSel_1->setVisible(false);
		ui->dataMASTER_1 ->setVisible(true);
		ui->combMASTERSel_11->clear();
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_36)/*"Before"*/);
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_37)/*"Same"*/);
		ui->combMASTERSel_11->addItem(LangSolver.GetString(datamanagement_LS,LID_38)/*"After"*/);
	}
	ui->leMASTERSel_1->clear();
}
void MasterUI::on_trMasterList_itemClicked(QTreeWidgetItem *item, int column)
{
    MasterJudge=1;
}

void MasterUI::on_MASTERView_itemClicked(QTableWidgetItem *item)
{
    MasterJudge=2;
}
//------------------------------------------------
MachineUI::MachineUI(Datamanagement *parent) : UIBase(parent){
	Mac			= new Machine(parent);
	MacModel	= new QSqlQueryModel(parent);
	OldMachineID = /**/"";
	view();
	connect(ui->MACHINEView->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(rowMoved(QModelIndex,QModelIndex)));
}
void MachineUI::view(){
	Mac->Select(MacModel);
	ui->MACHINEView->setModel(MacModel);
	ui->MACHINEView->show();
	clear();
	resizeHeader();
}
void MachineUI::clear(){
	for(int i=0;i<5;i++){
		getLineEdit(i)->clear();
	}
}
void MachineUI::changeUI(){
	ui->pbInsert->setVisible(true);
	ui->pbUpdate->setVisible(true);
}
void MachineUI::resizeHeader(){
	ui->MACHINEView->horizontalHeader()->resizeSection (0,80) ;//MACHINEID
	ui->MACHINEView->horizontalHeader()->resizeSection (1,310);//IPADRESS
	ui->MACHINEView->horizontalHeader()->resizeSection (2,310);//NAME
	ui->MACHINEView->horizontalHeader()->resizeSection (3,285);//VERSION
	ui->MACHINEView->horizontalHeader()->resizeSection (4,300);//REMARK
}
void MachineUI::rowMoved (QModelIndex INDEX, QModelIndex INDEX2){
	if (INDEX.row()==-1)
		return clear();
	OldMachineID=MacModel->data(MacModel->index(INDEX.row(),0)).toString();
	for(int i=0;i<5;i++){
		getLineEdit(i)->setText(MacModel->data(MacModel->index(INDEX.row(),i)).toString());
	}
}
void MachineUI::setData(QStringList &DataList){
	for(int i=0;i<5;i++){
		DataList.append(getLineEdit(i)->text());
////////////
		/*QLineEdit *p = getLineEdit(i);
		DataList[i]  = p->text();*/
	}
}
QLineEdit *MachineUI::getLineEdit(int i){
	switch(i){
	case 0: return ui->leMACHINEID;
	case 1: return ui->leMACHINENETID;
	case 2: return ui->leMACHINENAME;
	case 3: return ui->leMACHINEVERSION;
	case 4: return ui->leMACHINEREMARK;
	}
	return NULL;
}
bool MachineUI::isEmpty(QStringList &DataList){
	if(DataList[0].isEmpty()){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_17)/*"MachineID is NULL"*/);
		return false;
	}
	if(DataList[1]==/**/"..." || DataList[1].isEmpty()){
		QMessageBox::information(0, /**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_18)/*"NetID is NULL"*/);
		return false;
	}
	if (DataList[2].isEmpty()){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_19)/*"Name is NULL"*/);
		return false;
	}
	return true;
}
void MachineUI::Insert(){
	QStringList DataList;
	setData(DataList);
	if(isEmpty(DataList)==false)
		return;
	if(Mac->Insert(DataList)==false){
		message(QString(/**/"MACHINEID"));
		return;
	}
	view();			
}
void MachineUI::Update(){
	QStringList DataList;
	setData(DataList);
	if(isEmpty(DataList)==false)
		return;
	if(Mac->Update(DataList,OldMachineID)==false){
		message(QString(/**/"MACHINEID"));
		return;
	}
	view();
}
void MachineUI::Delete(){
	if(message(QString(/**/"DELETE"))==false)
		return;
	QString MachineID=ui->leMACHINEID->text();
	if(MachineID.isEmpty()){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_23)/*"MachineID is NULL"*/);
		return;
	}
	if(Mac->Delete(MachineID)==false){
		message(QString(/**/"MachineDelete"));
		return;
	}
	view();
}
void MachineUI::Backup(){
	QString FileName=QFileDialog::getSaveFileName( 0, /**/"Create MachineBackupFile",  /**/"",(/**/" (*.MacB)"));//MachineBackup
	if(FileName.isEmpty()==true)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::WriteOnly)==false)
		return;
	Mac->FieldSave(file,QString(/**/"MACHINE"));
	Mac->Save(file);
}
void MachineUI::Restore(){
	QString FileName=QFileDialog::getOpenFileName( 0, LangSolver.GetString(datamanagement_LS,LID_28)/*"Restore MachineBackupFile"*/,	/**/"",(/**/" (*.MacB)"));
	if(FileName.isEmpty()==true)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::ReadOnly)==false)
		return;
	QStringList BMacList;
	Mac->FieldLoad(file, BMacList);
	//現状のテーブルのフィールド取得
	QStringList MacList;
	QString Target=/**/"MACHINE";
	Mac->FieldGet(Target, MacList);
	QString Macins;
	Mac->RestoreField(BMacList, MacList, Target, Macins);
	Mac->Load(file, BMacList, MacList, Macins);
	view();
}
//-------------------------------------------------
WorkerUI::WorkerUI(Datamanagement *parent) : UIBase(parent){
	Work		= new Worker(parent);
	WorkerModel = new QSqlQueryModel(parent);
	OldWorkerID = /**/"";
	view();
	connect(ui->WORKERView	->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex))	,this, SLOT(rowMoved (QModelIndex,QModelIndex)));
}
void WorkerUI::view(){
	WorkerModel->clear();
	Work->Select(WorkerModel);
	ui->WORKERView->setModel(WorkerModel);
	ui->WORKERView->show();
	clear();
	resizeHeader();
}
void WorkerUI::clear(){
	for(int i=0;i<4;i++){
		getLineEdit(i)->clear();
	}
	ui->dateTimeEditWORKER->setDateTime(QDateTime::currentDateTime());
}
void WorkerUI::changeUI(){
	ui->pbInsert->setVisible(true);
	ui->pbUpdate->setVisible(true);
}
void WorkerUI::resizeHeader(){
	ui->WORKERView->horizontalHeader()->resizeSection (0,80) ;//WORKERID
	ui->WORKERView->horizontalHeader()->resizeSection (1,310);//SECTION
	ui->WORKERView->horizontalHeader()->resizeSection (2,310);//NAME
	ui->WORKERView->horizontalHeader()->resizeSection (3,285);//REMARK
	ui->WORKERView->horizontalHeader()->resizeSection (4,300);//Date&TIME
}
void WorkerUI::rowMoved(QModelIndex INDEX, QModelIndex INDEX2){
	if (INDEX.row()==-1)
		return clear();
	OldWorkerID=WorkerModel->data(WorkerModel->index(INDEX.row(),0)).toString();
	for(int i=0;i<4;i++){
		getLineEdit(i)->setText(WorkerModel->data(WorkerModel->index(INDEX.row(),i)).toString());
	}
	ui->dateTimeEditWORKER->setDateTime(WorkerModel->data(WorkerModel->index(INDEX.row(),4)).toDateTime());
}
void WorkerUI::setData(QStringList &DataList,QDateTime &Updatetime){
	for(int i=0;i<4;i++){
		DataList.append(getLineEdit(i)->text());
	}
	Updatetime = ui->dateTimeEditWORKER->dateTime();
}
QLineEdit *WorkerUI::getLineEdit(int i){
	switch(i){
	case 0: return ui->leWORKERID;
	case 1: return ui->leWORKERSECTION;
	case 2: return ui->leWORKERNAME;
	case 3: return ui->leWORKERREMARK;
	//case 4: return ui->dateTimeEditWORKER;
	}
	return NULL;
}
bool WorkerUI::isEmpty(QStringList &DataList){
	if(DataList[0].isEmpty()){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_20)/*"WorkerID is NULL"*/);
		return false;
	}
	if(DataList[1].isEmpty()){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_21)/*"Section is NULL"*/);
		return false;
	}
	if (DataList[2].isEmpty()){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_22)/*"Name is NULL"*/);
		return false;
	}
	return true;
}

void WorkerUI::Insert(){
	QStringList DataList;
	QDateTime Updatetime;
	setData(DataList,Updatetime);
	if(isEmpty(DataList)==false)
		return;
	if(Work->Insert(DataList,Updatetime)==false){
		message(QString(/**/"WORKERID"));
		return;
	}
	view();
}
void WorkerUI::Update(){
	QStringList DataList;
	QDateTime Updatetime;
	setData(DataList,Updatetime);
	if(isEmpty(DataList)==false)
		return;
	if(Work->Update(DataList,Updatetime,OldWorkerID)==false){
		message(QString(/**/"WORKERID"));
		return;
	}
	view();
}
void WorkerUI::Delete(){
	if(message(QString(/**/"DELETE"))==false)
		return;
	QString WorkerID=ui->leWORKERID->text();
	if (WorkerID.isEmpty()==true){
		QMessageBox::information(0,/**/"Data NULL",LangSolver.GetString(datamanagement_LS,LID_24)/*"WorkerID is NULL"*/);
		return;
	}
	if(Work->Delete(WorkerID)==false){
		message(QString(/**/"WorkerDelete"));
		return;
	}
	view();
}
void WorkerUI::Backup(){
	QString FileName=QFileDialog::getSaveFileName( 0, /**/"Create WorkerBackupFile",  /**/"",(/**/" (*.WorB)"));//WorkerBackup
	if(FileName.isEmpty()==true)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::WriteOnly)==false)
		return;

	/*Pdialog->P.progressBar->setMaximum(0);
	Pdialog->show();*/

	Work->FieldSave(file, QString(/**/"WORKER"));
	Work->Save(file);
	//Pdialog->close();
}
void WorkerUI::Restore(){
	QString	FileName=QFileDialog::getOpenFileName( 0, LangSolver.GetString(datamanagement_LS,LID_29)/*"Restore WorkerDataBackupFile"*/,  /**/"",(/**/" (*.WorB)"));
	if(FileName.isEmpty()==true)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::ReadOnly)==false)
		return;
	QStringList BWorkList;
	Work->FieldLoad(file, BWorkList);
	//現状のテーブルのフィールド取得
	QStringList WorkList;
	QString Target=/**/"WORKER";
	Work->FieldGet(Target, WorkList);
	QString Wins;
	Work->RestoreField(BWorkList, WorkList, Target, Wins);
	Work->Load(file, BWorkList, WorkList, Wins);
	view();
}
//--------------------------------------------------
LibUI::LibUI(Datamanagement *parent) : UIBase(parent){
	Folder			= new LibFolder(parent);
	Lib				= new InspectLib(parent);
	LibType			= new InspectLibType(parent);
	LibModel		= new QSqlQueryModel(parent);
	LibFolderModel	= new QSqlQueryModel(parent);
	LibJudge		= 0;

	ui->INSPECTLIBView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QStringList LFFieldNames;
	LFFieldNames << /**/"FOLDERNAME" << /**/"LIBFOLDERID" << /**/"LIBPARENTID";
	ui->LibTreeWidget->setColumnCount(LFFieldNames.count());
	ui->LibTreeWidget->setHeaderLabels(LFFieldNames);
	ui->LibTreeWidget->header()->setSectionResizeMode(0,QHeaderView::Stretch);
	ui->LibTreeWidget->hideColumn(1);
	ui->LibTreeWidget->hideColumn(2);
	showTree();

	resizeHeader();

	connect(ui->LibTreeWidget->selectionModel() , SIGNAL(currentChanged(QModelIndex,QModelIndex))	,this, SLOT(rowChanged(QModelIndex)));
	connect(ui->LibTreeWidget					, SIGNAL(itemPressed(QTreeWidgetItem *, int))		,this, SLOT(on_LibTreeWidget_itemClicked(QTreeWidgetItem *, int)));
	connect(ui->INSPECTLIBView					, SIGNAL(itemPressed(QTableWidgetItem *))			,this, SLOT(on_INSPECTLIBView_itemClicked(QTableWidgetItem *)));
}
void LibUI::changeUI(){
	ui->pbInsert->setVisible(false);
	ui->pbUpdate->setVisible(false);
}
void LibUI::resizeHeader(){
	ui->INSPECTLIBView->horizontalHeader()->resizeSection (0,50);//LIBID
	ui->INSPECTLIBView->horizontalHeader()->resizeSection (1,190);//LIBNAME
	ui->INSPECTLIBView->horizontalHeader()->resizeSection (2,200);//LIBTYPE
	ui->INSPECTLIBView->horizontalHeader()->resizeSection (3,160);//LASTWORKER
	ui->INSPECTLIBView->horizontalHeader()->resizeSection (4,120);//DATAVERSION
	ui->INSPECTLIBView->horizontalHeader()->resizeSection (5,180);//LASTUPDATED
	ui->INSPECTLIBView->horizontalHeader()->resizeSection (6,120);//LIBFOLDERID
}
void LibUI::view(){
	QTreeWidgetItem *p = ui->LibTreeWidget->currentItem();
	if(p==NULL)
		return resizeHeader();
	QString FolderID = p->text(1);
	if(FolderID.isEmpty()==true)
		return ;
	QString Sel;
	if (FolderID==/**/"-1"){
		Sel=/**/"WHERE INSPECTLIB.LIBFOLDERID<=0 ";
	}else{
		Sel=/**/"WHERE INSPECTLIB.LIBFOLDERID=" + FolderID;
	}
	QString Order=/**/"ORDER BY INSPECTLIB.LIBID";
	LibFolderModel->clear();
	Lib->Select(LibFolderModel, Sel, Order);
	ui->INSPECTLIBView->clear();
	int Row		=LibFolderModel->rowCount();
	int Column	=LibFolderModel->columnCount();
	ui->INSPECTLIBView->setRowCount(Row);
	ui->INSPECTLIBView->setColumnCount(Column);
	QStringList HeaderList;
	for(int i=0; i<Column; i++ )
		HeaderList.append(LibFolderModel->headerData(i, Qt::Horizontal).toString());
	ui->INSPECTLIBView->setHorizontalHeaderLabels(HeaderList);
	for(int iY=0; iY<Row; iY++){
		for(int iX=0; iX<Column; iX++){
			QTableWidgetItem *item = new QTableWidgetItem(LibFolderModel->data(LibFolderModel->index(iY,iX)).toString());
			ui->INSPECTLIBView->setItem(iY, iX,item);
		}
	}
	ui->INSPECTLIBView->show();
	resizeHeader();
}
void LibUI::Delete(){
	QString table;
	if(LibJudge==0){
		table=/**/"NOSELE";
		message(table);
		return;
	}else if(LibJudge==1){	//フォルダが選択されているなら
		table=/**/"FolderDelete";
		if (message(table)==false)
			return;
		if(ui->LibTreeWidget->itemAt(0,0)->isSelected()){
			Lib->ALLDelete();
			Folder->ALLDelete();
		}else{
			QList<QTreeWidgetItem*> items = ui->LibTreeWidget->selectedItems();
			for(int i=0;i<items.count();i++){
				QString FolderID = items.at(i)->text(1);
				Lib->FolderDelete(FolderID);////InspectLibのLibFolder削除
				Folder->Delete(FolderID);//リブフォルダー削除
				Folder->ChildDelete(FolderID);//子供の削除
			}
		}
		showTree();
		ui->INSPECTLIBView->clear();
		ui->INSPECTLIBView->setRowCount(0);
		ui->INSPECTLIBView->setColumnCount(0);
	}else if(LibJudge==2){
		QList<QTableWidgetItem*> items = ui->INSPECTLIBView->selectedItems();
		if(items.empty()){
			table=/**/"NOSELE";
			message(table);
			return ;
		}
		table=/**/"DELETE";
		if(message(table)==false)
			return;
		for(int i=0;i<items.count();i+=ui->INSPECTLIBView->columnCount()){
			int Row = items.at(i)->row();
			QString LibID   =LibFolderModel->data(LibFolderModel->index(Row, 0)).toString();
			QString TypeName=LibFolderModel->data(LibFolderModel->index(Row, 2)).toString();
			Lib->Delete(TypeName, LibID);
		}
		view();
	}
}
void LibUI::Backup(){
	if(LibJudge==0){
		QString table=/**/"NOSELE";
		message(table);
		return;
	}
	QString FileName=QFileDialog::getSaveFileName( 0, /**/"Create LibFolderBackupFile",  /**/"",(/**/" (*.LibB)"));
	if(FileName.isEmpty()==true)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::WriteOnly)==false)
		return;
	QString FolderID=ui->LibTreeWidget->currentItem()->text(1);
	if(FolderID.isEmpty()==true)
		return;
	::Save(&file, FolderID);

	QString Target=/**/"LIBFOLDER";
	Lib->FieldSave(file, Target);
	Target=/**/"INSPECTLIB";
	Lib->FieldSave(file, Target);
	Target=/**/"INSPECTLIBTYPE";
	Lib->FieldSave(file, Target);

	if(FolderID!=/**/"-1"){
		Target=/**/"Parent";
		Folder->SubSave(Target, file, FolderID);//親の階層を保存
		Target=/**/"Child";
		Folder->SubSave(Target, file, FolderID);//子供の階層を保存
	}
	Folder ->Save(file, FolderID);//自分自身の保存
	Lib	   ->Save(file, FolderID);//自分自身の中身
	LibType->Save(file);
}
void LibUI::Restore(){
	QString	FileName=QFileDialog::getOpenFileName( 0, LangSolver.GetString(datamanagement_LS,LID_30)/*"Restore LibFolderBackupFile"*/,  /**/"",(/**/" (*.LibB)"));
	if(FileName.isEmpty()==true)
		return;
	QFile file(FileName);
	if(file.open(QIODevice::ReadOnly)==false)
		return;
	QString FolderID;
	if(::Load(&file,FolderID)==false)
		return;
	//Backupフィールド名の取得
	QStringList BFolder,BLib,BLibType;
	Lib->FieldLoad(file, BFolder);
	Lib->FieldLoad(file, BLib);
	Lib->FieldLoad(file, BLibType);

	//現状のテーブルのフィールド取得
	QString Target=/**/"LIBFOLDER";
	QStringList NFolder;
	QString Fins;
	Lib->FieldGet(Target, NFolder);
	Lib->RestoreField(BFolder, NFolder, Target, Fins);
	Target=/**/"INSPECTLIB";
	QStringList NLib;
	QString Lins;
	Lib->FieldGet(Target, NLib);
	Lib->RestoreField(BLib, NLib, Target, Lins);
	Target=/**/"INSPECTLIBTYPE";
	QStringList NLibType;
	QString Tins;
	Lib->FieldGet(Target, NLibType);
	Lib->RestoreField(BLibType, NLibType, Target, Tins);

	if(FolderID!=/**/"-1"){
		Folder->SubLoad(file, BFolder, NFolder, Fins);//親の階層のリストア
		Folder->SubLoad(file, BFolder, NFolder, Fins);//子供階層のリストア
	}
	Folder->RootLoad(file, BFolder, NFolder, Fins);//自分自身のリストア
	Lib->Load(file, BLib, NLib, Lins);
	LibType->Load(file, BLibType, NLibType, Tins);

	showTree();
	ui->INSPECTLIBView->clear();
	ui->INSPECTLIBView->setRowCount(0);
	ui->INSPECTLIBView->setColumnCount(0);
}
void LibUI::saveRelatedMastercode(QIODevice &file,QString &MasterCode){
	QStringList RetFolderID;
	Folder->RetFolderID(MasterCode, RetFolderID);
	int FolderCount=RetFolderID.count();
	::Save(&file, FolderCount);
	for (int i=0; i<FolderCount; i++){
		QString FolderID=RetFolderID.at(i);
		::Save(&file, FolderID);
		//フィールド名の取得
		QString Target=/**/"LIBFOLDER";
		Lib->FieldSave(file, Target);
		Target=/**/"INSPECTLIB";
		Lib->FieldSave(file, Target);
		Target=/**/"INSPECTLIBTYPE";
		Lib->FieldSave(file, Target);
		//Dataの取得
		if(FolderID!=/**/"-1"){
			Target=/**/"Parent";
			Folder->SubSave(Target, file, FolderID);//親の階層を保存
			Target=/**/"Child";
			Folder->SubSave(Target, file, FolderID);//子供の階層を保存
		}
		Folder->Save(file, FolderID);//自分自身の保存
		Lib->Save(file, FolderID);//自分自身の中身
		LibType->Save(file);
	}
}
void LibUI::loadRelatedMastercode(QIODevice &file){
	QStringList BFolder, BLib, BLibType, NFolder, NLib, NLibType;
	int FolderCount;
	if(::Load(&file, FolderCount)==false)
		return;
	for (int count=0; count<FolderCount; count++){
		QString FolderID;
		if(::Load(&file, FolderID)==false)
			return;
		//Backupフィールド名の取得
		Lib->FieldLoad(file, BFolder);
		Lib->FieldLoad(file, BLib);
		Lib->FieldLoad(file, BLibType);

		//現状のテーブルのフィールド取得
		QString Fins, Lins, Tins ;
		QString Target=/**/"LIBFOLDER";
		Lib->FieldGet(Target, NFolder);
		Lib->RestoreField(BFolder, NFolder, Target, Fins);
		Target=/**/"INSPECTLIB";
		Lib->FieldGet(Target, NLib);
		Lib->RestoreField(BLib, NLib, Target, Lins);
		Target=/**/"INSPECTLIBTYPE";
		Lib->FieldGet(Target, NLibType);
		Lib->RestoreField(BLibType, NLibType, Target, Tins);
	//親の階層が存在しない場合Rootの直下につく
		if(FolderID!=/**/"-1"){
			Folder->RootSubLoad(file, BFolder, NFolder, Fins);//親の階層のリストア
		//	Folder->SubLoad(file, BFolder, NFolder, Fins);//子供階層のリストア
		}
		Folder->RootLoad2(file, BFolder, NFolder, Fins);//自分自身のリストア
		Lib->Load(file, BLib, NLib, Lins);
		LibType->Load(file, BLibType, NLibType, Tins);
	}
}
void LibUI::showTree(){
//Root階層のフォルダー表示
	disconnect(ui->LibTreeWidget->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(rowChanged(QModelIndex)));
	ui->LibTreeWidget->clear();
	connect(ui->LibTreeWidget->selectionModel(),SIGNAL(currentChanged(QModelIndex,QModelIndex)),this,SLOT(rowChanged(QModelIndex)));
//TreeWidget最初のフォルダー表示
	QTreeWidgetItem *RootItem;
	RootItem=new QTreeWidgetItem();
	RootItem->setText(0,tr(/**/"Root"));
	RootItem->setText(1,QString::number(-1));
	ui->LibTreeWidget->addTopLevelItem(RootItem);
//以下のフォルダー表示
	QString QueryData=/**/"SELECT FOLDERNAME, LIBFOLDERID, LIBPARENTID FROM LIBFOLDER WHERE LIBPARENTID=0 ORDER BY FOLDERNAME";
	return addChildTree(QueryData, RootItem);
}
void LibUI::addChildTree(QString &QueryData, QTreeWidgetItem *ParentItem){
	//Root下階層のフォルダー表示
	int Cnt=0;
	QSqlQuery SubQuery(QueryData);
	while (SubQuery.next()) {
		if(Cnt==0)
			Cnt = SubQuery.numRowsAffected();//Select数
		QTreeWidgetItem *item=new QTreeWidgetItem();
		QString Parent=SubQuery.value(1).toString();
		if(Parent.isEmpty()==true)
			break;
		item->setText(0, SubQuery.value(0).toString());
		item->setText(1, Parent);
		ParentItem->addChild(item);
		QString Select=/**/"SELECT FOLDERNAME, LIBFOLDERID FROM LIBFOLDER WHERE LIBPARENTID="
						+ Parent
						+ /**/" ORDER BY  FOLDERNAME";//LIBFOLDERIDLIBPARENTID";
		addChildTree(Select, item);
	}
	//return Cnt;
}
void LibUI::rowChanged(QModelIndex INDEX){
	view();
}
void LibUI::on_LibTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
	LibJudge=1;
}
void LibUI::on_INSPECTLIBView_itemClicked(QTableWidgetItem *item)
{
	LibJudge=2;
}
