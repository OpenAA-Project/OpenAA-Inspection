#ifndef EACHTHRESHOLDFORMVARIABLE_H
#define EACHTHRESHOLDFORMVARIABLE_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XEachThresholdCommon.h"
#include "XPasswordQWidget.h"

namespace Ui {
class EachThresholdFormVariable;
}
class ButtonSettingThresholdForm;

class EachThresholdFormVariable: public EachThresholdCommon
                                ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	double BHL ,BHH ,BSL ,BSH ,BVL ,BVH;
    double NHL ,NHH ,NSL ,NSH ,NVL ,NVH;
	bool	OnChanging;
public:
    explicit EachThresholdFormVariable(LayersBase *base ,ButtonSettingThresholdForm *p
										,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
										,QWidget *parent = 0);
    ~EachThresholdFormVariable();

private slots:
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

    void on_PushButtonMarker_clicked();
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();
    void on_PushButtonShowWhole_clicked();
    void on_toolButtonRegOK_clicked();
    void on_toolButtonRegNG_clicked();
    void on_toolButtonOKSize_clicked();
    void on_toolButtonBrightnessDarkStrict_clicked();
    void on_toolButtonBrightnessDarkStrictLoose_clicked();
    void on_toolButtonBrightnessLightStrict_clicked();
    void on_toolButtonBrightnessLightLoose_clicked();
    void on_toolButtonShiftStrict_clicked();
    void on_toolButtonShiftLoose_clicked();
    void on_spinBoxBrightnessDark_valueChanged(int arg1);
    void on_spinBoxBrightnessLight_valueChanged(int arg1);
    void on_spinBoxShift_valueChanged(int arg1);

    void on_toolButtonBroad_clicked();
    void on_toolButtonNarrow_clicked();

private:
    Ui::EachThresholdFormVariable *ui;

	virtual	void	MouseLDoubleClick(int gx,int gy,int LevelID) override;
	void	ShowDataAfterMarker(void);
	void	SetRGBRangeB(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH);
    void	SetRGBRangeN(int dhL ,int dhH ,int dsL ,int dsH ,int dvL, int dvH);
	void	FindRGBLowB (int R,int G, int B);
	void	FindRGBHighB(int R,int G, int B);
	void	FindRGBLowN (int R,int G, int B);
	void	FindRGBHighN(int R,int G, int B);

    void    FindRGBLowInside(DotColorMatchingThreshold::MThreshold *MThr,int R,int G, int B);
    void    FindRGBHighInside(DotColorMatchingThreshold::MThreshold *MThr,int R,int G, int B);

};

#endif // EACHTHRESHOLDFORMVARIABLE_H
