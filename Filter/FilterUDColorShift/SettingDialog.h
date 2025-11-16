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
	int		ShiftR;
	int		ShiftG;
	int		ShiftB;
	bool	CheckTime;
	int		TimeRange;
	int		ShiftOffset;

    explicit SettingDialog(LayersBase *base,QWidget *parent = 0);
    ~SettingDialog();
    
	void	Initial(int	_ShiftR ,int _ShiftG ,int _ShiftB
					,bool _CheckTime ,int _TimeRange
					,int _ShiftOffset);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
