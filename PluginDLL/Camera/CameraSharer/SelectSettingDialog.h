#ifndef SELECTSETTINGDIALOG_H
#define SELECTSETTINGDIALOG_H

#include <QDialog>
#include "CameraSharer.h"


namespace Ui {
class SelectSettingDialog;
}

class SelectSettingDialog : public QDialog
{
    Q_OBJECT

	CameraSharer	*ParentMain;
	int				Number;
public:
    explicit SelectSettingDialog(CameraSharer *ParentMain,int number ,QWidget *parent = 0);
    ~SelectSettingDialog();

private slots:
    void on_pushButtonSetting_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectSettingDialog *ui;
};

#endif // SELECTSETTINGDIALOG_H
