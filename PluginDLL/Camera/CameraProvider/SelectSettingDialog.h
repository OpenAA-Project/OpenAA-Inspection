#ifndef SELECTSETTINGDIALOG_H
#define SELECTSETTINGDIALOG_H

#include <QDialog>
#include "CameraProvider.h"


namespace Ui {
class SelectSettingDialog;
}

class SelectSettingDialog : public QDialog
{
    Q_OBJECT

	CameraProvider	*ParentMain;
	int				Number;
public:
    explicit SelectSettingDialog(CameraProvider *ParentMain,int number ,QWidget *parent = 0);
    ~SelectSettingDialog();

private slots:
    void on_pushButtonSetting_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectSettingDialog *ui;
};

#endif // SELECTSETTINGDIALOG_H
