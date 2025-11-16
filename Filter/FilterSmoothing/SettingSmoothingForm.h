#ifndef SETTINGSMOOTHINGFORM_H
#define SETTINGSMOOTHINGFORM_H

#include <QDialog>
#include "ui_SettingSmoothingForm.h"
#include "XServiceForLayers.h"

class SettingSmoothingForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingSmoothingForm(LayersBase *base,int methodValue ,QWidget *parent = 0);
	~SettingSmoothingForm();

	int	MethodValue;

private:
	Ui::SettingSmoothingFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETTINGSMOOTHINGFORM_H
