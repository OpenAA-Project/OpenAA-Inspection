#ifndef SHAREMASTERADDDESTINATIONDIALOG_H
#define SHAREMASTERADDDESTINATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ShareMasterAddDestinationDialog;
}

class ShareMasterAddDestinationDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShareMasterAddDestinationDialog(QWidget *parent = 0);
    ~ShareMasterAddDestinationDialog();
    
private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::ShareMasterAddDestinationDialog *ui;
};

#endif // SHAREMASTERADDDESTINATIONDIALOG_H
