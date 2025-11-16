#ifndef SETTINGMEASUREDIALOG_H
#define SETTINGMEASUREDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingMeasureDialog;
}

class	HookMeasureForm;

class SettingMeasureDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	HookMeasureForm	*Parent;
public:
    explicit SettingMeasureDialog(LayersBase *Base ,HookMeasureForm *P, QWidget *parent = 0);
    ~SettingMeasureDialog();

private slots:
    void on_toolButtonLineColor_clicked();
    void on_toolButtonCircleColor_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingMeasureDialog *ui;
};

#endif // SETTINGMEASUREDIALOG_H
