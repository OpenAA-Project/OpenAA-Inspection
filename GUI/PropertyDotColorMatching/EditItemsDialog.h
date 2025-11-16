#ifndef EDITITEMSDIALOG_H
#define EDITITEMSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class EditItemsDialog;
}

class EditItemsDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditItemsDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~EditItemsDialog();

    void    SetItemInfo(int MasterNoOriginCode
                        ,AlgorithmLibraryListContainer &SubLibBlock
                        ,int ExpandToSubBlock);

    bool    AvailableMasterNo;
    int     MasterNoOriginCode;

    bool    AvailableSubBlock;
    AlgorithmLibraryListContainer	SubBlockList;
    int 	ExpandToSubBlock;

private slots:
    void on_pushButtonMasterNo_clicked();
    void on_pushButtonSubtractLibID_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditItemsDialog *ui;
};

#endif // EDITITEMSDIALOG_H
