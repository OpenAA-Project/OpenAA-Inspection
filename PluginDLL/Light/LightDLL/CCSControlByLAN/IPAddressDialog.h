#ifndef IPADDRESSDIALOG_H
#define IPADDRESSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class IPAddressDialog;
}

class	CCSControlByLAN;
class	SettingDialog;

class IPAddressDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	SettingDialog	*SettingD;
public:
    explicit IPAddressDialog(SettingDialog *d ,LayersBase *base ,QWidget *parent = 0);
    ~IPAddressDialog();

private slots:
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::IPAddressDialog *ui;
};

#endif // IPADDRESSDIALOG_H
