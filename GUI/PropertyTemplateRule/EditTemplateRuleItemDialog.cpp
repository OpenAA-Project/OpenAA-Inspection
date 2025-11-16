#include "EditTemplateRuleItemDialog.h"
#include "ui_EditTemplateRuleItemDialog.h"

EditTemplateRuleItemDialog::EditTemplateRuleItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTemplateRuleItemDialog)
{
    ui->setupUi(this);
}

EditTemplateRuleItemDialog::~EditTemplateRuleItemDialog()
{
    delete ui;
}

void EditTemplateRuleItemDialog::on_pushButtonCreate_clicked()
{

}


void EditTemplateRuleItemDialog::on_pushButtonUpdate_clicked()
{

}


void EditTemplateRuleItemDialog::on_pushButtonDelete_clicked()
{

}


void EditTemplateRuleItemDialog::on_pushButtonClose_clicked()
{

}


void EditTemplateRuleItemDialog::on_tableWidgetMemberList_doubleClicked(const QModelIndex &index)
{

}

