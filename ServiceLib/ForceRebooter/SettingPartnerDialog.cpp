#include "SettingPartnerDialog.h"
#include "ui_SettingPartnerDialog.h"

SettingPartnerDialog::SettingPartnerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingPartnerDialog)
{
    ui->setupUi(this);
}

SettingPartnerDialog::~SettingPartnerDialog()
{
    delete ui;
}

void	SettingPartnerDialog::Init(void)
{
	ui->lineEditHostIP->setText(Info.HostName);
	ui->spinBoxPortNumber->setValue(Info.PortNumber);
	ui->lineEditRemark->setText(Info.Remark);
}

void SettingPartnerDialog::on_pushButtonOK_clicked()
{
	Info.HostName	=ui->lineEditHostIP->text();
	Info.PortNumber	=ui->spinBoxPortNumber->value();
	Info.Remark		=ui->lineEditRemark->text();
	done(true);
}

void SettingPartnerDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
