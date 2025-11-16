#include "ResultDataManagerResource.h"
#include "ManageByLot.h"
#include "ui_ManageByLot.h"

#include "MasterCategoryForm.h"
#include "XDLLOnly.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>
#include <QRegularExpression>
#include <QDateTime>
#include "ButtonSelectMachine.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"
#include "SelectMachineDialog.h"
#include "XFileRegistry.h"
#include "XMLGeneralFunc.h"
#include "XDirectoryAPI.h"
#include <QProgressDialog>
#include <QProgressBar>
#include <QScrollBar>

static	int	CategoryID;

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<ManageByLot *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
{
	QString	ret;
	QString	MachineSel=ParentWindow->MakeMachineSQL();
	if(MachineSel.isEmpty()==false){
		MachineSel=QString(/**/" AND (")+MachineSel+QString(/**/")");
	}
	switch(ParentWindow->ListMode){
		case ManageByLot::_IDNormal:
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
		case ManageByLot::_IDReverse:
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
		case ManageByLot::_TimeNormal:
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
		case ManageByLot::_TimeReverse:
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
		case ManageByLot::_NameNormal:
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
		case ManageByLot::_NameReverse:
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
		case ManageByLot::_LastEditNormal:
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
		case ManageByLot::_LastEditReverse:
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

MachineButton::MachineButton(int _MachineID ,ManageByLot *_ParentWindow ,QWidget *parent)
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

ManageByLot::ManageByLot(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::ManageByLot)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	SParam=Param;

	XMLServer=new XMLServerHandle(SParam->XML_IPAddress,SParam->XML_Port,this);
	XMLServer->SetParam(&ServerParam);
	ServerParam.LoadDefault(GetLayersBase()->GetUserPath());

	if(XMLServer->Open()==false){
		QMessageBox::warning(this, /**/"Check:XMLServer"
								, LangSolver.GetString(ManageByLot_LS,LID_8)/*"XMLServerに接続できない"*/);
	}

	SQLDatabase=GetLayersBase()->GetDatabaseLoader();

	if(GetLayersBase()->GetDatabase().tables().isEmpty()){
		QMessageBox::warning(this, /**/"Check:Database"
						, LangSolver.GetString(ManageByLot_LS,LID_9)/*"データベース異常"*/
						+ QString(/**/"\n") 
						+ LangSolver.GetString(ManageByLot_LS,LID_10)/*"テーブルを開けない"*/);
	}

	MListView=NULL;
	ListMode=_NameNormal;
	StartSearchID=0;
	SelectedMachineID	=-1;
	SelectedMasterCode	=-1;

	CategoryID=-1;
	//MasterCategory=new MasterCategoryForm(GetLayersBase(),ui->frameCategory);
	QGridLayout *glayout = new QGridLayout;
	MasterCategory = new MasterCategoryForm(GetLayersBase(), NULL);
	glayout->addWidget(MasterCategory, 0, 0);
	ui->frameCategory->setLayout(glayout);
	
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	LoadMachineList();
	//ScrollFrame.setFrameShape(QFrame::NoFrame);
	//ScrollFrame.setParent(this);
	//ui->scrollAreaWidgetContents->resize(ui->scrollAreaMachine->width()-3,MachineContainer.GetCount()*40);
	int	Y=0;
	if(MachineContainer.IsEmpty()==false){
		int	H=300/MachineContainer.GetCount()-1;
		for(MachineList *a=MachineContainer.GetFirst();a!=NULL;a=a->GetNext()){
			MachineButton	*M=new MachineButton(a->MachineID,this,ui->scrollAreaWidgetContents);
			M->setText(a->Name);
			M->setGeometry(0,Y,ui->scrollAreaMachine->width()-4,H-1);
			if(a->MachineID==GetLayersBase()->GetMachineID()){
				M->setChecked(true);
			}
			MachineButtonContainer.AppendList(M);
			Y+=H;
		}
	}
	//ui->scrollAreaWidgetContents->setGeometry(0,0,ui->scrollAreaMachine->width()-3,Y);
	//ScrollFrame.setGeometry(0,0,ui->scrollAreaMachine->width()-3,Y);
	//ScrollFrame.update();
	//ScrollFrame.show();
	//ui->scrollAreaMachine->setWidget(&ScrollFrame);

	QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	//MListView = new QTableView(ui->frameGrid);
	MListView = new QTableView(NULL);
	MListView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	MListView->horizontalHeader()->setStretchLastSection(true);
	glayout = new QGridLayout;
	glayout->addWidget(MListView);
	ui->frameGrid->setLayout(glayout);
	MListView->setModel(MModel);
	MListView->setObjectName(/**/"MListView");
	MListView->move(0,0);
	MListView->resize(ui->frameGrid->width(),ui->frameGrid->height());
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

	ui->tableWidgetLot->setColumnWidth(0,200);
	ui->tableWidgetLot->setColumnWidth(1,200);
	ui->tableWidgetLot->setColumnWidth(2,120);
	ui->tableWidgetLot->setColumnWidth(3,120);
	ui->tableWidgetLot->setColumnWidth(4,90);

	ui->tableWidgetInspection->setColumnWidth(0,60);
	ui->tableWidgetInspection->setColumnWidth(1,120);
	ui->tableWidgetInspection->setColumnWidth(2,60);

	ui->tableWidgetLot->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	ui->tableWidgetInspection->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	
	hhLotHeaderList << LangSolver.GetString(ManageByLot_LS,LID_11)/*"ロットファイル名"*/
					<< LangSolver.GetString(ManageByLot_LS,LID_12)/*"ロット名"*/ 
					<< LangSolver.GetString(ManageByLot_LS,LID_13)/*"開始検査時間"*/ 
					<< LangSolver.GetString(ManageByLot_LS,LID_14)/*"終了検査時間"*/
					<< LangSolver.GetString(ManageByLot_LS,LID_15)/*"検査数"*/;
	ui->tableWidgetLot->setHorizontalHeaderLabels(hhLotHeaderList);

	on_cbShowInspectFirstEndTime_stateChanged(Qt::CheckState::Unchecked);
	on_cbShowInspectionCount_stateChanged(Qt::CheckState::Unchecked);

	hhInsHeaderList << LangSolver.GetString(ManageByLot_LS,LID_16)/*"検査番号"*/
					<< LangSolver.GetString(ManageByLot_LS,LID_17)/*"日時"*/
					<< LangSolver.GetString(ManageByLot_LS,LID_18)/*"検査結果"*/;
	ui->tableWidgetInspection->setHorizontalHeaderLabels(hhInsHeaderList);

	connect(ui->tableWidgetLot->verticalScrollBar(), SIGNAL(valueChanged(int)), SLOT(SlotResizeHorizontalItemWidth()));
}

ManageByLot::~ManageByLot()
{
    delete ui;

	XMLServer->Close();
	while(XMLServer->GetState()==true){
		GSleep(1);
	}
	delete	XMLServer;
}

void	ManageByLot::RefreshGrid(void)
{
	if(MListView!=NULL){
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

QString	ManageByLot::MakeMachineSQL(void)
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

void	ManageByLot::ShowListHeader(void)
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
			ui->lineEditState->setText(/**/"MasterCode ->");
			break;
		case  _IDReverse:
			MasterCodeStr=MasterCodeStr+QString(/**/"Down");
			ui->lineEditState->setText(/**/"MasterCode <-");
			break;
		case  _TimeNormal:
			RegTimeStr	=RegTimeStr+QString(/**/"Up");
			ui->lineEditState->setText(/**/"RegTime ->");
			break;
		case  _TimeReverse:
			RegTimeStr	=RegTimeStr+QString(/**/"Down");
			ui->lineEditState->setText(/**/"RegTime <-");
			break;
		case  _NameNormal:
			NameStr		=NameStr+QString(/**/"Up");
			ui->lineEditState->setText(/**/"MasterName ->");
			break;
		case  _NameReverse:
			NameStr		=NameStr+QString(/**/"Down");
			ui->lineEditState->setText(/**/"MasterName <-");
			break;
		case  _LastEditNormal:
			LastEditStr	=LastEditStr+QString(/**/"Up");
			ui->lineEditState->setText(/**/"LastEdit ->");
			break;
		case  _LastEditReverse:
			LastEditStr	=LastEditStr+QString(/**/"Down");
			ui->lineEditState->setText(/**/"LastEdit <-");
			break;
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, MachineNameStr	,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, LastEditStr	,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(5, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
}

void	ManageByLot::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	::CategoryID=_CategoryID;

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	ListMode=_IDNormal;
	ShowListHeader();
	if(M!=NULL)
		M->select();
}

void	ManageByLot::SlotResizeHorizontalItemWidth()
{
	ui->tableWidgetLot->horizontalHeader()->resizeSections(QHeaderView::ResizeMode::ResizeToContents);
	ui->tableWidgetLot->horizontalHeader()->setStretchLastSection(true);
}

void	ManageByLot::LoadMachineList(void)
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

void	ManageByLot::SlotClicked(const QModelIndex &)
{
	SelectView();

	int	MachineID ,MasterCode;
	QModelIndex Index=MListView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	MasterCode=M->data(RIndex).toInt();
		QString	S=QString(/**/"SELECT MACHINEID FROM MASTERDATA WHERE MASTERCODE=")
			+QString::number(MasterCode);
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		if(query.next ()==false)
			return;
		MachineID	=query.value(query.record().indexOf(/**/"MACHINEID")).toInt();
	
		SelectedMachineID	=MachineID;
		SelectedMasterCode	=MasterCode;
		ShowLotAll(SelectedMachineID ,SelectedMasterCode);
		clearInspectionTable();
	}
}

void	ManageByLot::SelectView(void)
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
		ui->labelTopView->setPixmap(TopView);
	}
}

