#include "AddItemDialog.h"
#include "ui_AddItemDialog.h"

AddItemDialog::AddItemDialog(LayersBase *base ,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::AddItemDialog)
{
    ui->setupUi(this);
	PeakCount		=2;
	Angle			=90;
	PeakIsolation	=30;
	UsageLayer		=0;
	AbandonRateL	=0.1;
	AbandonRateH	=0.2;
	InstallOperationLog(this);
}

AddItemDialog::~AddItemDialog()
{
    delete ui;
}
void	AddItemDialog::SetInitial(QString &ItemName,int PeakCount,double Angle,int PeakIsolation ,int UsageLayer,double AbandonRateL ,double AbandonRateH)
{
	ui->lineEditItemName			->setText (ItemName		);
	ui->spinBoxPeakCount			->setValue(PeakCount	);
	ui->doubleSpinBoxAngle			->setValue(Angle		);
	ui->doubleSpinBoxPeakIsolation	->setValue(PeakIsolation		);
	ui->spinBoxUsageLayer			->setValue(UsageLayer	);
	ui->doubleSpinBoxAbandonRateL	->setValue(AbandonRateL	);
	ui->doubleSpinBoxAbandonRateH	->setValue(AbandonRateH	);
}

void AddItemDialog::on_pushButtonOK_clicked()
{
	ItemName		=ui->lineEditItemName			->text();
	PeakCount		=ui->spinBoxPeakCount			->value();
	Angle			=ui->doubleSpinBoxAngle			->value();
	PeakIsolation	=ui->doubleSpinBoxPeakIsolation	->value();
	UsageLayer		=ui->spinBoxUsageLayer			->value();
	AbandonRateL	=ui->doubleSpinBoxAbandonRateL	->value();
	AbandonRateH	=ui->doubleSpinBoxAbandonRateH	->value();

	done(true);
}

void AddItemDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
