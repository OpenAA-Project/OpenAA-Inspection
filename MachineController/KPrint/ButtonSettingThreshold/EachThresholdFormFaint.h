#ifndef EACHTHRESHOLDFORMFaint_H
#define EACHTHRESHOLDFORMFaint_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XPanelShowResultImage.h"
#include <QImage>
#include "XEachThresholdCommon.h"
#include "XPasswordQWidget.h"
#include <QTimer>

namespace Ui {
class EachThresholdFormFaint;
}
class ButtonSettingThresholdForm;
class EachThresholdFormFaint;

class	HSVMap : public QWidget
{
    Q_OBJECT
		
	EachThresholdFormFaint	*Parent;
	double	ZoomRate;
	QImage	HSVImageMap;
	QTimer	TM;
	bool	FlapToShowThreshold;
public:
	int	V;

	HSVMap(EachThresholdFormFaint *p);

	void	SetV(int v);
private:
	virtual	void paintEvent ( QPaintEvent * event ) 		override;
	virtual	void mouseReleaseEvent ( QMouseEvent * event )	override;
	virtual	void resizeEvent ( QResizeEvent * event )		override;

signals:
	void	SignalClickRGB(int R ,int G ,int B);

private slots:
	void	SlotTimeOut();
};



class EachThresholdFormFaint : public EachThresholdCommon
                              ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	HSVMap					PanelHSVMap;
	bool	OnChanging;
public:
    explicit EachThresholdFormFaint(LayersBase *base ,ButtonSettingThresholdForm *p
									,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
									,QWidget *parent = 0);
    ~EachThresholdFormFaint();
    
	bool	IsInsideInThresholdB(int r ,int g ,int b);

private slots:
    void on_horizontalSliderSizeB_valueChanged(int value);
    void on_doubleSpinBoxSizeBMM_valueChanged(double arg1);
    void on_spinBoxSizeB_valueChanged(int arg1);
	void on_horizontalSliderLengthB_valueChanged(int value);
	void on_doubleSpinBoxLengthBMM_valueChanged(double arg1);
	void on_spinBoxLengthB_valueChanged(int arg1);

    void on_horizontalSliderSizeN_valueChanged(int value);
    void on_doubleSpinBoxSizeNMM_valueChanged(double arg1);
    void on_spinBoxSizeN_valueChanged(int arg1);
	void on_horizontalSliderLengthN_valueChanged(int value);
	void on_doubleSpinBoxLengthNMM_valueChanged(double arg1);
	void on_spinBoxLengthN_valueChanged(int arg1);

    void on_verticalSliderY_valueChanged(int value);
    void on_spinBoxK_valueChanged(int arg1);
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();
	void on_PushButtonMarker_clicked();
    void on_PushButtonShowWhole_clicked();
    void on_toolButtonRegOK_clicked();
    void on_toolButtonRegNG_clicked();
    void on_toolButtonDrawColor_clicked();
    void on_toolButtonPickColor_clicked();
	void on_toolButtonOKSize_clicked();
	void	SlotClickRGB(int R ,int G ,int B);
	void	SlotMouseLDown(int,int);
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
    Ui::EachThresholdFormFaint *ui;

	virtual	void	MouseLDoubleClick(int gx,int gy ,int LevelID) override;
	void	ShowDataAfterMarker(void);
};

#endif // EACHTHRESHOLDFORM_H
