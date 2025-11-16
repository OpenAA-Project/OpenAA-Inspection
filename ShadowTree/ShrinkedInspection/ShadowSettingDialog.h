#ifndef SHADOWSETTINGDIALOG_H
#define SHADOWSETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class ShadowSettingDialog;
}

class ShrinkedInspection;


class ShadowSettingDialog : public QDialog
{
    Q_OBJECT
    
	ShrinkedInspection	*Handle;
public:
    explicit ShadowSettingDialog(ShrinkedInspection *Handle,QWidget *parent = 0);
    ~ShadowSettingDialog();
    
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ShadowSettingDialog *ui;
};

#endif // SHADOWSETTINGDIALOG_H
