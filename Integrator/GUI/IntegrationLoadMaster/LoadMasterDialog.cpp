#include "IntegrationLoadMasterResource.h"
#include "LoadMasterDialog.h"
#include "ui_LoadMasterDialog.h"
#include "IntegrationLoadMaster.h"
#include "InputPanelDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include "IntegrationShowRelationInfoForm.h"
#include "IntegrationShowName.h"

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<LoadMasterDialog *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
{
	QString	ret;

	if(ParentWindow->OrderMode==0){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
				+QString(/**/" ORDER BY RELATIONCODE;");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
				+QString(/**/" ORDER BY RELATIONCODE DESC;");
		}
	}
	else
	if(ParentWindow->OrderMode==1){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
				+QString(/**/" ORDER BY REGTIME;");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
				+QString(/**/" ORDER BY REGTIME DESC;");
		}
	}
	else
	if(ParentWindow->OrderMode==2){
		QString	SearchStr=ParentWindow->GetNumberForSearch();
		if(SearchStr.isEmpty()==false){
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION WHERE RELATIONNUMBER>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNUMBER");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION WHERE RELATIONNUMBER>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNUMBER DESC");
			}
		}
		else{
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION ORDER BY RELATIONNUMBER");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION ORDER BY RELATIONNUMBER DESC");
			}
		}
	}
	else
	if(ParentWindow->OrderMode==3){
		QString	SearchStr=ParentWindow->GetNameForSearch();
		if(SearchStr.isEmpty()==false){
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION WHERE RELATIONNAME>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNAME");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION WHERE RELATIONNAME>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNAME DESC");
			}
		}
		else{
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION ORDER BY RELATIONNAME");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION ORDER BY RELATIONNAME DESC");
			}
		}
	}
	else
	if(ParentWindow->OrderMode==4){
		QString	SearchStr=ParentWindow->GetRemarkForSearch();
		if(SearchStr.isEmpty()==false){
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION WHERE REMARK>=\'")
					+SearchStr
					+QString(/**/"\'  ORDER BY REMARK;");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION WHERE REMARK>=\'")
					+SearchStr
					+QString(/**/"\'  ORDER BY REMARK DESC;");
			}
		}
		else{
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
					+QString(/**/" ORDER BY REMARK;");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
					+QString(/**/" ORDER BY REMARK DESC;");
			}
		}
	}
	else
	if(ParentWindow->OrderMode==5){
		if(ParentWindow->AcsendantOrder==true){
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
				+QString(/**/" ORDER BY LASTLOADEDTIME;");
		}
		else{
			ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK,LASTLOADEDTIME FROM MASTERRELATION")
				+QString(/**/" ORDER BY LASTLOADEDTIME DESC;");
		}
	}
	return ret;
}

