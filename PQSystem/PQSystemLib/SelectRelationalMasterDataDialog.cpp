#include "SelectRelationalMasterDataDialog.h"
#include "ui_SelectRelationalMasterDataDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XDataInLayer.h"
#include "XIntegrationBase.h"
#include "PQSystemService.h"

QSqlLoadMasterModel::QSqlLoadMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<SelectRelationalMasterDataDialog *>(parent);
}
QString QSqlLoadMasterModel::selectStatement () const
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
		QString	SearchStr=ParentWindow->GetNumberForSearch();
		if(SearchStr.isEmpty()==false){
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION WHERE RELATIONNUMBER>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNUMBER");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION WHERE RELATIONNUMBER>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNUMBER DESC");
			}
		}
		else{
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNUMBER");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNUMBER DESC");
			}
		}
	}
	else
	if(ParentWindow->OrderMode==3){
		QString	SearchStr=ParentWindow->GetNameForSearch();
		if(SearchStr.isEmpty()==false){
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION WHERE RELATIONNAME>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNAME");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION WHERE RELATIONNAME>=\'")
					+SearchStr
					+QString(/**/"\' ORDER BY RELATIONNAME DESC");
			}
		}
		else{
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNAME");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNAME DESC");
			}
		}
	}
	//else
	//if(ParentWindow->OrderMode==4){
	//	if(ParentWindow->AcsendantOrder==true){
	//		ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
	//			+QString(/**/" ORDER BY REMARK;");
	//	}
	//	else{
	//		ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
	//			+QString(/**/" ORDER BY REMARK DESC;");
	//	}
	//}
	else
	if(ParentWindow->OrderMode==4){
		QString	SearchStr=ParentWindow->GetRemarkForSearch();
		if(SearchStr.isEmpty()==false){
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION WHERE REMARK>=\'")
					+SearchStr
					+QString(/**/"\'  ORDER BY REMARK;");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION WHERE REMARK>=\'")
					+SearchStr
					+QString(/**/"\'  ORDER BY REMARK DESC;");
			}
		}
		else{
			if(ParentWindow->AcsendantOrder==true){
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
					+QString(/**/" ORDER BY REMARK;");
			}
			else{
				ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION")
					+QString(/**/" ORDER BY REMARK DESC;");
			}
		}
	}
	return ret;
}

//=========================================================================================

SelectRelationalMasterDataDialog::SelectRelationalMasterDataDialog(LayersBase *Base,int LastOrderMode,int LastAcsendantOrder,int LastOpenedID,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
    ,ui(new Ui::SelectRelationalMasterDataDialog)
{
    ui->setupUi(this);

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

	LayersBasePQSystem	*LBase=(LayersBasePQSystem *)GetLayersBase();
	QString	MasterCodeStr	=tr("MasterCode");
	QString	RegTimeStr		=tr("RegTime");
	QString	NumberStr		=LBase->GetParamPQSystem()->TitleMasterNumber	;
	QString	NameStr			=LBase->GetParamPQSystem()->TitleMasterName		;
	QString	RemarkStr		=LBase->GetParamPQSystem()->TitleRemark			;

	MModel->setHeaderData(0, Qt::Horizontal, MasterCodeStr	,Qt::DisplayRole);
	MModel->setHeaderData(1, Qt::Horizontal, RegTimeStr		,Qt::DisplayRole);
	MModel->setHeaderData(2, Qt::Horizontal, NumberStr		,Qt::DisplayRole);
	MModel->setHeaderData(3, Qt::Horizontal, NameStr		,Qt::DisplayRole);
	MModel->setHeaderData(4, Qt::Horizontal, RemarkStr		,Qt::DisplayRole);

	ui->labelNumber	->setText(NumberStr);
	ui->labelName	->setText(NameStr);
	ui->labelRemark	->setText(RemarkStr);

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
}

SelectRelationalMasterDataDialog::~SelectRelationalMasterDataDialog()
{
	for(int i=0;i<AllocatedViewCount;i++){
		TopViewDim[i].close();
	}
	delete	[]TopViewDim;
	
	delete ui;
	TopViewDim=NULL;
}

QString	SelectRelationalMasterDataDialog::GetNameForSearch(void)
{
	return ui->lineEditSearchByName->text();
}
QString	SelectRelationalMasterDataDialog::GetNumberForSearch(void)
{
	return ui->lineEditSearchByNumber->text();
}
QString	SelectRelationalMasterDataDialog::GetRemarkForSearch(void)
{
	return ui->lineEditSearchByRemark->text();
}
void	SelectRelationalMasterDataDialog::SelectView(int RelationCode)
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

void	SelectRelationalMasterDataDialog::SelectView(void)
{
	QModelIndex Index=ui->tableView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		int	RelationCode=M->data(RIndex).toInt();
		int	N=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveCount();
		QString	S=QString(/**/"SELECT MASTERNAME,REMARK,TOPVIEW FROM MASTERDATA WHERE RELATIONCODE=")
			+QString::number(RelationCode);
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
	}
}

void SelectRelationalMasterDataDialog::on_pushButtonLoad_clicked()
{
	QModelIndex Index=ui->tableView->currentIndex();

	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		QModelIndex RIndex=Index.sibling ( Index.row(), 0);
		ResultRelationCode=M->data(RIndex).toInt();
		done(true);
	}
}

void SelectRelationalMasterDataDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectRelationalMasterDataDialog::on_lineEditSearchByNumber_textChanged(const QString &arg1)
{
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		OrderMode=2;
		M->select();
	}
}

void SelectRelationalMasterDataDialog::on_lineEditSearchByName_textChanged(const QString &arg1)
{
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		OrderMode=3;
		M->select();
	}
}

void SelectRelationalMasterDataDialog::on_tableView_clicked(const QModelIndex &index)
{
	ui->pushButtonLoad->setEnabled(true);
	SelectView();
}

void SelectRelationalMasterDataDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
	on_pushButtonLoad_clicked();
}
void	SelectRelationalMasterDataDialog::MListSectionClicked ( int logicalIndex )
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
void SelectRelationalMasterDataDialog::on_lineEditSearchByRemark_textChanged(const QString &arg1)
{
	QSqlLoadMasterModel	*M=dynamic_cast<QSqlLoadMasterModel	 *>(ui->tableView->model());
	if(M!=NULL){
		OrderMode=4;
		M->select();
	}
}
