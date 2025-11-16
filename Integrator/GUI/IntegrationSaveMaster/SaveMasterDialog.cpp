#include "IntegrationSaveMasterResource.h"
#include "SaveMasterDialog.h"
#include "ui_SaveMasterDialog.h"
#include "IntegrationSaveMaster.h"
#include "InputPanelDialog.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "XDatabaseLoader.h"
#include "IntegrationShowRelationInfoForm.h"
#include "IntegrationShowName.h"
#include "IntegrationNewMaster.h"
#include <QMessageBox>

QSqlSaveMasterModel::QSqlSaveMasterModel(QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentWindow	=dynamic_cast<SaveMasterDialog *>(parent);
}
QString QSqlSaveMasterModel::selectStatement () const
{
	QString	ret;

	QString	SearchStr=ParentWindow->GetSearchString();

	if(SearchStr.isEmpty()==true){
		ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION ORDER BY RELATIONNAME");
	}
	else{
		ret=QString(/**/"SELECT RELATIONCODE,REGTIME,RELATIONNUMBER,RELATIONNAME,REMARK FROM MASTERRELATION WHERE RELATIONNAME>=")
			+SearchStr
			+QString(/**/" ORDER BY RELATIONNAME");
	}

	return ret;
}
//------------------------------------------------------------------------------------------------------
SaveMasterDialog::SaveMasterDialog(LayersBase *Base
								,  IntegrationSaveMaster *P
								,  bool ModeNew ,bool ModeUpdate
								,  QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base)
	,ParentGUI(dynamic_cast<IntegrationSaveMaster *>(P))
    ,ui(new Ui::SaveMasterDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	QSqlSaveMasterModel *MModel = new QSqlSaveMasterModel(this,GetLayersBase()->GetDatabase());
	MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	MModel->select();
	MModel->removeColumn(0); // don't show the ID

	ui->tableView->setModel(MModel);
	ui->tableView->setColumnWidth (0, 90);
	ui->tableView->setColumnWidth (1, 120);
	ui->tableView->setColumnWidth (2, 200);
	ui->tableView->setColumnWidth (3, 200);	
	ui->tableView->setColumnWidth (4, 200);	

	QString	MasterCodeStr	=LangSolver.GetString(SaveMasterDialog_LS,LID_1)/*"MasterCode"*/;
	QString	RegTimeStr		=LangSolver.GetString(SaveMasterDialog_LS,LID_2)/*"RegTime"*/;
	QString	NumberStr		=LangSolver.GetString(SaveMasterDialog_LS,LID_3)/*"Number"*/;
	QString	NameStr			=LangSolver.GetString(SaveMasterDialog_LS,LID_4)/*"Name"*/;
	QString	RemarkStr		=LangSolver.GetString(SaveMasterDialog_LS,LID_5)/*"Remark"*/;

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

	ui->labelNumber	->setText(NumberStr);
	ui->labelName	->setText(NameStr);
	ui->labelRemark	->setText(RemarkStr);

	if(GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode()<0){
		ui->pushButtonUpdate->setEnabled(false);
	}
	else if(ModeUpdate==false){
		ui->pushButtonUpdate->setEnabled(false);
	}
	if(ModeNew==false){
		ui->pushButtonSaveNew->setEnabled(false);
	}

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
	IntegrationNewMaster	*fn=(IntegrationNewMaster *)GetLayersBase()->FindByName(/**/"Integration",/**/"NewMaster",/**/"");
	if(fn!=NULL){
		ui->doubleSpinBoxSizeX->setMaximum(fn->MaxWidth );
		ui->doubleSpinBoxSizeY->setMaximum(fn->MaxLength);
	}

	int	RelationCode=GetLayersBase()->GetIntegrationBasePointer()->GetMasterRelationCode();
	if(RelationCode>0){
		QString RetRelationNumber	;
		QString RetRelationName	;
		QString RetRemark		;
		int		RetRelationType	;
		QByteArray	CommonByteArray;
		int32	ThresholdLevelID;
		if(GetLayersBase()->GetDatabaseLoader()->G_GetMasterRelation(GetLayersBase()->GetDatabase() 
										,RelationCode
										,RetRelationNumber
										,RetRelationName
										,RetRemark
										,RetRelationType
										,CommonByteArray
										,ThresholdLevelID)==true){
			IntegrationCommonData	TmpCommonData(CommonByteArray);
			CommonData	=TmpCommonData;

			ui->EditMasterName		->setText(RetRelationName);
			ui->EditRemark			->setText(RetRemark);
			ui->EditMasterNumber	->setText(RetRelationNumber);
			ui->doubleSpinBoxSizeX	->setValue(TmpCommonData.CommonSizeX);
			ui->doubleSpinBoxSizeY	->setValue(TmpCommonData.CommonSizeY);
		}
	}
	else{
		IntegrationCommonData	*C=GetLayersBase()->GetIntegrationBasePointer()->GetCommonData();
		if(C!=NULL){
			ui->EditMasterName		->setText(C->RelationName);
			ui->EditRemark			->setText(C->RelationRemark);
			ui->EditMasterNumber	->setText(C->RelationNumber);
			ui->doubleSpinBoxSizeX	->setValue(C->CommonSizeX);
			ui->doubleSpinBoxSizeY	->setValue(C->CommonSizeY);
		}
	}
	InstallOperationLog(this);
}

