#ifndef LEARNINGSETTINGDIALOG_H
#define LEARNINGSETTINGDIALOG_H

#include <QDialog>
#include "ui_LearningSettingDialog.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WEditParameterTab.h"
#include "XServiceForLayers.h"

class LearningSettingDialog : public QDialog,public ServiceForLayers
{
	Q_OBJECT

public:
	LearningSettingDialog(LayersBase *Base,ParamBase *base,QWidget *parent = 0);
	~LearningSettingDialog();

private:
	Ui::LearningSettingDialogClass ui;

	WEditParameterTab	*WTabGeneral;
	ParamBase *Base;

private slots:
	void on_ButtonCancel_clicked();
	void on_ButtonOK_clicked();
};

#endif // LEARNINGSETTINGDIALOG_H
