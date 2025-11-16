#ifndef COMMDIALOGFORM_H
#define COMMDIALOGFORM_H

#include <QDialog>
#include"XDataInExe.h"
#include "XServiceForLayers.h"
#include "FormCommSetting.h"

namespace Ui {
class CommDialogForm;
}

class CommDialogForm : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    FormCommSetting	FormComm;
public:
    explicit CommDialogForm(LayersBase *Base ,QWidget *parent = 0);
    ~CommDialogForm();
    
private slots:
    void on_pushButtonFileName_clicked();
    void on_pushButtonLoad_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonSaveNew_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::CommDialogForm *ui;
};

#endif // COMMDIALOGFORM_H
