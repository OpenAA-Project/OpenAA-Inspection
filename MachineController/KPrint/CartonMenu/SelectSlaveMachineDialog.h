#ifndef SELECTSLAVEMACHINEDIALOG_H
#define SELECTSLAVEMACHINEDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include "XIntClass.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectSlaveMachineDialog;
}

class SelectSlaveMachineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    QCheckBox   *CBoxDim[100];
    QCheckBox   *CBoxDimRGen[100];
    QCheckBox   *CBoxDimKeepMark[100];
public:
    explicit SelectSlaveMachineDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~SelectSlaveMachineDialog();

    bool    ResetSwitchPhase;
    bool    ResetMakeAverage;
    IntList SelectedSlaveNoList;
    IntList ReGenList;
    IntList KeepMarkList;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectSlaveMachineDialog *ui;
};

#endif // SELECTSLAVEMACHINEDIALOG_H
