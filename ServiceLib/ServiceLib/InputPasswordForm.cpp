#include "ServiceLibResource.h"
#include "XTypeDef.h"
#include "InputPasswordForm.h"
#include "ui_InputPasswordForm.h"
#include "XGeneralFunc.h"

InputPasswordForm::InputPasswordForm(LayersBase *pbase ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(pbase)
    ,ui(new Ui::InputPasswordForm)
{
    ui->setupUi(this);
    LangLibSolver.SetUI(this);

    SetWidgetCenter(this);
    ui->lineEditPassword->setFocus();
    InstallOperationLog(this);
}

InputPasswordForm::~InputPasswordForm()
{
    delete ui;
}

void InputPasswordForm::on_pushButtonOK_clicked()
{
    Password=ui->lineEditPassword->text();
    done(true);
}

void InputPasswordForm::on_pushButtonCancel_clicked()
{
    done(false);
}
