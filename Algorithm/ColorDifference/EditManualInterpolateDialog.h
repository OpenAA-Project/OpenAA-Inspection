#ifndef EDITMANUALINTERPOLATEDIALOG_H
#define EDITMANUALINTERPOLATEDIALOG_H

#include <QDialog>

namespace Ui {
class EditManualInterpolateDialog;
}

class EditManualInterpolateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditManualInterpolateDialog(QWidget *parent = nullptr);
    ~EditManualInterpolateDialog();

private slots:
    void on_pushButtonDeleteLine_clicked();
    void on_pushButtonClose_clicked();

    void on_pushButtonAdd_clicked();

private:
    Ui::EditManualInterpolateDialog *ui;
};

#endif // EDITMANUALINTERPOLATEDIALOG_H
