#ifndef EACHTHRESHOLDFORMRED_H
#define EACHTHRESHOLDFORMRED_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XParamCustomized.h"
#include "XPanelShowResultImage.h"
#include "XEachThresholdCommon.h"
#include "XPasswordQWidget.h"

namespace Ui {
class EachThresholdFormRed;
}
class ButtonSettingThresholdForm;
class EachThresholdFormRed;


class RedPanelWidget : public QWidget
{
	EachThresholdFormRed	*Parent;
	QImage	RedImage;
	WORD	RedHighRate			;
	BYTE	RedMinBrightness	;
	BYTE	RedGBMerginRate		;
	BYTE	RedGBMerginOffset	;
public:
	RedPanelWidget(EachThresholdFormRed *p,QWidget *parent);
	~RedPanelWidget(void);

	void	ShowRed( WORD	_RedHighRate
					,BYTE	_RedMinBrightness
					,BYTE	_RedGBMerginRate
					,BYTE	_RedGBMerginOffset);
	void	Resize(int W,int H);

private:
	virtual	void mouseMoveEvent(QMouseEvent *event)	override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
	virtual	void paintEvent(QPaintEvent *event)		override;
	void	ShowRed(void);
};

class EachThresholdFormRed : public EachThresholdCommon
							,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	bool	OnChanging;
public:
    explicit EachThresholdFormRed(LayersBase *base ,ButtonSettingThresholdForm *p
								,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
								,QWidget *parent = 0);
    ~EachThresholdFormRed();

	void	ShowRedInMouse(int X,int Y,QRgb d);
private slots:
    void on_PushButtonMarker_clicked();
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();
    void on_PushButtonShowWhole_clicked();
    void on_toolButtonOKSize_clicked();

    void on_horizontalSliderRedMinBrightness_valueChanged(int value);
    void on_horizontalSliderRedHighRate_valueChanged(int value);
    void on_spinBoxRedMinBrightness_valueChanged(int arg1);
    void on_spinBoxRedHighRate_valueChanged(int arg1);
    void on_horizontalSliderRedGBMerginOffset_valueChanged(int value);
    void on_horizontalSliderRedGBMerginRate_valueChanged(int value);
    void on_spinBoxRedGBMerginOffset_valueChanged(int arg1);
    void on_spinBoxRedGBMerginRate_valueChanged(int arg1);
    void on_horizontalSliderRedOKDot_valueChanged(int value);
    void on_spinBoxRedOKDot_valueChanged(int arg1);
    void on_doubleSpinBoxRedOKDotMM_valueChanged(double arg1);

private:
    Ui::EachThresholdFormRed *ui;

	RedPanelWidget	RedPanel;

	virtual	void	MouseLDoubleClick(int gx,int gy,int LevelID) override;
	void	ShowDataAfterMarker(void);

	void	ShowRed(void);
};

#endif // EACHTHRESHOLDFORMRED_H
