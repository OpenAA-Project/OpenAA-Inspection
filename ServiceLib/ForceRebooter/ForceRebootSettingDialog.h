#ifndef FORCEREBOOTSETTINGDIALOG_H
#define FORCEREBOOTSETTINGDIALOG_H

#include <QDialog>
#include "XForceRebooter.h"

namespace Ui {
class ForceRebootSettingDialog;
}

class ForceRebootSettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ForceRebootSettingDialog(RebooterParam *param ,QWidget *parent = 0);
    ~ForceRebootSettingDialog();

	RebooterParam	Param;

private slots:
    void on_pushButtonAddPartner_clicked();
    void on_pushButtonDelPartner_clicked();
    void on_pushButtonAddProgram_clicked();
    void on_pushButtonDelProgram_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::ForceRebootSettingDialog *ui;

	void ShowPartnerList(void);
	void ShowPromramList(void);
};

#endif // FORCEREBOOTSETTINGDIALOG_H
