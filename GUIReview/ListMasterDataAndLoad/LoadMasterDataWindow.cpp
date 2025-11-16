#include "ListMasterDataAndLoadResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUIReview\ListMaster\LoadMasterDataWindow.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "LoadMasterDataWindow.h"
#include "MasterCategoryForm.h"
#include "XDLLOnly.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "ButtonSelectLot.h"
#include "ButtonSelectMachine.h"
#include "XGeneralFunc.h"
#include "ButtonLoadMasterData.h"
#include "XDatabaseLoader.h"
#include "SelectMachineDialog.h"
#include "XFileRegistry.h"
#include "ThreadSequence.h"
//#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include <QHeaderView>

extern	char	*sRoot;
extern	char	*sName;

static	int	CategoryID;

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<LoadMasterDataWindow *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
{
	QString	ret;
	QString	MachineSel=ParentWindow->MakeMachineSQL();
	if(MachineSel.isEmpty()==false){
		MachineSel=QString(/**/" AND (")+MachineSel+QString(/**/")");
	}
	switch(ParentWindow->ListMode){
		case LoadMasterDataWindow::_IDNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERCODE;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+QString(/**/" AND MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERCODE;");
			}
			break;
		case LoadMasterDataWindow::_IDReverse:
			if(ParentWindow->StartSearchID!=0){
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+MachineSel
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE<=")
						+QString::number(ParentWindow->StartSearchID)
						+QString(/**/" AND MASTERDATA.CATEGORYID=")
						+QString::number(CategoryID)
						+MachineSel
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
			}
			else{
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
						+MachineSel
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
				else{
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
						+QString(/**/",MASTERDATA.REMARK")
						+QString(/**/" FROM MASTERDATA,MACHINE ")
						+QString(/**/" WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
						+QString::number(CategoryID)
						+MachineSel
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
			}
			break;
		case LoadMasterDataWindow::_TimeNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.REGTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.REGTIME;");
			}
			break;
		case LoadMasterDataWindow::_TimeReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.REGTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.REGTIME DESC;");
			}
			break;
		case LoadMasterDataWindow::_NameNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERDATA.MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME;");
			}
			break;
		case LoadMasterDataWindow::_NameReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERNAME>=")
					+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERDATA.MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME DESC;");
			}
			break;
		case LoadMasterDataWindow::_LastEditNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME;");
			}
			break;
		case LoadMasterDataWindow::_LastEditReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME DESC;");
			}
			else{
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
					+QString(/**/",MASTERDATA.REMARK")
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME DESC;");
			}
			break;
	}
	return ret;
}
//=========================================================================================

MachineButton::MachineButton(int _MachineID ,LoadMasterDataWindow *_ParentWindow ,QWidget *parent)
:QToolButton(parent)
{
	ParentWindow=_ParentWindow;
	MachineID	=_MachineID;
	setCheckable(true);
	connect(this,SIGNAL(toggled(bool)),this,SLOT(ToggleButton(bool)));
}
void	MachineButton::ToggleButton(bool mode)
{
	ParentWindow->RefreshGrid();
}

LoadMasterDataWindow::LoadMasterDataWindow(LayersBase *Base,const QString &emitterRoot,const QString &emitterName,QWidget *parent)
	: QWidget(parent),ServiceForLayers(Base)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LogoInQWidget(Base,this,sRoot ,sName);
	ParentGUI=(ButtonLoadMasterData *)parent;

	MListView=NULL;
	ListMode=_NameNormal;
	StartSearchID=0;

	EmitterRoot	=emitterRoot;
	EmitterName =emitterName;
	CategoryID=-1;
	MasterCategory=new MasterCategoryForm(GetLayersBase(),ui.frameCategory);
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	LoadMachineList();
	ScrollFrame.setFrameShape(QFrame::NoFrame);
	ui.scrollAreaMachine->setWidget(&ScrollFrame);
	int	Y=0;
	for(MachineList *a=MachineContainer.GetFirst();a!=NULL;a=a->GetNext()){
		MachineButton	*M=new MachineButton(a->MachineID,this,&ScrollFrame);
		M->setText(a->Name);
		M->setGeometry(0,Y,ui.scrollAreaMachine->width()-4,38);
		if(a->MachineID==GetLayersBase()->GetMachineID()){
			M->setChecked(true);
		}
		MachineButtonContainer.AppendList(M);
		Y+=40;
	}
	ScrollFrame.setGeometry(0,0,ui.scrollAreaMachine->width()-3,Y);

	QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	MListView = new QTableView(ui.frameGrid);
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
	connect(MListView ,SIGNAL(clicked(const QModelIndex &)),this,SLOT(SlotClicked(const QModelIndex &)));
	
	ShowListHeader();
	connect(MListView->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	accept = false;
}

LoadMasterDataWindow::~LoadMasterDataWindow()
{

}

