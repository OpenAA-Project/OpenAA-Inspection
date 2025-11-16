#include "ButtonSelectMasterResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSelectMaster\SelectMasterForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

//#include "ButtonLoadMasterDataResource.h"
#include "SelectMasterForm.h"
#include "MasterCategoryForm.h"
#include "XDLLOnly.h"
#include "XGeneralFunc.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QHeaderView>
//#include "ButtonSelectLot.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	CategoryID;

QSqlSelectMasterModel::QSqlSelectMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<SelectMasterForm *>(parent);
}
QString QSqlSelectMasterModel::selectStatement () const
{
	QString	ret;
	switch(ParentWindow->ListMode){
		case SelectMasterForm::_IDNormal:
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
		case SelectMasterForm::_IDReverse:
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
						+QString(/**/" AND CATEGORYID=")
						+QString::number(CategoryID)
						+QString(/**/" ORDER BY MASTERCODE DESC;");
				}
			}
			break;
		case SelectMasterForm::_TimeNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA ORDER BY REGTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY REGTIME;");
			}
			break;
		case SelectMasterForm::_TimeReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA ORDER BY REGTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERCODE,REGTIME,MASTERNAME,REMARK FROM MASTERDATA WHERE CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" ORDER BY REGTIME DESC;");
			}
			break;
		case SelectMasterForm::_NameNormal:
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
		case SelectMasterForm::_NameReverse:
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

SelectMasterForm::SelectMasterForm(LayersBase *Base,const QString &emitterRoot,const QString &emitterName,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	//LangSolver.SetUI(this);
	LogoInQWidget(Base,this,sRoot ,sName);

	ListMode=_NameNormal;
	StartSearchID=0;

	EmitterRoot	=emitterRoot;
	EmitterName =emitterName;
	CategoryID=-1;
	MasterCategory=new MasterCategoryForm(GetLayersBase(),ui.frameCategory);
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	QSqlSelectMasterModel *MModel = new QSqlSelectMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	MListView = new QTableView(ui.frameGrid);
	MListView->setModel(MModel);
	MListView->move(0,0);
	MListView->resize(ui.frameGrid->width(),ui.frameGrid->height());
	MListView->setColumnWidth (0, 120);
	MListView->setColumnWidth (1, 150);
	MListView->setColumnWidth (2, 300);
	MListView->setColumnWidth (3, 250);
	MListView->setSelectionMode(QAbstractItemView::SingleSelection);
	MListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	MListView->setObjectName(/**/"SelectMasterDataListView");
	MListView->show();
	connect(MListView ,SIGNAL(clicked(const QModelIndex &)),this,SLOT(SlotClicked(const QModelIndex &)));
	
	ShowListHeader();
	
	connect(MListView->horizontalHeader() ,SIGNAL(sectionClicked(int)),this,SLOT(MListSectionClicked(int)));
	InstallOperationLog(this);
}

SelectMasterForm::~SelectMasterForm()
{

}

