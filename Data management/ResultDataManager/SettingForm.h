#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QDialog>
#include "XResultDataManager.h"
#include "WEditParameterTab.h"
#include "XServiceForLayers.h"

namespace Ui {
    class SettingForm;
}

class SettingForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ResultDataManagerParam	*SParam;
	WEditParameterTab	*WTabGeneral;

public:
    explicit SettingForm(LayersBase *Base ,ResultDataManagerParam *Param ,QWidget *parent = 0);
    ~SettingForm();

private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::SettingForm *ui;

	virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // SETTINGFORM_H
