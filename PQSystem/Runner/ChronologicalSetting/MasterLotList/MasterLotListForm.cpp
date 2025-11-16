#include "MasterLotListForm.h"
#include "ui_MasterLotListForm.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

MasterLotListForm::MasterLotListForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::MasterLotListForm)
{
    ui->setupUi(this);
	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());
}

MasterLotListForm::~MasterLotListForm()
{
    delete ui;
}
bool	MasterLotListForm::Initial(void)
{
	return true;
}
const QString	MasterLotListForm::GetPath(void)
{
	return "設定時系列表示/マスター、ロットのリスト表示";
}
void MasterLotListForm::showEvent(QShowEvent *event)
{
}
void MasterLotListForm::on_pushButtonStartSearch_clicked()
{

}

void MasterLotListForm::on_pushButtonView_clicked()
{

}

void MasterLotListForm::on_pushButtonExcel_clicked()
{

}
