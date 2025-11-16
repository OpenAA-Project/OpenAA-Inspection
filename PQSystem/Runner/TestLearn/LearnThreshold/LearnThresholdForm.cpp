#include "LearnThresholdForm.h"
#include "ui_LearnThresholdForm.h"
#include "SelectRelationalMasterDataDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

LearnThresholdForm::LearnThresholdForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::LearnThresholdForm)
{
    ui->setupUi(this);
	ResultRelationCode	=-1;
	CurrentAlgorithm	=NULL;
	CurrentLibrary		=NULL;

	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());

	::SetColumnWidthInTable(ui->tableWidgetLibrary,0, 25);
	::SetColumnWidthInTable(ui->tableWidgetLibrary,1, 75);
}

LearnThresholdForm::~LearnThresholdForm()
{
    delete ui;
}
bool	LearnThresholdForm::Initial(void)
{
	return true;
}
const QString	LearnThresholdForm::GetPath(void)
{
	return "分析から学習/しきい値を再設定";
}
void LearnThresholdForm::showEvent(QShowEvent *event)
{
	ResultRelationCode	=-1;
	CurrentAlgorithm	=NULL;
	CurrentLibrary		=NULL;

	ui->lineEditMasterID	->setText("");
	ui->lineEditMasterName	->setText("非選択で全マスターが対象");

	GetAllAlgorithmPointers(AlgorithmContainer);
	ui->listWidgetAlgorithm->clear();
	for(AlgorithmBasePointerList *a=AlgorithmContainer.GetFirst();a!=NULL;a=a->GetNext()){
		ui->listWidgetAlgorithm->addItem(a->GetAlgorithmBase()->GetExplain());
	}
	ui->tableWidgetLibrary->setRowCount(0);
	ui->listWidgetSpecial	->clear();
}
void LearnThresholdForm::on_pushButtonSelectMaster_clicked()
{
	SelectRelationalMasterDataDialog	D(GetLayersBase(),0,1,-1);
	if(D.exec()==(bool)true){
		ResultRelationCode=D.ResultRelationCode;
		QString		RetRelationNumber;
		QString		RetRelationName;
		QString		RetRemark;
		int			RetRelationType;
		QByteArray	CommonData;
		int32		ThresholdLevelID;
		if(GetMasterRelation(ResultRelationCode
							,RetRelationNumber
							,RetRelationName
							,RetRemark
							,RetRelationType
							,CommonData
							,ThresholdLevelID)==true){
			ui->lineEditMasterID	->setText(QString::number(ResultRelationCode));
			ui->lineEditMasterName	->setText(RetRelationName);
		}
	}
}

void LearnThresholdForm::on_listWidgetAlgorithm_clicked(const QModelIndex &index)
{
	int	Row=ui->listWidgetAlgorithm->currentRow();
	if(Row>=0){
		AlgorithmBasePointerList *a=AlgorithmContainer[Row];
		if(a!=NULL){
			CurrentAlgorithm=a->GetAlgorithmBase();
			AlgorithmLibraryContainer	*LibC=CurrentAlgorithm->GetLibraryContainer();
			if(LibC!=NULL){
				LibC->EnumLibrary(LibIDList);
				ui->tableWidgetLibrary->setRowCount(LibIDList.GetCount());
				int	ARow=0;
				for(AlgorithmLibraryList *L=LibIDList.GetFirst();L!=NULL;L=L->GetNext(),ARow++){
					::SetDataToTable(ui->tableWidgetLibrary,0,ARow,QString::number(L->GetLibID()));
					::SetDataToTable(ui->tableWidgetLibrary,1,ARow,L->GetLibName());
				}
				return;
			}
		}
	}
	ui->tableWidgetLibrary->setRowCount(0);
}

void LearnThresholdForm::on_tableWidgetLibrary_clicked(const QModelIndex &index)
{

}

void LearnThresholdForm::on_pushButtonStartSearch_clicked()
{

}

void LearnThresholdForm::on_pushButtonSimulateView_clicked()
{

}

void LearnThresholdForm::on_pushButtonTestByImage_clicked()
{

}

void LearnThresholdForm::on_pushButtonUpdate_clicked()
{

}
