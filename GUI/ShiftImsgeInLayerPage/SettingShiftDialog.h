#ifndef SETTINGSHIFTDIALOG_H
#define SETTINGSHIFTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SettingShiftDialog;
}

class SettingShiftDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    IntList SelectedPhase;
    IntList SelectedPage;
    IntList SelectedLayers;
    bool    ShiftMaster;
    bool    ShiftTarget;
    int     ShiftDx;
    int     ShiftDy;

    explicit SettingShiftDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SettingShiftDialog();
    
private slots:
    void on_pushButtonExecuteShift_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingShiftDialog *ui;
};

#endif // SETTINGSHIFTDIALOG_H