//------------------------------------------------------------------------------------------------------
LoadMasterDialog::LoadMasterDialog(LayersBase *Base,int LastOrderMode,int LastAcsendantOrder,int LastOpenedID,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(Base)
    ,ui(new Ui::LoadMasterDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	ParentGUI=dynamic_cast<IntegrationLoadMaster *>(parent);

	OrderMode=LastOrderMode;
	AcsendantOrder=LastAcsendantOrder;

	QSqlLoadMasterModel *MModel = new QSqlLoadMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	ui->tableView->setModel(MModel);
	ui->tableView->setColumnWidth (0, 90);
	ui->tableView->setColumnWidth (1, 120);
	ui->tableView->setColumnWidth (2, 200);
	ui->tableView->setColumnWidth (3, 200);	
	ui->tableView->setColumnWidth (4, 200);	

	QString	MasterCodeStr	=tr(/**/"MasterCode");
	QString	RegTimeStr		=tr(/**/"RegTime");
	QString	NumberStr		=tr(/**/"Number");
	QString	NameStr			=tr(/**/"Name");
	QString	RemarkStr		=tr(/**/"Remark");
	QString	LoadedTimeStr	=tr(/**/"LoadedTime");

	GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Integration",/**/"ShowRelationInfo",/**/"");
	if(f!=NULL){
		IntegrationShowRelationInfoForm	*Rf=dynamic_cast<IntegrationShowRelationInfoForm *>(f);
		if(Rf!=NULL){
			NumberStr=Rf->TitleMasterID;
			NameStr	 =Rf->TitleMasterName;
			RemarkStr=Rf->TitleLotName;
		}
	}
	else{
		f=GetLayersBase()->FindByName(/**/"Integration",/**/"ShowName",/**/"");
		if(f!=NULL){
			IntegrationShowName	*Rf=dynamic_cast<IntegrationShowName *>(f);
			if(Rf!=NULL){
				NumberStr=Rf->TitleMasterNumber;
				NameStr	 =Rf->TitleMasterName;
				RemarkStr=Rf->TitleRemark;
			}
		}
	}
	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, NumberStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);
	MModel->setHeaderData(5, Qt::Horizontal, LoadedTimeStr	,Qt::DisplayRole);

	ui->labelTitleMasterNumber	->setText(NumberStr	+QString(LangSolver.GetString(LoadMasterDialog_LS,LID_0)/*"検索"*/));
	ui->labelTitleMasterName	->setText(NameStr	+QString(LangSolver.GetString(LoadMasterDialog_LS,LID_1)/*"検索"*/));
	ui->labelTitleRemark		->setText(RemarkStr	+QString(LangSolver.GetString(LoadMasterDialog_LS,LID_2)/*"検索"*/));

	connect(ui->tableView->horizontalHeader() ,SIGNAL(sectionClicked (int)),this,SLOT(MListSectionClicked (int)));

	ui->pushButtonLoad->setEnabled(false);

	AllocatedViewCount=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
	if(AllocatedViewCount>0){
		int	W=ui->frameView->width()/AllocatedViewCount;
		TopViewDim=new QLabel[AllocatedViewCount];
		for(int i=0;i<AllocatedViewCount;i++){
			TopViewDim[i].setParent(ui->frameView);
			TopViewDim[i].setGeometry(W*i,0,W-1,ui->frameView->height());
		}
	}
	else{
		TopViewDim=NULL;
	}
	ResultRelationCode=-1;

	if(LastOpenedID>=0){
		SelectView(LastOpenedID);
	}

	InstallOperationLog(this);
}

LoadMasterDialog::~LoadMasterDialog()
{
	for(int i=0;i<AllocatedViewCount;i++){
		TopViewDim[i].close();
	}
	delete	[]TopViewDim;
	
	delete ui;
	TopViewDim=NULL;
}

QString	LoadMasterDialog::GetNameForSearch(void)
{
	return ui->lineEditSearchByName->text();
}
QString	LoadMasterDialog::GetNumberForSearch(void)
{
	return ui->lineEditSearchByNumber->text();
}
QString	LoadMasterDialog::GetRemarkForSearch(void)
{
	return ui->lineEditSearchByRemark->text();
}