void	ManageByLot::MListSectionClicked ( int logicalIndex )
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

void ManageByLot::on_pushButtonStartSearchByID_clicked()
{
	StartSearchID=ui->spinBoxSearchID->value();
	ListMode=_IDNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void ManageByLot::on_pushButtonStartSearchByName_clicked()
{
	StartSearchName=ui->lineEditSearchName->text();
	ListMode=_NameNormal;

	ShowListHeader();
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(MListView->model());
	if(M!=NULL)
		M->select();
}

void ManageByLot::on_pushButtonDeleteLot_clicked()
{
	IntList	SelectedLines;
	int	N=ui->tableWidgetLot->selectedItems ().count();
	if(N==0){
		return;
	}
	for(int i=0;i<N;i++){
		QTableWidgetItem *w=ui->tableWidgetLot->selectedItems ()[i];
		if(w->column()==0){
			SelectedLines.Add(w->row());
		}
	}
	QStringList modDirectories;
	QStringList deleteTableList;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext()){
		QStringList	JDTFileNames;
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(w->TableName);
			if(OpeHandle!=NULL){
				QString		OutputStr	=QString(/**/"<IST NGJ/>");
				QString		SearchStr	=QString(/**/"<IST */>");
				QStringList	ResultListStr;
				bool	SelectRet1=OpeHandle->Select(OutputStr,SearchStr,/**/"",ResultListStr);
				if(SelectRet1==true){
					int	N=ResultListStr.count();
					for(int i=0;i<N;i++){
						QString NGJFile;
						if(GetXMLAttrStr (ResultListStr[i],/**/"NGJ",NGJFile)==true){
							QString	FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
							QStringList	List=SParam->ImageDrive.split(QRegularExpression(/**/"[/\\\\]"),QString::SplitBehavior::SkipEmptyParts);
							int	LPoint=0;
							while(LPoint<List.count()){
								if((NGJFile.at(0)=='/' || NGJFile.at(0)=='\\') && (NGJFile.at(0)=='/' || NGJFile.at(0)=='\\')){
									NGJFile=NGJFile.remove(0,2);
									if(NGJFile.contains(/**/"NGImage2")==true){
										NGJFile=NGJFile.section('/',1);
										NGJFile=QString(/**/"NGImage2/")+NGJFile;
									}
									else if(NGJFile.contains(/**/"NGImage")==true){
										NGJFile=NGJFile.section('/',1);
										NGJFile=QString(/**/"NGImage/")+NGJFile;
									}
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
								}
								else if(NGJFile.at(0)==/**/'/' || NGJFile.at(0)==/**/'\\'){
									NGJFile=NGJFile.remove(0,1);
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
								}
								else if(NGJFile.left(List[LPoint].count())==List[LPoint]){
									NGJFile=NGJFile.mid(List[LPoint].count());
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
									LPoint++;
								}
								else{
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
									break;
								}
							}
							QFileInfo	FInfo(FileName);
							//QDir	SearchName(FInfo.absolutePath());
							//QStringList	FileSearchFilter;
							//FileSearchFilter.append(FInfo.fileName());
							//QStringList	FileList=SearchName.entryList(FileSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
							QStringList	FileList = GetDirectoryFileList(FInfo.absolutePath(), FInfo.fileName());
							for(int j=0;j<FileList.count();j++){
								JDTFileNames.append(FInfo.absolutePath() + ::GetSeparator()+FileList[j]);
							}
						}
					}
				}
				XMLServer->CloseXMLOperation(OpeHandle);
			}
		
			QString filepath;
			DeleteTable(w->TableName
					,XMLServer
					,SQLDatabase ,*GetLayersBase()->GetDataBase()
					,SParam, &filepath);
			deleteTableList.append(w->TableName);
			if(filepath.isEmpty()==false && modDirectories.contains(filepath)==false){
				modDirectories.append(filepath);
			}

			int	N=JDTFileNames.count();
			for(int i=0;i<N;i++){
				QFile	JDTFile(JDTFileNames[i]);
				JDTFile.remove();
			}

			::GSleep(SParam->WaitMilisec);
		}
	}
	for(QStringList::Iterator it=modDirectories.begin(); it!=modDirectories.end(); it++){
		DeleteEmptyDirectory(*it);
	}

	XMLServer->Close();
	while(XMLServer->GetState()==true){
		GSleep(1);
	}

	if(deleteTableList.isEmpty()==false){
		if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
			QMessageBox::warning(this, /**/"XMLServerError"
										,LangSolver.GetString(ManageByLot_LS,LID_19)/*"ロットデータを削除できない"*/);
			return;
		}else{
			for(int i=0; i<deleteTableList.count(); i++){
				XMLServer->DeleteTable(deleteTableList[i]);
			}
			XMLServer->Close();
		}
	}

	ShowLotAll(SelectedMachineID ,SelectedMasterCode);

	ui->tableWidgetLot->setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);
}

