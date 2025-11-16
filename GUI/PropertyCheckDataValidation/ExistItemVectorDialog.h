#ifndef EXISTITEMVECTORDIALOG_H
#define EXISTITEMVECTORDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ExistItemVectorDialog;
}

class SelectLibForValidationForm;
class CheckDataValidationExistItemVectorThreshold;

class ExistItemVectorDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SelectLibForValidationForm  *SelectLibPanel;
public:
    explicit ExistItemVectorDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~ExistItemVectorDialog();

    int SelectedLibType ;
    int SelectedLibID   ;

    void    SetCurrentItem(const CheckDataValidationExistItemVectorThreshold *RThr);
    void    GetCurrentItem(CheckDataValidationExistItemVectorThreshold *WThr);

private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

    void    SlotSelectedLib(int LibType,int LibID);
private:
    Ui::ExistItemVectorDialog *ui;
};

#endif // EXISTITEMVECTORDIALOG_H
