#ifndef PROHIBITEITEMDIALOG_H
#define PROHIBITEITEMDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class ProhibiteItemDialog;
}

class SelectLibForValidationForm;
class CheckDataValidationProhibiteItemThreshold;

class ProhibiteItemDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    SelectLibForValidationForm  *SelectLibPanel;

public:
    explicit ProhibiteItemDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~ProhibiteItemDialog();

    int SelectedLibType ;
    int SelectedLibID   ;

    void    SetCurrentItem(const CheckDataValidationProhibiteItemThreshold *RThr);
    void    GetCurrentItem(CheckDataValidationProhibiteItemThreshold *WThr);
private slots:
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonModify_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();

    void    SlotSelectedLib(int LibType,int LibID);
private:
    Ui::ProhibiteItemDialog *ui;
};

#endif // PROHIBITEITEMDIALOG_H