void ManageByLot::on_pushButtonDeleteAll_clicked()
{
	QProgressDialog progress;
	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_20)/*"表示中の全ロットを削除中"*/);
	progress.setRange(0, CurrentAllLots.count());
	progress.setModal(true);

	int count=0;
	QStringList deleteTableList;
	QStringList JDTFileNames;
	for(LotInfo	*w=CurrentAllLots.GetFirst();w!=NULL;w=w->GetNext(),count++){
		progress.setValue(count);
		qApp->processEvents();
		if(progress.wasCanceled()==true){
			break;
		}
		XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(w->TableName);
		if(OpeHandle!=NULL){
			QString		OutputStr	=QString(/**/"<IST NGJ/>");
			QString		SearchStr	=QString(/**/"<IST */>");
			QStringList	ResultListStr;
			bool	SelectRet1=OpeHandle->Select(OutputStr,SearchStr,/**/"",ResultListStr);
			if(SelectRet1==true){
				int	N=ResultListStr.count();
				for(int i=0;i<N;i++){
					QString NGJFile;
					if(GetXMLAttrStr (ResultListStr[i],/**/"NGJ",NGJFile)==true){
						QString	FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
						QStringList	List=SParam->ImageDrive.split(QRegularExpression(/**/"[/\\\\]"),QString::SplitBehavior::SkipEmptyParts);
						int	LPoint=0;
						while(LPoint<List.count()){
							if((NGJFile.at(0)==/**/'/' || NGJFile.at(0)==/**/'\\') && (NGJFile.at(0)==/**/'/' || NGJFile.at(0)==/**/'\\')){
								NGJFile=NGJFile.remove(0,2);
								if(NGJFile.contains(/**/"NGImage2")==true){
									NGJFile=NGJFile.section('/',1);
									NGJFile=QString(/**/"NGImage2/")+NGJFile;
								}
								else if(NGJFile.contains(/**/"NGImage")==true){
									NGJFile=NGJFile.section(/**/'/',1);
									NGJFile=QString(/**/"NGImage/")+NGJFile;
								}
								FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
							}
							else if(NGJFile.at(0)=='/' || NGJFile.at(0)=='\\'){
								NGJFile=NGJFile.remove(0,1);
								FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
							}
							else if(NGJFile.left(List[LPoint].count())==List[LPoint]){
								NGJFile=NGJFile.mid(List[LPoint].count());
								FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
								LPoint++;
							}
							else{
								FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
									break;
								}
							}
						QFileInfo	FInfo(FileName);
						//QDir	SearchName(FInfo.absolutePath());
						//QStringList	FileSearchFilter;
						//FileSearchFilter.append(FInfo.fileName());
						//QStringList	FileList=SearchName.entryList(FileSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
						QStringList	FileList = GetDirectoryFileList(FInfo.absolutePath(), FInfo.fileName());
						for(int j=0;j<FileList.count();j++){
							JDTFileNames.append(FInfo.absolutePath() + ::GetSeparator()+FileList[j]);
						}
					}
				}
			}
			XMLServer->CloseXMLOperation(OpeHandle);
		}
		QString filepath;
		DeleteTable(w->TableName
					,XMLServer
					,SQLDatabase ,*GetLayersBase()->GetDataBase()
					,SParam,&filepath);
		deleteTableList.append(w->TableName);
		::GSleep(SParam->WaitMilisec);
	}
	
	XMLServer->Close();
	while(XMLServer->GetState()==true){
		GSleep(1);
	}

	if(deleteTableList.isEmpty()==false){
		if(XMLServer->GetState()==false && XMLServer->Open()==false){
			QMessageBox::warning(this, /**/"XMLServerError"
										, LangSolver.GetString(ManageByLot_LS,LID_21)/*"ロットデータを削除できない"*/);
			return;
		}else{
			for(int i=0; i<deleteTableList.count(); i++){
				XMLServer->DeleteTable(deleteTableList[i]);
				GSleep(SParam->WaitMilisec);
			}
			XMLServer->Close();
		}
	}

	int	N=JDTFileNames.count();
	for(int i=0;i<N;i++){
		QFile	JDTFile(JDTFileNames[i]);
		JDTFile.remove();
	}

	progress.setVisible(false);
	ShowLotAll(SelectedMachineID ,SelectedMasterCode);

	ui->tableWidgetLot->setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);
}

void ManageByLot::on_tableWidgetLot_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetLot->currentRow();
	if(Row>=0){
		LotInfo	*w=CurrentAllLots.GetItem(Row);
		if(w!=NULL){
			ShowAllInspect(w);
		}
		ui->tableWidgetLot->setCurrentCell(index.row(), index.column(), QItemSelectionModel::SelectionFlag::Rows | QItemSelectionModel::SelectionFlag::Select | QItemSelectionModel::SelectionFlag::Current);
		ui->tableWidgetInspection->setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);
		for(int y=0; y<ui->tableWidgetInspection->rowCount(); y++){
			for(int x=0; x<ui->tableWidgetInspection->columnCount(); x++){
				ui->tableWidgetInspection->item(y, x)->setTextAlignment(Qt::AlignCenter);
			}
		}
	}
}

void ManageByLot::ShowAllInspect(LotInfo *w)
{
	if(XMLServer->GetState()==false && XMLServer->Open()==false){
		QMessageBox::warning(this, /**/"XMLServerError"
								, LangSolver.GetString(ManageByLot_LS,LID_22)/*"XMLServerに接続できない"*/);
		return;
	}

	XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(w->TableName);
	if(OpeHandle!=NULL){
		QString	OutputStr	=QString(/**/"<IST><INSPECT EID/><TIM>*</TIM><RES>*</RES></IST>");
		QString	SearchStr	=QString(/**/"<IST */>");
		QString	OrderStr	=QString(/**/"EID<INSPECT/>");
		QString InspectID;
		QString InspectTime;
		QString Result;
		QStringList	ResultStr;
		bool	SelectRet1=OpeHandle->Select(OutputStr,SearchStr,OrderStr,ResultStr);
		if(SelectRet1==true){
			CurrentLotTime.clear();
			int	N=ResultStr.count();
			ui->tableWidgetInspection->setRowCount(N);
			for(int i=0;i<N;i++){
				GetXMLAttrStr (ResultStr[i],/**/"EID",InspectID);
				GetXMLValueStr(ResultStr[i],/**/"TIM",InspectTime);
				GetXMLValueStr(ResultStr[i],/**/"RES",Result);

				SetDataToTable(ui->tableWidgetInspection ,0,i,InspectID);
				SetDataToTable(ui->tableWidgetInspection ,1,i,InspectTime);
				SetDataToTable(ui->tableWidgetInspection ,2,i,Result);
				CurrentLotTime.append(InspectTime);
			}
		}
		XMLServer->CloseXMLOperation(OpeHandle);
	}
}

