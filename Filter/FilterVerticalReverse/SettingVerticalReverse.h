#ifndef SETTINGVERTICALREVERSE_H
#define SETTINGVERTICALREVERSE_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingVerticalReverse;
}

class SettingVerticalReverse : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingVerticalReverse(LayersBase *base
									,double _Strength ,double _Width
									,  bool	_TopSide   ,bool _BottomSide
									,BoolList &_Layers
									,double	Gamma
									,QWidget *parent = 0);
    ~SettingVerticalReverse();

	BoolList	Layers;
	double Strength ,Width;
	bool	TopSide;
	bool	BottomSide;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingVerticalReverse *ui;
};

#endif // SETTINGVERTICALREVERSE_H
