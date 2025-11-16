#ifndef EDITOPERATIONDIALOG_H
#define EDITOPERATIONDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class EditOperationDialog;
}

class EditOperationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditOperationDialog(QWidget *parent = nullptr);
    ~EditOperationDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditOperationDialog *ui;
};

#endif // EDITOPERATIONDIALOG_H
