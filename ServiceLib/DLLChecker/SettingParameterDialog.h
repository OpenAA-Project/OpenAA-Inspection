#ifndef SETTINGPARAMETERDIALOG_H
#define SETTINGPARAMETERDIALOG_H

#include <QDialog>
#include "WEditParameterTab.h"
#include "XServiceForLayers.h"

class	ParamBase;

namespace Ui {
    class SettingParameterDialog;
}

class SettingParameterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ParamBase			*PBase;
	WEditParameterTab	*WTabGeneral;

public:
    explicit SettingParameterDialog(LayersBase *Base,ParamBase *p, QWidget *parent = 0);
    ~SettingParameterDialog();

private slots:
        void on_pushButtonOk_clicked();

private:
    Ui::SettingParameterDialog *ui;

	virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // SETTINGPARAMETERDIALOG_H
