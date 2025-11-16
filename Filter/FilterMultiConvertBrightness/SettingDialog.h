#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	double	StrengthL;
	double	WidthL;
	double	InclineL;
	double	AddVL;
	double	AddBL;

	double	StrengthR;
	double	WidthR;
	double	InclineR;
	double	AddVR;
	double	AddBR;

	explicit SettingDialog(LayersBase *base, QWidget *parent = 0);
    ~SettingDialog();


	void    Init(double	_StrengthL
				,double	_WidthL
				,double	_InclineL
				,double	_AddVL
				,double	_AddBL

				,double	_StrengthR
				,double	_WidthR
				,double	_InclineR
				,double	_AddVR
				,double	_AddBR);

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
