#ifndef PASSWORDFORM_H
#define PASSWORDFORM_H

#include <QDialog>
#include "ui_PasswordForm.h"

class PasswordForm : public QDialog
{
	Q_OBJECT

public:
	PasswordForm(QString sPassword,QWidget *parent = 0);
	~PasswordForm();

private slots:
	void	pbOKClicked();
	void	pbCancelClicked();

private:
	Ui::PasswordFormClass ui;
	QString Password;
};

#endif // PASSWORDFORM_H
