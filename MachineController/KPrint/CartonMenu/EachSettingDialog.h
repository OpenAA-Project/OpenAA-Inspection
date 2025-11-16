#ifndef EACHSETTINGDIALOG_H
#define EACHSETTINGDIALOG_H

#include <QDialog>
#include <QTimer>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

namespace Ui {
class EachSettingDialog;
}
class	CartonMenuForm;

class EachSettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
	friend	class CartonMenuForm;

    CartonMenuForm	*Parent;
	QTimer		TM;

public:
    explicit EachSettingDialog(LayersBase *Base ,CartonMenuForm *p,QWidget *parent = 0);
    ~EachSettingDialog();
    
private slots:
    void on_PushButtonSwitchPhase_clicked();
    void on_PushButtonMask_clicked();
    void on_PushButtonAlignment_clicked();
    void on_PushButtonInspection_clicked();
    void on_PushButtonBlade_clicked();
    void on_PushButtonAutoGenerate_clicked();
    void on_PushButtonSettingThresholdTop_clicked();
    void on_PushButtonBladeSettingThresholdBottom_clicked();
    void on_PushButtonClose_clicked();
	void	SlotInspectionDone(int SlaveNo,int64 InspectionID ,bool OK);
	void	SlotTimeOut();
    void on_PushButtonColorDifference_clicked();
    void on_PushButtonMakeAverageImage_clicked();
    void on_PushButtonSettingExpose_clicked();
    void on_PushButtonBCode_clicked();
    void on_PushButtonMeasure_clicked();
    void on_PushButtonSettingThresholdMono_clicked();
    void on_PushButtonCalcFinalize_clicked();

    void on_PushButtonResetSlaves_clicked();

private:
    Ui::EachSettingDialog *ui;

	void	SetRunningGray(void);
};

#endif // EACHSETTINGDIALOG_H
