#include "ButtonSettingThresholdResource.h"
#include "QuestionAddDelDialog.h"
#include "ui_QuestionAddDelDialog.h"
#include "XGeneralFunc.h"

QuestionAddDelDialog::QuestionAddDelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionAddDelDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SetWidgetCenter(this);
}

QuestionAddDelDialog::~QuestionAddDelDialog()
{
    delete ui;
}

void QuestionAddDelDialog::on_toolButtonOK_clicked()
{
	done(1);
}

void QuestionAddDelDialog::on_toolButtonNG_clicked()
{
	done(2);
}

void QuestionAddDelDialog::on_toolButtonCancel_clicked()
{
	done(0);
}