void ManageByLot::on_pushButtonDeleteLines_clicked()
{
	int	Row=ui->tableWidgetLot->currentRow();
	if(Row>=0){
		if(XMLServer->GetState()==false && XMLServer->Open()==false){
			QMessageBox::warning(this, /**/"XMLServerError"
									, LangSolver.GetString(ManageByLot_LS,LID_23)/*"XMLServerに接続できない"*/);
			return;
		}

		LotInfo	*w=CurrentAllLots.GetItem(Row);
		if(w!=NULL){
			IntList	SelectedLines;
			int	N=ui->tableWidgetInspection->selectedItems ().count();
			for(int i=0;i<N;i++){
				QTableWidgetItem *q=ui->tableWidgetInspection->selectedItems ()[i];
				if(q->column()==0){
					SelectedLines.Add(q->row());
				}
			}


			XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(w->TableName);
			bool isEmptyDXML=false;
			if(OpeHandle!=NULL){
				QProgressDialog progress;
				progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_24)/*"選択ロットの削除中"*/);
				progress.setRange(0, SelectedLines.GetCount());
				progress.setModal(true);

				int sect=0;
				for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext(),sect++){
					progress.setValue(sect);
					qApp->processEvents();
					if(progress.wasCanceled()){
						break;
					}

					QString	WhereStr=QString(/**/"<IST><TIM>")+CurrentLotTime[d->GetValue()]+QString(/**/"</TIM></IST>");
					QString	ResultStr;
					bool	SelectRet1=OpeHandle->SelectFirst(/**/"<IST NGJ/>",WhereStr,/**/"",ResultStr);
					if(SelectRet1==true && ResultStr.isEmpty()==false){
						QString filepath;
						DeleteJDT(ResultStr,SParam);
						OpeHandle->DeleteXML();
					}
					::GSleep(SParam->WaitMilisec);
				}

				QString ResultStr;
				OpeHandle->SelectFirst(/**/"<Count/>", /**/"<IST */>", /**/"",ResultStr);
				if(ResultStr.toUpper()==/**/"<COUNT=\"0\"/>"){
					isEmptyDXML = true;
				}

				XMLServer->CloseXMLOperation(OpeHandle);
			}

			XMLServer->Close();
			while(XMLServer->GetState()==true){
				GSleep(1);
			}

			if(isEmptyDXML==true){
				if(XMLServer->GetState()==false && XMLServer->Open()==false){
					QMessageBox::warning(this, /**/"XMLServerError"
												, LangSolver.GetString(ManageByLot_LS,LID_25)/*"ロットデータを削除できない"*/);
					clearInspectionTable();
					return;
				}else{
					XMLServer->DeleteTable(w->TableName);
				}
			}
		}
		ShowAllInspect(w);
		ui->tableWidgetInspection->setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);
	}
}

void ManageByLot::on_pushButtonBackup_clicked()
{
	IntList	SelectedLines;
	int	N=ui->tableWidgetLot->selectedItems ().count();
	for(int i=0;i<N;i++){
		QTableWidgetItem *w=ui->tableWidgetLot->selectedItems ()[i];
		if(w->column()==0){
			SelectedLines.Add(w->row());
		}
	}
	if(SelectedLines.IsEmpty()==true){
		return;
	}
	QString FileName=QFileDialog::getSaveFileName ( 0, /**/"Back up file", QString()
													,/**/"BackupFile (*.bkp);;all files (*.*)");
	if(FileName.isEmpty()==true){
		return;
	}
	clearInspectionTable();
	int32	LineCount=0;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext()){
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			LineCount++;
		}
	}
	QStringList	JDTFileNames;
	QProgressDialog progress(this);
	progress.setAutoClose(false);
	progress.setAutoReset(false);

	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_26)/*"選択ロットからNG画像ファイルの検索中"*/);
	progress.setRange(0, SelectedLines.GetCount());

	int count=0;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext(), count++){
		progress.setValue(count);
		qApp->processEvents();
		if(progress.wasCanceled()){
			return;
		}
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
				QMessageBox::warning(this, /**/"XMLServerError"
										, LangSolver.GetString(ManageByLot_LS,LID_27)/*"XMLServerに接続できない"*/);
				return;
			}

			XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(w->TableName);
			if(OpeHandle!=NULL){
				QString		OutputStr	=QString(/**/"<IST NGJ/>");
				QString		SearchStr	=QString(/**/"<IST */>");
				QStringList	ResultListStr;
				bool	SelectRet1=OpeHandle->Select(OutputStr,SearchStr,/**/"",ResultListStr);
				if(SelectRet1==true){
					int	N=ResultListStr.count();
					for(int i=0;i<N;i++){
						QString NGJFile;
						if(GetXMLAttrStr (ResultListStr[i],/**/"NGJ",NGJFile)==true){
							QString	FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
							QStringList	List=SParam->ImageDrive.split(QRegularExpression(/**/"[/\\\\]"),QString::SplitBehavior::SkipEmptyParts);
							int	LPoint=0;
							while(LPoint<List.count()){
								if((NGJFile.at(0)=='/' || NGJFile.at(0)=='\\') && (NGJFile.at(0)=='/' || NGJFile.at(0)=='\\')){
									NGJFile=NGJFile.remove(0,2);
									if(NGJFile.contains(/**/"NGImage2")==true){
										NGJFile=NGJFile.section('/',1);
										NGJFile=QString(/**/"NGImage2/")+NGJFile;
									}
									else if(NGJFile.contains(/**/"NGImage")==true){
										NGJFile=NGJFile.section('/',1);
										NGJFile=QString(/**/"NGImage/")+NGJFile;
									}
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
								}
								else if(NGJFile.at(0)=='/' || NGJFile.at(0)=='\\'){
									NGJFile=NGJFile.remove(0,1);
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
								}
								else if(NGJFile.left(List[LPoint].count())==List[LPoint]){
									NGJFile=NGJFile.mid(List[LPoint].count());
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
									LPoint++;
								}
								else{
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
									break;
								}
							}
							QFileInfo	FInfo(FileName);
							//QDir	SearchName(FInfo.absolutePath());
							//QStringList	FileSearchFilter;
							//FileSearchFilter.append(FInfo.fileName());
							//QStringList	FileList=SearchName.entryList(FileSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
							QStringList	FileList = GetDirectoryFileList(FInfo.absolutePath(), FInfo.fileName());
							for(int j=0;j<FileList.count();j++){
								JDTFileNames.append(FInfo.absolutePath() + ::GetSeparator()+FileList[j]);
							}
						}
					}
				}
				XMLServer->CloseXMLOperation(OpeHandle);
			}
		}
	}
	progress.setCancelButton(0);// ・ｽL・ｽ・ｽ・ｽ・ｽ・ｽZ・ｽ・ｽ・ｽ{・ｽ^・ｽ・ｽ・ｽﾈゑｿｽ
	progress.layout()->update();

	QFileInfo	FInfo(FileName);
	ForceDirectories(FInfo.absolutePath());

	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false){
		return;
	}

	int32	Ver=1;
	if(::Save(&WFile,Ver)==false){
		return;
	}
	if(::Save(&WFile,LineCount)==false){
		return;
	}
	int32	JDTCount=JDTFileNames.count();
	if(::Save(&WFile,JDTCount)==false){
		return;
	}

	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_28)/*"ロットファイルをバックアップ中"*/);
	progress.setRange(0, SelectedLines.GetCount());
	count=0;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext(),count++){
		progress.setValue(count);
		qApp->processEvents();
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
				QMessageBox::warning(this, /**/"XMLServerError"
											, LangSolver.GetString(ManageByLot_LS,LID_29)/*"XMLServerに接続できない"*/);
				return;
			}

			QByteArray AllData;
			if(XMLServer->GetTableAllData(w->TableName,AllData)==true){
				if(::Save(&WFile,w->TableName)==false){
					return;
				}
				if(::Save(&WFile,AllData)==false){
					return;
				}
			}
		}
	}

	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_30)/*"NG画像ファイルをバックアップ中"*/);
	progress.setRange(0, JDTCount);
	
	for(int i=0;i<JDTCount;i++){
		progress.setValue(i);
		qApp->processEvents();
		QFile	JDTFile(JDTFileNames[i]);
		if(::Save(&WFile,JDTFileNames[i])==false){
			return;
		}
		QByteArray	JDTData;
		if(JDTFile.open(QIODevice::ReadOnly)==true){
			JDTData=JDTFile.readAll();
		}
		if(::Save(&WFile,JDTData)==false){
			return;
		}
	}

	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_31)/*"ロットファイルとNG画像ファイルを削除中"*/);
	progress.setRange(0, SelectedLines.GetCount());

	QStringList modDirectories;
	count=0;
	QStringList deleteTableList;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext(),count++){
		progress.setValue(count);
		qApp->processEvents();
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			QString filepath;
			DeleteTable(w->TableName
					,XMLServer
					,SQLDatabase ,*GetLayersBase()->GetDataBase()
					,SParam,&filepath);
			deleteTableList.append(w->TableName);
			if(filepath.isEmpty()==false && modDirectories.contains(filepath)==false){
				modDirectories.append(filepath);
			}
		}
	}
	for(QStringList::Iterator it=modDirectories.begin(); it!=modDirectories.end(); it++){
		DeleteEmptyDirectory(*it);
	}
	
	XMLServer->Close();
	while(XMLServer->GetState()==true){
		GSleep(1);
	}

	if(deleteTableList.isEmpty()==false){
		if(XMLServer->GetState()==false && XMLServer->Open()==false){
			QMessageBox::warning(this, /**/"XMLServerError"
										, LangSolver.GetString(ManageByLot_LS,LID_32)/*"ロットデータを削除できない"*/);
			return;
		}else{
			for(int i=0; i<deleteTableList.count(); i++){
				XMLServer->DeleteTable(deleteTableList[i]);
			}
			XMLServer->Close();
		}
	}
	for(int i=0;i<JDTCount;i++){
		QFile	JDTFile(JDTFileNames[i]);
		JDTFile.remove();
	}

	progress.setVisible(false);

	ui->tableWidgetLot->setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);
	ShowLotAll(SelectedMachineID ,SelectedMasterCode);

	clearInspectionTable();

	QMessageBox::information(NULL, /**/"Finish"
				, LangSolver.GetString(ManageByLot_LS,LID_33)/*"バックアップ正常終了"*/
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);

}

