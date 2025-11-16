#ifndef SELECTMACHINEDIALOG_H
#define SELECTMACHINEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XIntClass.h"

namespace Ui {
class SelectMachineDialog;
}
class	LayersBase;

class SelectMachineDialog : public QDialog
{
    Q_OBJECT
    LayersBase *Base;
public:
    explicit SelectMachineDialog(LayersBase *base ,const IntList &machineList
                                 ,QWidget *parent = 0);
    ~SelectMachineDialog();
    
    IntList MachineList;
    int		SelectedMachineID;
private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectMachineDialog *ui;
};

#endif // SELECTMACHINEDIALOG_H