void	SelectMasterForm::ShowListHeader(void)
{
	QSqlSelectMasterModel *MModel = new QSqlSelectMasterModel(this,GetLayersBase()->GetDatabase());
	QString	MasterCodeStr	=LangSolver.GetString(SelectMasterForm_LS,LID_0)/*"MasterCode"*/;
	QString	RegTimeStr		=LangSolver.GetString(SelectMasterForm_LS,LID_1)/*"RegTime"*/;
	QString	NameStr			=LangSolver.GetString(SelectMasterForm_LS,LID_2)/*"Name"*/;
	QString	RemarkStr		=LangSolver.GetString(SelectMasterForm_LS,LID_3)/*"Remark"*/;
	switch(ListMode){
		case  _IDNormal:
			MasterCodeStr=MasterCodeStr+LangSolver.GetString(SelectMasterForm_LS,LID_4)/*"Up"*/;
			ui.lineEditState->setText(LangSolver.GetString(SelectMasterForm_LS,LID_5)/*"MasterCode ->"*/);
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+LangSolver.GetString(SelectMasterForm_LS,LID_6)/*"Down"*/;
			ui.lineEditState->setText(LangSolver.GetString(SelectMasterForm_LS,LID_7)/*"MasterCode <-"*/);
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+LangSolver.GetString(SelectMasterForm_LS,LID_8)/*"Up"*/;
			ui.lineEditState->setText(LangSolver.GetString(SelectMasterForm_LS,LID_9)/*"RegTime ->"*/);
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+LangSolver.GetString(SelectMasterForm_LS,LID_10)/*"Down"*/;
			ui.lineEditState->setText(LangSolver.GetString(SelectMasterForm_LS,LID_11)/*"RegTime <-"*/);
			break;
		case  _NameNormal:
			NameStr		=NameStr+LangSolver.GetString(SelectMasterForm_LS,LID_12)/*"Up"*/;
			ui.lineEditState->setText(LangSolver.GetString(SelectMasterForm_LS,LID_13)/*"MasterName ->"*/);
			break;
		case  _NameReverse:
			NameStr		=NameStr+LangSolver.GetString(SelectMasterForm_LS,LID_14)/*"Down"*/;
			ui.lineEditState->setText(LangSolver.GetString(SelectMasterForm_LS,LID_15)/*"MasterName <-"*/);
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
}


void	SelectMasterForm::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlSelectMasterModel	*M=dynamic_cast<QSqlSelectMasterModel	 *>(MListView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}


void SelectMasterForm::on_ButtonLoad_clicked()
{
	bool	ok;

	SelectView();

	int	MasterCode=ui.EditMasterCode->text().toInt(&ok);
	GetLayersBase()->SetMasterCode(MasterCode);
	GetLayersBase()->SetMasterName(MasterName);
	GetLayersBase()->SetRemark(Remark);
	
	for(int page=0;page<GetPageNumb();page++){
		GUICmdSelectMaster	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.MasterCode	=MasterCode;
		RCmd.MasterName	=MasterName;
		RCmd.Remark		=Remark;
		RCmd.Send(NULL,page,0);
	}

	emit	SignalClose();
}

void SelectMasterForm::on_ButtonCancel_clicked()
{
	emit	SignalClose();
}

void	SelectMasterForm::SlotClicked(const QModelIndex &)
{
	SelectView();
}
void	SelectMasterForm::SelectView(void)
{
	QModelIndex Index=MListView->currentIndex();

	QSqlSelectMasterModel	*M=dynamic_cast<QSqlSelectMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();
		ui.EditMasterCode->setText(QString::number(MasterCode));
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(MasterCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		if(query.next ()==false)
			return;

		MasterName	=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
		Remark		=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
		QByteArray	TopVArray=query.value(query.record().indexOf(/**/"TOPVIEW"	)).toByteArray();
		ui.EditMasterName->setText(MasterName);
		ui.EditRemark	 ->setText(Remark);
		QPixmap		TopView;
		TopView.loadFromData(TopVArray,/**/"PNG");
		ui.labelTopView->setPixmap(TopView);
	}
}


void SelectMasterForm::on_pushButtonStartSearchByName_clicked()
{
	StartSearchName=ui.lineEditSearchName->text();
	ListMode=_NameNormal;

	ShowListHeader();
	QSqlSelectMasterModel	*M=dynamic_cast<QSqlSelectMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}
void	SelectMasterForm::MListSectionClicked ( int logicalIndex )
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
		case 1:
			if(ListMode==_TimeNormal)
				ListMode=_TimeReverse;
			else if(ListMode==_TimeReverse)
				ListMode=_TimeNormal;
			else
				ListMode=_TimeNormal;
			break;
		case 2:
			if(ListMode==_NameNormal)
				ListMode=_NameReverse;
			else if(ListMode==_NameReverse)
				ListMode=_NameNormal;
			else
				ListMode=_NameNormal;
			break;
	}
	ShowListHeader();
	QSqlSelectMasterModel	*M=dynamic_cast<QSqlSelectMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}


void SelectMasterForm::on_pushButtonStartSearchByID_clicked()
{
	StartSearchID=ui.spinBoxSearchID->value();
	ListMode=_IDNormal;

	ShowListHeader();
	QSqlSelectMasterModel	*M=dynamic_cast<QSqlSelectMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();

}

GUICmdSelectMaster::GUICmdSelectMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSelectMaster::Load(QIODevice *f)
{
	if(::Load(f,MasterCode)==false){
		return false;
	}
	if(::Load(f,MasterName)==false){
		return false;
	}
	if(::Load(f,Remark)==false){
		return false;
	}
	return true;
}
bool	GUICmdSelectMaster::Save(QIODevice *f)
{
	if(::Save(f,MasterCode)==false){
		return false;
	}
	if(::Save(f,MasterName)==false){
		return false;
	}
	if(::Save(f,Remark)==false){
		return false;
	}
	return true;
}
void	GUICmdSelectMaster::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->SetMasterCode(MasterCode);
	GetLayersBase()->SetMasterName(MasterName);
	GetLayersBase()->SetRemark(Remark);
}