#include "RunningMachineForm.h"
#include "ui_RunningMachineForm.h"
#include "XGeneralFunc.h"
#include "XDatabaseLoader.h"

RunningMachineForm::RunningMachineForm(LayersBase *base ,const QString &root ,const QString &name
						 ,QWidget *parent) :
    PQSystemRunner(base ,root ,name,parent),
    ui(new Ui::RunningMachineForm)
{
    ui->setupUi(this);
	ui->dateTimeEditStart	->setDateTime(QDateTime::currentDateTime());
	ui->dateTimeEditEnd		->setDateTime(QDateTime::currentDateTime());
}

RunningMachineForm::~RunningMachineForm()
{
    delete ui;
}
bool	RunningMachineForm::Initial(void)
{
	return true;
}
const QString	RunningMachineForm::GetPath(void)
{
	return "設備稼働率グラフ/設備稼働率グラフ";
}
void RunningMachineForm::showEvent(QShowEvent *event)
{

}
void RunningMachineForm::on_pushButtonStartSearch_clicked()
{

}

void RunningMachineForm::on_pushButtonView_clicked()
{

}

void RunningMachineForm::on_pushButtonExcel_clicked()
{

}
