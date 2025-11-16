#include "SettingRobotDialog.h"
#include "ui_SettingRobotDialog.h"

SettingRobotDialog::SettingRobotDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SettingRobotDialog)
{
    ui->setupUi(this);

    IPAddress           =/**/"192.168.58.2";
    velPercentage       =30;
    accPercentage       =30;
    max_disPercentage   =20;
}

SettingRobotDialog::~SettingRobotDialog()
{
    delete ui;
}

void    SettingRobotDialog::Initial(void)
{
    ui->lineEditIPAddress           ->setText(IPAddress);
    ui->doubleSpinBoxSpeed          ->setValue(velPercentage);
    ui->doubleSpinBoxAccel          ->setValue(accPercentage);
    ui->doubleSpinBoxMaxDisPercent  ->setValue(max_disPercentage);
}

void SettingRobotDialog::on_pushButtonOK_clicked()
{
    IPAddress           =ui->lineEditIPAddress           ->text();
    velPercentage       =ui->doubleSpinBoxSpeed          ->value();
    accPercentage       =ui->doubleSpinBoxAccel          ->value();
    max_disPercentage   =ui->doubleSpinBoxMaxDisPercent  ->value();
    done(true);
}


void SettingRobotDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

