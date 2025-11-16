#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "FilterReplaceColor.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	FilterReplaceColor	*Parent;

public:
    explicit SettingDialog(LayersBase *base,FilterReplaceColor *filterparent,QWidget *parent=0);
    ~SettingDialog();

private slots:
    void on_toolButtonReplaceBrightness_clicked();
    void on_toolButtonShiftBrightness_clicked();
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

	void ChangeStack(void);
};

#endif // SETTINGDIALOG_H
