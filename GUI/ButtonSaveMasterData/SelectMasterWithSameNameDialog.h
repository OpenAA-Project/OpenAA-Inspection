#ifndef SELECTMASTERWITHSAMENAMEDIALOG_H
#define SELECTMASTERWITHSAMENAMEDIALOG_H

#include <QDialog>
#include "XIntClass.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectMasterWithSameNameDialog;
}

class SelectMasterWithSameNameDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    IntList MasterCodes;
public:
    explicit SelectMasterWithSameNameDialog(IntList &MasterCodes ,LayersBase *Base ,QWidget *parent = nullptr);
    ~SelectMasterWithSameNameDialog();

    int SelectedMasterCode;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectMasterWithSameNameDialog *ui;
};

#endif // SELECTMASTERWITHSAMENAMEDIALOG_H
