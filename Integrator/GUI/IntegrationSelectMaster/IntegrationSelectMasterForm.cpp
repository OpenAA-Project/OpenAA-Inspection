#include "IntegrationSelectMasterResource.h"
#include "IntegrationSelectMasterForm.h"
#include "ui_IntegrationSelectMasterForm.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include <QHeaderView>

QSqlLoadRelationModel::QSqlLoadRelationModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<IntegrationSelectMasterForm *>(parent);
}
QString QSqlLoadRelationModel::selectStatement () const
{
	QString	ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNAME ")
						+QString(/**/" FROM MASTERRELATION ")
						+QString(/**/" ORDER BY RELATIONCODE;");
	return ret;
}

IntegrationSelectMasterForm::IntegrationSelectMasterForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::IntegrationSelectMasterForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	if(GetLayersBase()->IsDatabaseOk()==true){
		QSqlLoadRelationModel *MModel = new QSqlLoadRelationModel(this,GetLayersBase()->GetDatabase());
		MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
		MModel->select();
		MModel->removeColumn(0); // don't show the ID

		MListView = new QTableView(ui->frameGrid);
		MListView->setModel(MModel);
		MListView->setObjectName(/**/"MListView");
		MListView->move(0,0);
		MListView->resize(ui->frameGrid->width(),ui->frameGrid->height());
		MListView->setColumnWidth (0, 60);
		MListView->setColumnWidth (1, 120);
		MListView->setColumnWidth (2, 120);

		MListView->setSelectionMode(QAbstractItemView::SingleSelection);
		MListView->setSelectionBehavior(QAbstractItemView::SelectRows);
		MListView->setObjectName(/**/"SelectRelationListView");
		MListView->show();
		connect(MListView ,SIGNAL(clicked(const QModelIndex &))		 ,this,SLOT(SlotClicked(const QModelIndex &)));
		connect(MListView ,SIGNAL(doubleClicked(const QModelIndex &)),this,SLOT(SlotDoubleClicked(const QModelIndex &)));
		
		ShowListHeader();
		connect(MListView->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));
	}
	else{
		MListView=NULL;
	}

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationSelectMasterForm::~IntegrationSelectMasterForm()
{
    delete ui;
}
void	IntegrationSelectMasterForm::ResizeAction()
{
	ui->frame->setGeometry(0,height()-ui->frame->height(),width(),ui->frame->height());
	ui->pushButtonSelect->move((width()-ui->pushButtonSelect->width())/2,ui->pushButtonSelect->geometry().top());
	ui->frameGrid->resize(width(),height()-ui->frame->height());
	if(MListView!=NULL){
		MListView->resize(ui->frameGrid->width(),ui->frameGrid->height());

		MListView->setColumnWidth (0, (width()-24)/6);
		MListView->setColumnWidth (1, (width()-24)*2/6);
		MListView->setColumnWidth (2, (width()-24)*3/6);
	}
}

void	IntegrationSelectMasterForm::ShowListHeader(void)
{
	if(MListView!=NULL){
		//QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
		QSqlLoadRelationModel *MModel = (QSqlLoadRelationModel*)(MListView->model());
		QString	MasterCodeStr	=LangSolver.GetString(IntegrationSelectMasterForm_LS,LID_0)/*"MasterCode"*/;
		QString	RegTimeStr		=LangSolver.GetString(IntegrationSelectMasterForm_LS,LID_1)/*"RegTime"*/;
		QString	NameStr			=LangSolver.GetString(IntegrationSelectMasterForm_LS,LID_2)/*"Name"*/;

		MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
		MModel->setHeaderData(1, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
		MModel->setHeaderData(2, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	}
}

void IntegrationSelectMasterForm::on_pushButtonSelect_clicked()
{
	if(MListView!=NULL){
		QModelIndex Index=MListView->currentIndex();

		QSqlLoadRelationModel	*M=dynamic_cast<QSqlLoadRelationModel	 *>(MListView->model());
		if(M!=NULL){
			QModelIndex RIndex=Index.sibling ( Index.row(), 0);
			int	RelationCode=M->data(RIndex).toInt();
			if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
				GetLayersBase()->ShowProcessingForm(LangSolver.GetString(IntegrationSelectMasterForm_LS,LID_3)/*"Loading all lots index"*/);
				GetLayersBase()->StepProcessing(0);
				if(GetLayersBase()->GetIntegrationBasePointer()->LoadRelationMaster(RelationCode)==true){
					GetLayersBase()->GetIntegrationBasePointer()->LoadLotData();
				}
				GetLayersBase()->CloseProcessingForm();
				BroadcastBuildForShow();
			}
		}
	}

}

void	IntegrationSelectMasterForm::SlotClicked(const QModelIndex &Index)
{
}

void	IntegrationSelectMasterForm::SlotDoubleClicked	(const QModelIndex &Index)
{
	on_pushButtonSelect_clicked();
}

