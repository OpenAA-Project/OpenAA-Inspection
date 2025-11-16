#ifndef SHOWSETTINGVCUTFORM_H
#define SHOWSETTINGVCUTFORM_H

#include <QWidget>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class ShowSettingVCutForm;
}

class ShowSettingVCutForm;

class	DisplaySimPanelVCutInspection	: public DisplaySimPanel
{
	ShowSettingVCutForm	*ParentWidget;
public:
	DisplaySimPanelVCutInspection(LayersBase *base ,ShowSettingVCutForm *parentw ,QWidget *parent = 0);

	virtual	void	DrawOther(QPainter &Pnt);
};

class ShowSettingVCutForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT

public:
    explicit ShowSettingVCutForm(LayersBase *Base,QWidget *parent = 0);
    ~ShowSettingVCutForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
	void	GetDataFromWindow(void);

	AlgorithmItemIndependentPack	*IData;
	HistgramTypeListInAlgoContainer	HContainer;
	bool	ModeShowItem;

private slots:
    void on_pushButtonSetOne_clicked();
    void on_pushButtonSetAll_clicked();
    void on_pushButtonClose_clicked();
    void on_toolButtonSimShowItem_clicked();
    void on_toolButtonSimShowNGMark_clicked();
    void on_pushButtonSimShowCenterPos_clicked();
    void on_EditThresholdLevel_valueChanged(int arg1);
    void on_EditThresholdShift_valueChanged(int arg1);
    void on_EditThresholdLength_valueChanged(int arg1);
    void on_EditExpandGenMask_valueChanged(int arg1);
    void on_checkBoxGenDynamicMask_clicked();

    void on_EditThresholdLevel_valueChanged(double arg1);

private:
    Ui::ShowSettingVCutForm *ui;

	DisplaySimPanelVCutInspection		SimPanel;
	void Calc(void);
};

#endif // SHOWSETTINGVCUTFORM_H
