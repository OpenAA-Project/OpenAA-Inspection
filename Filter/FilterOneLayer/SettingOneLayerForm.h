#ifndef SETTINGONELAYERFORM_H
#define SETTINGONELAYERFORM_H

#include <QDialog>
#include "ui_SettingOneLayerForm.h"
#include "XServiceForLayers.h"

class SettingOneLayerForm : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingOneLayerForm(LayersBase *base
					,int _Layer ,int _LayerNumb
					,int _MethodValue
					,int _Param
					,QWidget *parent = 0);
	~SettingOneLayerForm();

	int	Layer;
	int	MethodValue;
	int	Param;
private:
	Ui::SettingOneLayerFormClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETTINGONELAYERFORM_H
