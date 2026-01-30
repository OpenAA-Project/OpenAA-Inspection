/*
 * Copyright (C) 2012
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

	//���ʕ\�����̌����Ή�
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