#ifndef SETTINGMEDIANFORM_H
#define SETTINGMEDIANFORM_H

#include <QDialog>
#include "ui_SettingMedianForm.h"
#include "XServiceForLayers.h"

class SettingMedianForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingMedianForm(LayersBase *base,int _FilterDot,QWidget *parent = 0);
	~SettingMedianForm();

	int		FilterDot;
private:
	Ui::SettingMedianFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETTINGMEDIANFORM_H
