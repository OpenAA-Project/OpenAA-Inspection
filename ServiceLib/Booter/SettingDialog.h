#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XBooter.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingDialog(BooterParameter &param ,QWidget *parent = 0);
    ~SettingDialog();

    BooterParameter		BooterData;

private slots:
    void on_pushButtonAddIPAddress_clicked();
    void on_pushButtonDelIPAddress_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_tableWidgetBeforeBooter_doubleClicked(const QModelIndex &index);
    void on_tableWidgetAfterBooter_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddProgBefore_clicked();
    void on_pushButtonDelProgBefore_clicked();
    void on_pushButtonAddProgAfter_clicked();
    void on_pushButtonDelProgAfter_clicked();

private:
    Ui::SettingDialog *ui;

	void	ShowBeforeList(void);
	void	ShowAfterList(void);
};

#endif // SETTINGDIALOG_H
