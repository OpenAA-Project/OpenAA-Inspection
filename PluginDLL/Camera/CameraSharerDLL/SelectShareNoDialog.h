#ifndef SELECTSHARENODIALOG_H
#define SELECTSHARENODIALOG_H

#include <QDialog>

namespace Ui {
class SelectShareNoDialog;
}

class SelectShareNoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectShareNoDialog(int ShareNo,QWidget *parent = 0);
    ~SelectShareNoDialog();

	int	ShareNo;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectShareNoDialog *ui;
};

#endif // SELECTSHARENODIALOG_H
