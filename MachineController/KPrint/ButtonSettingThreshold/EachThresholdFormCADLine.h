#ifndef EACHTHRESHOLDFORMCADLINE_H
#define EACHTHRESHOLDFORMCADLINE_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "mtPushButtonColored.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XPanelShowResultImage.h"
#include "XEachThresholdCommon.h"
#include "XIntegrationPacketComm.h"
#include "XDXFOperationCommon.h"
#include "XPasswordQWidget.h"

namespace Ui {
class EachThresholdFormCADLine;
}

class	ButtonSettingThresholdForm;
class	DXFOperationBase;
class	DotColorMatchingBase;
class	CartonMenuForm;

class EachThresholdFormCADLine : public EachThresholdCommon
                                ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	CartonMenuForm	*CartonMenuProp;
	double BHL ,BHH ,BSL ,BSH ,BVL ,BVH;
    double NHL ,NHH ,NSL ,NSH ,NVL ,NVH;

	AlgorithmLibraryListContainer	LibList;
	bool	OnChanging;
public:
    explicit EachThresholdFormCADLine(LayersBase *base ,ButtonSettingThresholdForm *p,QWidget *parent = 0);
    ~EachThresholdFormCADLine();
    
private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_horizontalSliderBCL_valueChanged(int value);
    void on_horizontalSliderBCH_valueChanged(int value);
    void on_horizontalSliderBML_valueChanged(int value);
    void on_horizontalSliderBMH_valueChanged(int value);
    void on_horizontalSliderBYL_valueChanged(int value);
    void on_horizontalSliderBYH_valueChanged(int value);
    void on_spinBoxBCL_valueChanged(int arg1);
    void on_spinBoxBCH_valueChanged(int arg1);
    void on_spinBoxBML_valueChanged(int arg1);
    void on_spinBoxBMH_valueChanged(int arg1);
    void on_spinBoxBYL_valueChanged(int arg1);
    void on_spinBoxBYH_valueChanged(int arg1);
    void on_horizontalSliderSizeB_valueChanged(int value);
    void on_doubleSpinBoxSizeBMM_valueChanged(double arg1);
    void on_spinBoxSizeB_valueChanged(int arg1);
    void on_horizontalSliderLengthB_valueChanged(int value);
    void on_doubleSpinBoxLengthBMM_valueChanged(double arg1);
    void on_spinBoxLengthB_valueChanged(int arg1);

    void on_horizontalSliderNCL_valueChanged(int value);
    void on_horizontalSliderNCH_valueChanged(int value);
    void on_horizontalSliderNML_valueChanged(int value);
    void on_horizontalSliderNMH_valueChanged(int value);
    void on_horizontalSliderNYL_valueChanged(int value);
    void on_horizontalSliderNYH_valueChanged(int value);
    void on_spinBoxNCL_valueChanged(int arg1);
    void on_spinBoxNCH_valueChanged(int arg1);
    void on_spinBoxNML_valueChanged(int arg1);
    void on_spinBoxNMH_valueChanged(int arg1);
    void on_spinBoxNYL_valueChanged(int arg1);
    void on_spinBoxNYH_valueChanged(int arg1);
    void on_horizontalSliderSizeN_valueChanged(int value);
    void on_doubleSpinBoxSizeNMM_valueChanged(double arg1);
    void on_spinBoxSizeN_valueChanged(int arg1);
    void on_horizontalSliderLengthN_valueChanged(int value);
    void on_doubleSpinBoxLengthNMM_valueChanged(double arg1);
    void on_spinBoxLengthN_valueChanged(int arg1);

    void on_toolButtonOK_clicked();
    void on_toolButtonOKSize_clicked();
    void on_toolButtonCancel_clicked();

    void on_toolButtonBroad_clicked();
    void on_toolButtonNarrow_triggered(QAction *arg1);

private:
    Ui::EachThresholdFormCADLine *ui;

	DXFOperationBase		*GetDXFOperationBase(void);
	DotColorMatchingBase	*GetDotColorMatchingBase(void);
	void	ShowAllocation(void);
	void	ShowSelectedLibList(void);
	void	ShowDataAfterMarker(void);
	void	FindRGBLowB(int R,int G, int B);
	void	FindRGBLowN(int R,int G, int B);
	void	FindRGBHighB(int R,int G, int B);
	void	FindRGBHighN(int R,int G, int B);
	void	SetRGBRangeB(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH);
	void	SetRGBRangeN(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH);

    void FindRGBLowInside(DotColorMatchingThreshold::MThreshold *MThr ,int R,int G, int B);
    void FindRGBHighInside(DotColorMatchingThreshold::MThreshold *MThr ,int R,int G, int B);
    GUIFormBase			*DxfForm;
};

class	ColorButtonInList : public mtPushButtonColored
{
    Q_OBJECT

public:
	int	Row;
	ColorButtonInList(int row ,QWidget *parent = 0);

signals:
	void	SignalClicked(int row);
private slots:
	void	SlotClicked();
};

#endif // EACHTHRESHOLDFORMCADLINE_H
