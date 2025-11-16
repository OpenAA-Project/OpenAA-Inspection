#include "ShadowSettingDialog.h"
#include "ui_ShadowSettingDialog.h"
#include "ShrinkedInspection.h"

ShadowSettingDialog::ShadowSettingDialog(ShrinkedInspection *_Handle,QWidget *parent) :
    QDialog(parent),Handle(_Handle),
    ui(new Ui::ShadowSettingDialog)
{
    ui->setupUi(this);

	ui->spinBoxSkipDot			->setValue(Handle->SkipDot);
	ui->checkBoxHorizontalTile	->setChecked(Handle->HorizontalTile );
	ui->checkBoxVerticalTile	->setChecked(Handle->VerticalTile	);
}

ShadowSettingDialog::~ShadowSettingDialog()
{
    delete ui;
}

void ShadowSettingDialog::on_pushButtonOK_clicked()
{
	Handle->SetSkipDot(ui->spinBoxSkipDot->value());
	Handle->HorizontalTile	=ui->checkBoxHorizontalTile	->isChecked();
	Handle->VerticalTile	=ui->checkBoxVerticalTile	->isChecked();
	done(true);
}

void ShadowSettingDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
