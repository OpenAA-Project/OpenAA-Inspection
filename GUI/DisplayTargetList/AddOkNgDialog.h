#ifndef ADDOKNGDIALOG_H
#define ADDOKNGDIALOG_H

#include <QDialog>

namespace Ui {
class AddOkNgDialog;
}

class AddOkNgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddOkNgDialog(QWidget *parent = nullptr);
    ~AddOkNgDialog();

    int Ret;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonNG_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::AddOkNgDialog *ui;
};

#endif // ADDOKNGDIALOG_H
