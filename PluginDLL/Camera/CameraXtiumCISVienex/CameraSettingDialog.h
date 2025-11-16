#ifndef CAMERASETTINGDIALOG_H
#define CAMERASETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class CameraSettingDialog;
}
class CameraXtiumCISVienex;

class CameraSettingDialog : public QDialog
{
    Q_OBJECT

    CameraXtiumCISVienex *V;
public:
    explicit CameraSettingDialog(CameraXtiumCISVienex *index ,QWidget *parent = nullptr);
    ~CameraSettingDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_pushButtonLoadFromCamera_clicked();

private:
    Ui::CameraSettingDialog *ui;

    void ShowDataToWindow(void);
};

#endif // CAMERASETTINGDIALOG_H
