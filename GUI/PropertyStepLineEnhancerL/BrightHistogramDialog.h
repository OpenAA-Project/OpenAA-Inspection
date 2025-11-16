#ifndef BRIGHTHISTOGRAMDIALOG_H
#define BRIGHTHISTOGRAMDIALOG_H

#include <QDialog>

namespace Ui {
class BrightHistogramDialog;
}

class BrightHistogramDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BrightHistogramDialog(QWidget *parent = 0);
    ~BrightHistogramDialog();

private slots:
    void on_ButtonReflect_clicked();

    void on_EditPickupL_valueChanged(int arg1);

    void on_EditPickupH_valueChanged(int arg1);

    void on_ButtonClose_clicked();

private:
    Ui::BrightHistogramDialog *ui;
};

#endif // BRIGHTHISTOGRAMDIALOG_H
