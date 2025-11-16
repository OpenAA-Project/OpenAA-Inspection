#ifndef SETTINGFILTERHORIZONTALLINEAR_H
#define SETTINGFILTERHORIZONTALLINEAR_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingFilterHorizontalLinear;
}

class SettingFilterHorizontalLinear : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingFilterHorizontalLinear(LayersBase *base
										,double _Strength 
										, bool WholeImage
										, bool	_LeftSide   ,bool _RightSide
										,BoolList &_Layers
										,double	Gamma
										, QWidget *parent = 0);
    ~SettingFilterHorizontalLinear();

	BoolList	Layers;
	double	Strength;
	bool	WholeImage;
	bool	LeftSide;
	bool	RightSide;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_checkBoxWholeImage_clicked();

private:
    Ui::SettingFilterHorizontalLinear *ui;
};

#endif // SETTINGFILTERHORIZONTALLINEAR_H
