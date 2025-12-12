#ifndef ACTIVATIONDIALOG_H
#define ACTIVATIONDIALOG_H

#include <QDialog>

namespace Ui {
class ActivationDialog;
}

class   TypeDefinition;

class ActivationDialog : public QDialog
{
    Q_OBJECT
    TypeDefinition  *Parent;

public:
    explicit ActivationDialog(TypeDefinition *p,QWidget *parent = 0);
    ~ActivationDialog();
    
private slots:
    void on_checkBoxOrderCode_clicked();
    void on_checkBoxLicenseFile_clicked();
    void on_checkBoxActivationCode_clicked();
    void on_pushButtonActivateByOrderCode_clicked();
    void on_pushButtonSelectLicenseFiile_clicked();
    void on_pushButtonActivateByLicenseFile_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonLoadLicenseFiile_clicked();
    void on_pushButtonWriteReqActivationFile_clicked();
    void on_pushButtonLoadActivationFile_clicked();

private:
    Ui::ActivationDialog *ui;

    void    SetFrame(void);
    void    ShowResult(void);
};

#endif // ACTIVATIONDIALOG_H