void ManageByLot::clearInspectionTable()
{
	ui->tableWidgetInspection->setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);
	ui->tableWidgetInspection->setRowCount(0);
}

void ManageByLot::on_pushButtonRestore_clicked()
{
	if(SelectedMachineID<0 || SelectedMasterCode<0){
		return;
	}
	QString	FileName=QFileDialog::getOpenFileName ( 0
													, LangSolver.GetString(ManageByLot_LS,LID_34)/*"バックアップファイルの選択"*/
													, QString()
													,/**/"BackupFile (*.bkp);;all files (*.*)");
	if(FileName.isEmpty()==true){
		return;
	}
	QFile	RFile(FileName);
	if(RFile.open(QIODevice::ReadOnly)==false){
		return;
	}
	QFileInfo RFileInfo(FileName);
	QProgressDialog progress(this);
	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_35)/*"リストア情報の取得中"*/);
	progress.setRange(0, 100);
	progress.setValue(0);
	progress.setCancelButton(0);

	qint64 fullsize = RFile.size();

	int32	Ver;
	if(::Load(&RFile,Ver)==false){
		return;
	}
	progress.setValue(RFile.pos() / (double)fullsize * progress.maximum());
	qApp->processEvents();
	
	int32	LineCount;
	if(::Load(&RFile,LineCount)==false){
		return;
	}
	progress.setValue(RFile.pos() / (double)fullsize * progress.maximum());
	qApp->processEvents();

	int32	JDTCount;
	if(::Load(&RFile,JDTCount)==false){
		return;
	}
	progress.setValue(RFile.pos() / (double)fullsize * progress.maximum());
	qApp->processEvents();
	
	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_36)/*"ロットファイルのリストア中"*/);
	for(int i=0;i<LineCount;i++){
		QString	TableName;
		if(::Load(&RFile,TableName)==false){
			return;
		}
		progress.setValue(RFile.pos() / (double)fullsize * progress.maximum());
		qApp->processEvents();

		QByteArray	AllData;
		if(::Load(&RFile,AllData)==false){
			return;
		}
		progress.setValue(RFile.pos() / (double)fullsize * progress.maximum());
		qApp->processEvents();

		if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
			QMessageBox::warning(this, /**/"XMLServerError"
										, LangSolver.GetString(ManageByLot_LS,LID_37)/*"XMLServerに接続できない"*/);
			return;
		}

		if(XMLServer->ReplaceTableAllData(TableName,AllData)==false){
			QMessageBox Q( /**/"Error in Restore"
						, LangSolver.GetString(ManageByLot_LS,LID_38)/*"リストア中にエラーが発生しました"*/
						, QMessageBox::Critical
						, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
			Q.exec();
			return;
		}
	}

	
	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_39)/*"NG画像ファイルのリストア中"*/);
	QStringList JDTFileNames;
	for(int i=0; i<JDTCount; i++){
		QString filename;
		if(::Load(&RFile, filename)==false){
			return;
		}
		progress.setValue(RFile.pos() / (double)fullsize * progress.maximum());
		qApp->processEvents();

		QByteArray JDTData;
		if(::Load(&RFile, JDTData)==false){
			return;
		}
		progress.setValue(RFile.pos() / (double)fullsize * progress.maximum());
		qApp->processEvents();
		
		QFile file;
		QFileInfo fileInfo(filename);
		file.setFileName(filename);
		QDir dir = fileInfo.absoluteDir();
		dir.mkpath(dir.absolutePath());
		if(file.open(QIODevice::WriteOnly)==false){
			return;
		}
		if(::Save(&file, JDTData)==false){
			return;
		}
	}

	progress.setVisible(false);
	ShowLotAll(SelectedMachineID ,SelectedMasterCode);

	QMessageBox::information(NULL, /**/"Finish"
				, LangSolver.GetString(ManageByLot_LS,LID_40)/*"リストア正常終了"*/
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);

	clearInspectionTable();
}

void ManageByLot::on_pushButtonClose_clicked()
{
	done(true);
}

void ManageByLot::on_cbShowInspectFirstEndTime_stateChanged(int state)
{
	bool visible;
	if(state==Qt::CheckState::Checked){
		visible = true;
		ShowLotAll(SelectedMachineID, SelectedMasterCode);
	}else if(state==Qt::CheckState::Unchecked){
		visible = false;
	}else{
		visible = false;
	}

	ui->tableWidgetLot->setColumnHidden(hhLotHeaderList.indexOf(hhLotLabelFirstInsTime), !visible);
	ui->tableWidgetLot->setColumnHidden(hhLotHeaderList.indexOf(hhLotLabelLastInsTime), !visible);
}

