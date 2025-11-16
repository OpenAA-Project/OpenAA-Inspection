#ifndef OKCHECKFORM_H
#define OKCHECKFORM_H

#include <QWidget>
#include "ui_OKCheckForm.h"

class OKCheckForm : public QWidget
{
	Q_OBJECT

public:
	OKCheckForm(QWidget *parent = 0);
	~OKCheckForm();

private:
	Ui::OKCheckFormClass ui;
};

#endif // OKCHECKFORM_H
