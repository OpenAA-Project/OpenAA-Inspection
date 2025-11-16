#ifndef EACHTHRESHOLDFORMMULTISPOT_H
#define EACHTHRESHOLDFORMMULTISPOT_H

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
class EachThresholdFormMultiSpot;
}

class ButtonSettingThresholdForm;


class EachThresholdFormMultiSpot:public EachThresholdCommon
                                ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	bool	OnChanging;
public:
    explicit EachThresholdFormMultiSpot(LayersBase *base ,ButtonSettingThresholdForm *p
										,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
										,QWidget *parent = 0);
    ~EachThresholdFormMultiSpot();

private slots:
    void on_horizontalSliderSIze_valueChanged(int value);
    void on_doubleSpinBoxSizeMM_valueChanged(double arg1);
    void on_spinBoxSize_valueChanged(int arg1);
    void on_horizontalSliderNGCount_valueChanged(int value);
    void on_spinBoxNGCount_valueChanged(int arg1);
    void on_PushButtonMarker_clicked();
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();

    void on_PushButtonShowWhole_clicked();

private:
    Ui::EachThresholdFormMultiSpot *ui;

	virtual	void	MouseLDoubleClick(int gx,int gy,int LevelID) override;
	void	ShowDataAfterMarker(void);
};

#endif // EACHTHRESHOLDFORMMULTISPOT_H
