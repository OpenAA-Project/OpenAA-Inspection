#ifndef EDITDENSEINTERPOLATEDIALOG_H
#define EDITDENSEINTERPOLATEDIALOG_H

#include <QDialog>

namespace Ui {
class EditDenseInterpolateDialog;
}

class EditDenseInterpolateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDenseInterpolateDialog(QWidget *parent = nullptr);
    ~EditDenseInterpolateDialog();

private slots:
    void on_pushButtonAddDense_clicked();

    void on_pushButtonDeleteLine_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::EditDenseInterpolateDialog *ui;
};

#endif // EDITDENSEINTERPOLATEDIALOG_H
