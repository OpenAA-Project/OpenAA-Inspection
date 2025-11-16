#ifndef SETTINGPARAMETERFORM_H
#define SETTINGPARAMETERFORM_H

#include <QDialog>
#include "WEditParameterTab.h"

class	XMLExplorer;

namespace Ui {
    class SettingParameterForm;
}

class SettingParameterForm : public QDialog
{
    Q_OBJECT

	XMLExplorer			*Handle;
	WEditParameterTab	*WTabGeneral;

public:
    explicit SettingParameterForm(XMLExplorer *SHandle, QWidget *parent = 0);
    ~SettingParameterForm();

private slots:
    void on_pushButtonOk_clicked();

private:
    Ui::SettingParameterForm *ui;

	virtual	void	showEvent (QShowEvent * event)	override;
};

#endif // SETTINGPARAMETERFORM_H
