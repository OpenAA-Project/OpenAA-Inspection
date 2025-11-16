#ifndef ZOOMMECHANICALPANELFORM_H
#define ZOOMMECHANICALPANELFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ZoomMechanicalPanelForm;
}

class SignalOperandFloat;

class ZoomMechanicalPanelForm : public GUIFormBase
{
    Q_OBJECT

	SignalOperandFloat	*oValueZ;
	GUIFormBase			*VRSOpe;

public:
	double	MinZoomRate;
	double	MaxZoomRate;
	int32	SysValueZoom;

    explicit ZoomMechanicalPanelForm(LayersBase *base ,QWidget *parent = 0);
    ~ZoomMechanicalPanelForm();

	virtual void	Prepare(void)	override;

private slots:
    void on_verticalSlider_valueChanged(int value);
    void on_pushButtonSetValue_clicked();

private:
    Ui::ZoomMechanicalPanelForm *ui;
};

#endif // ZOOMMECHANICALPANELFORM_H
