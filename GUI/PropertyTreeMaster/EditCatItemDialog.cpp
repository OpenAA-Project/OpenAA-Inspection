#include "AddAreaDialogResource.h"
#include "EditCatItemDialog.h"
#include "ui_EditCatItemDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include "XGeneralFunc.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

static	int	CategoryID;

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<EditCatItemDialog *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
{
	QString	ret;
	QString	MachineSel=ParentWindow->MakeMachineSQL();
	if(MachineSel.isEmpty()==false){
		MachineSel=QString(/**/" AND (")+MachineSel+QString(/**/")");
	}
	switch(ParentWindow->ListMode){
		case EditCatItemDialog::_IDNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
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
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.MASTERCODE>=")
					+QString::number(ParentWindow->StartSearchID)
					+QString(/**/" AND MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERCODE;");
			}
			break;
		case EditCatItemDialog::_IDReverse:
			if(ParentWindow->StartSearchID!=0){
				if(CategoryID==-1){
					ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
						+QString(/**/",MACHINE.NAME")
						+QString(/**/",MASTERDATA.REGTIME")
						+QString(/**/",MASTERDATA.LASTEDITTIME")
						+QString(/**/",MASTERDATA.MASTERNAME")
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
						+QString(/**/" FROM MASTERDATA,MACHINE ")
						+QString(/**/" WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
						+QString::number(CategoryID)
						+MachineSel
						+QString(/**/" ORDER BY MASTERDATA.MASTERCODE DESC;");
				}
			}
			break;
		case EditCatItemDialog::_TimeNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
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
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.REGTIME;");
			}
			break;
		case EditCatItemDialog::_TimeReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
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
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.REGTIME DESC;");
			}
			break;
		case EditCatItemDialog::_NameNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
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
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERDATA.MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME;");
			}
			break;
		case EditCatItemDialog::_NameReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
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
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+QString(/**/" and MASTERDATA.MASTERNAME>=")+QString(/**/"\'")+ParentWindow->StartSearchName+QString(/**/"\'")
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.MASTERNAME DESC;");
			}
			break;
		case EditCatItemDialog::_LastEditNormal:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
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
					+QString(/**/" FROM MASTERDATA,MACHINE WHERE MACHINE.MACHINEID=MASTERDATA.MACHINEID and MASTERDATA.CATEGORYID=")
					+QString::number(CategoryID)
					+MachineSel
					+QString(/**/" ORDER BY MASTERDATA.LASTEDITTIME;");
			}
			break;
		case EditCatItemDialog::_LastEditReverse:
			if(CategoryID==-1){
				ret=QString(/**/"SELECT MASTERDATA.MASTERCODE")
					+QString(/**/",MACHINE.NAME")
					+QString(/**/",MASTERDATA.REGTIME")
					+QString(/**/",MASTERDATA.LASTEDITTIME")
					+QString(/**/",MASTERDATA.MASTERNAME")
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

MachineButton::MachineButton(int _MachineID ,EditCatItemDialog *_ParentWindow ,QWidget *parent)
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

//=========================================================================================

EditCatItemDialog::EditCatItemDialog(int TMItemID ,LayersBase *Base,QTableWidget *TMList,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::EditCatItemDialog)
{
    ui->setupUi(this);

	MListView=NULL;
	ListMode=_NameNormal;
	StartSearchID=0;

	CategoryID=-1;
	MasterCategory=new MasterCategoryForm(GetLayersBase(),ui->frameCategory);
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	LoadMachineList();
	ScrollFrame.setFrameShape(QFrame::NoFrame);
	ui->scrollAreaMachine->setWidget(&ScrollFrame);
	int	Y=0;
	for(MachineList *a=MachineContainer.GetFirst();a!=NULL;a=a->GetNext()){
		MachineButton	*M=new MachineButton(a->MachineID,this,&ScrollFrame);
		M->setText(a->Name);
		M->setGeometry(0,Y,ui->scrollAreaMachine->width()-4,38);
		if(a->MachineID==GetLayersBase()->GetMachineID()){
			M->setChecked(true);
		}
		MachineButtonContainer.AppendList(M);
		Y+=40;
	}
	ScrollFrame.setGeometry(0,0,ui->scrollAreaMachine->width()-3,Y);

	QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	MListView = new QTableView(ui->frameGrid);
	MListView->setModel(MModel);
	MListView->setObjectName(/**/"MListView");
	MListView->move(0,0);
	MListView->resize(ui->frameGrid->width(),ui->frameGrid->height());
	MListView->setColumnWidth (0, 90);
	MListView->setColumnWidth (1, 100);
	MListView->setColumnWidth (2, 120);
	MListView->setColumnWidth (3, 120);
	MListView->setColumnWidth (4, 220);
	MListView->setSelectionMode(QAbstractItemView::SingleSelection);
	MListView->setSelectionBehavior(QAbstractItemView::SelectRows);
	MListView->setObjectName(/**/"SelectMasterDataListView");
	MListView->show();
	connect(MListView ,SIGNAL(clicked(const QModelIndex &)),this,SLOT(SlotClicked(const QModelIndex &)));
	
	ShowListHeader();
	connect(MListView->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	ui->lineEditCatID	->setText(QString::number(TMItemID));
	ui->lineEditCatName->setText(GetLayersBase()->GetMasterName());

	ui->tableWidgetDst->setColumnWidth (0,45);
	ui->tableWidgetDst->setColumnWidth (1,100);
	ui->tableWidgetDst->setColumnWidth (2,64);
	ui->tableWidgetDst->setColumnWidth (3,100);
	ui->tableWidgetDst->setColumnWidth (4,40);

	ui->tableWidgetDst->setRowCount(TMList->rowCount());
	for(int	N=0;N<TMList->rowCount();N++){
		::SetDataToTable(ui->tableWidgetDst,0,N,TMList->item(N,0)->text());
		::SetDataToTable(ui->tableWidgetDst,1,N,TMList->item(N,1)->text());
		::SetDataToTable(ui->tableWidgetDst,2,N,TMList->item(N,2)->text());
		::SetDataToTable(ui->tableWidgetDst,3,N,TMList->item(N,3)->text());
		::SetDataToTable(ui->tableWidgetDst,4,N,TMList->item(N,4)->text());
	}
	InstallOperationLog(this);
}

void	EditCatItemDialog::Initial(QString catname, int mastercode)
{
	ui->lineEditCatName	->setText(catname);
	ui->pushButtonDelete->setEnabled(true);

	QString	S=QString(/**/"SELECT MASTERCODE FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(mastercode);
	QSqlQuery query(S ,GetLayersBase()->GetDatabase());
	if(query.next ()==true){
	}
}

EditCatItemDialog::~EditCatItemDialog()
{
    delete ui;
}

void	EditCatItemDialog::RefreshGrid(void)
{
	if(MListView!=NULL){
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

QString	EditCatItemDialog::MakeMachineSQL(void)
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

void	EditCatItemDialog::ShowListHeader(void)
{
	//QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	QSqlLoadMasterModel *MModel = (QSqlLoadMasterModel*)(MListView->model());
	QString	MasterCodeStr	=LangSolver.GetString(EditCatItemDialog_LS,LID_0)/*"MasterCode"*/;
	QString	MachineNameStr	=LangSolver.GetString(EditCatItemDialog_LS,LID_1)/*"Machine"*/;
	QString	RegTimeStr		=LangSolver.GetString(EditCatItemDialog_LS,LID_2)/*"RegTime"*/;
	QString	LastEditStr		=LangSolver.GetString(EditCatItemDialog_LS,LID_3)/*"Last Edit"*/;
	QString	NameStr			=LangSolver.GetString(EditCatItemDialog_LS,LID_4)/*"Name"*/;
	switch(ListMode){
		case  _IDNormal:
			MasterCodeStr=MasterCodeStr+LangSolver.GetString(EditCatItemDialog_LS,LID_5)/*"Up"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_6)/*"MasterCode ->"*/);
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+LangSolver.GetString(EditCatItemDialog_LS,LID_7)/*"Down"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_8)/*"MasterCode <-"*/);
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+LangSolver.GetString(EditCatItemDialog_LS,LID_9)/*"Up"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_10)/*"RegTime ->"*/);
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+LangSolver.GetString(EditCatItemDialog_LS,LID_11)/*"Down"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_12)/*"RegTime <-"*/);
			break;
		case  _NameNormal:
			NameStr		=NameStr+LangSolver.GetString(EditCatItemDialog_LS,LID_13)/*"Up"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_14)/*"MasterName ->"*/);
			break;
		case  _NameReverse:
			NameStr		=NameStr+LangSolver.GetString(EditCatItemDialog_LS,LID_15)/*"Down"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_16)/*"MasterName <-"*/);
			break;
		case  _LastEditNormal:
			LastEditStr	=LastEditStr+LangSolver.GetString(EditCatItemDialog_LS,LID_17)/*"Up"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_18)/*"LastEdit ->"*/);
			break;
		case  _LastEditReverse:
			LastEditStr	=LastEditStr+LangSolver.GetString(EditCatItemDialog_LS,LID_19)/*"Down"*/;
			ui->lineEditState->setText(LangSolver.GetString(EditCatItemDialog_LS,LID_20)/*"LastEdit <-"*/);
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, MachineNameStr	,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, LastEditStr	,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, NameStr		,Qt::DisplayRole);
}


