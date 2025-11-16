#include "ButtonThresholdResource.h"
#include "PasswordForm.h"
#include <QMessageBox>

PasswordForm::PasswordForm(QString sPassword,QWidget *parent)
	: QDialog(parent),Password(sPassword)
{
	ui.setupUi(this);

	//connect
	connect(ui.pbOK		,SIGNAL(clicked()),this,SLOT(pbOKClicked()));
	connect(ui.pbCancel	,SIGNAL(clicked()),this,SLOT(pbCancelClicked()));

	//focus
	ui.lePassword->setFocus();

	//‰æ–Ê•\Ž¦•”‚ÌŒ¾Œê‘Î‰ž
	LangSolver.SetUI(this);
}

PasswordForm::~PasswordForm()
{
}

void PasswordForm::pbOKClicked()
{
	if(ui.lePassword->text()==Password){
		accept();
	}
	else{
		QMessageBox::warning(this,LangSolver.GetString(PasswordForm_LS,LID_4)/*"Message"*/,LangSolver.GetString(PasswordForm_LS,LID_5)/*"Password is wrong."*/);
		reject();
	}
}

void PasswordForm::pbCancelClicked()
{
	reject();
}
