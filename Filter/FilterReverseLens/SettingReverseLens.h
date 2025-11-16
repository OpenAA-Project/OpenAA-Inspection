#ifndef SETTINGREVERSELENS_H
#define SETTINGREVERSELENS_H

#include <QDialog>
#include "ui_SettingReverseLens.h"
#include "XServiceForLayers.h"

class SettingReverseLens : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	SettingReverseLens(LayersBase *base
						,double _Strength ,double _Width
						,int32 StartX,int32 EndX
						, QWidget *parent = 0);
	~SettingReverseLens();

	double Strength ,Width;
	int32	StartX;
	int32	EndX;
private:
	Ui::SettingReverseLensClass ui;

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonOK_clicked();
};

#endif // SETTINGREVERSELENS_H
