#ifndef SELECTMASTERNODIALOG_H
#define SELECTMASTERNODIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XIntClass.h"
namespace Ui {
class SelectMasterNoDialog;
}

class SelectMasterNoDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    IntList     LibTypeList;
public:
    explicit SelectMasterNoDialog(LayersBase *Base,int OriginCode ,QWidget *parent = nullptr);
    ~SelectMasterNoDialog();

    int MasterNoOriginCode;

private slots:
    void on_groupBoxMasterNo_clicked();
    void on_groupBoxAlgorithm_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectMasterNoDialog *ui;
};

#endif // SELECTMASTERNODIALOG_H
