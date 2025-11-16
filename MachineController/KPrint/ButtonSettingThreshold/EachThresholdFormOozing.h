#ifndef EACHTHRESHOLDFORMOOZING_H
#define EACHTHRESHOLDFORMOOZING_H

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
class EachThresholdFormOozing;
}
class ButtonSettingThresholdForm;


class EachThresholdFormOozing :  public EachThresholdCommon
                                ,public PasswordInQWodget
{
    Q_OBJECT
    ButtonSettingThresholdForm	*Parent;
	bool	OnChanging;
public:
    explicit EachThresholdFormOozing(LayersBase *base ,ButtonSettingThresholdForm *p
									,EachThresholdCommon::__AreaType areatype ,EachThresholdCommon::__InspectionType inspectiontype
									,QWidget *parent = 0);
    ~EachThresholdFormOozing();

private slots:
    void on_horizontalSliderOozing_valueChanged(int value);
    void on_doubleSpinBoxOozingMM_valueChanged(double arg1);
    void on_spinBoxOozing_valueChanged(int arg1);
    void on_PushButtonMarker_clicked();
    void on_toolButtonOK_clicked();
    void on_toolButtonCancel_clicked();

    void on_PushButtonShowWhole_clicked();

private:
    Ui::EachThresholdFormOozing *ui;

	virtual	void	MouseLDoubleClick(int gx,int gy ,int LevelID) override;
	void	ShowDataAfterMarker(void);
};

#endif // EACHTHRESHOLDFORMOOZING_H