void	EditCatItemDialog::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}

void	EditCatItemDialog::LoadMachineList(void)
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
				a->Name=MacName;
				MachineContainer.AppendList(a);
			}
		}
	}
}
void	EditCatItemDialog::SlotClicked(const QModelIndex &)
{
	SelectView();
}

void	EditCatItemDialog::SelectView(void)
{
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();

		QString	S=QString(/**/"SELECT TOPVIEW FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(MasterCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		if(query.next ()==false)
			return;

		QByteArray	TopVArray=query.value(query.record().indexOf(/**/"TOPVIEW"	)).toByteArray();
		QPixmap		TopView;
		TopView.loadFromData(TopVArray,/**/"PNG");
		ui->labelTopView->setPixmap(TopView);

		QModelIndex SIndex = Index.sibling(Index.row(),4);
		ui->lineEditCatName->setText(M->data(SIndex).toString());
	}
}
void EditCatItemDialog::on_pushButtonOK_clicked()
{
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		SelectedMasterCode	=M->data(RIndex).toInt();
		SelectedMasterName = M->data(Index.sibling(Index.row(),4)).toString();
		CatName				=ui->lineEditCatName->text();
		Deleted				=false;
		done(true);
	}
}

void EditCatItemDialog::on_pushButtonDelete_clicked()
{
	int currentRow = ui->tableWidgetDst->currentRow();
	if(currentRow<0)
		return;
	ui->tableWidgetDst->removeRow(currentRow);
	for(int row = currentRow;row<ui->tableWidgetDst->rowCount();row++){
		QTableWidgetItem *item = ui->tableWidgetDst->item(row,0);
		if(item!=NULL){
			int catID = item->text().toInt() - 1;
			item->setText(QString::number(catID));
		}
	}
	int CatID = ui->tableWidgetDst->rowCount() + 1;
	ui->lineEditCatID->setText(QString::number(CatID));
	/*Deleted				=true;
	done(true);*/
}

void EditCatItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void EditCatItemDialog::on_pushButtonStartSearchByID_clicked()
{
	StartSearchID=ui->spinBoxSearchID->value();
	ListMode=_IDNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void EditCatItemDialog::on_pushButtonStartSearchByName_clicked()
{
	StartSearchName=ui->lineEditSearchName->text();
	ListMode=_NameNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void	EditCatItemDialog::MListSectionClicked ( int logicalIndex )
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

void EditCatItemDialog::on_pushButtonNew_clicked()
{
	for(int row=0;row<ui->tableWidgetDst->rowCount();row++){
		if(ui->tableWidgetDst->item(row,2)->text().toInt() == GetLayersBase()->GetMasterCode()){
			QMessageBox::information(0,/**/"Dialog",LangSolver.GetString(EditCatItemDialog_LS,LID_21)/*"The item has already exsisted in current masterdata. "*/,QMessageBox::Close);
			return;
		}
	}
	int R = ui->tableWidgetDst->rowCount();
	ui->tableWidgetDst->setRowCount(R+1);
	for(int row=0;row<=R;row++){
		for(int column=0;column<4;column++){
			QTableWidgetItem *item = new QTableWidgetItem();
			ui->tableWidgetDst->setItem(row,column,item);
		}
	}
	::SetDataToTable(ui->tableWidgetDst,0,R,ui->lineEditCatID->text());
	::SetDataToTable(ui->tableWidgetDst,1,R,ui->lineEditCatName->text());
	::SetDataToTable(ui->tableWidgetDst,2,R,GetLayersBase()->GetMasterCode());
	::SetDataToTable(ui->tableWidgetDst,3,R,GetLayersBase()->GetMasterName());
	::SetDataToTable(ui->tableWidgetDst,4,R,/**/"");

	ui->lineEditCatID->setText(QString::number(ui->lineEditCatID->text().toInt() + 1));
}

void EditCatItemDialog::on_pushButtonAdd_clicked()
{
	QModelIndex Index=MListView->currentIndex();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int MasterCode	=M->data(RIndex).toInt();
		QString MasterName = M->data(Index.sibling(Index.row(),4)).toString();
		CatName				=ui->lineEditCatName->text();

		for(int row=0;row<ui->tableWidgetDst->rowCount();row++){
			if(MasterCode == ui->tableWidgetDst->item(row,2)->text().toInt()){
				::SetDataToTable(ui->tableWidgetDst,1,row,ui->lineEditCatName->text());
				return;
			}
		}
		int R = ui->tableWidgetDst->rowCount();
		ui->tableWidgetDst->setRowCount(R+1);
		for(int column=0;column<4;column++){
			QTableWidgetItem *item = new QTableWidgetItem();
			ui->tableWidgetDst->setItem(R,column,item);
		}
		::SetDataToTable(ui->tableWidgetDst,0,R,ui->lineEditCatID->text());
		::SetDataToTable(ui->tableWidgetDst,1,R,ui->lineEditCatName->text());
		::SetDataToTable(ui->tableWidgetDst,2,R,MasterCode);
		::SetDataToTable(ui->tableWidgetDst,3,R,MasterName);
		::SetDataToTable(ui->tableWidgetDst,4,R,/**/"");

		ui->lineEditCatID->setText(QString::number(ui->lineEditCatID->text().toInt() + 1));
	}
}

QTableWidget *EditCatItemDialog::getTable(){
	return ui->tableWidgetDst;
}
void EditCatItemDialog::on_tableWidgetDst_doubleClicked(const QModelIndex &index)
{
	int currentRow = ui->tableWidgetDst->currentRow();
	if(currentRow<0)
		return;
	QString	AlertMark=ui->tableWidgetDst->item(currentRow,4)->text();
	if(AlertMark.isEmpty()==true){
		::SetDataToTable(ui->tableWidgetDst,4,currentRow,/**/"●");
	}
	else{
		::SetDataToTable(ui->tableWidgetDst,4,currentRow,/**/"");
	}
}
