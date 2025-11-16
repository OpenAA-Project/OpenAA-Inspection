#include "SettingKoreaST8ChDialog.h"
#include "ui_SettingKoreaST8ChDialog.h"
#include "KoreaST8CH.h"

SettingKoreaST8ChDialog::SettingKoreaST8ChDialog(KoreaST8ChPanel *panel ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingKoreaST8ChDialog)
	,Panel(panel)
{
    ui->setupUi(this);
	for(int i=0;i<MaxCountOfLED;i++){
		ui->listWidgetCH->addItem(QString("Channel ")+QString::number(i+1));
	}
	panel->GetLayersBase()->InstallOperationLog(this);
}

SettingKoreaST8ChDialog::~SettingKoreaST8ChDialog()
{
    delete ui;
}

void SettingKoreaST8ChDialog::on_pushButtonTransmit_clicked()
{
	int	Ch=ui->listWidgetCH->currentRow();
	bool	OnOff=ui->toolButtonLightON->isChecked();
	int		LightValue=ui->spinBoxLightValue->value();
	Panel->SetValue(Ch,LightValue,OnOff);
}

void SettingKoreaST8ChDialog::on_pushButtonClose_clicked()
{
	close();
}
