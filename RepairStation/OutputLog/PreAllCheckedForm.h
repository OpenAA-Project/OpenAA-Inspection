#ifndef PREALLCHECKEDFORM_H
#define PREALLCHECKEDFORM_H

#include <QWidget>
#include "ui_PreAllCheckedForm.h"

class PreAllCheckedForm : public QWidget
{
	Q_OBJECT

public:
	PreAllCheckedForm(QWidget *parent = 0);
	~PreAllCheckedForm();

	Ui::PreAllCheckedFormClass ui;

private:
//	Ui::PreAllCheckedFormClass ui;
};

#endif // PREALLCHECKEDFORM_H
