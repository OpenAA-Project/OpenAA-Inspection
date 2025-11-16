#ifndef SETTINGVERTICALLINEAR_H
#define SETTINGVERTICALLINEAR_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingVerticalLinear;
}

class SettingVerticalLinear : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingVerticalLinear(LayersBase *base
										,double _Strength 
										, bool _WholeImage
										, bool	_TopSide   ,bool _BottomSide
										,BoolList &_Layers
										,double	Gamma
										, QWidget *parent = 0);
    ~SettingVerticalLinear();

	BoolList	Layers;
	double	Strength;
	bool	WholeImage;
	bool	TopSide;
	bool	BottomSide;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingVerticalLinear *ui;
};

#endif // SETTINGVERTICALLINEAR_H
