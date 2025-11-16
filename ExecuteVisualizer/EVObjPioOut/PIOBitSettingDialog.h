#ifndef PIOBITSETTINGDIALOG_H
#define PIOBITSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
    class PIOBitSettingDialog;
}

class	RunnerPIOOut;

class PIOBitSettingDialog : public QDialog
{
    Q_OBJECT

	RunnerPIOOut		*Obj;
public:
    explicit PIOBitSettingDialog(RunnerPIOOut *obj, QWidget *parent = 0);
    ~PIOBitSettingDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

    void on_spinBoxBoardNumber_valueChanged(int arg1);

private:
    Ui::PIOBitSettingDialog *ui;
};

#endif // PIOBITSETTINGDIALOG_H
