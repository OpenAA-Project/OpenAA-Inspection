#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "mtLineGraph.h"
#include "mtGraph.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	mtLineGraph		LGraph;
	mtGStick		GraphBrightness;
public:
	double ThresholdBrightness;
	double ThresholdWidth;

    explicit SettingDialog(double _ThresholdBrightness ,double _ThresholdWidth ,LayersBase *base,QWidget *parent = 0);
    ~SettingDialog();

private slots:
    void on_doubleSpinBoxThresholdBrightness_valueChanged(double arg1);
    void on_doubleSpinBoxThresholdWidth_valueChanged(double arg1);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

	void	ShowGraph(void);
};

#endif // SETTINGDIALOG_H