SaveMasterDialog::~SaveMasterDialog()
{
	for(int i=0;i<AllocatedViewCount;i++){
		TopViewDim[i].close();
	}
	delete	[]TopViewDim;

    delete ui;
	TopViewDim=NULL;
}

QString	SaveMasterDialog::GetSearchString(void)
{
	return ui->lineEditSearchByName->text();
}

void	SaveMasterDialog::SelectView(void)
{
	QModelIndex Index=ui->tableView->currentIndex();

	QSqlSaveMasterModel	*M=dynamic_cast<QSqlSaveMasterModel	 *>(ui->tableView->model());
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
void SaveMasterDialog::on_pushButtonInputPanelName_clicked()
{
	InputPanelDialog	D(-1 ,ui->EditMasterName->text());
	if(D.exec()==(bool)true){
		ui->EditMasterName->setText(D.GetResult());
	}
}

void SaveMasterDialog::on_pushButtonInputPanelRemark_clicked()
{
	InputPanelDialog	D(-1 ,ui->EditRemark->text());
	if(D.exec()==(bool)true){
		ui->EditRemark->setText(D.GetResult());
	}
}

void SaveMasterDialog::on_pushButtonSaveNew_clicked()
{
	ResultName	=ui->EditMasterName		->text();
	ResultRemark=ui->EditRemark			->text();
	ResultNumber=ui->EditMasterNumber	->text();

	if(ResultNumber.isEmpty()==true && ResultName.isEmpty()!=true){
		ResultNumber=ResultName;
	}
	if(ResultNumber.isEmpty()!=true && ResultName.isEmpty()==true){
		ResultName=ResultNumber;
	}
	if(ParentGUI->CheckDupInMaster(ResultName,ResultNumber,ResultRemark,true)==false){
		QMessageBox::critical(NULL
								,LangSolver.GetString(SaveMasterDialog_LS,LID_14)/*"Error"*/
								,LangSolver.GetString(SaveMasterDialog_LS,LID_15)/*"Please set unique name."*/);
		return;
	}

	CommonData.CommonSizeX	=ui->doubleSpinBoxSizeX	->value();
	CommonData.CommonSizeY	=ui->doubleSpinBoxSizeY	->value();
	CommonData.RelationName		=ResultName;
	CommonData.RelationRemark	=ResultRemark;
	CommonData.RelationNumber	=ResultNumber;
	done(1);
}

void SaveMasterDialog::on_pushButtonUpdate_clicked()
{
	ResultName	=ui->EditMasterName		->text();
	ResultRemark=ui->EditRemark			->text();
	ResultNumber=ui->EditMasterNumber	->text();

	if(ResultNumber.isEmpty()==true && ResultName.isEmpty()!=true){
		ResultNumber=ResultName;
	}
	if(ResultNumber.isEmpty()!=true && ResultName.isEmpty()==true){
		ResultName=ResultNumber;
	}
	if(ParentGUI->CheckDupInMaster(ResultName,ResultNumber,ResultRemark,false)==false){
		QMessageBox::critical(NULL
								,LangSolver.GetString(SaveMasterDialog_LS,LID_16)/*"Error"*/
								,LangSolver.GetString(SaveMasterDialog_LS,LID_17)/*"Please set unique name."*/);
		return;
	}
	CommonData.CommonSizeX		=ui->doubleSpinBoxSizeX	->value();
	CommonData.CommonSizeY		=ui->doubleSpinBoxSizeY	->value();
	CommonData.RelationName		=ResultName;
	CommonData.RelationRemark	=ResultRemark;
	CommonData.RelationNumber	=ResultNumber;
	done(2);
}

void SaveMasterDialog::on_pushButtonCancel_clicked()
{
	done(0);
}

void SaveMasterDialog::on_pushButtonInputPanel_clicked()
{
	InputPanelDialog	D(-1 ,ui->lineEditSearchByName->text());
	if(D.exec()==(bool)true){
		ui->lineEditSearchByName->setText(D.GetResult());
		ui->tableView->show();
	}
}

void SaveMasterDialog::on_tableView_clicked(const QModelIndex &index)
{
	SelectView();
}

void SaveMasterDialog::on_pushButtonInputPanelSizeX_clicked()
{
	InputPanelDialog	D(IPD_Number ,QString::number(ui->doubleSpinBoxSizeX->value(),'f',1));
    if(D.exec()==(bool)true){
		ui->doubleSpinBoxSizeX->setValue(D.GetResult().toDouble());
    }
}

void SaveMasterDialog::on_pushButtonInputPanelSizeY_clicked()
{
    InputPanelDialog	D(IPD_Number ,QString::number(ui->doubleSpinBoxSizeY->value(),'f',1));
    if(D.exec()==(bool)true){
        ui->doubleSpinBoxSizeY->setValue(D.GetResult().toDouble());
    }
}

void SaveMasterDialog::on_pushButtonInputPanelNumber_clicked()
{
    InputPanelDialog	D(-1 ,ui->EditMasterNumber->text());
    if(D.exec()==(bool)true){
        ui->EditMasterNumber->setText(D.GetResult());
    }
}
