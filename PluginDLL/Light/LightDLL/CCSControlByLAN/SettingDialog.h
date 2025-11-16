#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class	CCSControlByLAN;
class	CCSControlByLANParam;

class SettingDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

	CCSControlByLAN		*Panel;
	int					CurrentChannel;
public:
	CCSControlByLANParam	*Data;

	explicit SettingDialog(CCSControlByLAN *p ,LayersBase *base ,QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_comboBoxChannel_currentIndexChanged(int index);
    void on_horizontalSliderPower_valueChanged(int value);
    void on_spinBoxPower_valueChanged(int arg1);
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonIPAddress_clicked();

private:
    Ui::SettingDialog *ui;

	void	LoadFromWindow(int currentChannel);
	void	SetToWindow(int NewChannel);
};

#endif // SETTINGDIALOG_H
