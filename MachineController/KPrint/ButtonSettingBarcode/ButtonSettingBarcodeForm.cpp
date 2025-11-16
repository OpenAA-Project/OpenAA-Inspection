#include "ButtonSettingBarcodeForm.h"
#include "ui_ButtonSettingBarcodeForm.h"
#include "SettingBarcodeFormDialog.h"

extern	char *sRoot;
extern	char *sName;

ButtonSettingBarcodeForm::ButtonSettingBarcodeForm(LayersBase *Base, QWidget *parent) :
	GUIFormBase(Base, parent),
    ui(new Ui::ButtonSettingBarcodeForm)
{
    ui->setupUi(this);
	SlaveNo=0;
	Msg=/**/"Set Barcose Threshold";
	connect(this, SIGNAL(SignalResize()), this, SLOT(ResizeAction()));
}

ButtonSettingBarcodeForm::~ButtonSettingBarcodeForm()
{
    delete ui;
}
void	ButtonSettingBarcodeForm::Prepare(void)
{
	ui->PushButtonThreshold->setText(Msg);
	ui->PushButtonThreshold->setFont(CFont);
	ResizeAction();
}
void	ButtonSettingBarcodeForm::ResizeAction()
{
	ui->PushButtonThreshold->resize(width(), height());
}

void ButtonSettingBarcodeForm::on_PushButtonThreshold_clicked()
{
	SettingBarcodeFormDialog	D(GetLayersBase(), this);
	D.exec();
}
