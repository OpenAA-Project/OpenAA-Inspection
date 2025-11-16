#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingDialog(LayersBase *base,double	_Gain
										,int _Length
										,BoolList &_Layers
										,bool	_Vertical
										,bool	_BPF
										,int	_PassWidth
										,QWidget *parent = 0);
    ~SettingDialog();

	BoolList	Layers;
	double	Gain;
	int		Length;
	bool	Vertical;
	bool	BPF;
	int		PassWidth;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
