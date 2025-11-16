#ifndef SETTINGSHRINKFORM_H
#define SETTINGSHRINKFORM_H

#include <QDialog>
#include "ui_SettingShrinkForm.h"
#include "XServiceForLayers.h"

class SettingShrinkForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingShrinkForm(LayersBase *base,int _ShrinkRate,int _ShrinkMethod,QWidget *parent = 0);
	~SettingShrinkForm();

	int		ShrinkRate;
	int		ShrinkMethod;
private:
	Ui::SettingShrinkFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETTINGSHRINKFORM_H
