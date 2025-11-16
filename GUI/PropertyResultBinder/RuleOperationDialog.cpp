#include "PropertyResultBinderFormResource.h"
#include "RuleOperationDialog.h"
#include "ui_RuleOperationDialog.h"

RuleOperationDialog::RuleOperationDialog(LayersBase *base, QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::RuleOperationDialog)
{
    ui->setupUi(this);
	InstallOperationLog(this);
}

RuleOperationDialog::~RuleOperationDialog()
{
    delete ui;
}
void	RuleOperationDialog::Initial(RuleOfBinderBase *rule)
{
	ui->lineEditName	->setText(rule->Name);
	ui->lineEditRemark	->setText(rule->Remark);
	ui->checkBoxConclusion	->setChecked(rule->Conclusion);
}
void RuleOperationDialog::on_pushButtonOK_clicked()
{
	RuleName	=ui->lineEditName	->text();
	RuleRemark	=ui->lineEditRemark	->text();
	Conclusion	=ui->checkBoxConclusion	->isChecked();
	done(true);
}

void RuleOperationDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
