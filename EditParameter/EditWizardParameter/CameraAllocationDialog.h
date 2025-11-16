#ifndef CAMERAALLOCATIONDIALOG_H
#define CAMERAALLOCATIONDIALOG_H

#include <QDialog>

namespace Ui {
class CameraAllocationDialog;
}

class CameraAllocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CameraAllocationDialog(QWidget *parent = 0);
    ~CameraAllocationDialog();

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::CameraAllocationDialog *ui;
};

#endif // CAMERAALLOCATIONDIALOG_H
