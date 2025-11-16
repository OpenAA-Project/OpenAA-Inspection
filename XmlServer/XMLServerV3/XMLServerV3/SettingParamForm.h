#ifndef SETTINGPARAMFORM_H
#define SETTINGPARAMFORM_H

#include <QWidget>
#include "WEditParameterTab.h"

namespace Ui {
    class SettingParamForm;
}

class	XMLServerComm;

class SettingParamForm : public QWidget
{
    Q_OBJECT

	XMLServerComm	&SMain;
	WEditParameterTab	*WTabGeneral;

public:
    explicit SettingParamForm(XMLServerComm	&sMain ,QWidget *parent = 0);
    ~SettingParamForm();

private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::SettingParamForm *ui;

	virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // SETTINGPARAMFORM_H
