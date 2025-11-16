#ifndef SETTINGFILTERHORIZONTALBAND_H
#define SETTINGFILTERHORIZONTALBAND_H

#include <QDialog>
#include "XBoolList.h"
#include "XServiceForLayers.h"

namespace Ui {
class SettingFilterHorizontalBand;
}

class SettingFilterHorizontalBand : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SettingFilterHorizontalBand(LayersBase *base
										,double	Gain
										,int CenterX
										,int BandWidth
										,int GradationWidth
										,BoolList &_Layers
										,double	Gamma
										,QWidget *parent = 0);
    ~SettingFilterHorizontalBand();

	BoolList	Layers;
	double	Gain;
	int		CenterX;
	int		BandWidth;
	int		GradationWidth;
	double	Gamma;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingFilterHorizontalBand *ui;
};

#endif // SETTINGFILTERHORIZONTALBAND_H