void	LoadMasterDialog::SelectView(int RelationCode)
{
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		int	N=1000000;
		for(int row=0;row<N;row++){
			QModelIndex RIndex=ui->tableView->model()->index(row, 0);
			bool	ok;
			int	Code=M->data(RIndex).toInt(&ok);
			if(ok==false)
				break;
			if(Code==RelationCode){
				ui->tableView->setCurrentIndex(RIndex);
				SelectView();
				break;
			}
		}
	}
}
int		LoadMasterDialog::GetLastRelationCode(void)
{
	return ParentGUI->LastOpenedID;
}
void	LoadMasterDialog::SelectView(void)
{
	QModelIndex Index=ui->tableView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	RelationCode=M->data(RIndex).toInt();
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE RELATIONCODE=")
			+QString::number(RelationCode)
			+QString(/**/" order by MACHINEID");
		QSqlQuery query(S ,GetLayersBase()->GetDatabase());
		for(int i=0;i<N;i++){
			if(query.next ()==false)
				break;

			QString	MasterName	=query.value(query.record().indexOf(/**/"MASTERNAME")).toString();
			QString	Remark		=query.value(query.record().indexOf(/**/"REMARK"	)).toString();
			QByteArray	TopVArray=query.value(query.record().indexOf(/**/"TOPVIEW"	)).toByteArray();

			QPixmap		TopView;
			TopView.loadFromData(TopVArray,/**/"PNG");
			TopViewDim[i].setPixmap(TopView);
		}

		QString RetRelationNumber	;
		QString RetRelationName		;
		QString RetRemark			;
		int		RetRelationType		;
		QByteArray CommonData		;
		int32	ThresholdLevelID	;
		if(GetLayersBase()->GetDatabaseLoader()->G_GetMasterRelation(GetLayersBase()->GetDatabase()
										,RelationCode
										,RetRelationNumber
										,RetRelationName
										,RetRemark
										,RetRelationType
										,CommonData
										,ThresholdLevelID)==true){
			QBuffer	CommonBuff(&CommonData);
			CommonBuff.open(QIODevice::ReadOnly);
			IntegrationCommonData	CommonData;
			CommonData.Load(&CommonBuff);

			ui->doubleSpinBoxSizeX	->setValue(CommonData.CommonSizeX);
			ui->doubleSpinBoxSizeY	->setValue(CommonData.CommonSizeY);
		}
	}
}

void LoadMasterDialog::on_pushButtonLoad_clicked()
{
	QModelIndex Index=ui->tableView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		ResultRelationCode=M->data(RIndex).toInt();
		done(true);
	}
}

void LoadMasterDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void LoadMasterDialog::on_pushButtonInputPanel_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditSearchByName->text());
	if(D.exec()==(bool)true){
		OrderMode=3;
		ui->lineEditSearchByName->setText(D.GetResult());
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
		if(M!=NULL){
			M->select();
		}

	}
}

void LoadMasterDialog::on_tableView_clicked(const QModelIndex &index)
{
	ui->pushButtonLoad->setEnabled(true);
	SelectView();
}

void LoadMasterDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
	on_pushButtonLoad_clicked();
}

void	LoadMasterDialog::MListSectionClicked ( int logicalIndex )
{
	if(OrderMode==logicalIndex){
		AcsendantOrder=!AcsendantOrder;
	}
	else{
		OrderMode=logicalIndex;
		AcsendantOrder=true;
	}
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL)
		M->select();

}
void LoadMasterDialog::on_lineEditSearchByNumber_textChanged(const QString &arg1)
{
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		OrderMode=2;
		M->select();
	}
}

void LoadMasterDialog::on_lineEditSearchByName_textChanged(const QString &arg1)
{
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		OrderMode=3;
		M->select();
	}
}

void LoadMasterDialog::on_pushButtonInputMasterNumber_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditSearchByNumber->text());
	if(D.exec()==(bool)true){
		OrderMode=2;
		ui->lineEditSearchByNumber->setText(D.GetResult());
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

void LoadMasterDialog::on_pushButtonInputMasterName_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditSearchByName->text());
	if(D.exec()==(bool)true){
		OrderMode=3;
		ui->lineEditSearchByName->setText(D.GetResult());
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

void LoadMasterDialog::on_pushButtonInputRemark_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditSearchByRemark->text());
	if(D.exec()==(bool)true){
		OrderMode=4;
		ui->lineEditSearchByRemark->setText(D.GetResult());
		QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
		if(M!=NULL){
			M->select();
		}
	}
}

void LoadMasterDialog::on_lineEditSearchByRemark_textChanged(const QString &arg1)
{
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		OrderMode=4;
		M->select();
	}
}