void ManageByLot::on_cbShowInspectionCount_stateChanged(int state)
{
	bool visible;
	if(state==Qt::CheckState::Checked){
		visible = true;
		ShowLotAll(SelectedMachineID, SelectedMasterCode);
	}else if(state==Qt::CheckState::Unchecked){
		visible = false;
	}else{
		visible = false;
	}

	ui->tableWidgetLot->setColumnHidden(hhLotHeaderList.indexOf(hhLotLabelInspectCount), !visible);
}

class	RetListDIm
{
public:
	QString	OriginalName;
	QString	TagName;
	int		TailNumber;

	RetListDIm	&operator=(RetListDIm &src);
};
RetListDIm	&RetListDIm::operator=(RetListDIm &src)
{
	OriginalName	=src.OriginalName;
	TagName			=src.TagName;
	TailNumber		=src.TailNumber;
	return *this;
}

void ManageByLot::ShowLotAll(int MachineID ,int MasterCode)
{
	CurrentAllLots.RemoveAll();

	if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
		QMessageBox::warning(this, /**/"XMLServerError"
									, LangSolver.GetString(ManageByLot_LS,LID_41)/*"XMLServerに接続できない"*/);
		return;
	}

	QString	Filter=QString::number(MachineID)+QString(/**/"-")+QString::number(MasterCode);
	bool	Ret=XMLServer->EnumTables(Filter,EnumResultList);
	if(Ret==true){
		int	N=EnumResultList.count();
		RetListDIm	*Dim=new RetListDIm[N];
		for(int i=0;i<N;i++){
			QString	BodyName;
			Dim[i].OriginalName=EnumResultList[i];
			Dim[i].TailNumber	=-1;
			int	n=EnumResultList[i].count();
			if(n>0){
				n--;
				QChar	c=EnumResultList[i].at(n);
				if(c.isDigit()==true){
					while(EnumResultList[i].at(n).isDigit()==true){
						n--;
					}
					QString	NumberStr=EnumResultList[i].mid(n+1);
					Dim[i].TagName	 =EnumResultList[i].left(n);
					bool	ok;
					Dim[i].TailNumber=NumberStr.toInt(&ok);
					if(ok==false)
						Dim[i].TailNumber=-1;
				}
			}
		}
		bool	Flag;
		do{
			Flag=false;
			for(int i=0;i<N-1;i++){
				if(Dim[i].TagName==Dim[i+1].TagName
				&& Dim[i].TailNumber>=0 && Dim[i+1].TailNumber>=0
				&& Dim[i].TailNumber>Dim[i+1].TailNumber){
					RetListDIm	Tmp;
					Tmp=Dim[i];
					Dim[i]=Dim[i+1];
					Dim[i+1]=Tmp;
					Flag=true;
				}
			}
		}while(Flag==true);

		EnumResultList.clear();
		for(int i=0;i<N;i++){
			EnumResultList.append(Dim[i].OriginalName);
		}
		delete	[]Dim;


		ui->progressBar->setMaximum(EnumResultList.count());
		ui->progressBar->setValue(0);


		for(int i=0;i<EnumResultList.count();i++){
			bool gottenByDatabase=false;
			QString LotName;
			QString LotID;
			QString LotRemark;
			QString	TableStr=EnumResultList[i];
			QStringList SpList = TableStr.split(/**/"/");
			if(SpList.count()>=2){
				QString qStr = QString(/**/"SELECT LOTNAME,IDNAME,REMARK FROM INSPECTIONLOT WHERE MASTERCODE='%1' AND IDNAME='%2'").arg(MasterCode).arg(SpList.last());
				QSqlQuery query(qStr);
				if(query.next()==true){
					LotID = query.record().value(0).toString();
					LotName = query.record().value(1).toString();
					LotRemark = query.record().value(2).toString();
					gottenByDatabase = true;
				}
			}

			if(gottenByDatabase==true && ui->cbShowInspectionCount->isChecked()==false && ui->cbShowInspectFirstEndTime->isChecked()==false){
				LotInfo	*w			= new LotInfo();
				w->TableName		= TableStr;
				w->LotName			= TableStr.split(/**/"/").last();
				w->LotID			= LotID;
				w->LotRemark		= LotRemark;
				CurrentAllLots.AppendList(w);
				ui->progressBar->setValue(ui->progressBar->value()+1);
				continue;
			}

			XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(TableStr);
			if(OpeHandle!=NULL){
				QString	OutputStr	=QString(/**/"<IST><LOT *>*</LOT><TIM *>*</TIM></IST>");
				QString	SearchStr	=QString(/**/"<IST */>");
				QString	OrderStr	=QString(/**/"EID<INSPECT/>");
				QString	ResultStr;
				QString StartTimeValue;
				QString EndTimeValue;
				int		ISTCount=0;
				QStringList	ResultListStr;

				QDateTime first_tim;
				do{
					if(ui->cbShowInspectionCount->isChecked()==true){
						if(OpeHandle->Select(/**/"<COUNT/>",/**/"<IST */>",/**/"",ResultListStr)==false || ResultListStr.isEmpty()==true){
							break;
						}else{
							QString countStr = ResultListStr.first();
							countStr = countStr.mid(countStr.indexOf(/**/"\"")+1);
							countStr = countStr.left(countStr.lastIndexOf(/**/"\""));
							ISTCount = countStr.toInt();
						}
					}
					
					if(LotName.isEmpty()==true){
						if(OpeHandle->SelectFirst(/**/"<IST><LOT *>*</LOT></IST>", /**/"<IST */>", /**/"",ResultStr)==false || ResultStr.isEmpty()==true || ResultStr==/**/"<BOF/>" || ResultStr==/**/"<EOF/>"){
							;// ・ｽ・ｽ・ｽb・ｽg・ｽ・ｽ・ｽ・ｽ・ｽﾍ厄ｿｽ・ｽ・ｽ
						}else{
							do{
								if(GetXMLAttrStr (ResultStr, /**/"LID", LotName)==true){
									GetXMLValueStr(ResultStr, /**/"LOT", LotID);
									break;
								}
							}while(OpeHandle->SelectNext(ResultStr)==true);
						}
					}

					if(ui->cbShowInspectFirstEndTime->isChecked()==true){
						StartTimeValue = EndTimeValue = /**/"can't read";
						if(OpeHandle->SelectFirst(/**/"<IST><TIM *>*</TIM></IST>", /**/"<IST */>", /**/"EID<INSPECT/>",ResultStr)==false || ResultStr.isEmpty()==true || ResultStr==/**/"<EOF/>" || ResultStr==/**/"<BOF/>"){
							;// ・ｽ・ｽ・ｽﾔ擾ｿｽ・ｽ・ｽ・ｽﾍ厄ｿｽ・ｽ・ｽ
						}else{
							QString timeValue;
														
							if(GetXMLValueStr(ResultStr, /**/"TIM", timeValue)==true){
								first_tim = QDateTime::fromString(timeValue, /**/"yy/MM/dd hh:mm:ss");
								first_tim.addYears(100);// 20xx・ｽN・ｽﾉゑｿｽ・ｽ・ｽ
								StartTimeValue = first_tim.toString(/**/"yy/MM/dd hh:mm:ss");
							}
							//if(GetXMLValueStr(ResultListStr.first(), /**/"TIM", timeValue)==true){
							//	first_tim = last_tim = QDateTime::fromString(timeValue, /**/"yy/MM/dd hh:mm:ss");
							//}

							//StartTimeValue = EndTimeValue = /**/"can't read";

							//for(int tim_i=1; tim_i<ResultListStr.count(); tim_i++){
							//	GetXMLValueStr(ResultListStr[tim_i],/**/"TIM",EndTimeValue);
					
							//	QDateTime timeTIM = QDateTime::fromString(EndTimeValue, /**/"yy/MM/dd hh:mm:ss");
							//	timeTIM.addYears(100);// 20xx・ｽN・ｽﾉゑｿｽ・ｽ・ｽ

							//	if(first_tim.isNull()==true || first_tim.isValid()==false || first_tim>timeTIM){
							//		first_tim = timeTIM;
							//	}
							//	if(last_tim.isNull()==true || last_tim.isValid()==false || last_tim<timeTIM){
							//		last_tim = timeTIM;
							//	}
							//}

							//StartTimeValue = first_tim.toString(/**/"yy/MM/dd hh:mm:ss");
							//EndTimeValue = last_tim.toString(/**/"yy/MM/dd hh:mm:ss");
						}

						if(OpeHandle->SelectLast(/**/"<IST><TIM *>*</TIM></IST>", /**/"<IST */>", /**/"EID<INSPECT/>",ResultStr)==false || ResultStr.isEmpty()==true || ResultStr==/**/"<EOF/>" || ResultStr==/**/"<BOF/>"){
							;// ・ｽ・ｽ・ｽﾔ擾ｿｽ・ｽ・ｽ・ｽﾍ厄ｿｽ・ｽ・ｽ
						}else{
							QDateTime last_tim;
							QString timeValue;
														
							if(GetXMLValueStr(ResultStr, /**/"TIM", timeValue)==true){
								last_tim = QDateTime::fromString(timeValue, /**/"yy/MM/dd hh:mm:ss");
								last_tim.addYears(100);// 20xx・ｽN・ｽﾉゑｿｽ・ｽ・ｽ
								EndTimeValue = last_tim.toString(/**/"yy/MM/dd hh:mm:ss");
							}
						}
					}
				}while(false);

				LotInfo	*w			= new LotInfo();
				w->TableName		= TableStr;
				w->LotName			= TableStr.split(/**/"/").last();
				w->LotID			= LotID;
				w->LotRemark		= LotRemark;
				w->StartTimeValue	= StartTimeValue;
				w->EndTimeValue		= EndTimeValue;
				w->ISTCount			= ISTCount;
				w->StartTime		= first_tim;
				CurrentAllLots.AppendList(w);

				XMLServer->CloseXMLOperation(OpeHandle);

				delete OpeHandle;
				//bool	SelectRet3=OpeHandle->Select(/**/"<COUNT/>",/**/"<IST */>",/**/"",ResultListStr);
				//if(SelectRet3==true){
				//	//GetXMLCountValue(ResultListStr[0],"COUNT",ISTCount);
				//	if(ResultListStr.isEmpty() || ResultListStr.count()!=1 || ResultListStr.first().count(/**/'\"')!=2){
				//		continue;
				//	}
				//	QString countStr = ResultListStr.first();
				//	countStr = countStr.mid(countStr.indexOf(/**/"\"")+1);
				//	countStr = countStr.left(countStr.lastIndexOf(/**/"\""));
				//	ISTCount = countStr.toInt();
				//	if(ISTCount==0){
				//		LotInfo	*w=new LotInfo();
				//		w->TableName=TableStr;
				//		w->LotName	=TableStr.split(/**/"/").last();
				//		w->LotID	=/**/"";
				//		w->StartTimeValue	=/**/"";
				//		w->EndTimeValue		=/**/"";
				//		w->ISTCount			=ISTCount;
				//		CurrentAllLots.AppendList(w);
				//		XMLServer->CloseXMLOperation(OpeHandle);
				//		ui->progressBar->setValue(ui->progressBar->value()+1);
				//		continue;
				//	}
				//}
				//if(SelectRet3==false/* || ISTCount==0*/){
				//	XMLServer->CloseXMLOperation(OpeHandle);
				//	ui->progressBar->setValue(ui->progressBar->value()+1);
				//	continue;
				//}
				//// ・ｽ・ｽ・ｽb・ｽg・ｽ・ｽ・ｽA・ｽ・ｽ・ｽb・ｽgID・ｽ・ｽ・ｽ謫ｾ
				//bool	SelectRet1=OpeHandle->Select(/**/"<IST><LOT *>*</LOT></IST>", /**/"<IST */>", /**/"",ResultListStr);
				//if(SelectRet1==false || ResultListStr.isEmpty()==true){
				//	;
				//}else if(GetXMLAttrStr (ResultStr,/**/"LID",LotName)==true){
				//	GetXMLValueStr(ResultStr,/**/"LOT",LotID);
				//}else{
				//	;
				//}
				//// ・ｽ・ｽ・ｽ・ｽ・ｽE・ｽﾅ終・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ・ｽ
				//bool	SelectRet2=OpeHandle->Select(/**/"<IST><TIM *>*</TIM></IST>", /**/"<IST */>", /**/"",ResultListStr);
				//QDateTime first_tim,last_tim;
				//StartTimeValue = EndTimeValue = "can't read";
				//if(SelectRet2==false || ResultListStr.isEmpty()==true){
				//	;
				//}else{
				//	first_tim = last_tim = QDateTime::fromString(ResultListStr.first(), "yy/MM/dd hh:mm:ss");
				//	for(int tim_i=1; tim_i<ResultListStr.count(); tim_i++){
				//		GetXMLValueStr(ResultListStr[tim_i],/**/"TIM",EndTimeValue);
				//	
				//		QDateTime timeTIM = QDateTime::fromString(EndTimeValue, "yy/MM/dd hh:mm:ss");
				//		timeTIM.addYears(100);// 20xx・ｽN・ｽﾉゑｿｽ・ｽ・ｽ

				//		if(first_tim.isNull()==true || first_tim.isValid()==false || first_tim>timeTIM){
				//			first_tim = timeTIM;
				//		}
				//		if(last_tim.isNull()==true || last_tim.isValid()==false || last_tim<timeTIM){
				//			last_tim = timeTIM;
				//		}
				//	}
				//	StartTimeValue = first_tim.toString("yy/MM/dd hh:mm:ss");
				//	EndTimeValue = last_tim.toString("yy/MM/dd hh:mm:ss");
				//}

				//LotInfo	*w=new LotInfo();
				//w->TableName=TableStr;
				//w->LotName	=LotName;
				//w->LotID	=LotID;
				//w->StartTimeValue	=StartTimeValue;
				//w->EndTimeValue		=EndTimeValue;
				//w->ISTCount			=ISTCount;
				//CurrentAllLots.AppendList(w);
				//
				//XMLServer->CloseXMLOperation(OpeHandle);
			}
			ui->progressBar->setValue(ui->progressBar->value()+1);
			GSleep(SParam->WaitMilisec);
		}
	}

	ui->tableWidgetLot	->setRowCount(CurrentAllLots.GetCount());
	int	Row=0;
	for(LotInfo	*w=CurrentAllLots.GetFirst();w!=NULL;w=w->GetNext() ,Row++){
		SetDataToTable(ui->tableWidgetLot ,0,Row,w->LotName);
		SetDataToTable(ui->tableWidgetLot ,1,Row,w->LotID);
		SetDataToTable(ui->tableWidgetLot ,2,Row,w->StartTimeValue);
		SetDataToTable(ui->tableWidgetLot ,3,Row,w->EndTimeValue);
		SetDataToTable(ui->tableWidgetLot ,4,Row,QString::number(w->ISTCount));
	}

	XMLServer->Close();
}


