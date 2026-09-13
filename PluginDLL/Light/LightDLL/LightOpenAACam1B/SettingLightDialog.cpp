#include "SettingLightDialog.h"
#include "ui_SettingLightDialog.h"

SettingLightDialog::SettingLightDialog(LayersBase *base ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
    , ui(new Ui::SettingLightDialog)
{
    ui->setupUi(this);


}

SettingLightDialog::~SettingLightDialog()
{
    delete ui;
}
void SettingLightDialog::Initial(int32 LightID,struct  SocketPacket &dataPacket)
{
    DataPacket=dataPacket;

    ui->checkBoxLight0Enable->setChecked(DataPacket.Data1.Light0Enable);
    ui->checkBoxLight1Enable->setChecked(DataPacket.Data1.Light1Enable);
    ui->spinBoxLightValue0->setValue(DataPacket.Data1.Light0Value);
    ui->spinBoxLightValue1->setValue(DataPacket.Data1.Light1Value);
}

void SettingLightDialog::on_pushButtonOK_clicked()
{
    DataPacket.Data1.Light0Enable=ui->checkBoxLight0Enable->isChecked();
    DataPacket.Data1.Light1Enable=ui->checkBoxLight1Enable->isChecked();
    DataPacket.Data1.Light0Value    =ui->spinBoxLightValue0->value();
    DataPacket.Data1.Light1Value    =ui->spinBoxLightValue1->value();
    done(true);
}


void SettingLightDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

