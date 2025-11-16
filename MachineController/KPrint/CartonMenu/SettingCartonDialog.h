#ifndef SETTINGCARTONDIALOG_H
#define SETTINGCARTONDIALOG_H

#include <QDialog>
#include "WEditParameterTab.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingCartonDialog;
}
class CartonMenuForm;

class SettingCartonDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
	WEditParameterTab	*WTabGeneral;
	CartonMenuForm	*Parent;
public:
    explicit SettingCartonDialog(LayersBase *Base ,CartonMenuForm *PForm,QWidget *parent = 0);
    ~SettingCartonDialog();
    
    void	AdjustTrigger(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonTrigger_clicked();
    void on_pushButtonUsageLibrary_clicked();

private:
    Ui::SettingCartonDialog *ui;
};

#endif // SETTINGCARTONDIALOG_H
