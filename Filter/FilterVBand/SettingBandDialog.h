#ifndef SETTINGBANDDIALOG_H
#define SETTINGBANDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingBandDialog;
}

class SettingBandDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingBandDialog(LayersBase *base,int x1 ,int x2 ,double multipleRate ,int offset ,QWidget *parent = 0);
    ~SettingBandDialog();

	double	MultipleRate;
	int		Offset;
	int		X1,X2;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingBandDialog *ui;
};

#endif // SETTINGBANDDIALOG_H