void ManageByLot::on_pushButtonBackupOnly_clicked()
{
	IntList	SelectedLines;
	int	N=ui->tableWidgetLot->selectedItems ().count();
	for(int i=0;i<N;i++){
		QTableWidgetItem *w=ui->tableWidgetLot->selectedItems ()[i];
		if(w->column()==0){
			SelectedLines.Add(w->row());
		}
	}
	if(SelectedLines.IsEmpty()==true){
		return;
	}
	QString FileName=QFileDialog::getSaveFileName ( 0, /**/"Back up file", QString()
													,/**/"BackupFile (*.bkp);;all files (*.*)");
	if(FileName.isEmpty()==true){
		return;
	}
	clearInspectionTable();
	int32	LineCount=0;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext()){
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			LineCount++;
		}
	}
	QStringList	JDTFileNames;
	QProgressDialog progress(this);
	progress.setAutoClose(false);
	progress.setAutoReset(false);

	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_42)/*"選択ロットからNG画像ファイルの検索中"*/);
	progress.setRange(0, SelectedLines.GetCount());

	int count=0;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext(), count++){
		progress.setValue(count);
		qApp->processEvents();
		if(progress.wasCanceled()){
			return;
		}
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
				QMessageBox::warning(this, /**/"XMLServerError"
											, LangSolver.GetString(ManageByLot_LS,LID_43)/*"XMLServerに接続できない"*/);
				return;
			}

			XMLOperationHandle	*OpeHandle=XMLServer->OpenXMLOperation(w->TableName);
			if(OpeHandle!=NULL){
				QString		OutputStr	=QString(/**/"<IST NGJ/>");
				QString		SearchStr	=QString(/**/"<IST */>");
				QStringList	ResultListStr;
				bool	SelectRet1=OpeHandle->Select(OutputStr,SearchStr,/**/"",ResultListStr);
				if(SelectRet1==true){
					int	N=ResultListStr.count();
					for(int i=0;i<N;i++){
						QString NGJFile;
						if(GetXMLAttrStr (ResultListStr[i],/**/"NGJ",NGJFile)==true){
							QString	FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
							QStringList	List=SParam->ImageDrive.split(QRegularExpression(/**/"[/\\\\]"),QString::SplitBehavior::SkipEmptyParts);
							int	LPoint=0;
							while(LPoint<List.count()){
								if((NGJFile.at(0)=='/' || NGJFile.at(0)=='\\') && (NGJFile.at(0)=='/' || NGJFile.at(0)=='\\')){
									NGJFile=NGJFile.remove(0,2);
									if(NGJFile.contains(/**/"NGImage2")==true){
										NGJFile=NGJFile.section('/',1);
										NGJFile=QString(/**/"NGImage2/")+NGJFile;
									}
									else if(NGJFile.contains(/**/"NGImage")==true){
										NGJFile=NGJFile.section('/',1);
										NGJFile=QString(/**/"NGImage/")+NGJFile;
									}
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
								}
								else if(NGJFile.at(0)=='/' || NGJFile.at(0)=='\\'){
									NGJFile=NGJFile.remove(0,1);
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
								}
								else if(NGJFile.left(List[LPoint].count())==List[LPoint]){
									NGJFile=NGJFile.mid(List[LPoint].count());
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
									LPoint++;
								}
								else{
									FileName=SParam->ImageDrive + ::GetSeparator()+NGJFile;
									break;
								}
							}
							QFileInfo	FInfo(FileName);
							//QDir	SearchName(FInfo.absolutePath());
							//QStringList	FileSearchFilter;
							//FileSearchFilter.append(FInfo.fileName());
							//QStringList	FileList=SearchName.entryList(FileSearchFilter,QDir::Files | QDir::NoDotAndDotDot);
							QStringList	FileList = GetDirectoryFileList(FInfo.absolutePath(), FInfo.fileName());
							for(int j=0;j<FileList.count();j++){
								JDTFileNames.append(FInfo.absolutePath() + ::GetSeparator()+FileList[j]);
							}
						}
					}
				}
				XMLServer->CloseXMLOperation(OpeHandle);
			}
		}
	}
	progress.setCancelButton(0);// ・ｽL・ｽ・ｽ・ｽ・ｽ・ｽZ・ｽ・ｽ・ｽ{・ｽ^・ｽ・ｽ・ｽﾈゑｿｽ
	progress.layout()->update();

	QFileInfo	FInfo(FileName);
	ForceDirectories(FInfo.absolutePath());

	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false){
		return;
	}

	int32	Ver=1;
	if(::Save(&WFile,Ver)==false){
		return;
	}
	if(::Save(&WFile,LineCount)==false){
		return;
	}
	int32	JDTCount=JDTFileNames.count();
	if(::Save(&WFile,JDTCount)==false){
		return;
	}

	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_44)/*"ロットファイルをバックアップ中"*/);
	progress.setRange(0, SelectedLines.GetCount());
	count=0;
	for(IntClass *d=SelectedLines.GetFirst();d!=NULL;d=d->GetNext(),count++){
		progress.setValue(count);
		qApp->processEvents();
		LotInfo	*w=CurrentAllLots.GetItem(d->GetValue());
		if(w!=NULL){
			if(XMLServer->IsConnected(0)==false && XMLServer->Open()==false){
				QMessageBox::warning(this, /**/"XMLServerError"
											, LangSolver.GetString(ManageByLot_LS,LID_45)/*"XMLServerに接続できない"*/);
				return;
			}

			QByteArray AllData;
			if(XMLServer->GetTableAllData(w->TableName,AllData)==true){
				if(::Save(&WFile,w->TableName)==false){
					return;
				}
				if(::Save(&WFile,AllData)==false){
					return;
				}
			}
		}
	}

	progress.setLabelText(LangSolver.GetString(ManageByLot_LS,LID_46)/*"NG画像ファイルをバックアップ中"*/);
	progress.setRange(0, JDTCount);
	
	for(int i=0;i<JDTCount;i++){
		progress.setValue(i);
		qApp->processEvents();
		QFile	JDTFile(JDTFileNames[i]);
		if(::Save(&WFile,JDTFileNames[i])==false){
			return;
		}
		QByteArray	JDTData;
		if(JDTFile.open(QIODevice::ReadOnly)==true){
			JDTData=JDTFile.readAll();
		}
		if(::Save(&WFile,JDTData)==false){
			return;
		}
	}

	
	XMLServer->Close();
	while(XMLServer->GetState()==true){
		GSleep(1);
	}

	progress.setVisible(false);

	ui->tableWidgetLot->setCurrentCell(-1, -1, QItemSelectionModel::SelectionFlag::Clear);
	ShowLotAll(SelectedMachineID ,SelectedMasterCode);

	clearInspectionTable();

	QMessageBox::information(NULL, /**/"Finish"
				, LangSolver.GetString(ManageByLot_LS,LID_47)/*"バックアップ正常終了"*/
				, QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);

}
