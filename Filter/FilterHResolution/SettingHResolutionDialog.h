#ifndef SETTINGHRESOLUTIONDIALOG_H
#define SETTINGHRESOLUTIONDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingHResolutionDialog;
}

class SettingHResolutionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingHResolutionDialog(LayersBase *base,double rate ,QWidget *parent = 0);
    ~SettingHResolutionDialog();

	double	Rate;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingHResolutionDialog *ui;
};

#endif // SETTINGHRESOLUTIONDIALOG_H
