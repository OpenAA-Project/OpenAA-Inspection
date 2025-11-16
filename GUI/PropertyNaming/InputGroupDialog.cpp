#include "PropertyNamingFormResource.h"
#include "InputGroupDialog.h"
#include "ui_InputGroupDialog.h"

InputGroupDialog::InputGroupDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::InputGroupDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	InstallOperationLog(this);
}

InputGroupDialog::~InputGroupDialog()
{
    delete ui;
}

void InputGroupDialog::on_pushButtonOK_clicked()
{
	GroupString	=ui->lineEditGroupName->text();
	done(true);
}

void InputGroupDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
