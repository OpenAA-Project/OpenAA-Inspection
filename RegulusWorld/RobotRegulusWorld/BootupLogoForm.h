#ifndef BOOTUPLOGOFORM_H
#define BOOTUPLOGOFORM_H

#include <QWidget>
#include "ui_BootupLogoForm.h"

class BootupLogoForm : public QWidget
{
	Q_OBJECT

public:
	BootupLogoForm(QWidget *parent = 0);
	~BootupLogoForm();

private:
	Ui::BootupLogoFormClass ui;
};

#endif // BOOTUPLOGOFORM_H
