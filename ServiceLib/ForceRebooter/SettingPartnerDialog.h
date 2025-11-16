#ifndef SETTINGPARTNERDIALOG_H
#define SETTINGPARTNERDIALOG_H

#include <QDialog>
#include "XForceRebooter.h"

namespace Ui {
class SettingPartnerDialog;
}

class SettingPartnerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingPartnerDialog(QWidget *parent = 0);
    ~SettingPartnerDialog();
    
	PartnerInfo	Info;
	void	Init(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingPartnerDialog *ui;
};

#endif // SETTINGPARTNERDIALOG_H
