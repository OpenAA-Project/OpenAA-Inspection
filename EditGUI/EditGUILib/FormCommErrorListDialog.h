#ifndef FORMCOMMERRORLISTDIALOG_H
#define FORMCOMMERRORLISTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class FormCommErrorListDialog;
}

class FormCommErrorListDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit FormCommErrorListDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~FormCommErrorListDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonSave_clicked();

private:
    Ui::FormCommErrorListDialog *ui;
    void    ShowList(void);
};

#endif // FORMCOMMERRORLISTDIALOG_H
