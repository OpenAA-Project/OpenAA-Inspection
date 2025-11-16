#include "SelectSettingDialog.h"
#include "ui_SelectSettingDialog.h"

SelectSettingDialog::SelectSettingDialog(CameraProvider *parentMain,int number ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectSettingDialog)
{
    ui->setupUi(this);

	ParentMain	=parentMain;
	Number		=number;

	ui->spinBoxCameraNo->setValue(ParentMain->GetCam(Number)->GetCamNo());
}

SelectSettingDialog::~SelectSettingDialog()
{
    delete ui;
}

void SelectSettingDialog::on_pushButtonSetting_clicked()
{

}


void SelectSettingDialog::on_pushButtonClose_clicked()
{
	ParentMain->SetCamNo(Number,ui->spinBoxCameraNo->value());
	close();
}
