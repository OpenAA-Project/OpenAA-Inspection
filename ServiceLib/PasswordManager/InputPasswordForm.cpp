#include "XTypeDef.h"
#include "InputPasswordFormDialog.h"
#include "ui_InputPasswordForm.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

InputPasswordFormDialog::InputPasswordFormDialog(QWidget *parent, Qt::WindowFlags f) :
    QDialog(parent),
    ui(new Ui::InputPasswordFormDialog)
{
    ui->setupUi(this);

    QRegularExpression rx("^[a-z|A-Z|\\d]*$");
    QRegularExpressionValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->liedPassword->setValidator(validator);
}

InputPasswordFormDialog::~InputPasswordFormDialog()
{
    delete ui;
}

QString	InputPasswordFormDialog::GetLiedPassword(void)
{
	return ui->liedPassword->text();
}