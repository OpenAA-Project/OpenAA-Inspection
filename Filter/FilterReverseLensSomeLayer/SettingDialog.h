#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XServiceForLayers.h"
namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SettingDialog( LayersBase *base
							,bool _Layer0, bool _Layer1, bool _Layer2
							, double _Strength ,double _Width
							,  bool	_LeftSide   ,bool _RightSide
							, QWidget *parent);
    ~SettingDialog();

	bool	Layer0;
	bool	Layer1;
	bool	Layer2;
	double Strength ,Width;
	bool	LeftSide;
	bool	RightSide;
    
private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonTest_clicked();

private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
