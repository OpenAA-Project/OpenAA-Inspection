#ifndef CONTROLPRECISIONCHECKERFORM_H
#define CONTROLPRECISIONCHECKERFORM_H

#include "XGUIFormBase.h"
#include "ui_ControlPrecisionCheckerForm.h"
#include "PrecisionCheckerLib.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ControlPrecisionCheckerForm : public GUIFormBase,public PrecisionCheckerLib
{
	Q_OBJECT

public:
	ControlPrecisionCheckerForm(LayersBase *Base ,QWidget *parent = 0);
	~ControlPrecisionCheckerForm();

private:
	Ui::ControlPrecisionCheckerFormClass ui;

private slots:
	void on_comboBoxPage_currentIndexChanged(int index);
	void on_pushButtonAngle_clicked();
	void on_pushButtonResolution_clicked();
	void on_pushButtonBrightness_clicked();
	void on_pushButtonFocus_clicked();
	void on_pushButtonGrp_clicked();
	void on_pushButtonSetParam_clicked();
};

#endif // CONTROLPRECISIONCHECKERFORM_H