void	LoadMasterDataWindow::RefreshGrid(void)
{
	if(MListView!=NULL){
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

QString	LoadMasterDataWindow::MakeMachineSQL(void)
{
	QString	Ret;
	int	N=0;
	for(MachineButton *a=MachineButtonContainer.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->isChecked()==true){
			if(N!=0){
				Ret=Ret+QString(/**/" or ");
			}
			Ret=Ret+QString(/**/"MASTERDATA.MACHINEID=")+QString::number(a->MachineID);
			N++;
		}
	}
	return Ret;
}

void	LoadMasterDataWindow::ShowListHeader(void)
{
	//QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	QSqlLoadMasterModel *MModel = (QSqlLoadMasterModel*)(MListView->model());
	QString	MasterCodeStr	=tr(/**/"MasterCode");
	QString	MachineNameStr	=tr(/**/"Machine");
	QString	RegTimeStr		=tr(/**/"RegTime");
	QString	LastEditStr		=tr(/**/"Last Edit");
	QString	NameStr			=tr(/**/"Name");
	QString	RemarkStr		=tr(/**/"Remark");
	switch(ListMode){
		case  _IDNormal:
			MasterCodeStr=MasterCodeStr+QString(/**/"Up");
			ui.lineEditState->setText(/**/"MasterCode ->");
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+QString(/**/"Down");
			ui.lineEditState->setText(/**/"MasterCode <-");
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+QString(/**/"Up");
			ui.lineEditState->setText(/**/"RegTime ->");
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+QString(/**/"Down");
			ui.lineEditState->setText(/**/"RegTime <-");
			break;
		case  _NameNormal:
			NameStr		=NameStr+QString(/**/"Up");
			ui.lineEditState->setText(/**/"MasterName ->");
			break;
		case  _NameReverse:
			NameStr		=NameStr+QString(/**/"Down");
			ui.lineEditState->setText(/**/"MasterName <-");
			break;
		case  _LastEditNormal:
			LastEditStr	=LastEditStr+QString(/**/"Up");
			ui.lineEditState->setText(/**/"LastEdit ->");
			break;
		case  _LastEditReverse:
			LastEditStr	=LastEditStr+QString(/**/"Down");
			ui.lineEditState->setText(/**/"LastEdit <-");
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, MachineNameStr	,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, LastEditStr	,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(5, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
}


void	LoadMasterDataWindow::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}

void	LoadMasterDataWindow::LoadMachineList(void)
{
	int		EnumMachine[1000];

	MachineContainer.RemoveAll();
	if(GetLayersBase()->GetDatabaseLoader()){
		int	N=GetLayersBase()->GetDatabaseLoader()->G_EnumMachine(*GetLayersBase()->GetDataBase()
																,EnumMachine
																,sizeof(EnumMachine)/sizeof(EnumMachine[0]));
		for(int i=0;i<N;i++){
			MachineList	*a=new MachineList();
			a->MachineID	=EnumMachine[i];
			QString MacNetID;
			QString MacName;
			QString MacVersion;
			QString MacRemark;
			if(GetLayersBase()->GetDatabaseLoader()->G_GetMachineInfo(*GetLayersBase()->GetDataBase()
																	,EnumMachine[i]
																	,MacNetID
																	,MacName
																	,MacVersion
																	,MacRemark)==true){
				a->NetID=MacNetID;
				a->Name=MacName;
				a->Version=MacVersion;
				a->Remark=MacRemark;
				MachineContainer.AppendList(a);
			}
		}
	}
}

int LoadMasterDataWindow::currentMachineID()
{
	for(int i=0; i<MachineButtonContainer.count(); i++){
		if(MachineButtonContainer[i]->isChecked()){
			return MachineButtonContainer[i]->MachineID;
		}
	}
	return -1;
}

void LoadMasterDataWindow::on_ButtonLoad_clicked()
{
	bool	ok;

	SelectView();

	SelectedMasterCode=ui.EditMasterCode->text().toInt(&ok);
	if(ok==true){
		accept = true;
		emit	SignalClose();
	}
}

void LoadMasterDataWindow::on_ButtonCancel_clicked()
{
	accept = false;
	emit	SignalClose();
}

void	LoadMasterDataWindow::SlotClicked(const QModelIndex &)
{
	SelectView();
}
void	LoadMasterDataWindow::SelectView(void)
{
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();
		ui.EditMasterCode->setText(QString::number(MasterCode));
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(MasterCode);
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
	}
}


void LoadMasterDataWindow::on_pushButtonStartSearchByName_clicked()
{
	StartSearchName=ui.lineEditSearchName->text();
	ListMode=_NameNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}
void	LoadMasterDataWindow::MListSectionClicked ( int logicalIndex )
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


void LoadMasterDataWindow::on_pushButtonStartSearchByID_clicked()
{
	StartSearchID=ui.spinBoxSearchID->value();
	ListMode=_IDNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();

}