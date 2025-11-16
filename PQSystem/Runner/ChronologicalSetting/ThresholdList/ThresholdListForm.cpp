#include "ThresholdListForm.h"
#include "ui_ThresholdListForm.h"
#include "SelectRelationalMasterDataDialog.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

ThresholdListForm::ThresholdListForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::ThresholdListForm)
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

ThresholdListForm::~ThresholdListForm()
{
    delete ui;
}
bool	ThresholdListForm::Initial(void)
{
	return true;
}
const QString	ThresholdListForm::GetPath(void)
{
	return "設定時系列表示/変更リスト表示";
}
void ThresholdListForm::showEvent(QShowEvent *event)
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
void ThresholdListForm::on_pushButtonSelectMaster_clicked()
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

void ThresholdListForm::on_listWidgetAlgorithm_clicked(const QModelIndex &index)
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

void ThresholdListForm::on_tableWidgetLibrary_clicked(const QModelIndex &index)
{

}

void ThresholdListForm::on_pushButtonStartSearch_clicked()
{

}

void ThresholdListForm::on_pushButtonView_clicked()
{

}

void ThresholdListForm::on_pushButtonExcel_clicked()
{

}
