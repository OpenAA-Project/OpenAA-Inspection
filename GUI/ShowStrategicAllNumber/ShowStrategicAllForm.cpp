#include "ShowStrategicAllFormResource.h"
#include "ShowStrategicAllForm.h"
#include "ui_ShowStrategicAllForm.h"

ShowStrategicAllForm::ShowStrategicAllForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ShowStrategicAllForm)
{
    ui->setupUi(this);
}

ShowStrategicAllForm::~ShowStrategicAllForm()
{
    delete ui;
}

void ShowStrategicAllForm::on_pushButtonShow_clicked()
{
	int	n=GetLayersBase()->GetCurrentStrategicNumber();
	ui->lineEditCurrentStrategicNumber->setText(QString::number(n));

	n=GetLayersBase()->GetCurrentStrategicNumberForSeq();
	ui->lineEditCurrentStrategicNumberForSeq->setText(QString::number(n));

	n=GetLayersBase()->GetCurrentStrategicNumberForCalc();
	ui->lineEditCurrentStrategicNumberForCalc->setText(QString::number(n));
}
