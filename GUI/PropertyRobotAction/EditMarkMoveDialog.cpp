#include "EditMarkMoveDialog.h"
#include "ui_EditMarkMoveDialog.h"
#include "XRobotAction.h"

EditMarkMoveDialog::EditMarkMoveDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::EditMarkMoveDialog)
{
    ui->setupUi(this);

    Speed=20;
    ui->doubleSpinBox->setValue(Speed);
}

EditMarkMoveDialog::~EditMarkMoveDialog()
{
    delete ui;
}

void    EditMarkMoveDialog::Initial(ActionMarkBase *src)
{
    ActionMarkMove  *a=dynamic_cast<ActionMarkMove *>(src);
    if(a!=NULL){
        Speed=a->Speed;
        ui->doubleSpinBox->setValue(Speed);
    }
}

void EditMarkMoveDialog::on_pushButtonOK_clicked()
{
    Speed=ui->doubleSpinBox->value();
    done(true);
}


void EditMarkMoveDialog::on_pushButtonCancel_clicked()
{
    done(false);
}

