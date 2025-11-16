#include "GeneralTabSheetResource.h"
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

	//?a?E?\?|???I???e?I??
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
		QMessageBox::warning(this,LangSolver.GetString(PasswordForm_LS,LID_1)/*"Message"*/,LangSolver.GetString(PasswordForm_LS,LID_2)/*"Password is wrong."*/);
		reject();
	}
}

void PasswordForm::pbCancelClicked()
{
	reject();
}
